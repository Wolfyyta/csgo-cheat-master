#include <Windows.h>
#include <vector>
#include <array>

#include "utils.h"
#include "../core/interfaces.h"

std::uint8_t* utils::PatternScan(const char* moduleName, const char* pattern) noexcept
{
    static auto patternToByte = [](const char* pattern) noexcept -> const std::vector<std::int32_t>
    {
        std::vector<std::int32_t> bytes = std::vector<std::int32_t>{ };
        char* start = const_cast<char*>(pattern);
        const char* end = const_cast<char*>(pattern) + std::strlen(pattern);

        for (auto current = start; current < end; ++current)
        {
            if (*current == '?')
            {
                ++current;

                if (*current == '?')
                    ++current;

                bytes.push_back(-1);
            }
            else
                bytes.push_back(std::strtoul(current, &current, 16));
        }

        return bytes;
    };

    const HINSTANCE handle = GetModuleHandle(moduleName);

    if (!handle)
        return nullptr;

    const PIMAGE_DOS_HEADER dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(handle);
    const PIMAGE_NT_HEADERS ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(handle) + dosHeader->e_lfanew);

    const std::uintptr_t size = ntHeaders->OptionalHeader.SizeOfImage;
    const std::vector<std::int32_t> bytes = patternToByte(pattern);
    std::uint8_t* scanBytes = reinterpret_cast<std::uint8_t*>(handle);

    const std::size_t s = bytes.size();
    const std::int32_t* d = bytes.data();

    for (std::size_t i = 0ul; i < size - s; ++i)
    {
        bool found = true;

        for (std::size_t j = 0ul; j < s; ++j)
        {
            if (scanBytes[i + j] != d[j] && d[j] != -1)
            {
                found = false;
                break;
            }
        }

        if (found)
            return &scanBytes[i];
    }

    return nullptr;
}

bool utils::WorldToScreen(const CVector& world, CVector& screen)
{
    static auto& viewmatrix = *(VMatrix*)(*(uint8_t**)(PatternScan("client", "0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9") + 3) + 176);

    auto mul_row = [world](size_t index) {
        return  viewmatrix[index][0] * world.x +
            viewmatrix[index][1] * world.y +
            viewmatrix[index][2] * world.z +
            viewmatrix[index][3];
    };

    auto w = mul_row(3);

    if (w < 0.01f)
        return false;

    int x, y;
    interfaces::engine->GetScreenSize(x, y);

    screen.x = (x / 2.0f) * (1.0f + mul_row(0) / w);
    screen.y = (y / 2.0f) * (1.0f - mul_row(1) / w);

    return true;
}

bool utils::GetBBox(CEntity* ent, CVector& min, CVector& max)
{
    CVector VecMins = CVector(-16, -16, 0);
    CVector VecMaxs = CVector(16, 16, 72);
    CVector Origin = ent->GetAbsOrigin();
    CVector Center;
    Origin.VectorCopy(Origin, Center);
    Center += CVector((VecMins.x + VecMaxs.x) * 0.5, (VecMins.y + VecMaxs.y) * 0.5, (VecMins.z + VecMaxs.z) * 0.5);

    float stand = ent->GetPoseParams().at(1);
    float body_pitch = ent->GetPoseParams().at(12);
    float top_offset = stand * 18 + 58 - body_pitch * 6;
    float base_offset = VecMaxs.z * -0.6f;

    CVector Top, Base;
    Center.VectorCopy(Center, Top);
    Center.VectorCopy(Center, Base);

    Top.z = Origin.z + top_offset;
    Base.z += base_offset;

    CVector ScrTop, ScrBase;
    bool v1, v2;
    v1 = utils::WorldToScreen(Top, ScrTop);
    v2 = utils::WorldToScreen(Base, ScrBase);

    if (!v1 || !v2)
        return false;

    int y2 = ScrTop.y + abs(ScrTop.y - ScrBase.y);
    int height = y2 - ScrTop.y;
    int current_width = ScrBase.x - ScrTop.x;
    int center_x = ScrTop.x + current_width / 2;

    int width = height / 2;
    int x1 = center_x - width / 2;
    int x2 = center_x + width / 2;

    min.x = x1; min.y = ScrTop.y;
    max.x = x2; max.y = y2;

    return true;
}