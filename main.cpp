//
//  main.cpp
//  Shreya Wagley
//
//

#include<iostream>
#include<random>
#include<ctime>
#include<stack>
using namespace std;

#include"State.h"
#include "Solver.h"




int main() {
    
    srand(time(0));
    
    int choice = 0;
    
    cout << "================================ Mini-SHRDLU ================================" << endl << endl;
    
    while (choice != 5) {
        cout << "Choose a level to run: " << endl;
        cout << "1. Single goal solver with 3x3 board" << endl;
        cout << "2. Single goal solver with nxn board" << endl;
        cout << "3. A* sover on nxn board" << endl;
        cout << "4. A* sover on 3x3 board" << endl;
        cout << "5. Quit" << endl;

        cin >> choice;

        switch (choice) {
            case 1: {
                // Initialize a 3x3 state with 6 blocks
                State state(3, 6);
                
                cout << "Initial State: " << endl;

                state.pushDown(); // Apply gravity to arrange blocks
                state.printBoard();
                
                int block, destRow, destCol;
                cout << "Input a goal in the format (block, row, col): " << endl;
                cout << "Block (1 - 6): ";
                cin >> block;
                cout << "Row (0 - 2 top-down): ";
                cin >> destRow;
                cout << "Column (0 - 2 left-right): ";
                cin >> destCol;

                Solver solver(state);
                solver.search(block, destRow, destCol);
                break;
            }
            case 2: {
                // Get the board size from the user
                int board_size;
                cout << "Enter board size (3 or greater): ";
                cin >> board_size;
                
                // Validate the board size
                while (board_size < 3) {
                    cout << "Invalid size. Enter board size (3 or greater): ";
                    cin >> board_size;
                }

                // Get the number of blocks from the user
                int num_blocks;
                cout << "Enter number of blocks (1-" << board_size * board_size - 1 << "): ";
                cin >> num_blocks;

                // Validate the number of blocks
                while (num_blocks < 1 || num_blocks > board_size * board_size - 1) {
                    cout << "Invalid number of blocks. Enter number of blocks (1-" << board_size * board_size - 1 << "): ";
                    cin >> num_blocks;
                }

                // Create an initial state
                State state(board_size, num_blocks);

                cout << "Initial State: " << endl;

                state.pushDown(); // Apply gravity to arrange blocks
                state.printBoard();

                int block, destRow, destCol;
                cout << "Input a goal in the format (block, row, col): " << endl;
                cout << "Block (1 - " << num_blocks << "): ";
                cin >> block;
                cout << "Row (0 - " << board_size - 1 << " top-down): ";
                cin >> destRow;
                cout << "Column (0 - " << board_size - 1 << " left-right): ";
                cin >> destCol;

                Solver solver(state);
                solver.search(block, destRow, destCol);

                break;
            }
            case 3: {
                // Get the board size from the user
                int board_size;
                cout << "Enter board size (3 or greater): ";
                cin >> board_size;

                // Validate the board size
                while (board_size < 3) {
                    cout << "Invalid size. Enter board size (3 or greater): ";
                    cin >> board_size;
                }

                // Get the number of blocks from the user
                int num_blocks;
                cout << "Enter number of blocks (1-" << board_size * board_size - 1 << "): ";
                cin >> num_blocks;

                // Validate the number of blocks
                while (num_blocks < 1 || num_blocks > board_size * board_size - 1) {
                    cout << "Invalid number of blocks. Enter number of blocks (1-" << board_size * board_size - 1 << "): ";
                    cin >> num_blocks;
                }

                // Create an initial state
                State state(board_size, num_blocks);

                cout << "Initial State: " << endl;

                state.pushDown(); // Apply gravity to arrange blocks
                state.printBoard();

                int block, destRow, destCol;
                cout << "Input a goal in the format (block, row, col): " << endl;
                cout << "Block (1 - " << num_blocks << "): ";
                cin >> block;
                cout << "Row (0 - " << board_size - 1 << " top-down): ";
                cin >> destRow;
                cout << "Column (0 - " << board_size - 1 << " left-right): ";
                cin >> destCol;

                Solver solver(state);
                solver.AStarSearch(block, destRow, destCol);

                break;
            }
            case 4: {
                // Create an initial state with a 3x3 board and 6 blocks
                State state(3, 6);

                cout << "Initial State: " << endl;

                // Apply gravity to arrange blocks
                state.pushDown();
                state.printBoard();

                int block, destRow, destCol;
                cout << "Input a goal in the format (block, row, col): " << endl;
                cout << "Block (1 - 6): ";
                cin >> block;
                cout << "Row (0 - 2 top-down): ";
                cin >> destRow;
                cout << "Column (0 - 2 left-right): ";
                cin >> destCol;

                // Create a solver and perform A* search
                Solver solver(state);
                solver.AStarSearch(block, destRow, destCol);

                break;
            }

            case 5:{
                cout << "BYE BYE!" << endl;
                break;
            }
                
                
            default:
                cout << "Invalid choice. Please choose again." << endl << endl;
        }
    }
    return 0;
}

