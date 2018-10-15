
#include <GL/sgl.hpp>
#include "hexgamelogic.h"

// The game engine that controls the flow of the game and
// determines a winner.
HexGameLogic engine;

const double WINDOW_WIDTH = 800.0;
// The scaling factor
// (more rows mean smaller cells)
const double SCALE = WINDOW_WIDTH / (3.2*ROWS);


// The visual representation of a Hex game cell.  Draws the hexagonal
// cell, provides visual feedbak to users (players), and cooperates with
// the Hex game engine to provide a graphical user interface to a 
// Hex game. 
class HexCell : public sgl::GraphicalObject, public HexCellInterface {
	int index;        // This cell's index within the Hex board 
	Player player;    // The player owning this cell

	// Precompute some trigonometric functions speed up the runtime.
	// These are static, so they are precomputed once when the program
	// begins running.
	static const double SIN30;
	static const double COS30;

	// Scaled unit circle point positions for the hexagon vertices
	// These are static, so they are precomputed once when the program
	// begins running.
	static const sgl::Point TOP_VERTEX;
	static const sgl::Point UPPER_LEFT_VERTEX;
	static const sgl::Point LOWER_LEFT_VERTEX;
	static const sgl::Point BOTTOM_VERTEX;
	static const sgl::Point LOWER_RIGHT_VERTEX;
	static const sgl::Point UPPER_RIGHT_VERTEX;

	// Width of a hexagonal cell
	static const double WIDTH;

public:
	// Map a Hex grid cell address (row, column) to a point (x, y)
	// in the graphics window.  Returns a graphical point.
	static sgl::Point location_to_point(int row, int column) {
		//double x = START_X + WIDTH * column + START_Y + 0.5*WIDTH*row,
		// Where the row 0, column 0 cell of the Hex game board appears in the window 
		static const double START_X = SCALE * ROWS; // 200.0; // 15.0;
		static const double START_Y = 70.0; // 100.0; // 10 * ROWS;  // 70.0;
		double x = START_X + WIDTH * column + START_Y - 0.5*WIDTH*row,
			y = START_Y + 1.5*SCALE * row;
		return { x, y };
	}

	HexCell(int idx) :
		GraphicalObject(idx / ROWS, idx%ROWS, 0.8*WIDTH, 0.8*WIDTH), index(idx),
		player(Player::None) {
		auto p = location_to_point(index / ROWS, index%ROWS);
		double center_x = p.x;
		double center_y = p.y;
		left = center_x - WIDTH * 0.4;
		bottom = center_y - WIDTH * 0.4;
		// Register this new graphical Hex game cell with the game engine
		engine.add_cell(index, this);
	}

	//int get_index() const override { return index; }

	// Returns this cell's current owner (Player::None if no one)
	Player get_player() const override { return player; }

	// Assigns an owner (blue or red) to this cell
	void set_player(Player p) override {
		player = p;
	}

	// Renders the cell within a graphical window
	void paint() const override {
		switch (player) {
			case Player::Blue:
				sgl::set_color(sgl::BLUE); break;
			case Player::Red:
				sgl::set_color(sgl::RED); break;
			default:
				if (mouse_over)
					if (engine.current_player() == Player::Blue)
						sgl::set_color(sgl::LIGHT_BLUE);
					else
						sgl::set_color(sgl::LIGHT_RED);
				else
					sgl::set_color(sgl::WHITE);
				break;
		}
		auto p = location_to_point(index / ROWS, index%ROWS);
		double center_x = p.x;
		double center_y = p.y;
		std::vector<sgl::Point> points;
		points.push_back({ TOP_VERTEX.x + center_x, TOP_VERTEX.y + center_y });
		points.push_back({ UPPER_LEFT_VERTEX.x + center_x, UPPER_LEFT_VERTEX.y + center_y });
		points.push_back({ LOWER_LEFT_VERTEX.x + center_x, LOWER_LEFT_VERTEX.y + center_y });
		points.push_back({ BOTTOM_VERTEX.x + center_x, BOTTOM_VERTEX.y + center_y });
		points.push_back({ LOWER_RIGHT_VERTEX.x + center_x, LOWER_RIGHT_VERTEX.y + center_y });
		points.push_back({ UPPER_RIGHT_VERTEX.x + center_x, UPPER_RIGHT_VERTEX.y + center_y });
		points.push_back({ TOP_VERTEX.x + center_x, TOP_VERTEX.y + center_y });
		sgl::fill_polygon(points);

		// Draw Hex cell frame
		sgl::set_color(sgl::BLACK);
		sgl::draw_polygon(points);
	}

