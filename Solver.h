//
//  Solver.h
//  Shreya Wagley
//

#ifndef Solver_h
#define Solver_h
#include "State.h"

#include <queue>
#include <vector>
#include <set>
using namespace std;

class Solver {
private:
    State current_state;

public:
    // Constructor taking an initial state
    Solver(State initial_state) : current_state(initial_state) {
        // Set the current state to the provided initial state
        current_state = initial_state;
    }
    
    // Function to perform a search using a specified algorithm
    void search(int block, int destRow, int destCol);

    // Function to perform A* search
    void AStarSearch(int block, int destRow, int destCol);
};


void Solver::search(int block, int destRow, int destCol) {
    
      // Create a queue to hold the states to be explored
      queue<State> frontier;
      // Add the initial state to the frontier
      frontier.push(current_state);
      // Create a vector to store explored states
      vector<State> explored;

      int step = 0;//
      while ( step < 101 && !frontier.empty()) {
          // Get the next state from the queue
          current_state = frontier.front();
          frontier.pop();

          // Check if the current state is the goal state
          if (current_state.getBlockRow(block) == destRow && current_state.getBlockCol(block) == destCol) {
              cout << "Step " << step << ":" << endl;
              current_state.printBoard();
              current_state.pushDown();
              cout << "GOAL ACHIEVED!!! Block " << block << " moved to (" << destRow << ", " << destCol << ") in " << step << " steps." << endl;
              return;
          }
          
          // Print the current state and step number
          cout << "Step " << step << ":" << endl;
          current_state.printBoard();
          current_state.pushDown();

          // Get the valid moves from the current state
          vector<State> valid_moves = current_state.getValidMoves();

          // Check each valid move
          for (State move : valid_moves) {
              // Check if the move has already been explored
              bool is_explored = false;
              for (State state : explored) {
                  if (state == move) {
                      is_explored = true;
                      break;
                  }
              }
              if (!is_explored) {
                  // Add the move to the frontier if it hasn't been explored
                  frontier.push(move);
              }
          }
          step++;
      }
      cout << "Failed to move block " << block << " to (" << destRow << ", " << destCol << ") within in " << step << " steps" << endl << "or all possible states explored so search terminated to avoid back and forth." << endl;
  }

void Solver::AStarSearch(int block, int destRow, int destCol) {
    // Create a priority queue to hold the states to be explored
    priority_queue<pair<int, State>, vector< pair< int, State > >, greater< pair< int, State > > > frontier;
    // Add the initial state to the frontier with a priority of 0
    frontier.push(make_pair(0, current_state));
    // Create a set to store explored states
    set<State> explored;

    int step = 0;
    while (step < 101 && !frontier.empty()) {
        // Get the next state from the queue
        current_state = frontier.top().second;
        frontier.pop();

        // Check if the current state is the goal state
        if (current_state.getBlockRow(block) == destRow && current_state.getBlockCol(block) == destCol) {
            cout << "Step " << step << ":" << endl;
            current_state.printBoard();
            current_state.pushDown();
            cout << "GOAL ACHIEVED!!! Block " << block << " moved to (" << destRow << ", " << destCol << ") in " << step << " steps." << endl;
            return;
        }

        // Print the current state and step number
        cout << "Step " << step << ":" << endl;
        current_state.printBoard();
        current_state.pushDown();

        // Get the valid moves from the current state
        vector<State> valid_moves = current_state.getValidMoves();

        // Check each valid move
        for (State move : valid_moves) {
            // Calculate the heuristic value for the move
            int h = move.manhattanDistance(block, destRow, destCol);
            // Calculate the total cost for the move
            int f = step + h;

            // Check if the move has already been explored
            if (explored.find(move) == explored.end()) {
                // Add the move to the frontier with the calculated priority
                frontier.push(make_pair(f, move));
                // Add the move to the explored states
                explored.insert(move);
            }
        }
        step++;
    }
    cout << "Failed to move block " << block << " to (" << destRow << ", " << destCol << ") within in " << step << " steps" << endl << "or all possible states explored so search terminated to avoid back and forth." << endl;
}

#endif /* Solver_h */






