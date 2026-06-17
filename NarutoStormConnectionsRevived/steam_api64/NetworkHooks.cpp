#include "StdInc.h"
#include "NetworkHooks.h"
#include "Logger.h"

#include <cctype>
#include <cstring>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

typedef int (WSAAPI* connectFn)(
    SOCKET s,
    const sockaddr* name,
    int namelen);

typedef int (WSAAPI* WSAConnectFn)(
    SOCKET s,
    const sockaddr* name,
    int namelen,
    LPWSABUF lpCallerData,
    LPWSABUF lpCalleeData,
    LPQOS lpSQOS,
    LPQOS lpGQOS);

typedef int (WSAAPI* getaddrinfoFn)(
    PCSTR pNodeName,
    PCSTR pServiceName,
    const ADDRINFOA* pHints,
    PADDRINFOA* ppResult);

typedef INT(WSAAPI* GetAddrInfoWFn)(
    PCWSTR pNodeName,
    PCWSTR pServiceName,
    const ADDRINFOW* pHints,
    PADDRINFOW* ppResult);

typedef int (WSAAPI* sendtoFn)(
    SOCKET s,
    const char* buf,
    int len,
    int flags,
    const sockaddr* to,
    int tolen);

typedef int (WSAAPI* WSASendToFn)(
    SOCKET s,
    LPWSABUF lpBuffers,
    DWORD dwBufferCount,
    LPDWORD lpNumberOfBytesSent,
    DWORD dwFlags,
    const sockaddr* lpTo,
    int iToLen,
    LPWSAOVERLAPPED lpOverlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);

typedef int (WSAAPI* recvFn)(
    SOCKET s,
    char* buf,
    int len,
    int flags);

typedef int (WSAAPI* WSARecvFn)(
    SOCKET s,
    LPWSABUF lpBuffers,
    DWORD dwBufferCount,
    LPDWORD lpNumberOfBytesRecvd,
    LPDWORD lpFlags,
    LPWSAOVERLAPPED lpOverlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);

typedef int (WSAAPI* selectFn)(
    int nfds,
    fd_set* readfds,
    fd_set* writefds,
    fd_set* exceptfds,
    const timeval* timeout);

typedef int (WSAAPI* closesocketFn)(SOCKET s);

static connectFn g_OriginalConnect = nullptr;
static WSAConnectFn g_OriginalWSAConnect = nullptr;
static getaddrinfoFn g_OriginalGetAddrInfo = nullptr;
static GetAddrInfoWFn g_OriginalGetAddrInfoW = nullptr;
static sendtoFn g_OriginalSendTo = nullptr;
static WSASendToFn g_OriginalWSASendTo = nullptr;
static recvFn g_OriginalRecv = nullptr;
static WSARecvFn g_OriginalWSARecv = nullptr;
static selectFn g_OriginalSelect = nullptr;
static closesocketFn g_OriginalCloseSocket = nullptr;

static std::mutex g_AllowedPublicMutex;
static std::set<uint32_t> g_AllowedPublicIPv4;

static std::mutex g_FakeSocketMutex;
static std::set<SOCKET> g_FakeConnectedSockets;

static void MarkFakeSocket(SOCKET s)
{
    if (s == INVALID_SOCKET)
        return;

    std::lock_guard<std::mutex> lock(g_FakeSocketMutex);
    g_FakeConnectedSockets.insert(s);
}

static void UnmarkFakeSocket(SOCKET s)
{
    std::lock_guard<std::mutex> lock(g_FakeSocketMutex);
    g_FakeConnectedSockets.erase(s);
}

static bool IsFakeSocket(SOCKET s)
{
    std::lock_guard<std::mutex> lock(g_FakeSocketMutex);
    return g_FakeConnectedSockets.find(s) != g_FakeConnectedSockets.end();
}

