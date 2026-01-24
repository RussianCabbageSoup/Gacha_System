#include <iostream>
#include <conio.h>
#include "artifact_sys.h"
#include "banner_sys.h"

int main() {
    while (true) {
        std::cout << "My Console" << std::endl;
        std::cout << std::endl;

        std::cout << "(1) Banners\n(2) Artifacts" << std::endl;
        int choose = _getch();
        std::cout << std::endl;

        if (choose == '1') { start_banner(); }
        else if (choose == '2') { start_artifact(); }
        else if (choose == ESC_KEY) { break; }
    }

    return 0;
}