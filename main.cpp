#include <windows.h>
#include <iostream>
#include <math.h>

#include "src/offsets.h"

#include "sdk/clientEntitylist.h"
#include "sdk/LocalPlayer.h"
#include "sdk/entity.h"

#include "sdk/const.h"

float M_PI = 3.14159265358979323846;

BOOL WINAPI HackThread(HMODULE hModule)
{
    AllocConsole();
    FILE* file;
    freopen_s(&file, "CONOUT$", "w", stdout);

    uintptr_t client = (uintptr_t)GetModuleHandleA("client.dll");
    uintptr_t engine = (uintptr_t)GetModuleHandleA("engine.dll");


    std::cout << "Injected" << std::endl;
    while (!GetAsyncKeyState(VK_END)) {
        CEntity* entity = entityList->GetClientEntity(LocalPlayer::GetClosestEnemy());
        CEntity* localPlayer = entityList->GetClientEntity(1);
        
        if (entity != nullptr && localPlayer != entity && *reinterpret_cast<int*>(entity + m_iTeamNum) != *reinterpret_cast<int*>(localPlayer + m_iTeamNum)) {
            float maxDist = 99999.f;

            Vector3 epos = entity->GetBonePos(8);
            Vector3 pos = localPlayer->GetBonePos(8);
            
            Vector3 deltaVec = { epos.x - pos.x, epos.y - pos.y, epos.z - pos.z }; 
            float magn = deltaVec.x * deltaVec.x + deltaVec.y * deltaVec.y + deltaVec.z * deltaVec.z;

            float headDeltaLength = sqrt(deltaVec.x * deltaVec.x + deltaVec.y * deltaVec.y);

            float yaw = atan(- deltaVec.z / headDeltaLength)* (180 / M_PI);
            float pitch = atan2(deltaVec.y, deltaVec.x) * (180 / M_PI);

            if (deltaVec.x <= 0)
                deltaVec.x += 180;
            
            *reinterpret_cast<float*>(*(uintptr_t*)(engine + dwClientState) + dwClientState_ViewAngles) = yaw;
            *reinterpret_cast<float*>(*(uintptr_t*)(engine + dwClientState) + dwClientState_ViewAngles + 0x4) = pitch;
        }
    }

    if(file)
        fclose(file);
    
    FreeLibraryAndExitThread(hModule, 0);
    return false;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        const auto thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, 0);
        DisableThreadLibraryCalls(hModule);
        if (thread) CloseHandle(thread);
    }
    return TRUE;
}