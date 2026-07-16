// forgotoriginalsub { studiorender.dll + 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 81 EC ? ? ? ? 33 ED  }

struct ModelLODInfo_t {
    int m_nMinLOD;
    int m_nMaxLOD;
    void* m_pStudioHdr;
};

struct CDrawModelInfo {
    void* pStudioHdr;
    ModelLODInfo_t* pLODInfo;

    uint8_t pad[0x1A];

    uint8_t m_nLOD;

    uint8_t pad2[5];
};


struct DrawModelResults_t {
    void* pUnused;

    uint8_t pad[0x14];

    int m_nLOD;
    int m_nUnused;

    uint64_t m_RenderTime;
};

void __fastcall CStudioRender::DrawModel(CStudioRender* pStudioRender, DrawModelResults_t* pResults, CDrawModelInfo* pInfo, matrix3x4_t* pBoneToWorld, Vector* pOrigin, uint32_t drawFlags) {
    if (pResults){
        pResults->pUnused = nullptr;
    }

    if (!pInfo->pStudioHdr)
        return;

    ModelLODInfo_t* pLODInfo = pInfo->pLODInfo;
    if (!pLODInfo)
        return;

    if (!pLODInfo->m_nMaxLOD || !pLODInfo->m_pStudioHdr)
        return;

    IStudioRenderContext* pRenderContext = (IStudioRenderContext*) (*(void* (__fastcall**)())(*(uintptr_t*)qword_1801FFBD8 + 952))();

    int lod = pInfo->m_nLOD;

    if (lod < pLODInfo->m_nMinLOD) {
        lod = pLODInfo->m_nMinLOD;
    }
    else if (lod >= pLODInfo->m_nMaxLOD) {
        lod = pLODInfo->m_nMaxLOD - 1;
    }


    pInfo->m_nLOD = lod;

    if (pResults) {
        pResults->m_nLOD = lod;
        pResults->m_nUnused = 0;

        pResults->m_RenderTime = __rdtsc();
    }

    bool bThreadedRendering = (*(int*)(qword_1801FF938 + 92) != 0) && qword_1801FF748();

    if (bThreadedRendering) {
        SetupStudioRender(pStudioRender, pRenderContext, pInfo, drawFlags); // sub_1800174A0

        StudioRenderState_t state;

        memcpy(&state, (uintptr_t)pStudioRender + 8, sizeof(state));

        StudioRenderCommand_t command;

        command.modelInfo = *(__m128*)pInfo;
        command.lodInfo   = *((__m128*)pInfo + 1);
        command.extraInfo = *((__m128*)pInfo + 2);
        command.renderState = state;
        command.renderContext = *((uintptr_t*)pStudioRender + 13);

        QueueStudioRenderCommand(DrawModelInternal, off_18007A148, &command, pBoneToWorld, drawFlags); // sub_180013D10
    }
    else {
        DrawModelInternal(off_18007A148, pInfo, (uintptr_t)pStudioRender + 8, pBoneToWorld, drawFlags); // sub_180012380
    }

    if (pResults) {
        uint64_t end = __rdtsc();

        pResults->m_RenderTime = end - pResults->m_RenderTime;



        // STUDIORENDER_DRAW_NO_SHADOWS?
        if (drawFlags & 0x40) {
            pStudioRender->OnDrawModelFinished(pResults, pInfo);
        }
    }

    if (pRenderContext) {
        pRenderContext->Release();
    }
}
