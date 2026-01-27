#include <iostream>
#include <conio.h>
#include "artifact_sys.h"
#include "banner_sys.h"

int main() {
    while (true) {
        std::cout << "My Console" << std::endl;
        std::cout << std::endl;

        std::cout << "(1) Banners\n(2) Artifacts" << std::endl;

        bool correctKey = true;

        while (correctKey) {
            int choose = _getch();

            switch (choose) {
            case('1'): start_banner(); correctKey = false; break;
            case('2'): start_artifact(); correctKey = false; break;
            case(ESC_KEY): return 0;
            }
        }
    }
    return 0;
}