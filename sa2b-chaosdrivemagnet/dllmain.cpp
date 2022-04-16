#include "pch.h"
#include <SA2ModLoader.h>
#include <IniFile.hpp>
#include <Trampoline.h>

#define TRAMPOLINE(name) ((decltype(name##_r)*)name##_t->Target())
#define PLAYERS_MAX 2

static float magnet_radius = 100.0f;
static float magnet_force = 1.75f;
static float magnet_maxspd = 5.0f;

static bool MagneticShieldCdt = false;
static bool DisableYellow     = false;
static bool DisableGreen      = false;
static bool DisableRed        = false;
static bool DisablePurple     = false;

static Trampoline* ChaosDrive_Main_t = nullptr;

static float CalcDistanceV(NJS_VECTOR* p1, NJS_VECTOR* p2)
{
    float x = p2->x - p1->x;
    float y = p2->y - p1->y;
    float z = p2->z - p1->z;
    auto len = x * x + y * y + z * z;

    if (len <= 0.0f)
    {
        return 0.0f;
    }
    else
    {
        return sqrtf(len);
    }
}

static void ChaosDrive_GetClosestPlayer(NJS_VECTOR* position, int& playerid, float& distance)
{
    distance = magnet_radius;
    playerid = -1;

    for (int i = 0; i < PLAYERS_MAX; ++i)
    {
        auto ptwp = MainCharObj1[i];
        auto ppwk = MainCharObj2[i];

        if (!ptwp || !ppwk)
        {
            continue;
        }

        if (MagneticShieldCdt == true && !(ppwk->Powerups & Powerups_MagneticBarrier))
        {
            continue;
        }

        auto pldist = CalcDistanceV(position, &ptwp->Position);

        if (pldist < distance)
        {
            distance = pldist;
            playerid = i;
        }
    }
}

static bool ChaosDrive_MagnetCheckColor(int color)
{
    switch (color)
    {
    case 0: // Yellow
        return DisableYellow == false;
    case 1: // Green
        return DisableGreen == false;
    case 2: // Red
        return DisableRed == false;
    case 3: // Purple
        return DisablePurple == false;
    }

    return true;
}

static void ChaosDrive_MagnetMovement(NJS_VECTOR* p1, NJS_VECTOR* p2, NJS_VECTOR& out, float speed)
{
    NJS_VECTOR normal;

    normal.x = p1->x - p2->x;
    normal.y = p1->y - p2->y;
    normal.z = p1->z - p2->z;

    if (njUnitVector(&normal) == 0.0f)
    {
        out = *p2;
    }
    else
    {
        normal.x *= speed;
        normal.y *= speed;
        normal.z *= speed;
        out.x = normal.x + p2->x;
        out.y = normal.y + p2->y;
        out.z = normal.z + p2->z;
    }
}

static void ChaosDrive_Magnet(EntityData1* data)
{
    if (ChaosDrive_MagnetCheckColor(data->Index) == true)
    {
        float dist;
        int pID;
        
        ChaosDrive_GetClosestPlayer(&data->Position, pID, dist);

        if (pID != -1)
        {
            auto ptwp = MainCharObj1[pID];
            auto ppwk = MainCharObj2[pID];

            if (!ptwp || !ppwk)
            {
                return;
            }

            auto speed = max(0.85f, min(magnet_maxspd, dist * magnet_force / magnet_radius));

            speed *= (njScalor(&ppwk->Speed) * 0.5f + 1.0f);

            ChaosDrive_MagnetMovement(&ptwp->Collision->CollisionArray->center, &data->Position, data->Position, speed);
        }
    }
}

static void __cdecl ChaosDrive_Main_r(ObjectMaster* obj)
{
    auto data = obj->Data1.Entity;

    if (obj->MainSub != DeleteObject_ && data->Action == 0)
    {
        ChaosDrive_Magnet(data);
    }

    TRAMPOLINE(ChaosDrive_Main)(obj);
}

extern "C"
{
    __declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
    {
        ChaosDrive_Main_t = new Trampoline(0x48EEF0, 0x48EEF5, ChaosDrive_Main_r);

        const auto config = new IniFile(std::string(path) + "\\config.ini");

        MagneticShieldCdt = config->getBool("", "MagneticShieldCdt", MagneticShieldCdt);
        DisableYellow = config->getBool("", "DisableYellow", DisableYellow);
        DisableGreen = config->getBool("", "DisableGreen", DisableGreen);
        DisableRed = config->getBool("", "DisableRed", DisableRed);
        DisablePurple = config->getBool("", "DisablePurple", DisablePurple);

        auto physicsgrp = config->getGroup("Physics");

        if (physicsgrp)
        {
            magnet_radius = physicsgrp->getFloat("Radius", magnet_radius);
            magnet_force = physicsgrp->getFloat("Force", magnet_force);
            magnet_maxspd = physicsgrp->getFloat("MaxSpeed", magnet_maxspd);
        }

        delete config;
    }

    __declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

