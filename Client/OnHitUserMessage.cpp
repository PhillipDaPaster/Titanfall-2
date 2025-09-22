// sub_180340D20  ( client.dll + 4C 8B DC 57 48 83 EC 60 )

// 0x3A is Entity Hit
char __fastcall OnHitUserMessage(void* pData, int message_flag, __int128* pMessageBuffer) 
{
    if (message_flag < 0 || message_flag >= *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(pData) + 36))
        return 0;

    __int64 entry = *reinterpret_cast<__int64*>((32LL * message_flag) + *reinterpret_cast<__int64*>(reinterpret_cast<uintptr_t>(pData) + 8) + 24);

    if (!entry)
        return 0;

    int numCallbacks = *reinterpret_cast<int*>(entry + 40);
    for (int i = 0; i < numCallbacks; ++i)
    {
        __int128 args[4];
        args[0] = pMessageBuffer[0];
        args[1] = pMessageBuffer[1];
        args[2] = pMessageBuffer[2];
        args[3] = pMessageBuffer[3];

        __int64 fnTable = *reinterpret_cast<__int64*>(entry + 16);
        auto callback = reinterpret_cast<void(__fastcall*)(__int128*)>(fnTable + (8LL * i));

        callback(args);
    }

    return 1;
}