static bool IsAllowedIPv4(uint32_t ip)
{
    const uint8_t a = static_cast<uint8_t>((ip >> 24) & 0xFF);
    const uint8_t b = static_cast<uint8_t>((ip >> 16) & 0xFF);
    const uint8_t d = static_cast<uint8_t>(ip & 0xFF);

    if (a == 10) return true;
    if (a == 127) return true;
    if (a == 172 && b >= 16 && b <= 31) return true;
    if (a == 192 && b == 168) return true;
    if (a == 169 && b == 254) return true;
    if (a == 255 && b == 255 && ((ip >> 8) & 0xFF) == 255 && d == 255) return true;

    // Common gaming VPN ranges: Hamachi 25/8, Radmin VPN 26/8, Tailscale/CGNAT 100.64/10.
    if (a == 25) return true;
    if (a == 26) return true;
    if (a == 100 && b >= 64 && b <= 127) return true;

    {
        std::lock_guard<std::mutex> lock(g_AllowedPublicMutex);
        if (g_AllowedPublicIPv4.find(ip) != g_AllowedPublicIPv4.end())
            return true;
    }

    return false;
}

static bool IsAllowedIPv6(const IN6_ADDR& ip)
{
    const auto* bytes = reinterpret_cast<const uint8_t*>(&ip);

    bool loopback = true;
    for (int i = 0; i < 15; ++i)
        loopback = loopback && bytes[i] == 0;

    if (loopback && bytes[15] == 1)
        return true;

    if ((bytes[0] & 0xFE) == 0xFC)
        return true;

    if (bytes[0] == 0xFE && (bytes[1] & 0xC0) == 0x80)
        return true;

    return false;
}

static bool TryParseIPv4HostOrder(const std::string& text, uint32_t& out)
{
    IN_ADDR addr{};
    if (inet_pton(AF_INET, text.c_str(), &addr) != 1)
        return false;

    out = ntohl(addr.S_un.S_addr);
    return true;
}

static bool TryParseAllowedIPv6(const std::string& text)
{
    IN6_ADDR addr{};
    return inet_pton(AF_INET6, text.c_str(), &addr) == 1 && IsAllowedIPv6(addr);
}

static bool EndsWith(const std::string& text, const char* suffix)
{
    if (!suffix)
        return false;

    const size_t suffixLength = strlen(suffix);
    return text.size() >= suffixLength &&
        text.compare(text.size() - suffixLength, suffixLength, suffix) == 0;
}


static bool IsOnlineMenuServiceHost(const std::string& lower)
{
    // NSC checks these HTTPS services before it opens the online menu.
    // Let only these auth/status endpoints connect for menu compatibility.
    return EndsWith(lower, ".playfabapi.com") ||
        lower == "titleid.playfabapi.com" ||
        EndsWith(lower, ".cosmos.channel.or.jp") ||
        lower == "neo.cosmos.channel.or.jp";
}

static bool IsAllowedHostName(const std::string& host)
{
    if (host.empty() || host == "null")
        return true;

    std::string lower = host;
    std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) {
        return static_cast<char>(std::tolower(c));
    });

    if (lower == "localhost")
        return true;

    // Single-label names are local machine/LAN names, not public DNS names.
    if (lower.find('.') == std::string::npos && lower.find(':') == std::string::npos)
        return true;

    if (EndsWith(lower, ".local") || EndsWith(lower, ".lan"))
        return true;

    if (IsOnlineMenuServiceHost(lower))
        return true;

    return false;
}

static void RememberAllowedIPv4Results(PADDRINFOA result)
{
    std::lock_guard<std::mutex> lock(g_AllowedPublicMutex);
    for (ADDRINFOA* item = result; item; item = item->ai_next)
    {
        if (item->ai_family != AF_INET || !item->ai_addr)
            continue;

        auto* address = reinterpret_cast<sockaddr_in*>(item->ai_addr);
        g_AllowedPublicIPv4.insert(ntohl(address->sin_addr.S_un.S_addr));
    }
}

