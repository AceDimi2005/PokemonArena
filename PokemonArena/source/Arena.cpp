#include <locale.h>
#include <codecvt>
#include <locale>
#include "../headers/Arena.h"
#include "../headers/GameException.h"
#include <random>
#include <fstream>
//#include <ncurses.h>
#include <vector>
#include <string>

/*static void drawHPBar(int y, int x, int hp, int maxHp) {
    if (maxHp <= 0) return;

    int width = 20;
    int filled = hp * width / maxHp;
    int percent = hp * 100 / maxHp;

    int color = 1;
    if (percent < 30) color = 3;
    else if (percent < 60) color = 2;

    attron(COLOR_PAIR(color));
    mvaddch(y, x, '[');
    for (int i = 0; i < width; ++i) {
        mvaddch(y, x + 1 + i, (i < filled ? '#' : ' '));
    }
    mvaddch(y, x + width + 1, ']');
    attroff(COLOR_PAIR(color));

    mvprintw(y, x + width + 4, "%d/%d", hp, maxHp);
}
*/

/*static const std::vector<std::string> ASCII_PIKACHU = {
    "  \\__/\\",
    " ( o.o )",
    "  > ^ <"
};

static const std::vector<std::string> ASCII_BULBASAUR = {
    "   /\\_/\\",
    "  ( o o )",
    "  /  ^  \\",
    " (_______)"
};

static const std::vector<std::string> ASCII_CHARMANDER = {
    "   /\\_/\\",
    "  ( o o )",
    "  >  ^  <",
    "    ~~~"
};

static const std::vector<std::string> ASCII_SQUIRTLE = {
    "   /\\_/\\",
    "  ( o o )",
    "  <  ^  >",
    "  [_____]"
};

static const std::vector<std::wstring> ASCII_PIKACHU_UNICODE = {
    L"⠸⣷⣦⠤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣠⣤⠀⠀⠀",
    L"⠀⠙⣿⡄⠈⠑⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠔⠊⠉⣿⡿⠁⠀⠀⠀",
    L"⠀⠀⠈⠣⡀⠀⠀⠑⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⠊⠁⠀⠀⣰⠟⠀⠀⠀⣀⣀",
    L"⠀⠀⠀⠀⠈⠢⣄⠀⡈⠒⠊⠉⠁⠀⠈⠉⠑⠚⠀⠀⣀⠔⢊⣠⠤⠒⠊⠉⠀⡜",
    L"⠀⠀⠀⠀⠀⠀⠀⡽⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠩⡔⠊⠁⠀⠀⠀⠀⠀⠀⠇",
    L"⠀⠀⠀⠀⠀⠀⠀⡇⢠⡤⢄⠀⠀⠀⠀⠀⡠⢤⣄⠀⡇⠀⠀⠀⠀⠀⠀⠀⢰⠀",
    L"⠀⠀⠀⠀⠀⠀⢀⠇⠹⠿⠟⠀⠀⠤⠀⠀⠻⠿⠟⠀⣇⠀⠀⡀⠠⠄⠒⠊⠁⠀",
    L"⠀⠀⠀⠀⠀⠀⢸⣿⣿⡆⠀⠰⠤⠖⠦⠴⠀⢀⣶⣿⣿⠀⠙⢄⠀⠀⠀⠀⠀⠀",
    L"⠀⠀⠀⠀⠀⠀⠀⢻⣿⠃⠀⠀⠀⠀⠀⠀⠀⠈⠿⡿⠛⢄⠀⠀⠱⣄⠀⠀⠀⠀",
    L"⠀⠀⠀⠀⠀⠀⠀⢸⠈⠓⠦⠀⣀⣀⣀⠀⡠⠴⠊⠹⡞⣁⠤⠒⠉⠀⠀⠀⠀⠀",
    L"⠀⠀⠀⠀⠀⠀⣠⠃⠀⠀⠀⠀⡌⠉⠉⡤⠀⠀⠀⠀⢻⠿⠆⠀⠀⠀⠀⠀⠀⠀",
    L"⠀⠀⠀⠀⠀⠰⠁⡀⠀⠀⠀⠀⢸⠀⢰⠃⠀⠀⠀⢠⠀⢣⠀⠀⠀⠀⠀⠀⠀⠀",
    L"⠀⠀⠀⢶⣗⠧⡀⢳⠀⠀⠀⠀⢸⣀⣸⠀⠀⠀⢀⡜⠀⣸⢤⣶⠀⠀⠀⠀⠀⠀",
    L"⠀⠀⠀⠈⠻⣿⣦⣈⣧⡀⠀⠀⢸⣿⣿⠀⠀⢀⣼⡀⣨⣿⡿⠁⠀⠀⠀⠀⠀⠀",
    L"⠀⠀⠀⠀⠀⠈⠻⠿⠿⠓⠄⠤⠘⠉⠙⠤⢀⠾⠿⣿⠟⠋"
};

static const std::vector<std::wstring> ASCII_CHARMANDER_UNICODE = {
    L"⠀⠀⠀⠀⠀⠀⠀⡀⠠⢀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
    L"⠀⠀⠀⠀⠀⡔⠁⠀⠀⠀⠈⠑⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
    L"⠀⠀⠀⠀⣜⠃⠀⠀⠀⢘⢳⢆⠘⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
    L"⠀⠀⢀⠔⠉⠀⠀⠀⠀⣜⠀⢸⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
    L"⠀⠀⢸⠀⡀⠀⠀⠀⠀⠈⠉⠁⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠀⠀",
    L"⠀⡤⢄⣳⣦⠤⠤⠤⠄⣄⡲⡪⠀⡇⠀⢀⡀⢤⠀⠀⠀⢠⠒⢋⠤⠀",
    L"⠘⢝⠁⠈⠙⠷⠒⠒⠾⠓⢎⠀⠀⠁⠉⠁⠈⢛⠆⠀⠀⠈⢷⣿⠀⣆",
    L"⠀⠀⠑⢄⠀⡘⠀⠀⠀⠀⠀⠣⡀⠀⠀⣀⠔⠁⠀⠀⠀⢀⠃⠹⢷⡄",
    L"⠀⠀⠀⠀⠑⡇⠀⠀⠀⠀⠀⠀⢡⠀⠈⡄⠀⠀⠀⠀⠀⠈⠣⢤⡼⠀",
    L"⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⡆⠀⠰⠀⠀⠀⠀⠀⠀⠀⡌⡇⠀",
    L"⠀⠀⠀⠀⠀⢠⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⡇⠀⠀⠀⠀⢀⠌⢠⠃⠀",
    L"⠀⠀⠀⠀⡐⠉⠣⡀⠀⠀⠀⠀⢀⠃⠂⠐⡎⠁⠒⠂⠈⠀⣠⠏⠀⠀",
    L"⠀⠀⠀⠀⡀⠀⠀⠈⠒⡤⠀⠠⠊⠀⠀⠀⡠⣀⣀⠠⢄⠾⠃⠀⠀⠀",
    L"⠀⠀⣀⡤⠚⠲⠀⠀⠸⡁⠀⢘⠄⠀⠀⣠⠋⠁⠀⠉⠁⠀⠀⠀⠀⠀",
    L"⠀⠈⠛⡊⠂⠀⠀⠒⠂⠁⠀⠘⢖⣔⣶⡲⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀"
};

static const std::vector<std::wstring> ASCII_BULBASAUR_UNICODE = {
    L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
    L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⠉⢳⠴⢲⠂⠀⠀⠀⠀⠀",
    L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠖⠊⠀⣠⠎⠀⡞⢹⠏⠀⠀⠀⠀",
    L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡴⠊⠁⠀⠀⠀⠀⠀⢀⡠⠤⠄⠀⠀⠀⠁⠀⠀⢀⠀⢸⠀⠀⠀⠀⠀",
    L"⠀⠀⠀⠀⠀⣠⠤⠤⠄⣀⠀⠀⠀⠀⢀⣌⠀⠀⠀⠀⠀⢀⣠⣆⡁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠘⡄⠀⠀⠀⠀",
    L"⠀⠀⠀⠀⡴⠁⠀⠀⠐⠛⠉⠁⠀⠀⣉⠉⠉⠉⠑⠒⠉⠁⠀⠀⢸⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢧⠀⠱⡀⠀⠀⠀",
    L"⠀⠀⠀⢰⣥⠆⠀⠀⠀⣠⣴⣶⣿⣿⣿⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⢇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⡆⠀⠑⡄⠀⠀",
    L"⠀⠀⢀⡜⠁⠀⠀⢀⠀⠻⣿⣿⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⠀⠀⠸⡀⠀",
    L"⠀⢀⣮⢖⣧⢠⠀⣿⠇⠀⠀⠁⠀⠀⠀⠠⠀⢀⣠⣴⣤⡀⠀⠀⠀⠈⡗⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⢱⠀",
    L"⠀⣼⠃⣼⣿⠘⠀⠀⠀⢠⣶⣿⡆⠀⠀⠁⣠⠊⣸⣿⣿⣿⡄⠀⠀⠀⡇⠀⢑⣄⠀⠀⠀⠀⠀⠀⢠⠃⠀⠀⠸⡆",
    L"⠀⣿⢰⣿⣿⠀⠀⠀⠀⠙⠻⠿⠁⠀⠀⠠⠁⠀⣿⣿⣿⣿⡇⠀⠀⠀⠇⠀⢻⣿⣷⣦⣀⡀⣀⠠⠋⠀⠀⠀⢀⡇",
    L"⠈⠉⠺⠿⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⢿⣿⣿⣿⠇⠀⠀⠀⠀⠀⠈⢿⣿⣿⣿⣿⢦⡀⠀⠀⠀⠀⡸⠀",
    L"⠘⣟⠦⢀⠀⠀⢠⠀⠀⡠⠀⠀⠀⠀⠀⠀⠉⠉⠉⠉⠁⣀⠔⠀⠀⠀⠀⠀⠀⠀⠛⠻⠟⠋⠀⠙⢦⠀⣠⠜⠀⠀",
    L"⠀⠈⠑⠤⡙⠳⣶⣦⣤⣤⣤⣤⣤⣤⣤⣤⣴⣶⡶⠞⠁⠀⠀⣠⠖⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⠀⠈⢯⠁⠀⠀⠀",
    L"⠀⠀⠀⠀⠈⢳⠤⣙⡻⠿⣿⣿⣿⣿⡿⠿⠛⠉⠀⢀⣀⡤⡚⠁⠀⠀⠀⠀⠀⠀⣧⠖⣁⣤⣦⠀⠀⠈⢇⠀⠀⠀",
    L"⠀⠀⠀⠀⠀⢸⠀⢀⣩⣍⠓⠒⣒⠒⠒⠒⠒⠊⠉⠁⢀⡟⠀⠀⣾⣷⠀⠀⠀⠀⠏⢴⣿⣿⣿⠀⠀⠀⢸⠀⠀⠀",
    L"⠀⠀⠀⠀⠀⠘⣶⣿⣿⣿⠀⠀⠈⠒⢄⣀⡀⠀⠀⠀⣼⣶⣿⡇⠈⠋⠀⠀⠀⡼⠀⠈⠻⣿⡿⠀⠀⠀⢸⠀⠀⠀",
    L"⠀⠀⠀⠀⠀⠀⠹⡿⠿⠋⠀⠀⠀⠀⡜⠁⠈⢯⡀⢺⣿⣿⣿⠃⠀⠀⠀⢀⣼⣇⠀⠀⠀⠀⠀⠀⠀⠀⡞⠀⠀⠀",
    L"⠀⠀⠀⠀⠀⠀⠀⣿⣦⣄⣠⣀⣠⠞⠀⠀⠀⠈⠛⣿⡛⠛⠁⠀⠀⠀⣠⠊⠀⠈⢦⣄⣀⣀⣀⣀⢀⡼⠁⠀⠀⠀",
    L"⠀⠀⠀⠀⠀⠀⠀⠉⠉⠉⠛⠉⠀⠀⠀⠀⠀⠀⠘⠛⠿⣿⠷⡾⠗⠊⠁⠀⠀⠀⠈⠉⠙⠛⠛⠛⠉⠀⠀⠀⠀⠀"
};

static const std::vector<std::string>& getAsciiForPokemon(const std::string& nume) {
    if (nume == "Pikachu") return ASCII_PIKACHU;
    if (nume == "Bulbasaur") return ASCII_BULBASAUR;
    if (nume == "Charmander") return ASCII_CHARMANDER;
    if (nume == "Squirtle") return ASCII_SQUIRTLE;
    return ASCII_PIKACHU; // fallback
}

static void drawAsciiArt(int y, int x, const std::vector<std::string>& art) {
    for (size_t i = 0; i < art.size(); ++i) {
        mvprintw(y + i, x, "%s", art[i].c_str());
    }
}

static int asciiWidth(const std::vector<std::wstring>& art) {
    size_t maxLen = 0;
    for (const auto& line : art) {
        if (line.size() > maxLen)
            maxLen = line.size();
    }
    return static_cast<int>(maxLen);
}

static void drawAsciiArtWide(int y, int x, const std::vector<std::wstring>& art) {
    static std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    for (size_t i = 0; i < art.size(); ++i) {
        std::string utf8 = converter.to_bytes(art[i]);
        mvaddstr(y + i, x, utf8.c_str());
    }
}
*/
Arena::Arena() {

    listaPokemoni.emplace_back("Pikachu", "Electric", 1200, 55, 40, 90);
    listaPokemoni.emplace_back("Bulbasaur", "Iarba",   1400, 49, 49, 45);
    listaPokemoni.emplace_back("Charmander", "Foc",    1200, 52, 43, 65);
    listaPokemoni.emplace_back("Squirtle", "Apa",      1300, 48, 65, 43);
}

