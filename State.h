//
//  State.h
//  Shreya Wagley
//

#ifndef State_h
#define State_h

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <random>
using namespace std;


class State {
private:
    
   
  

public:
    
    int BOARDSIZE;
    int NUMBER_OF_BLOCKS;

    
    vector<vector<int>> grid;

    State(int board_size, int num_blocks) {

        BOARDSIZE = board_size;
        NUMBER_OF_BLOCKS = num_blocks;
        
        //initialize grid to all zeros
        grid = vector<vector<int>>(BOARDSIZE, vector<int>(BOARDSIZE, 0));
        
    
        
        //place blocks on grid
        int count = 0;
        while (count < NUMBER_OF_BLOCKS) {
            int i = rand() % BOARDSIZE;
            int j = rand() % BOARDSIZE;
            if (grid[i][j] == 0) {
                grid[i][j] = count + 1;
                count++;
            }
        }
    }


    void printBoard();
    void pushDown();
    bool moveBlock(int block, int destCol);
    int getBlockRow(int block);
    int getBlockCol(int block);
    bool canMoveBlock(int block, int destCol);
    vector<State> getValidMoves();
    bool operator==(const State& other) const;
    int manhattanDistance(int block, int destRow, int destCol);
    bool operator<(const State& other) const;

    

    

    
};

// Overloaded equality operator for comparing two State objects
// Returns true if the grid of the current State is equal to the grid of the other State, false otherwise
bool State::operator==(const State& other) const {
    for (int i = 0; i < BOARDSIZE; i++) {
        for (int j = 0; j < BOARDSIZE; j++) {
            if (grid[i][j] != other.grid[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Overloaded less-than operator for comparing two State objects
// Returns true if the grid of the current State is lexicographically less than the grid of the other State, false otherwise
bool State::operator<(const State& other) const {
    for (int i = 0; i < BOARDSIZE; i++) {
        for (int j = 0; j < BOARDSIZE; j++) {
            if (grid[i][j] < other.grid[i][j]) {
                return true;
            } else if (grid[i][j] > other.grid[i][j]) {
                return false;
            }
        }
    }
    return false;
}

// Function to print the current state's board
void State::printBoard() {
    cout << endl;
    
    // Iterate through rows
    for (int i = BOARDSIZE - 1; i >= 0; i--) {
        // Iterate through columns
        for (int j = 0; j < BOARDSIZE; j++) {
            cout << "|";
            
            // Print the cell content
            if (grid[i][j] == 0) {
                cout << "   "; // Empty cell
            }
            else {
                printf("%2d ", grid[i][j]); // Cell with a number
            }
        }
        cout << "|" << endl;
    }
    
    // Print horizontal separator
    for (int j = 0; j < BOARDSIZE; j++) {
        cout << " ---";
    }
    cout << endl;
}


void State::pushDown() {
    //each column
       for (int j = 0; j < BOARDSIZE; j++) {
           //stack to hold non-zero elements
           stack<int> nonZeroElements;

           //push all non-zero elements in column onto stack
           for (int i = BOARDSIZE - 1; i >= 0; i--) {
               if (grid[i][j] != 0) {
                   nonZeroElements.push(grid[i][j]);
               }
           }

           //pop elements from stack and store in column,
           int k = 0;
           while (!nonZeroElements.empty()) {
               grid[k][j] = nonZeroElements.top(); //store top element in column
               nonZeroElements.pop(); //pop top element from stack
               k++; //move down to next cell in column
           }
           while (k < BOARDSIZE) {
               grid[k][j] = 0; //fill remaining cells in column with zeros
               k++;
           }
       }
}


// Function to find the row index of a block in the state's grid
int State::getBlockRow(int block) {
    // Iterate through rows
    for (int i = 0; i < BOARDSIZE; i++) {
        // Iterate through columns
        for (int j = 0; j < BOARDSIZE; j++) {
            // Check if the current cell contains the target block
            if (grid[i][j] == block) {
                return i; // Return the row index where the block is found
            }
        }
    }
    
    return -1; // Block not found in the state's grid
}


// Function to find the column index of a block in the state's grid
int State::getBlockCol(int block) {
    // Iterate through rows
    for (int i = 0; i < BOARDSIZE; i++) {
        // Iterate through columns
        for (int j = 0; j < BOARDSIZE; j++) {
            // Check if the current cell contains the target block
            if (grid[i][j] == block) {
                return j; // Return the column index where the block is found
            }
        }
    }
    
    return -1; // Block not found in the state's grid
}

//Function to test if a block can be moved
bool State::canMoveBlock(int block, int destCol) {
    // Find the current row and column of the block
    int row = getBlockRow(block);
    int col = getBlockCol(block);

    if (row == -1 || col == -1) {
        // Block not found on the board
        return false;
    }
    
    // Check if the block is the topmost block in its column
    if (row != BOARDSIZE - 1 && grid[row+1][col] != 0) {
        // Block has another block on top of it
        return false;
    }


    // Check if the destination column is valid
    if (destCol < 0 || destCol >= BOARDSIZE) {
        return false;
    }

    // Find the highest row in the destination column that is empty
    int destRow = -1;
    for (int i = BOARDSIZE - 1; i >= 0; i--) {
        if (grid[i][destCol] == 0) {
            destRow = i;
            break;
        }
    }
    if (destRow < 0) {
        // Destination column is full
        return false;
    }

    // Check if the block can be moved to the destination column
    for (int i = row + 1; i <= destRow; i++) {
        if (grid[i][col] != 0) {
            // There is a block in the way
            return false;
        }
    }

    return true;
}

// Function to move a block to a specified column
bool State::moveBlock(int block, int destCol) {
    // Find the current row and column of the block
    int row = getBlockRow(block);
    int col = getBlockCol(block);
    int destRow = BOARDSIZE - 1;
    
    // Check if the block can be moved to the destination column
    if (canMoveBlock(block, destCol)){
        // Move the block
        grid[row][col] = 0;         // Clear the current position of the block
        grid[destRow][destCol] = block; // Place the block in the destination column
        pushDown(); // Adjust the grid by pushing blocks down
        
        return true; // Block successfully moved
    }
    
    return false; // Block cannot be moved to the destination column
}


vector<State> State::getValidMoves() {
    vector<State> valid_moves;
    // loop through all blocks on the grid
    for (int i = 1; i <= NUMBER_OF_BLOCKS; i++) {
        int row = getBlockRow(i);
        int col = getBlockCol(i);

        // check if the block can move left
        if (col > BOARDSIZE-BOARDSIZE && grid[row][col - 1] == 0) {
            State new_state = *this; // Create a new state as a copy of the current state.
            new_state.moveBlock(i, col - 1); // Move the block to the left.
            valid_moves.push_back(new_state);
        }

        // check if the block can move right
        if (col < BOARDSIZE && grid[row][col + 1] == 0) {
            State new_state = *this; // Create a new state as a copy of the current state.
            new_state.moveBlock(i, col + 1); // Move the block to the right.
            valid_moves.push_back(new_state);
        }

    }

    return valid_moves;
    
}

// Function to calculate the Manhattan distance between a block and a specified position
int State::manhattanDistance(int block, int destRow, int destCol) {
    // Get the current row and column of the block
    int blockRow = getBlockRow(block);
    int blockCol = getBlockCol(block);

    // Calculate and return the Manhattan distance
    return abs(blockRow - destRow) + abs(blockCol - destCol);
}


#endif /* State_h */
