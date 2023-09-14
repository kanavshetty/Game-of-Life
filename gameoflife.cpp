#include <iostream>
#include <thread>
#include <chrono>

int main() {

    // Initializing the size of the grid
    const int grid_size = 10;
    // Representing the grid as a 2d boolean array
    bool grid[grid_size][grid_size];

    // Setting every cell in our grid to false
    for (int i = 0; i < grid_size; i = i + 1) {     
        for (int j = 0; j < grid_size; j = j + 1) { 
            grid[i][j] = false;
        }
    }

    // Initializing the initial state of our grid.
    grid[4][3] = grid[4][4] = grid[4][5] = grid[3][5] = grid[2][4] = true;


    
    // Initializing the game loop.
    while(true) {

        // Clear the console
        system("CLS"); 

        // This helps us to print the state of the grid
        for (int row = 0; row < grid_size; row++) {     
            for (int col = 0; col < grid_size; col++) { 
                // If the current cell is true, print "#". Otherwise, print "-"
                if (grid[row][col]) std::cout << "#";
                else std::cout << "-";
            }
            // A line break at the end of each row
            std::cout << std::endl;
        }

        // We now create another array of the same dimensions and use it to determine the
        // next state of the game.
        bool new_grid[grid_size][grid_size];

        // Determine the next state of the game
        // For each cell:
        // If it's alive, it remains alive only if it has 2 or 3 alive neighbours.
        // If it's dead, it resurrects if and only if it has 3 alive neighbours.
        for (int row = 0; row < grid_size; row++) {     // Go through each row
            for (int col = 0; col < grid_size; col++) { // Go through each column
                
                // Go through all its neighbours by iterating through row - 1 to row + 1, and col - 1 to col + 1
                // Count the number of neighbours alive
                int n_neighbors = 0;
                for(int neighbor_row = row - 1; neighbor_row <= row + 1; neighbor_row++) {
                    for (int neighbor_col = col - 1; neighbor_col <= col + 1; neighbor_col++) {
                        if ((neighbor_col == col && neighbor_row == row) // A cell is not its own neighbour
                            // Border cells might have fewer than 8 neighbours.
                            // For instance if neighbor_col is -1, it is not an actual neighbour
                            || neighbor_col < 0 || neighbor_row < 0
                            || neighbor_col >= grid_size || neighbor_row >= grid_size) {
                            continue;
                        }
                        // If the current neighbour is on, increment the number of alive neighbours
                        if (grid[neighbor_row][neighbor_col]) n_neighbors++;
                    }
                }

                if (grid[row][col]) { // The cell is currently alive
                    new_grid[row][col] = (n_neighbors == 2 || n_neighbors == 3);
                } else {              // The cell is dead
                    new_grid[row][col] = (n_neighbors == 3);
                }
            }
        }

        // We then use a flag to see if any of the cells have changed, and initialize it to false
        bool changed = false;
        // We then copy new_grid to grid
        for (int row = 0; row < grid_size; row++) {
            for (int col = 0; col < grid_size; col++) {
                // If a cell has changed, we change the flag "changed" to true.
                if (grid[row][col] != new_grid[row][col]) changed = true;
                // We copy new_grid to grid
                grid[row][col] = new_grid[row][col];
            }
        }

        // If the grid hasn't changed, break out of the loop
        if (!changed) break;

        // Pause for a second
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }


    return 0;
}