void Arena::afiseazaLeaderboard() {
    std::ifstream fin("leaderboard.txt");
    if (!fin.is_open()) {
        std::cout << "Nu exista leaderboard inca.\n";
        return;
    }

    std::cout << "\n=== LEADERBOARD ===\n";
    std::string n;
    int s;
    while (fin >> n >> s)
        std::cout << n << " — " << s << " victorii\n";

    std::cout << "==========================\n";
    fin.close();
}
 void Arena::actualizeazaLeaderboard(const std::string& castigator) {
    std::ifstream fin("leaderboard.txt");
    std::vector<std::string> nume;
    std::vector<int> scoruri;

    std::string n;
    int s;
    bool gasit = false;

    while (fin >> n >> s) {
        if (n == castigator) {
            s++;
            gasit = true;
        }
        nume.push_back(n);
        scoruri.push_back(s);
    }
    fin.close();

    if (!gasit) {
        nume.push_back(castigator);
        scoruri.push_back(1);
    }

    std::ofstream fout("leaderboard.txt");
    for (size_t i = 0; i < nume.size(); i++) {
        fout << nume[i] << " " << scoruri[i] << "\n";
    }
    fout.close();

    std::cout << "Leaderboard actualizat!\n";
}

void Arena::salveazaProgres(const Player& p1, const Player& p2){
    std::ofstream fout("save.txt");
    if (!fout.is_open()) {
        std::cout << "Eroare: nu pot salva progresul.\n";
        return;
    }

    fout << p1.getNume() << " " << p1.getPokemon().getNume() << " "
         << p1.getPokemon().getHP() << "\n";
    fout << p2.getNume() << " " << p2.getPokemon().getNume() << " "
         << p2.getPokemon().getHP() << "\n";

    fout.close();
}