	// Assigns this cell's owner to the current player, but only if
	// the cell does not have a preexisting owner.
	void move() override {
		if (player == Player::None) {
			//player = engine.current_player();
			engine.move(index);
			switch (engine.check_for_win()) {
				case Player::Blue:
					get_window()->set_title("Blue Wins!"); break;
				case Player::Red:
					get_window()->set_title("Red Wins!"); break;
			}
		}
	}


	// Makes a move to this cell.
	void mouse_pressed(double, double, sgl::MouseButton) override {
		if (!engine.game_over() && player == Player::None) {
			move();
			//std::cout << "index = " << index << '\n';
		}
	}

	// Ensures a cell knows when the mouse cursor is over it.
	// Enables the GUI to provide feedback to the user about
	// which cell may be chosen and which player would be its
	// potential owner.
	void mouse_moved(double x, double y) override {
		//std::cout << "x = " << x << ", y = " << y << '\n';
		if (hit(x, y)) {
			mouse_over = true;
		}
		else {
			mouse_over = false;
		}
	}
};


// Initialize HexCell class constants

const double HexCell::SIN30 = 0.5;
const double HexCell::COS30 = 0.866;
//const double HexCell::SCALE = 20.0;
// Scaled unit circle point positions for the hexagon vertices
const sgl::Point HexCell::TOP_VERTEX{ 0.0   * SCALE,  1.0 * SCALE };
const sgl::Point HexCell::UPPER_LEFT_VERTEX{ -COS30 * SCALE,  SIN30 * SCALE };
const sgl::Point HexCell::LOWER_LEFT_VERTEX{ -COS30 * SCALE, -SIN30 * SCALE };
const sgl::Point HexCell::BOTTOM_VERTEX{ 0.0   * SCALE, -1.0 * SCALE };
const sgl::Point HexCell::LOWER_RIGHT_VERTEX{ COS30 * SCALE, -SIN30 * SCALE };
const sgl::Point HexCell::UPPER_RIGHT_VERTEX{ COS30 * SCALE,  SIN30 * SCALE };
// Width of a hexagonal cell
const double HexCell::WIDTH = 2 * COS30 * SCALE;

// The graphical window in which players play a Hex game.
class HexWindow : public sgl::ObjectWindow {
public:
	HexWindow() : ObjectWindow("Hex", 0.0, WINDOW_WIDTH, 0.0, 0.6*WINDOW_WIDTH) {
		for (int idx = 0; idx < NUM_CELLS; idx++)
			add(new HexCell(idx));
	}
	// Draws the borders for the Hex game (the individual Hex cells
	// draw themselves)
	void paint() override {
		sgl::set_color(sgl::BLUE);
		static const int HIGH = ROWS - 1;
		auto p1 = HexCell::location_to_point(0, 0);
		auto p2 = HexCell::location_to_point(HIGH, 0);
		auto p3 = HexCell::location_to_point(ROWS, -1);
		auto p4 = HexCell::location_to_point(-1, -1);
		sgl::fill_polygon({ p1, p2, p3,  p4 });
		p1 = HexCell::location_to_point(0, HIGH);
		p2 = HexCell::location_to_point(HIGH, HIGH);
		p3 = HexCell::location_to_point(ROWS, ROWS);
		p4 = HexCell::location_to_point(-1, ROWS);
		sgl::fill_polygon({ p1, p2, p3,  p4 });
		sgl::set_color(sgl::RED);
		p1 = HexCell::location_to_point(0, HIGH);
		p2 = HexCell::location_to_point(-1, ROWS);
		p3 = HexCell::location_to_point(-1, -1);
		p4 = HexCell::location_to_point(0, 0);
		sgl::fill_polygon({ p1, p2, p3,  p4 });
		p1 = HexCell::location_to_point(HIGH, 0);
		p2 = HexCell::location_to_point(ROWS, -1);
		p3 = HexCell::location_to_point(ROWS, ROWS);
		p4 = HexCell::location_to_point(HIGH, HIGH);
		sgl::fill_polygon({ p1, p2, p3,  p4 });
	}

	// Provides user access via the keyboard to special functions
	// (random moves) 
	void key_pressed(int k, double x, double y) {
		switch (k) {
			case 'm':
			case 'M':
				engine.random_move();
				break;
			case 'r':
			case 'R':
				engine.random_move(100);
				break;
			case 27:   // Ecsape key 
				clear_board();
				break;
			default:
				ObjectWindow::key_pressed(k, x, y);
				break;
		}
		repaint();
	}

	// Resets the Hex board in preparation for a new game.
	void clear_board() {
		engine.reset();    // Reinitializes the game state
		set_title("Hex");  // Removes winner indication from window
		repaint();
	}
};



int main() {
	srand(42);   // Use a constant pseudorandom number seed for reproduceable testing

	sgl::run<HexWindow>();  // Start the program
}

