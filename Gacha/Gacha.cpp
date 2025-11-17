#include <iostream>
#include <conio.h>
#include "artifact.h"
#include "gacha.h"

int main() {
    std::cout << "SIMULATOR" << std::endl;
    std::cout << std::endl;
    GachaAlgorithm gachaSystem;
    static constexpr int ESC_KEY = 27;

    std::cout << "(1) to Wish once\n(2) to Wish 10 times\n(3) to view inventory\n(4) to view statistics" << std::endl;

    while (true) {

        std::cout << std::endl;
        std::cout << "Total pulls: " << gachaSystem.getPulls() << " (" << gachaSystem.getPulls() * 160 << " Primogems)" << std::endl;
        gachaSystem.getCurrency();

        std::cout << "____________________" << std::endl;

        int type = _getch();
        std::cout << std::endl;

        if (type == '1') {
            gachaSystem.singleWish();
            std::cout << std::endl;
        }
        else if (type == '2') {
            gachaSystem.multiWish(10);
            std::cout << std::endl;
        }
        else if (type == '3') {
            gachaSystem.getInventory();
        }
        else if (type == '4') {
            std::cout << "Constellations: " << std::endl;
            gachaSystem.constellationList();

            std::cout << std::endl;

            std::cout << "Statistics: " << std::endl;
            gachaSystem.getStatistic();
            std::cout << std::endl;
        }
        else if (type == ESC_KEY) { return 0; } // выход на esc
        // debug
        else {
            if (type == '0') {
                int doubleCheck = _getch();
                if (doubleCheck == '0') {
                    std::cout << "// debug //" << std::endl;
                    std::cout << std::endl;
                    DebugSys init;
                    init.start();
                }
            }
        }
    }
    return 0;
}