void Arena::startGame() const {
    std::cout << "=== Pokemon Arena ===\n";
    std::cout << "1. Continuă ultimul meci\n";
    std::cout << "2. Joc nou\n";
    std::cout << "3. Afiseaza leaderboard-ul\n";
    std::cout << "Alege optiunea: ";

    int opt;
    std::cin >> opt;

    if (opt == 1) {
        std::ifstream fin("save.txt");
        if (!fin.is_open()) {
            std::cout << "Nu există un fisier de salvare.\n";
        } else {
            std::string nume1, poke1, nume2, poke2;
            int hp1, hp2;
            fin >> nume1 >> poke1 >> hp1;
            fin >> nume2 >> poke2 >> hp2;

            Player p1(nume1);
            Player p2(nume2);

            Pokemon pk1, pk2;
            bool found1 = false, found2 = false;

            for (const auto& p : listaPokemoni) {
                if (p.getNume() == poke1) {
                    pk1 = p;
                    found1 = true;
                }
                if (p.getNume() == poke2) {
                    pk2 = p;
                    found2 = true;
                }
            }

            if (found1 && found2) {
                pk1.primesteDamage(pk1.getHP() - hp1);
                pk2.primesteDamage(pk2.getHP() - hp2);

                p1.setPokemon(pk1);
                p2.setPokemon(pk2);

                std::cout << "\n=== Joc incarcat cu succes! ===\n";
                std::cout << pk1 << "\n" << pk2 << "\n";

                desfasoaraLupta(p1, p2);
                return;
            } else {
                std::cout << "Eroare: Pokemonii salvati nu au fost gasiti.\n";
            }
        }
    }
    else if (opt == 2) {
        std::cout << "=== Pokemon Arena ===\n";
        std::cout << "1. Player vs Player\n";
        std::cout << "2. Player vs AI\n";
        std::cout << "Alege modul: ";

        int mod;
        std::cin >> mod;
        std::string numeP1, numeP2;
        std::cout << "Introdu numele pentru Player 1: ";
        std::cin >> numeP1;
        if (mod == 1) {
            std::cout << "Introdu numele pentru Player 2: ";
            std::cin >> numeP2;
        } else {
            numeP2 = "AI";
        }
        Player p1(numeP1);
        Player p2(numeP2);

        p1.alegePokemon(listaPokemoni, false);
        p2.alegePokemon(listaPokemoni, mod == 2);

        try {
            p1.getPokemon().valideaza();
            p2.getPokemon().valideaza();
        } catch (const GameException& e) {
            std::cout << "Eroare joc: " << e.what() << "\n";
            return;
        }

        std::cout << "\n=== Lupta incepe! ===\n";
        std::cout << p1 << "\n" << p2 << "\n";

        desfasoaraLupta(p1, p2);

    } else if (opt == 3) {
        afiseazaLeaderboard();
    }


}