static void RememberAllowedIPv4ResultsW(PADDRINFOW result)
{
    std::lock_guard<std::mutex> lock(g_AllowedPublicMutex);
    for (ADDRINFOW* item = result; item; item = item->ai_next)
    {
        if (item->ai_family != AF_INET || !item->ai_addr)
            continue;

        auto* address = reinterpret_cast<sockaddr_in*>(item->ai_addr);
        g_AllowedPublicIPv4.insert(ntohl(address->sin_addr.S_un.S_addr));
    }
}

static bool IsAllowedEndpoint(const sockaddr* addr)
{
    if (!addr)
        return true;

    if (addr->sa_family == AF_INET)
    {
        const auto* ipv4 = reinterpret_cast<const sockaddr_in*>(addr);
        const uint16_t port = ntohs(ipv4->sin_port);

        // NSC online-menu auth/status checks are HTTPS.
        // v8 still failed because the service can resolve to a new IP after DNS.
        // Allow outbound 443 so the menu handshake can finish, while LAN/VPN remains allowed.
        if (port == 443)
            return true;

        return IsAllowedIPv4(ntohl(ipv4->sin_addr.S_un.S_addr));
    }

    if (addr->sa_family == AF_INET6)
    {
        const auto* ipv6 = reinterpret_cast<const sockaddr_in6*>(addr);
        const uint16_t port = ntohs(ipv6->sin6_port);

        // Same as IPv4: allow HTTPS checks needed for entering the online menu.
        if (port == 443)
            return true;

        return IsAllowedIPv6(ipv6->sin6_addr);
    }

    return false;
}

static std::string WideToUtf8(const wchar_t* text)
{
    if (!text)
        return "null";

    int needed = WideCharToMultiByte(
        CP_UTF8,
        0,
        text,
        -1,
        nullptr,
        0,
        nullptr,
        nullptr);

    if (needed <= 0)
        return "wide-conversion-failed";

    std::string result;
    result.resize(needed - 1);

    WideCharToMultiByte(
        CP_UTF8,
        0,
        text,
        -1,
        &result[0],
        needed,
        nullptr,
        nullptr);

    return result;
}

static bool ExtractIpAndPort(
    const sockaddr* addr,
    std::string& outIp,
    uint16_t& outPort)
{
    outIp.clear();
    outPort = 0;

    if (!addr)
        return false;

    char ip[INET6_ADDRSTRLEN]{};

    if (addr->sa_family == AF_INET)
    {
        const sockaddr_in* ipv4 =
            reinterpret_cast<const sockaddr_in*>(addr);

        if (!inet_ntop(
            AF_INET,
            const_cast<IN_ADDR*>(&ipv4->sin_addr),
            ip,
            sizeof(ip)))
        {
            return false;
        }

        outIp = ip;
        outPort = ntohs(ipv4->sin_port);
        return true;
    }

    if (addr->sa_family == AF_INET6)
    {
        const sockaddr_in6* ipv6 =
            reinterpret_cast<const sockaddr_in6*>(addr);

        if (!inet_ntop(
            AF_INET6,
            const_cast<IN6_ADDR*>(&ipv6->sin6_addr),
            ip,
            sizeof(ip)))
        {
            return false;
        }

        outIp = ip;
        outPort = ntohs(ipv6->sin6_port);
        return true;
    }

    return false;
}

static std::string FormatEndpoint(
    const std::string& ip,
    uint16_t port)
{
    if (ip.empty())
        return "unknown";

    return ip + ":" + std::to_string(port);
}

static void LogNetworkDecision(
    const char* action,
    bool allowed,
    const std::string& endpoint)
{
    if (allowed)
        return;

    Logger::Info(
        std::string("OFFLINE fake public ") +
        action +
        " -> " +
        endpoint);
}

static int WSAAPI HookedConnect(
    SOCKET s,
    const sockaddr* name,
    int namelen)
{
    std::string ip;
    uint16_t port = 0;

    bool allowed = IsAllowedEndpoint(name);

    if (ExtractIpAndPort(name, ip, port))
    {
        LogNetworkDecision("connect", allowed, FormatEndpoint(ip, port));
    }
    else
    {
        LogNetworkDecision("connect", allowed, "unknown endpoint");
    }

    if (!allowed)
    {
        MarkFakeSocket(s);
        WSASetLastError(0);
        return 0;
    }

    return g_OriginalConnect
        ? g_OriginalConnect(s, name, namelen)
        : SOCKET_ERROR;
}

