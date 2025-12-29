#pragma once

#include <iostream>
#include <string>
#include "Character.h"

inline std::vector<std::wstring> getPlayerFaceLines(int hp) {
    std::vector<std::wstring> lines;
    int max_hp = 30;

    if (hp >= max_hp * 0.7) {
        lines = {
        L"██████████■",
        L"██▀█████▀ ▀█",
        L"█ ▀  ██▀ ▀ ▐",
        L"▌ ▐      ▌ ▐",
        L"▌«  ════  »▐",
        L"■▀▀▀▀▀▀▀▀▀▀■"

        };
    }
    else if (hp >= max_hp * 0.4) {
        lines = {
        L" ■██████████■",
        L" ██▀█████║ ▀█",
         L"█ ▀ ▀█║  ▀ ▐",
         L"▌ @  ▀   @ ▐",
         L"▌    ()   ;▐",
         L"■▀▀▀▀▀▀▀▀▀▀■"

        };
    }
    else if (hp >= max_hp * 0.1) {
        lines = {
        L"■██████████■",
        L"██▀█████║ ▀█",
        L"█ ▄ ║█║ ▄  ▐",
       L" ▌  X     X ▐",
       L" ▌~~  ╒╕  ~~▐",
        L"■▀▀▀▀▀▀▀▀▀▀■",

        };
    }
    else {
        lines = {
        L"██████████■",
        L"██▀█████▀ ▀█",
        L"█ ▀  ██▀ ▀ ▐",
        L"▌ ▐      ▌ ▐",
        L"▌«  ════  »▐",
        L"■▀▀▀▀▀▀▀▀▀▀■"
        };
    }
    return lines;
}

inline std::vector<std::wstring> getEnemyFaceLines(int hp) {
    std::vector<std::wstring> lines;
    int max_hp = 15;

    if (hp >= max_hp * 0.7) {
        lines = {
            L" ■▀▀▀▀▀■■▀▀▀▀▀▀■ ",
            L" ▌             ▐ ",
            L" ▌   ■   ■     ▐ ",
            L" ▌   ═════     ▐ ",
            L" ▌             ▐ ",
            L" ▀▀▀▀▀▀▀▀▀▀▀▀▀▀ "
        };
    }
    else if (hp >= max_hp * 0.4) {
        lines = {
            L" ■▀▀▀▀▀■■▀▀ ",
            L" ▌         \\\\ ",
            L" ▌   ■   ■   ▐ ",
            L" ▌   ═════   ▐ ",
            L" ▌            ▐ ",
            L" ▀▀▀▀▀▀▀▀▀▀▀▀▀▀ "
        };
    }
    else if (hp >= max_hp * 0.1) {
        lines = {
            L"■▀▀▀▀▀■■▀▀ ",
            L" ▌       ▌",
            L" ▌   0    ■■■",
            L" ▌   ════_   ■■",
            L" ▌            ▐ ",
            L" ▀▀▀▀▀▀▀▀▀▀▀▀▀▀ "
        };
    }
    else {
        lines = {
            L"   ▀▀▀■■▀▀ ",
            L"    ▌  ▌",
            L" ▌■  0  ■■■",
            L" ▌    /\\  ■■",
            L" ▌■■       ▐ ",
            L"    ▀▀▀▀▀▀▀▀▀"
        };
    }
    return lines;
}