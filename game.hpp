//game class header file
/*this class is a combination of previous menu and board classes.
The goal is to correct past mistakes (group project) and simplify
how I create, maintain, and traverse space in games.
The class will contain the Space board, handle all IO with player*/
#ifndef GAME_HPP
#define GAME_HPP
#include "space.hpp"
#include "character.hpp"
#include "item.hpp"
#include <string>

using std::string;

class Game
{
private:
  int bossToken;
  int rows;
  int columns;
  bool WIN_CONDITION;
  Space*** gameBoard;
  Player* Vio;
  Boss* boss;
  Item* xSaber;

  int input;

public:
  Game();
  ~Game();

  void displayBoard();//prints gameBoard
  void displayMenu();//displays Game intro menu (play or quit)
  int getInput();//

  void movePlayer();
  void moveEnemies();
  void battle(Space*);//displays combat menu during combat sequences
  void bossBattle();
  void updatePointers();
  void placeEnemy(int, int);
  void placeChest(int, int, Item*);
  void placeBoss(int, int);
  void updateBoard();

  int getInt(int);
  char getChar();
  string getString();
  double getDouble(int);

  void setWin(bool tf)
  {
    WIN_CONDITION = tf;
  }

  bool getWin()
  {return WIN_CONDITION;}

  int getVioHP()
  {
    return Vio->getHP();
  }
  Space* getVio()
  {
    return Vio;
  }
};
#endif