void Arena::desfasoaraLupta(Player& p1, Player& p2) {
    setlocale(LC_ALL, "");
    /*initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
*/
    const Pokemon& poke1 = p1.getPokemon();
    const Pokemon& poke2 = p2.getPokemon();

    Player* first;
    Player* second;

    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> distrib(1, 3);

    if (poke1.getSpeed() > poke2.getSpeed()) {
        first = &p1; second = &p2;
    } else if (poke1.getSpeed() < poke2.getSpeed()) {
        first = &p2; second = &p1;
    } else {
        if (std::uniform_int_distribution<>(0, 1)(gen) == 0) { first = &p1; second = &p2; }
        else { first = &p2; second = &p1; }
    }

    std::cout << first->getNume() << " va incepe primul!\n";

    while (poke1.esteViu() && poke2.esteViu()) {

        Pokemon& attacker = first->getPokemon();
        Pokemon& defender = second->getPokemon();

        std::cout << "\n" << first->getNume() << ", alege o actiune:\n";
        std::cout << "1. Atac normal\n";
        std::cout << "2. Aparare\n";
        std::cout << "3. Abilitate speciala\n> ";

        int actiune;
        if (first->getNume() == "AI") {
            actiune = distrib(gen);
        } else {
            std::cin >> actiune;
        }

        if (actiune == 1) {
            attacker.ataca(defender);
        } else if (actiune == 2) {
            attacker.setDefending(true);
            std::cout << attacker.getNume() << " se apara!\n";
        } else if (actiune == 3) {
            attacker.folosesteAbilitate(defender);
        } else {
            std::cout << "Actiune invalida. Se considera atac normal.\n";
            attacker.ataca(defender);
        }


        if (attacker.esteViu() && defender.esteViu())
        {
        Pokemon& attacker2 = second->getPokemon();
        Pokemon& defender2 = first->getPokemon();

        std::cout << "\n" << second->getNume() << ", alege o actiune:\n";
        std::cout << "1. Atac normal\n";
        std::cout << "2. Aparare\n";
        std::cout << "3. Abilitate speciala\n> ";

        if (second->getNume() == "AI") {
            actiune = distrib(gen);
            std::cout << actiune << "\n";
        } else {
            std::cin >> actiune;
        }

        if (actiune == 1) {
            attacker2.ataca(defender2);
        } else if (actiune == 2) {
            attacker2.setDefending(true);
            std::cout << attacker2.getNume() << " se apara!\n";
        } else if (actiune == 3) {
            attacker2.folosesteAbilitate(defender2);
        } else {
            std::cout << "Actiune invalida. Se considera atac normal.\n";
            attacker2.ataca(defender2);
        }
        }

        //clear();

        //const int BASE_Y = 2;
        //const int LEFT_X = 2;
        //const int rightX = 40;

        /*if (p1.getPokemon().getNume() == "Pikachu") art1 = &ASCII_PIKACHU_UNICODE;
        else if (p1.getPokemon().getNume() == "Charmander") art1 = &ASCII_CHARMANDER_UNICODE;
        else if (p1.getPokemon().getNume() == "Bulbasaur") art1 = &ASCII_BULBASAUR_UNICODE;

        if (p2.getPokemon().getNume() == "Pikachu") art2 = &ASCII_PIKACHU_UNICODE;
        else if (p2.getPokemon().getNume() == "Charmander") art2 = &ASCII_CHARMANDER_UNICODE;
        else if (p2.getPokemon().getNume() == "Bulbasaur") art2 = &ASCII_BULBASAUR_UNICODE;



        int rightX;

        if (art1) {
            drawAsciiArtWide(BASE_Y, LEFT_X, *art1);
            rightX = LEFT_X + asciiWidth(*art1) + 8;  // deplasare după lățimea reală
        } else {
            drawAsciiArt(BASE_Y, LEFT_X, getAsciiForPokemon(p1.getPokemon().getNume()));
            rightX = LEFT_X + 30; // fallback ASCII mic
        }

        if (art2) {
            drawAsciiArtWide(BASE_Y, rightX, *art2);
        } else {
            drawAsciiArt(BASE_Y, rightX, getAsciiForPokemon(p2.getPokemon().getNume()));
        }

        */
/*

        mvprintw(BASE_Y + 18, LEFT_X, "%s", p1.getPokemon().getNume().c_str());
        mvprintw(BASE_Y + 18, rightX, "%s", p2.getPokemon().getNume().c_str());


        drawHPBar(BASE_Y + 19, LEFT_X,
                  p1.getPokemon().getHP(),
                  p1.getPokemon().getMaxHP());

        drawHPBar(BASE_Y + 19, rightX,
                  p2.getPokemon().getHP(),
                  p2.getPokemon().getMaxHP());

        mvprintw(12, 2, "Apasa orice tasta pentru runda urmatoare...");
        refresh();
        getch();

        p1.getPokemon().reduceCooldown();
        p2.getPokemon().reduceCooldown();
*/
        salveazaProgres(p1, p2);

    }
    //endwin();

    std::string castigator;
    if (poke1.esteViu()){
        std::cout << p1.getNume() << " a castigat!\n";
        castigator = p1.getNume();
    }
    else{
        std::cout << p2.getNume() << " a castigat!\n";
        castigator = p2.getNume();
    }
    actualizeazaLeaderboard(castigator);

    std::remove("save.txt");

}

std::ostream& operator<<(std::ostream& out, const Arena& a) {
    out << "=== Pokemon Arena ===\n";
    out << "Numar total de pokemoni disponibili: " << a.listaPokemoni.size() << "\n";
    out << "Lista pokemoni:\n";
    for (const auto& p : a.listaPokemoni) {
         out << p << ")\n";
    }
    out << "=========================\n";
    return out;
}
