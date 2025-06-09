#include <iostream>
#include <fstream>
#include <conio.h>
#include "define.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

vec2 pos(0, 0);
c8* path = "scene.json";

void loadFromJson(const json& j, vec2& v)
{
    v.x = j["position"]["x"];
    v.y = j["position"]["y"];
}

void saveToJson(json& j, const vec2& v)
{
    j["position"]["x"] = v.x;
    j["position"]["y"] = v.y;
}

void load()
{
    std::ifstream in(path);
    if (!in)
        return;

    json j;
    in >> j;
    loadFromJson(j, pos);
}

void input()
{
    // 押したときだけ判定
    if (_kbhit())
    {
        s32 code = _getch();
        switch (code)
        {
        case 72: pos.y += 1; break; // ↑
        case 80: pos.y -= 1; break; // ↓
        case 75: pos.x -= 1; break; // ←
        case 77: pos.x += 1; break; // →
        }
    }
    std::cout << "\rx=" << pos.x << ", y=" << pos.y << " ";
    std::cout.flush();
}

void save()
{
    json j;
    saveToJson(j, pos);

    std::ofstream out(path);
    out << j.dump(4);
}

int main()
{
    while (true)
    {
        load();
        input();
        save();
    }

    return 0;
}