static int WSAAPI HookedWSAConnect(
    SOCKET s,
    const sockaddr* name,
    int namelen,
    LPWSABUF lpCallerData,
    LPWSABUF lpCalleeData,
    LPQOS lpSQOS,
    LPQOS lpGQOS)
{
    std::string ip;
    uint16_t port = 0;

    bool allowed = IsAllowedEndpoint(name);

    if (ExtractIpAndPort(name, ip, port))
    {
        LogNetworkDecision("WSAConnect", allowed, FormatEndpoint(ip, port));
    }
    else
    {
        LogNetworkDecision("WSAConnect", allowed, "unknown endpoint");
    }

    if (!allowed)
    {
        MarkFakeSocket(s);
        WSASetLastError(0);
        return 0;
    }

    return g_OriginalWSAConnect
        ? g_OriginalWSAConnect(
            s,
            name,
            namelen,
            lpCallerData,
            lpCalleeData,
            lpSQOS,
            lpGQOS)
        : SOCKET_ERROR;
}

static int WSAAPI HookedSendTo(
    SOCKET s,
    const char* buf,
    int len,
    int flags,
    const sockaddr* to,
    int tolen)
{
    std::string ip;
    uint16_t port = 0;
    bool allowed = IsAllowedEndpoint(to);

    if (ExtractIpAndPort(to, ip, port))
    {
        LogNetworkDecision("sendto", allowed, FormatEndpoint(ip, port));
    }
    else
    {
        LogNetworkDecision("sendto", allowed, "connected-or-unknown endpoint");
    }

    if (!allowed)
        return len;

    return g_OriginalSendTo
        ? g_OriginalSendTo(s, buf, len, flags, to, tolen)
        : SOCKET_ERROR;
}

static int WSAAPI HookedWSASendTo(
    SOCKET s,
    LPWSABUF lpBuffers,
    DWORD dwBufferCount,
    LPDWORD lpNumberOfBytesSent,
    DWORD dwFlags,
    const sockaddr* lpTo,
    int iToLen,
    LPWSAOVERLAPPED lpOverlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
    std::string ip;
    uint16_t port = 0;
    bool allowed = IsAllowedEndpoint(lpTo);

    if (ExtractIpAndPort(lpTo, ip, port))
    {
        LogNetworkDecision("WSASendTo", allowed, FormatEndpoint(ip, port));
    }
    else
    {
        LogNetworkDecision("WSASendTo", allowed, "connected-or-unknown endpoint");
    }

    if (!allowed)
    {
        if (lpNumberOfBytesSent)
        {
            DWORD total = 0;
            for (DWORD i = 0; i < dwBufferCount; ++i)
                total += lpBuffers[i].len;
            *lpNumberOfBytesSent = total;
        }
        return 0;
    }

    return g_OriginalWSASendTo
        ? g_OriginalWSASendTo(
            s,
            lpBuffers,
            dwBufferCount,
            lpNumberOfBytesSent,
            dwFlags,
            lpTo,
            iToLen,
            lpOverlapped,
            lpCompletionRoutine)
        : SOCKET_ERROR;
}


static int WSAAPI HookedRecv(
    SOCKET s,
    char* buf,
    int len,
    int flags)
{
    if (IsFakeSocket(s))
    {
        if (buf && len > 0)
            ZeroMemory(buf, static_cast<SIZE_T>(len));

        WSASetLastError(WSAEWOULDBLOCK);
        return SOCKET_ERROR;
    }

    return g_OriginalRecv
        ? g_OriginalRecv(s, buf, len, flags)
        : SOCKET_ERROR;
}

