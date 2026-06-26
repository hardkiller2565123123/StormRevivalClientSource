#pragma once
#include <string>
namespace StormRevival::OnlineMenu::Models {
struct LobbyRoomLayout {
    static constexpr int CurrentPlayers=0x28, MaxPlayers=0x2C, PlayerBase=0xE8, PlayerStride=0x48;
    static constexpr int CurrentRoom=0x478, SessionHandle=0x488;
};
struct LobbyPlayerLayout { static constexpr int HostFlag=0x24, VoiceState=0x28, PingValue=0x2C, PlayerId=0x40; };
struct LobbyPlayerSnapshot { int slot=-1; int playerId=-1; bool host=false; bool voice=false; int pingBars=0; std::string personaName; };
inline int PlayerOffset(int index){ return LobbyRoomLayout::PlayerBase + (index * LobbyRoomLayout::PlayerStride); }
}
