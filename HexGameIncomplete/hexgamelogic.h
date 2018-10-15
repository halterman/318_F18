#ifndef HEX_GAME_LOGIC_
#define HEX_GAME_LOGIC_

const int ROWS = 11;
// Total number of Hex cells
const int NUM_CELLS = ROWS * ROWS;

// The possible states of a Hex cell: The value indicates the cell's owner.
enum class Player { None, Blue, Red };

// The Hex game engine must interoperate with
// the game's presentation (GUI, in the case of this
// project).  The game engine expects a type that
// provides the following interface.
class HexCellInterface {
public:
	// The game engine must be able to see which player
	// owns the Hex cell
	virtual Player get_player() const = 0;
	// The game engine must be able to change the owner
	// of a Hex cell if it needs to
	virtual void set_player(Player p) = 0;
	// The game engine must be be able to make a move on 
	// behalf of a Hex cell
	virtual void move() = 0;
};


// The Hex game engine enforces the Hex rules ensuring that
// players cannot move into occupied cells or move to invalid cells 
// (attempt to use bad cell indices).  It also monitors the progress
// of the game and declares a winner when the game is over. 
class HexGameLogic {
	Player player;  // The player whose turn it is
	bool playing;   // True if the game is in progress; false when the game ends
public:
	// The constructor sets the blue player to start and ensures the
	// the game status is "playing."  Note: You should not call the reset
	// method in this constructor; the reset method attempts to clear the
	// the players associated with each Hex cell, but Hex cells may be 
	// added to the game board only after it has been created (see the
	// Hex cell constructor in the GUI code).
	HexGameLogic();

	// Returns the winner of the current game or Player::None if
	// neither player has yet won
	Player check_for_win();

	// Returns the player (Player::Blue or PLayer::Red) whose 
	// turn it is
	Player current_player() const;

	// Claims the Hex cell at the given index for the current player
	// if the cell currently is unoccupied.  If the move is possible,
	// and the move is not a winning move, the opposing player then 
	// takes control of the next move.
	void move(int index);

	// Positions the current player at an open cell pseudorandomly
	// chosen on the Hex game board
	void random_move();

	// Makes upton n pseudorandom moves during a Hex game. 
	// Makes fewer than n moves if a move results in a game
	// winnner.
	void random_move(int n);

	// Adds a Hex cell with index idx to the Hex board.
	void add_cell(int idx, HexCellInterface *cell);

	// Returns true if a player has won the game; otherwise, the
	// game is still in progress, and the method returns false
	bool game_over() const;

	// Reinitializes the Hex board to begin a new game:
	//  - The opening move should be the blue player's
	//  - All the associated Hex cells (in the GUI) should
	//    be empty (have no associated player)
	//  - All the sets in the disjoint set should have cardinality one
	//  - The game's status should be "playing"
	void reset();
};

#endif