static int WSAAPI HookedWSARecv(
    SOCKET s,
    LPWSABUF lpBuffers,
    DWORD dwBufferCount,
    LPDWORD lpNumberOfBytesRecvd,
    LPDWORD lpFlags,
    LPWSAOVERLAPPED lpOverlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
    if (IsFakeSocket(s))
    {
        if (lpNumberOfBytesRecvd)
            *lpNumberOfBytesRecvd = 0;

        WSASetLastError(WSAEWOULDBLOCK);
        return SOCKET_ERROR;
    }

    return g_OriginalWSARecv
        ? g_OriginalWSARecv(
            s,
            lpBuffers,
            dwBufferCount,
            lpNumberOfBytesRecvd,
            lpFlags,
            lpOverlapped,
            lpCompletionRoutine)
        : SOCKET_ERROR;
}

static void RemoveFakeSocketsFromSet(fd_set* sockets)
{
    if (!sockets)
        return;

    u_int writeIndex = 0;
    for (u_int readIndex = 0; readIndex < sockets->fd_count; ++readIndex)
    {
        SOCKET s = sockets->fd_array[readIndex];
        if (!IsFakeSocket(s))
            sockets->fd_array[writeIndex++] = s;
    }
    sockets->fd_count = writeIndex;
}

static int WSAAPI HookedSelect(
    int nfds,
    fd_set* readfds,
    fd_set* writefds,
    fd_set* exceptfds,
    const timeval* timeout)
{
    RemoveFakeSocketsFromSet(readfds);
    RemoveFakeSocketsFromSet(writefds);
    RemoveFakeSocketsFromSet(exceptfds);

    if (readfds && readfds->fd_count == 0) readfds = nullptr;
    if (writefds && writefds->fd_count == 0) writefds = nullptr;
    if (exceptfds && exceptfds->fd_count == 0) exceptfds = nullptr;

    if (!readfds && !writefds && !exceptfds)
    {
        WSASetLastError(0);
        return 0;
    }

    return g_OriginalSelect
        ? g_OriginalSelect(nfds, readfds, writefds, exceptfds, timeout)
        : SOCKET_ERROR;
}

static int WSAAPI HookedCloseSocket(SOCKET s)
{
    UnmarkFakeSocket(s);
    return g_OriginalCloseSocket
        ? g_OriginalCloseSocket(s)
        : 0;
}

static int WSAAPI HookedGetAddrInfo(
    PCSTR pNodeName,
    PCSTR pServiceName,
    const ADDRINFOA* pHints,
    PADDRINFOA* ppResult)
{
    std::string host =
        pNodeName ? pNodeName : "null";

    std::string service =
        pServiceName ? pServiceName : "null";

    bool allowed = IsAllowedHostName(host);

    if (!allowed)
    {
        Logger::Info(
            "BLOCK public getaddrinfo -> host=" +
            host +
            " service=" +
            service);
    }

    // Offline compatibility: do not fail public DNS here.
    // Let DNS resolve, then fake public socket connects/sends so the game can enter the online menu without reaching official servers.

    int result = g_OriginalGetAddrInfo
        ? g_OriginalGetAddrInfo(pNodeName, pServiceName, pHints, ppResult)
        : EAI_FAIL;

    if (result == 0 && allowed && ppResult && *ppResult)
        RememberAllowedIPv4Results(*ppResult);

    return result;
}

static INT WSAAPI HookedGetAddrInfoW(
    PCWSTR pNodeName,
    PCWSTR pServiceName,
    const ADDRINFOW* pHints,
    PADDRINFOW* ppResult)
{
    std::string host =
        WideToUtf8(pNodeName);

    std::string service =
        WideToUtf8(pServiceName);

    bool allowed = IsAllowedHostName(host);

    if (!allowed)
    {
        Logger::Info(
            "BLOCK public GetAddrInfoW -> host=" +
            host +
            " service=" +
            service);
    }

    // Offline compatibility: do not fail public DNS here.
    // Let DNS resolve, then fake public socket connects/sends so the game can enter the online menu without reaching official servers.

    INT result = g_OriginalGetAddrInfoW
        ? g_OriginalGetAddrInfoW(pNodeName, pServiceName, pHints, ppResult)
        : EAI_FAIL;

    if (result == 0 && allowed && ppResult && *ppResult)
        RememberAllowedIPv4ResultsW(*ppResult);

    return result;
}

