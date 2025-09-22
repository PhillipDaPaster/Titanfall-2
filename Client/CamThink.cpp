#include "CamThink.h"

// sub_18024DB60 { client.dll + 40 55 53 57 48 8D AC 24 ? ? ? ? 48 81 EC 00 02 00 00 }

__int64 __fastcall CamThink(__int64 input) {
    __int64 OriginalCamState = GetCameraStatePtr(input, 0xFFFFFFFFLL);
    CameraState* cam = reinterpret_cast<CameraState*>(OriginalCamState);

    if (*(uint64_t*)(OriginalCamState + 248))
        return (*(std::int64_t(__fastcall**)(__int64))(*(_QWORD*)input + 400LL))(input);

    int type = *(int*)(OriginalCamState + 256);
    if (type == 1) {
        OriginalCamState = (*(std::int64_t(__fastcall**)(__int64))(*(_QWORD*)input + 272LL))(input);
    }
    else if (type == 2) {
        OriginalCamState = (*(std::int64_t(__fastcall**)(__int64))(*(_QWORD*)input + 280LL))(input);
    }

    if (cam->flag2) {
        if (!svCheatsConVar) {
            svCheatsConVar = (*(std::int64_t(__fastcall**)(__int64, const char*))(*(_QWORD*)qword_182E43F80 + 128LL)) 
              (qword_182E43F80, "sv_cheats");
        }

        __int64 serverVar = GetServerObject();
        bool bypass = svCheatsConVar &&
                      !*(_DWORD*)(*(_QWORD*)(svCheatsConVar + 56) + 92LL) &&
                      !*(_DWORD*)(qword_1811BC9F8 + 92) &&
                      (!serverVar || !*(_BYTE*)(serverVar + 11360));

        if (bypass) {
            return (*(std::int64_t(__fastcall**)(__int64))(*(_QWORD*)input + 280LL))(input);
        }

        if (!byte_1811BD9EC) {
        process_flags:
            if (cam->flag3) {
                int v1, v2;
                sub_180256BC0(input, &v1, &v2);
                cam->value1 = v1;
                cam->value2 = v2;

                if (!cam->flag4) {
                    int v3, v4;
                    sub_180256BF0(input, &v3, &v4);
                    cam->value1 = cam->value1;
                    cam->value2 = cam->value2;
                    (*(void(__fastcall**)(__int64))(*(_QWORD*)input + 232LL))(input);
                }
            }

            if (((float(__fastcall*)(__int64(__fastcall***)(), __int64*))off_180B1D380[14])(&off_180B1D380, &qword_1811BD990) == 0.0f)
                ((float(__fastcall*)(__int64(__fastcall***)(), __int64*))off_180B1D380[14])(&off_180B1D380, &qword_1811BD9A0);
            if (((float(__fastcall*)(__int64(__fastcall***)(), __int64*))off_180B1D380[14])(&off_180B1D380, &qword_1811BD9B0) == 0.0f)
                ((float(__fastcall*)(__int64(__fastcall***)(), __int64*))off_180B1D380[14])(&off_180B1D380, &qword_1811BD9C0);
            if (((float(__fastcall*)(__int64(__fastcall***)(), __int64*))off_180B1D380[14])(&off_180B1D380, &qword_1811BD9D0) == 0.0f)
                ((float(__fastcall*)(__int64(__fastcall***)(), __int64*))off_180B1D380[14])(&off_180B1D380, &qword_1811BD9E0);

            float curDist = cam->dist;
            float smoothFactor = *(float*)(qword_1811BD928 + 88) + 1.0f;
            if (smoothFactor < 1.0f) smoothFactor = 1.0f;

            float targetPitch, targetYaw, targetDist;

            if (*(uint32_t(__fastcall**)(__int64, __int64))(*(_QWORD*)input + 256LL)(input, 0xFFFFFFFFLL)
                && serverVar && *(_BYTE*)(serverVar + 11360)) 
            {
                targetPitch = *(float*)(serverVar + 11400);
                targetYaw = *(float*)(serverVar + 11396);
                targetDist = *(float*)(serverVar + 11404);
            } 
            else {
                targetPitch = sub_18024EB00();
                targetYaw = targetPitch;
                targetDist = curDist + ((*(float*)(qword_1811BD088 + 88) - curDist) / smoothFactor);
            }

            cam->pitch = targetPitch;
            cam->yaw = targetYaw;
            cam->dist = targetDist;

            if (*(int*)(qword_1811BD7A8 + 92)) {
                (*(void(**)(__int64, __int64, const char*, ...))(*(_QWORD*)qword_180C3D940 + 1712LL))
                    (qword_180C3D940, 4LL, "Pitch: %6.1f Yaw: %6.1f %38s", targetPitch, targetYaw, "view angles");
            }
        }
        else {
            cam->flag4 = (*(uint8_t(__fastcall**)(__int64, __int64))(*(_QWORD*)qword_182E44028 + 128LL))(qword_182E44028, 81LL)
                        || !(*(uint8_t(__fastcall**)(__int64, __int64))(*(_QWORD*)qword_182E44028 + 128LL))(qword_182E44028, 82LL);
            cam->flag2 = cam->flag4;
            cam->flag1 = cam->flag4;
        }
    }

    return OriginalCamState;
}
