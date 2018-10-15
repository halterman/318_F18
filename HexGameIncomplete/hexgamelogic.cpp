#include "HexGameLogic.h"
#include "disjointset.h"
#include <array>

// Used to determine when a player has created a winning path
// on the Hex game board
static DisjointSet<NUM_CELLS> disjoint_set;

// The Hex board consists of a collection of NUM_CELLS Hex cells
// This array allows the game engine to access the cell objects
// in the program's presentation.
static std::array<HexCellInterface *, NUM_CELLS> cells;

// The constructor sets the blue player to start and ensures the
// the game status is "playing."  Note: You should not call the reset
// method in this constructor; the reset method attempts to clear the
// the players associated with each Hex cell, but Hex cells may be 
// added to the game board only after it has been created (see the
// Hex cell constructor in the GUI code).
HexGameLogic::HexGameLogic() {
	// Implement as needed (but add a constructor initialization
	// list to do it right!)
}

// If the current board configuration contains a winning path for
// a player, this function returns that player; otherwise, the 
// function returns Player::None if neither player has yet won.
Player HexGameLogic::check_for_win() {
	return Player::None;  // Replace with your code
}

// Claims the Hex cell at the given index for the current player
// if the cell currently is unoccupied.  If the move is possible,
// and the move is not a winning move, the opposing player then 
// takes control of the next move.
void HexGameLogic::move(int index) {
	// Add your code
	cells[index]->set_player(Player::Blue);
}

// Positions the current player at an open cell pseudorandomly
// chosen on the Hex game board
void HexGameLogic::random_move() {
	// Add your code
}

// Makes upton n pseudorandom moves during a Hex game. 
// Makes fewer than n moves if a move results in a game
// winnner.
void HexGameLogic::random_move(int n) {
	// Add your code
}

// Adds a Hex cell with index idx to the Hex board.
// Also adds it to the disjoint set used to detect a 
// game winner.
void HexGameLogic::add_cell(int idx, HexCellInterface *cell) {
	// Add your code
	cells[idx] = cell;
}

// Returns the player (Player::Blue or PLayer::Red) whose 
// turn it is
Player HexGameLogic::current_player() const {
	return Player::None;   // Replace with your code
}

// Returns true if a player has won the game; otherwise, the
// game is still in progress, and the method returns false
bool HexGameLogic::game_over() const {
	return false;  // Replace with your code
}

// Resets the Hex board to begin a new game:
//  - The opening move should be the blue player's
//  - All the associated Hex cells (in the GUI) should
//    be empty (have no associated player)
//  - All the sets in the disjoint set should have cardinality one
//  - The game's status should be "playing"
void HexGameLogic::reset() {
	// Add your code
}