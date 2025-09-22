// sub_18014EF40 { client.dll + E9 ? ? ? ? 49 8B 84 D1 ? ? ? ? }

__int64 GetServerObject()
{
    int handle = dword_180C20834;

    if (handle == -1)
        return 0; 

    if (static_cast<unsigned short>(handle) >= 0x4000u)
        return 0; 
  
    __int64* serverArrayEntry = &off_180B0F030[4 * static_cast<unsigned short>(handle)];

    if (*reinterpret_cast<uint32_t*>(serverArrayEntry + 4) != HIWORD(handle))
        return 0; 

    return serverArrayEntry[1];
}
