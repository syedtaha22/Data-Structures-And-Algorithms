#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>

// Structure to represent a cell in the maze
struct Cell {
    /*
        * The cell structure is used to represent a cell in the maze.
        * It has four fields north, east, south, west to store the walls of the cell.
        * The walls can be either present (true) or absent (false).
        * It also has a field 'visited' to store the visit status of the cell.
    */
    bool north = true, east = true, south = true, west = true; // walls
    bool visited = false; // visit status
};


// Structure to represent a position in the maze
struct Position {
    /*
        * The position structure is used to represent a cell in the maze.
        * It has two fields x and y to store the row and column indices of the cell.
    */
    int x, y;
};

class Maze {
    /*
        * The Maze class is used to generate a maze using the depth-first search algorithm.
        * The maze is represented as a 2D grid of cells. Each cell has four walls
        * (north, east, south, west) that can be either present (true) or absent (false).
    */
    std::vector<std::vector<Cell>> maze;
    int size;

public:
    Maze(int n) : size(n) {
        maze.resize(n + 2, std::vector<Cell>(n + 2));
        initialise_maze();
    }

    void print_maze() const {
        /*
            * The printMaze function is used to print the maze to the console.
            * The maze is printed as a grid of cells with walls between them.
            * The walls are represented by '+', '-', and '|'.
            * First, print the north walls of the cells, then the west walls.
            * This gives a structure like:
                    +---+---+---+---+ (North Walls then a new line)
                    |   |   |   |   | (West Walls then a new line)
                    +---+---+---+---+ (North Walls then a new line)
                    |   |   |   |   | (West Walls then a new line)
                    +---+---+---+---+ (North Walls then a new line)
                    |   |   |   |   | (West Walls then a new line)
                    +---+---+---+---+ (Bottom Border)
        */
        for (int x = 1; x <= size; x++) {
            // Print the north walls
            for (int y = 1; y <= size; y++) {
                std::cout << "+";
                std::cout << (maze[x][y].north ? "---" : "   ");
            }
            std::cout << "+\n";

            // Print the west walls and cells
            for (int y = 1; y <= size; y++) {
                std::cout << (maze[x][y].west ? "|" : " ");
                std::cout << "   ";
            }
            std::cout << "|\n";
        }

        // Print the bottom border
        for (int y = 1; y <= size; y++) {
            std::cout << "+---";
        }
        std::cout << "+\n";
    }
private:

    // Function to get Neighbors of a cell
    std::vector<Position> get_Neighbors(Position current) {
        std::vector<Position> neighbors;

        /*
            * Check the neighbors of the current cell and add them to the list of unvisited neighbors.
            * A neighbor is unvisited if it is within the bounds of the maze and has not been visited yet.
            * (x, y+1) is the neighbor to the north of (x, y)
            * (x, y-1) is the neighbor to the south of (x, y)
            * (x-1, y) is the neighbor to the west of (x, y)
            * (x+1, y) is the neighbor to the east of (x, y)
        */
        if (current.x > 1 && !maze[current.x - 1][current.y].visited)
            neighbors.push_back({ current.x - 1, current.y });
        if (current.x < size && !maze[current.x + 1][current.y].visited)
            neighbors.push_back({ current.x + 1, current.y });
        if (current.y > 1 && !maze[current.x][current.y - 1].visited)
            neighbors.push_back({ current.x, current.y - 1 });
        if (current.y < size && !maze[current.x][current.y + 1].visited)
            neighbors.push_back({ current.x, current.y + 1 });

        return neighbors;
    }

    // Helper function to knock down walls between cells
    void knock_walls(Position current, Position next) {
        /*
            * The knockWalls function is used to knock down the walls between the current cell
            * and the next cell.
            * If the next cell is to the north of the current cell, the north wall of the current
            * cell and the south wall of the next cell are knocked down.
            * If the next cell is to the south of the current cell, the south wall of the current
            * cell and the north wall of the next cell are knocked down.
            * If the next cell is to the west of the current cell, the west wall of the current
            * cell and the east wall of the next cell are knocked down.
            * If the next cell is to the east of the current cell, the east wall of the current
            * cell and the west wall of the next cell are knocked down.
        */

        if (next.x == current.x - 1) {
            maze[current.x][current.y].north = false;
            maze[next.x][next.y].south = false;
        }
        else if (next.x == current.x + 1) {
            maze[current.x][current.y].south = false;
            maze[next.x][next.y].north = false;
        }
        else if (next.y == current.y - 1) {
            maze[current.x][current.y].west = false;
            maze[next.x][next.y].east = false;
        }
        else if (next.y == current.y + 1) {
            maze[current.x][current.y].east = false;
            maze[next.x][next.y].west = false;
        }

    }

    // Function to generate a maze using the depth-first search algorithm
    void initialise_maze() {
        std::stack<Position> cellStack; // Depth-first search stack
        int visitedCells = 1;
        int totalCells = size * size;

        // Randomize starting point
        Position current = { 1, 1 };
        maze[current.x][current.y].visited = true;
        cellStack.push(current);

        srand(time(0));

        while (visitedCells < totalCells) {
            std::vector<Position> neighbors = get_Neighbors(current);

            // If there are unvisited neighbors
            if (!neighbors.empty()) {
                // Choose a random neighbor
                Position next = neighbors[rand() % neighbors.size()];
                knock_walls(current, next);

                // Move to the next cell
                cellStack.push(next);
                maze[next.x][next.y].visited = true;
                current = next;
                visitedCells++;
            }
            else {
                // Backtrack
                current = cellStack.top();
                cellStack.pop();
            }
        }
    }
};


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <n>" << std::endl;
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        std::cerr << "Error: n must be a positive integer." << std::endl;
        return 1;
    }

    Maze maze(n);

    std::cout << "\nGenerated maze:" << std::endl;
    maze.print_maze();


    return 0;
}
