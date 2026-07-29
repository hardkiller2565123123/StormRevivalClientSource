#include "StdInc.h"
#include "ResourceReverseMap.h"
#include "Logger.h"

namespace ResourceReverseMap
{
    void LogKnownResourceFunctions()
    {
        Logger::Info("=== Resource / Loader Reverse Map ===");
        Logger::Info("sub_14126CE30 ResourceManager_GetOrLoad");
        Logger::Info("sub_14126CEC0 ResourceManager_CreateResource");
        Logger::Info("sub_14126D580 ResourceManager_FindByNormalizedPath");
        Logger::Info("sub_14126D100 ResourceManager_AllocateAndRegisterHandle");
        Logger::Info("sub_14126C2B0 ResourcePath_BuildFullPath");
        Logger::Info("sub_14125EDA0 ResourcePath_NormalizeForLookup");
        Logger::Info("sub_1412B19C0 ResourcePath_Split");
        Logger::Info("sub_1412B1720 ResourcePath_SetPart");
        Logger::Info("sub_1412B1610 ResourcePath_ResetParts");
        Logger::Info("sub_1412D0340 nuccXfbinDoc_Ctor");
        Logger::Info("sub_1412D08F0 XfbinDoc_SetPath");
        Logger::Info("sub_1412D4950 XfbinDoc_GetState");
        Logger::Info("sub_1412EC090 LoaderQueue_PushBack");
        Logger::Info("sub_1412EC1C0 LoaderQueue_PushFront");
        Logger::Info("sub_1412EC4F0 LoaderQueue_GrowRingBuffer");
        Logger::Info("sub_1412EC9D0 LoaderQueue_ResizeLogicalCount");
        Logger::Info("sub_1412EB820 LoaderQueue_Ctor184");
        Logger::Info("sub_1412EBE20 LoaderQueue_CreateWorkerChannels");
        Logger::Info("sub_14135CCD0 nuccChannel_Ctor560");
        Logger::Info("sub_14127ADE0 nuccChannel_StartThread");
        Logger::Info("sub_1411E4BC0 nuccThread_Create");
        Logger::Info("sub_1413A9DB0 WinThread_CreateSuspendedAndResume");
        Logger::Info("sub_1413A9EC0 WinThread_CrtEntryThunk");
        Logger::Info("sub_1411E4020 nuccThread_Trampoline");
        Logger::Info("sub_140BEEE70 ScaleformManager_QueueMovieLoad");
        Logger::Info("sub_140BEE4C0 ScaleformManager_CleanupFinishedPendingRequests");
        Logger::Info("sub_140BF2440 ScaleformMovieRequest_Ctor80");
        Logger::Info("sub_140BF0250 ScaleformPendingRequestTree_EraseNode");
        Logger::Info("sub_1412EC6B0 PointerVector_ReserveAndCopy");
        Logger::Info("sub_1412EC460 PointerVector_SwapStorage");
        Logger::Info("sub_1412EB630 PointerVector_InsertReallocate");
        Logger::Info("sub_14126C930 XfbinDocManager_CreateLoaderQueues");
        Logger::Info("sub_14126B210 XfbinDocManager_Dtor");
        Logger::Info("sub_14126BC10 XfbinDocManager_StopLoaderQueues");
        Logger::Info("sub_14126AF80 LoaderQueueVector_Dtor");
        Logger::Info("sub_14126AAA0 ResourcePathTree_DestroyRecursive");
        Logger::Info("sub_14135CD30 nuccChannel_Dtor");
        Logger::Info("sub_14127AD20 nuccChannelBase_Dtor");
        Logger::Info("sub_1411E4D20 nuccThread_StopOrJoin");
        Logger::Info("sub_1413A9F10 WinThread_JoinClose");
        Logger::Info("sub_1413A9C40 WinThread_Dtor");
        Logger::Info("sub_140BF1610 ScaleformPendingRequestTree_RotateLeft");
        Logger::Info("sub_140BF1790 ScaleformPendingRequestTree_RotateRight");
    }
}
