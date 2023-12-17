// This module implements an Interpreter class which manages the game.

#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__
#include <memory>
#include <string>

#include "Human.h"
class Floor;
class Potion;
class Player;
class Cell;
class Interpreter {
   private:
    int floorNum;                    // Tracks which floor the player is on.
    std::unique_ptr<Floor> level;    // Stores the current Floor.
    std::shared_ptr<Player> player;  // Stores a pointer to the Player.
    int seed;                        // Stores the seed for randomization.
    std::string filename;
    bool dlc_enabled;
    // barrier gen check
    static bool barrier_noinput;
    const int b_seed = 3;

   public:
    // Basic Constructor.
    Interpreter(std::string filename = std::string(), int seed = 0);

    // Executes the given command for the player by calling the appropriate methods.
    void command(std::string cmd);

    // Starts new game or restarts existing game. Everything is reset.
    // Should also set values for fields [level] and [player] once floor is generated.
    void init();
    // Updates all Entities (primarily Enemies) on the floor. Returns a message describing results.
    std::string update();
    // Displays the game to output (Also calls out << Floor as part of this process).
    void display(std::string action);

    // Gets the cell in relation to the player the specified direction.
    //   if the cell is out of bounds, returns nullptr.
    Cell *getCellInDir(std::string direction);
    // Returns full direction name (North, South, East, West, etc.) from abbreviated (no, so, ea, we, etc.)
    std::string directionName(std::string direction);
    // Moves the player in the direction specified by the input string.
    void movePlayer(Cell *target);
    // Uses the potion given on the player.
    void usePotion(Potion *p);
    // Proceeds to the next floor. Updates floorNum.
    void nextFloor();

    // Basic Destructor.
    ~Interpreter();
};

#endif
