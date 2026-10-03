#include <SFML/Graphics.hpp>
#include "Grid.h"

int main()
{
    const int windowWidth = 1000;
    const int windowHeight = 1000;

    const float cellSize = 10.f;

    sf::RenderWindow window(
        sf::VideoMode({
            static_cast<unsigned int>(windowWidth),
            static_cast<unsigned int>(windowHeight)
        }),
        "SFML Grid"
    );

    Grid grid(windowWidth, windowHeight, cellSize, true);
    Grid ngGrid(windowWidth, windowHeight, cellSize, false);

    grid.setCell(40, 40, 1);
    grid.setCell(41, 40, 1);
    grid.setCell(42, 40, 1);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        int nb = 0;

        for (int x = 0; x < 100; x++) {
            for (int y = 0; y < 100; y++) {

            }
        }

        window.clear();

        for (int x = 0; x < grid.getColumns(); x++) {
            for (int y = 0; y < grid.getRows(); y++) {
                int nb = 0;

                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (dx == 0 && dy == 0) continue;
                        if (grid.getCell(x + dx, y + dy) == 1) nb++;
                    }
                }

                int current = grid.getCell(x, y);

                if (current == 1 && (nb == 2 || nb == 3)) {
                    ngGrid.setCell(x, y, 1);
                }
                else if (current == 0 && nb == 3) {
                    ngGrid.setCell(x, y, 1);
                } else {
                    ngGrid.setCell(x, y, 0);
                }
            }
        }

        for (int x = 0; x < grid.getColumns(); x++) {
            for (int y = 0; y < grid.getRows(); y++) {
                grid.setCell(x, y, ngGrid.getCell(x, y));
            }
        }

        for (int x = 0; x < grid.getColumns(); x++) {
            for (int y = 0; y < grid.getRows(); y++) {
                if (grid.getCell(x, y) == 1) {
                    sf::RectangleShape alive({10.f, 10.f});
                    alive.setPosition({static_cast<float>(x * 10), static_cast<float>(y * 10)});

                    window.draw(alive);
                }
            }
        }

        grid.draw(window);

        window.display();
    }

    return 0;
}