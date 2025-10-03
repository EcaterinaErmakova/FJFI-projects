// Conway's Game of Life

#include <iostream>
#include <vector>

// Defaultni typ pro enum je int
//enum CellState : int {
enum CellState : char {
    DEAD = 0,
    ALIVE = 1
};

class GameBoard
{
private:
    std::vector<std::vector<CellState>> cells;
    // alternativa: std::unordered_set<std::pair<int, int>>

public:
    GameBoard(int x, int y);

    // zjisteni rozmeru hraci plochy
    int get_x() const;
    int get_y() const;

    // pristupova metoda k bunce podle pozice
    CellState get(int x, int y) const;
    void set(int x, int y, CellState state);

    // metoda pro zjisteni poctu zivych sousedu
    int count_alive_neighbors(int x, int y) const;

    // metoda pro overovani pravidel hry
    CellState get_new_state(int x, int y) const;
};

std::ostream& operator<<(std::ostream& stream, const GameBoard& game)
{
    // ...

    return stream;
}

void run(GameBoard& game)
{
    GameBoard game2(game.get_x(), game.get_y());

    // algoritmus hry:
    int time = 0;
    while (time < 100) {
        // projit vsechny bunky
        for (int x = 0; x < game.get_x(); x++) {
            for (int y = 0; y < game.get_y(); y++) {
                // 1. zjistit novy stav bunky
                CellState new_state = game.get_new_state(x, y);
                // 2. aplikovat zmenu stavu - do pomocne hraci plochy !!!
                game2.set(x, y, new_state);
            }
        }

        // preneseni stavu do game
        //game = game2;
        std::swap(game, game2);

        // vizualizace hry
        std::cout << "Time = " << time << std::endl;
        std::cout << game;

        time++;
    }
}

int main()
{
    CellState c = DEAD;

    GameBoard game(40, 20);

    // inicializace: Blinker (period 2)
    game.set(10, 10, CellState::ALIVE);
    game.set(10, 11, CellState::ALIVE);
    game.set(10, 12, CellState::ALIVE);

    run(game);
}
