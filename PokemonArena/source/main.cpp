#include "../headers/Arena.h"
#include "../headers/GameException.h"

int main() {
    try {
        Arena arena;
        std::cout << arena;
        arena.startGame();
    }
    catch (const GameException& e) {
        std::cerr << "Eroare joc: " << e.what() << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Eroare standard: " << e.what() << "\n";
    }
    return 0;
}
