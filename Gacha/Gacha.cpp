#include <iostream>
#include <conio.h>
#include "artifact.h"
#include "gacha.h"

static constexpr int ESC_KEY = 27;

int main() {
    while (true) {
        std::cout << "My Console" << std::endl;
        std::cout << std::endl;

        std::cout << "(1) Banners\n(2) Artifacts" << std::endl;
        int choose = _getch();
        std::cout << std::endl;

        if (choose == '1') { startGacha_Banner(); }
        else if (choose == '2') { startGacha_Artifact(); }
        else if (choose == ESC_KEY) { break; }
    }

    return 0;
}