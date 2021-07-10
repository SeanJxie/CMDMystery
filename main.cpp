#include "game.hpp"

int main() {
    // HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // // you can loop k higher to see more color choices
    // for(int k = 1; k < 255; k++)
    // {
    //     // pick the colorattribute k you want
    //     SetConsoleTextAttribute(hConsole, k);
    //     std::cout << k << " I want to be nice today!" << std::endl;
    // }

    CmdMysteryGame game_inst;
    game_inst.start();

    return 0;
}