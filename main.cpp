//this is the main for the final project game: Gauntlet
#include <iostream>
#include "game.hpp"
#include "space.hpp"


using namespace std;

int main()
{
  cout << "Welcome to Gauntlet, a simple dungeon crawler demo!\n";
  cout << "The goal is to defeat all the enemies, then the boss\n";
  cout << "The game ends when you die, when you pass enter the flag space, or when time runs out\n";
  cout << "You have 100 steps to beat the game\n";

  //create game
  int input = 0;
  bool playAgain = true;
  char again;
  Game *gameIO = new Game();

  do {
    int steps = 0;
    gameIO->updatePointers();
    gameIO->displayMenu();
    input = gameIO->getInput();

    if(input == 1)//play game
    {
      while(!gameIO->getWin() && steps < 100)
      {
        steps++;
        cout << "Steps: " << steps << endl;
        gameIO->displayBoard();
        gameIO->movePlayer();

        if(gameIO->getVioHP() <= 0)
          break;

        gameIO->updatePointers();
        gameIO->moveEnemies();

        if(gameIO->getVio() <= 0)
          break;

        gameIO->updatePointers();
        gameIO->updateBoard();
      }

      if(steps == 100)
        cout << "You ran out of time, game over!\n";

      cout << "Would you like to play again?\n";
      again = gameIO->getChar();

      if(again == 'n')
        playAgain = false;
      else
        delete gameIO;
        gameIO = new Game();
    }

    if(input == 2)
      playAgain = false;
  } while(playAgain);

  if(gameIO != NULL)
    delete gameIO;

  return 0;
}
