
// forgotoriginalsub { studiorender.dll + 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 81 EC ? ? ? ? 33 ED  }

struct ModelLODInfo
{
    int minLOD;
    int maxLOD;
    void* unk;
};

struct CDrawModelInfo
{
    void* model;
    ModelLODInfo* lodInfo;
    uint8_t pad[0x1A];
    uint8_t lod;
    uint8_t pad2[5];
};

void __fastcall DrawModel(
        struct CStudioRender *this,
        struct DrawModelResults_t *results,
        CDrawModelInfo *info,
        struct Matrix *bones,
        struct Vector *origin,
        uint32_t flags)
{
  __int64 v10; // rax
  __int64 v11; // rax
  __int64 v12; // rdx
  int v13; // ecx
  __int64 v14; // rbx
  unsigned __int8 v15; // al
  char v16; // bp
  __int128 v17; // xmm1
  __int128 v18; // xmm1
  __int128 v19; // xmm1
  __int128 v20; // xmm1
  __int128 v21; // xmm0
  unsigned __int64 v22; // rax
  __int128 v23[3]; // [rsp+30h] [rbp-B8h] BYREF
  __int128 v24[6]; // [rsp+60h] [rbp-88h] BYREF
  __int64 v25; // [rsp+C0h] [rbp-28h]

  if ( results )
    *(_QWORD *)results = 0LL;
  if ( *(_QWORD *)info )
  {
    v10 = *((_QWORD *)info + 1);
    if ( v10 )
    {
      if ( *(_DWORD *)(v10 + 4) && *(_QWORD *)(v10 + 8) )
      {
        v11 = (*(__int64 (**)(void))(*(_QWORD *)qword_1801FFBD8 + 952LL))();
        v12 = *((_QWORD *)info + 1);
        v13 = *((unsigned __int8 *)info + 42);
        v14 = v11;
        if ( v13 >= *(_DWORD *)v12 )
        {
          if ( v13 > *(_DWORD *)(v12 + 4) - 1 )
            LOBYTE(v13) = *(_BYTE *)(v12 + 4) - 1;
          v15 = v13;
        }
        else
        {
          v15 = *(_DWORD *)v12;
        }
        *((_BYTE *)info + 42) = v15;
        if ( results )
        {
          *((_DWORD *)results + 6) = 0;
          *((_DWORD *)results + 5) = v15;
          *((_QWORD *)results + 4) = __rdtsc();
        }
        if ( *(_DWORD *)(qword_1801FF938 + 92) && (unsigned int)qword_1801FF748() )
        {
          v16 = flags;
          sub_1800174A0(this, v14, info, flags);
          v17 = *(_OWORD *)((char *)this + 24);
          v24[0] = *(_OWORD *)((char *)this + 8);
          v24[1] = v17;
          v18 = *(_OWORD *)((char *)this + 56);
          v24[2] = *(_OWORD *)((char *)this + 40);
          v24[3] = v18;
          v19 = *(_OWORD *)((char *)this + 88);
          v24[4] = *(_OWORD *)((char *)this + 72);
          v24[5] = v19;
          v20 = *((_OWORD *)info + 1);
          v25 = *((_QWORD *)this + 13);
          v21 = *(_OWORD *)info;
          v23[1] = v20;
          v23[0] = v21;
          v23[2] = *((_OWORD *)info + 2);
          sub_180013D10(
            (unsigned int)sub_180012380,
            (_DWORD)off_18007A148,
            (unsigned int)v23,
            (unsigned int)v24,
            (__int64)bones,
            flags);
        }
        else
        {
          v16 = flags;
          sub_180012380((_DWORD)off_18007A148, (_DWORD)info, (_DWORD)this + 8, (_DWORD)bones, flags);
        }
        if ( results )
        {
          v22 = __rdtsc();
          *((_QWORD *)results + 4) = (((unsigned __int64)HIDWORD(v22) << 32) | (unsigned int)v22)
                                   - *((_QWORD *)results + 4);
          if ( (v16 & 0x40) != 0 )
            (*(void (__fastcall **)(struct CStudioRender *, struct DrawModelResults_t *, struct CDrawModelInfo *))(*(_QWORD *)this + 280LL))(
              this,
              results,
              info);
        }
        if ( v14 )
          (*(void (__fastcall **)(__int64))(*(_QWORD *)v14 + 8LL))(v14);
      }
    }
  }
}