static bool HookExport(
    HMODULE module,
    const char* exportName,
    void* detour,
    void** original)
{
    void* target =
        reinterpret_cast<void*>(
            GetProcAddress(module, exportName));

    if (!target)
    {
        Logger::Error(
            std::string("Network hook missing export: ") +
            exportName);

        return false;
    }

    MH_STATUS createStatus = MH_CreateHook(
        target,
        detour,
        original);

    if (createStatus != MH_OK &&
        createStatus != MH_ERROR_ALREADY_CREATED)
    {
        Logger::Error(
            std::string("Network hook create failed: ") +
            exportName);

        return false;
    }

    MH_STATUS enableStatus =
        MH_EnableHook(target);

    if (enableStatus != MH_OK &&
        enableStatus != MH_ERROR_ENABLED)
    {
        Logger::Error(
            std::string("Network hook enable failed: ") +
            exportName);

        return false;
    }

    Logger::Info(
        std::string("Network hook enabled: ") +
        exportName);

    return true;
}

namespace NetworkHooks
{
    bool Init()
    {
        HMODULE ws2 =
            GetModuleHandleA("Ws2_32.dll");

        if (!ws2)
            ws2 = LoadLibraryA("Ws2_32.dll");

        if (!ws2)
        {
            Logger::Error(
                "Failed to load Ws2_32.dll");

            return false;
        }

        Logger::Info(
            "Initializing network hooks: LAN/VPN allowed, HTTPS menu checks allowed, other public sockets faked");

        bool ok = true;

        ok &= HookExport(
            ws2,
            "connect",
            reinterpret_cast<void*>(&HookedConnect),
            reinterpret_cast<void**>(&g_OriginalConnect));

        ok &= HookExport(
            ws2,
            "WSAConnect",
            reinterpret_cast<void*>(&HookedWSAConnect),
            reinterpret_cast<void**>(&g_OriginalWSAConnect));

        ok &= HookExport(
            ws2,
            "getaddrinfo",
            reinterpret_cast<void*>(&HookedGetAddrInfo),
            reinterpret_cast<void**>(&g_OriginalGetAddrInfo));

        ok &= HookExport(
            ws2,
            "GetAddrInfoW",
            reinterpret_cast<void*>(&HookedGetAddrInfoW),
            reinterpret_cast<void**>(&g_OriginalGetAddrInfoW));

        ok &= HookExport(
            ws2,
            "sendto",
            reinterpret_cast<void*>(&HookedSendTo),
            reinterpret_cast<void**>(&g_OriginalSendTo));

        ok &= HookExport(
            ws2,
            "WSASendTo",
            reinterpret_cast<void*>(&HookedWSASendTo),
            reinterpret_cast<void**>(&g_OriginalWSASendTo));

        ok &= HookExport(
            ws2,
            "recv",
            reinterpret_cast<void*>(&HookedRecv),
            reinterpret_cast<void**>(&g_OriginalRecv));

        ok &= HookExport(
            ws2,
            "WSARecv",
            reinterpret_cast<void*>(&HookedWSARecv),
            reinterpret_cast<void**>(&g_OriginalWSARecv));

        ok &= HookExport(
            ws2,
            "select",
            reinterpret_cast<void*>(&HookedSelect),
            reinterpret_cast<void**>(&g_OriginalSelect));

        ok &= HookExport(
            ws2,
            "closesocket",
            reinterpret_cast<void*>(&HookedCloseSocket),
            reinterpret_cast<void**>(&g_OriginalCloseSocket));

        if (!ok)
        {
            Logger::Error("Network hooks initialized with failures");
            return false;
        }

        Logger::Info("Network hooks initialized: LAN/VPN real, HTTPS menu checks real, other public connect/send/recv faked offline");

        return true;
    }

    void Shutdown()
    {
        Logger::Info("Network hooks shutdown");
    }
}

