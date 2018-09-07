//game class implementation file
#include "game.hpp"
#include "space.hpp"
#include "character.hpp"
#include "item.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

Game::Game()
{
  bossToken = 1;
  input = 0;
  WIN_CONDITION = false;
  rows = 20;
  columns = 40;
  boss = NULL;

  //initialize board as blank floor
  gameBoard = new Space**[rows];
  for(int i = 0; i < rows; ++i)
  {
    gameBoard[i] = new Space* [columns];
    for(int n = 0; n < columns; ++n)
    {
      gameBoard[i][n] = NULL;
    }
  }

  //create walls
  for(int i = 0; i < rows; i++)
  {
    for(int n = 0; n < columns; n++)
    {
      if(i == 0 && (n > 10 && n < 30))//upper boundary
        gameBoard[i][n] = new Wall(i, n);
      if(i == 19 && (n > 10 && n < 30))//lower boundary
        gameBoard[i][n] = new Wall(i, n);
      if(n == 0)//left boundary
        gameBoard[i][n] = new Wall(i, n);
      if(n == 39 && (i > 6 && i < 12))//right boundary
        gameBoard[i][n] = new Wall(i, n);

      //the above lines were causing memory leaks, so I had to redo the boundaries.
      //REMEMBER TO ALWAYS CHECK BOARD FOR LEAKS


      if((i >= 0 && i <= 6) && (n > 0 && n <= 10))//upper left
        gameBoard[i][n] = new Wall(i, n);
      if((i >= 0 && i <= 6) && (n >= 30 && n < 40))//upper right
        gameBoard[i][n] = new Wall(i, n);
      if((i >= 12 && i < 20) && (n > 0 && n <= 10))//bottom left
        gameBoard[i][n] = new Wall(i, n);
      if((i >= 12 && i < 20) && (n >= 30 && n < 40))//bottom right
        gameBoard[i][n] = new Wall(i, n);
      if((i > 6 && i < 12) && (n == 30))//wall blocking boss room
        gameBoard[i][n] = new Gate(i, n);
    }
  }

  //place player
  Vio = new Player(9, 5);
  gameBoard[9][5] = Vio;

  //place chest
  xSaber = new Weapon(5);
  gameBoard[9][20] = new Chest(9, 20, xSaber);

  //place initial enemies
  gameBoard[15][15] = new Enemy(15, 15);
  gameBoard[3][15] = new Enemy(3, 15);
  gameBoard[15][25] = new Enemy(15, 25);
  gameBoard[3][25] = new Enemy(3, 25);

  //place flag
  gameBoard[9][35] = new Flag(9, 35);

  //fill in rest with floor
  for(int i = 0; i < rows; i++)
  {
    for(int n = 0; n < columns; n++)
    {
      if(gameBoard[i][n] == NULL)
        gameBoard[i][n] = new Floor(i, n);
    }
  }
}

Game::~Game()
{
  for(int i = 0; i < rows; i++)
  {
    for(int n = 0; n < columns; n++)
    {
      if(gameBoard[i][n] != NULL && !gameBoard[i][n]->isPlayer() && !gameBoard[i][n]->isBoss())
      {
        delete gameBoard[i][n];
        gameBoard[i][n] = NULL;
      }
    }
    delete[] gameBoard[i];
    gameBoard[i] = NULL;
  }
  delete[] gameBoard;
  gameBoard = NULL;

  delete xSaber;

  if(Vio != NULL)
  {
    delete Vio;
  }

  if(boss != NULL)
  {
    delete boss;
  }
}

void Game::displayBoard()
{
  for (int r = 0; r < rows; r++)
  {
   for (int col = 0; col < columns; col++)
   {
      if(gameBoard[r][col]->isFloor())//plain space
        cout << " " << " ";
      else if(gameBoard[r][col]->isPlayer())//player
        cout << "O" << " ";
      else if(gameBoard[r][col]->isChest())//chest
        cout << "C" << " ";
      else if(gameBoard[r][col]->isWall())//wall
        cout << "|" << " ";
      else if(gameBoard[r][col]->isEnemy())//Enemy
        cout << "@" << " ";
      else if(gameBoard[r][col]->isBoss())//boss
        cout << "B" << " ";
      else if(gameBoard[r][col]->isGate())//gate
        cout << "#" << " ";
      else if(gameBoard[r][col]->isFlag())//Flag
        cout << "F" << " ";
    }
   cout << " : " << r;
   cout << endl;
   }
}

void Game::displayMenu()
{
  cout << "1. Play game\n";
  cout << "2. Quit\n";
  int num;
  string str = "";
  while(true)
  {
    getline(cin, str);
    stringstream convert(str);

    if(convert >> num && !(convert >> str) && (num > 0 && num <= 2))
    {
      input = num;
      return;
    }

    cin.clear();
    cerr << "Input is not valid, please try again.\n";
  }
}

int Game::getInput()
{
  return input;
}

char Game::getChar()
{
  char yn;
  string str;
  while(true)
  {
    getline(cin, str);
    stringstream convert(str);

    if(convert >> yn && !(convert >> str) && (yn == 'y' || yn == 'n'))
      return yn;

    cin.clear();
    cerr << "Input is not valid, please try again.\n";
  }
}

int Game::getInt(int max)
{
  int num;
  string str = "";
  while(true)
  {
    getline(cin, str);
    stringstream convert(str);

    if(convert >> num && !(convert >> str) && (num >= 0 && num <= max))
      return num;

    cin.clear();
    cerr << "Input is not valid, please try again.\n";
  }
}

string Game::getString()
{
  string content = "";
  string str = "";
  while (true)
  {
    getline(cin, str);

    if(str.find_first_of("1234567890") == std::string::npos)
      return str;

    cin.clear();
    cerr << "Input is not valid, please try again.\n";
  }
}

double Game::getDouble(int max)
{
  string str = "";
  double num;
  while(true)
  {
    getline(cin, str);
    stringstream convert(str);

    if((convert >> num) && !(convert >> str) && (num > 0.00 && num <= max))
    {

      return num;
    }

    cin.clear();
    cerr << "Input is not valid, please try again.\n";
  }
}

void Game::movePlayer()
{
  Space* direction;
  char yn;
  char WASD;
  string str;
  cout <<"Which direction would you like to move? (WASD)\n";
  cout << "Enter the letter q to quit the game\n";
  while(true)
  {
    getline(cin, str);
    stringstream convert(str);

    if(str == "q")
    {
      Vio->setHP(0);
      return;
    }

    if(convert >> WASD && !(convert >> str) && (WASD == 'w' || WASD == 'a' || WASD == 's' || WASD == 'd'))
      {
        direction = Vio->move(WASD);
        break;
      }

    cin.clear();
    cerr << "Input is not valid, please try again.\n";
  }

  if(direction != NULL && direction->isFloor())//floor spaces
  {
    int newX = direction->getX();
    int newY = direction->getY();
    int oldX = Vio->getX();
    int oldY = Vio->getY();

    Space* temp = gameBoard[oldY][oldX];
    gameBoard[oldY][oldX] = gameBoard[newY][newX];
    gameBoard[newY][newX] = temp;
    return;
  }

  else if(direction != NULL && direction->isChest())//chest
  {
    cout << "You have opened the chest!\n";
    Vio->setSword(direction->getTreasure());
    cout << "You found the X-Blade!\n";

    //delete chest
    int chestX = direction->getX();
    int chestY = direction->getY();
    delete gameBoard[chestY][chestX];
    gameBoard[chestY][chestX] = new Floor(chestY, chestX);
    return;
  }

  else if(direction != NULL && direction->isEnemy())//enemy
  {
    this->battle(direction);

    if(direction->getHP() <= 0)//enemy dies
    {
      int newX = direction->getX();
      int newY = direction->getY();

      cout << "You have killed the spectre!\n";
      delete gameBoard[newY][newX];
      gameBoard[newY][newX] = new Floor(newY, newX);
      return;
    }
  }

  else if(direction != NULL && direction->isBoss())//boss
  {
    this->bossBattle();

    if(direction->getHP() <= 0)//enemy dies
    {
      int newX = direction->getX();
      int newY = direction->getY();

      cout << "You have killed the Boss!\n";
      gameBoard[newY][newX] = new Floor(newY, newX);
      return;
    }
  }

  else if(direction != NULL && direction->isGate() && Vio->getKeysSize() == 0)
    cout << "You need a key to open this gate\n";

  else if(direction != NULL && direction->isGate() && Vio->getKeysSize() > 0 && (Vio->useKey() % 2 != 0))//gate
  {
    /*I could have designed a function here to clear the gate
    using the Space pointers, but i got lazy. Will probably do it next time
    if I make more than 1 gate*/
    for(int i = 7; i < 12; i++)
    {
      if(gameBoard[i][30] != NULL && gameBoard[i][30]->isGate())
      {
        delete gameBoard[i][30];
        gameBoard[i][30] = new Floor(i, 30);
      }
    }
  }

  else if(direction != NULL && direction->isFlag())//flag, end game
  {
    cout << "You have beat the game!\n";
    cout << "Congrats! Thanks for playing!\n";
    this->setWin(true);
  }
}

void Game::updatePointers()//this function updates all the space pointers
{
  for(int i = 0; i < rows; ++i)
  {
    for(int n = 0; n < columns; ++n)//sets all character's locations
    {
      gameBoard[i][n]->setX(n);
      gameBoard[i][n]->setY(i);

      if(i == 0 && n == 0)//top left corner
      {
        gameBoard[i][n]->setDown(gameBoard[i+1][n]);
        gameBoard[i][n]->setRight(gameBoard[i][n+1]);
      }
      else if(i == 0 && n == 39)//top right
      {
        gameBoard[i][n]->setDown(gameBoard[i+1][n]);
        gameBoard[i][n]->setLeft(gameBoard[i][n-1]);
      }
      else if(i == 19 && n == 0)//bottom left
      {
        gameBoard[i][n]->setRight(gameBoard[i][n+1]);
        gameBoard[i][n]->setUp(gameBoard[i-1][n]);
      }
      else if(i == 19 && n == 39)//bottom right
      {
        gameBoard[i][n]->setUp(gameBoard[i-1][n]);
        gameBoard[i][n]->setLeft(gameBoard[i][n-1]);
      }
      else if(i == 0 && n > 0 && n < 39)//top row - corners
      {
        gameBoard[i][n]->setDown(gameBoard[i+1][n]);
        gameBoard[i][n]->setRight(gameBoard[i][n+1]);
        gameBoard[i][n]->setLeft(gameBoard[i][n-1]);
      }
      else if(i == 19 && n > 0 && n < 39)//bottom row - corners
      {
        gameBoard[i][n]->setRight(gameBoard[i][n+1]);
        gameBoard[i][n]->setLeft(gameBoard[i][n-1]);
        gameBoard[i][n]->setUp(gameBoard[i-1][n]);
      }
      else if(n == 0 && i > 0 && i < 19)//left column - corners
      {
        gameBoard[i][n]->setRight(gameBoard[i][n+1]);
        gameBoard[i][n]->setUp(gameBoard[i-1][n]);
        gameBoard[i][n]->setDown(gameBoard[i+1][n]);
      }
      else if(n == 39 && i > 0 && i < 19)//right column - corners
      {
        gameBoard[i][n]->setDown(gameBoard[i+1][n]);
        gameBoard[i][n]->setLeft(gameBoard[i][n-1]);
        gameBoard[i][n]->setUp(gameBoard[i-1][n]);
      }
      if(i != 0 && i != 19 && n != 0 && n != 39) // rest
      {
        gameBoard[i][n]->setDown(gameBoard[i+1][n]);
        gameBoard[i][n]->setRight(gameBoard[i][n+1]);
        gameBoard[i][n]->setUp(gameBoard[i-1][n]);
        gameBoard[i][n]->setLeft(gameBoard[i][n-1]);
      }
    }
  }
}

void Game::battle(Space* enemy)
{
  int num;
  int playerATK;
  int enemyATK;
  do {
    cout << "\n";
    cout << "1. Attack\n";
    cout << "2. Use Item\n";
    cout << "3. Run\n";
    cout << "\n";
    string str = "";
    while(true)
    {
      getline(cin, str);
      stringstream convert(str);

      if(convert >> num && !(convert >> str) && (num > 0 && num <= 3))
      {
        input = num;
        break;
      }

      cin.clear();
      cerr << "Input is not valid, please try again.\n";
    }

    if(num == 1)//attack
    {
      playerATK = Vio->attack();
      cout << "Vio attacked with " << playerATK << " damage!\n";
      enemy->defend(playerATK);
      cout << "The spectre now has " << enemy->getHP() << " HP\n";
    }

    if(num == 2)//use item
    {
      Vio->usePotion();
    }

    if(enemy->getHP() > 0)
    {
      enemyATK = enemy->attack();
      cout << "The spectre attacked with " << enemyATK << " damage!\n";
      Vio->defend(enemyATK);
      cout << "Vio now has " << Vio->getHP() << " HP\n";
    }
  } while(enemy->getHP() > 0 && num != 3 && Vio->getHP() > 0);

  if(Vio->getHP() <= 0)
  {
    cout << "Vio has died! Game Over!\n";

    this->setWin(true);
    return;
  }

  if(Vio->getBagSize() < 3 && enemy->getHP() <= 0)//if bag is not full
  {
    int rand100 = rand() % 100 + 1;
    if(rand100 < 35) //35% chance for potion, change for ease of completion
    {
      cout << "The spectre dropped a potion\n";
      Vio->pickUpPotion();
      cout << "You now have " << Vio->getBagSize() << " potions!\n";
    }
  }
}

void Game::bossBattle()
{
  int num;
  int playerATK;
  int bossATK;
  do {
    cout << "\n";
    cout << "1. Attack\n";
    cout << "2. Use Item\n";
    cout << "\n";
    string str = "";
    while(true)
    {
      getline(cin, str);
      stringstream convert(str);

      if(convert >> num && !(convert >> str) && (num > 0 && num <= 2))
      {
        input = num;
        break;
      }

      cin.clear();
      cerr << "Input is not valid, please try again.\n";
    }

    if(num == 1)//attack
    {
      playerATK = Vio->attack();
      cout << "Vio attacked with " << playerATK << " damage!\n";
      boss->defend(playerATK);
      cout << "Myke now has " << boss->getHP() << " HP\n";
    }

    if(num == 2)//use item
    {
      Vio->usePotion();
    }

    if(boss->getHP() > 0)
    {
      bossATK = boss->attack();
      cout << "Myke attacked with " << bossATK << " damage!\n";
      Vio->defend(bossATK);
      cout << "Vio now has " << Vio->getHP() << " HP\n";
    }

  } while(boss->getHP() > 0 && Vio->getHP() > 0);

  if(Vio->getHP() <= 0)
  {
    cout << "Vio has died! Game Over!\n";
    this->setWin(true);
    return;
  }

  if(boss->getHP() <= 0)
  {
    cout << "Myke dropped a key,\n";
    Vio->pickUpKey();
    cout << "You now have " << Vio->getKeysSize() << " keys!\n";

    gameBoard[9][5] = new Floor(9, 5);
  }
}

void Game::moveEnemies()
{
  Space* direction;
  for(int i = 0; i < rows; i++)
  {
    for(int n = 0; n < columns; n++)
    {
      if(gameBoard[i][n]->isEnemy())
      {
        direction = gameBoard[i][n]->move();

        if(direction != NULL && direction->isEmpty())//floor
        {
          int newX = direction->getX();
          int newY = direction->getY();

          Space* temp = gameBoard[i][n];
          gameBoard[i][n] = gameBoard[newY][newX];
          gameBoard[newY][newX] = temp;
        }
        else if(direction != NULL && direction->isPlayer())//player
        {
          this->battle(gameBoard[i][n]);

          if(gameBoard[i][n]->getHP() <= 0)//enemy dies
          {
            int newX = gameBoard[i][n]->getX();
            int newY = gameBoard[i][n]->getY();

            cout << "You have killed the spectre!\n";
            delete gameBoard[newY][newX];
            gameBoard[newY][newX] = new Floor(newY, newX);
          }
          return;
        }
      }
    }
  }
}

void Game::placeEnemy(int r, int col)
{
  delete gameBoard[r][col];
  gameBoard[r][col] = new Enemy(r, col);
}

void Game::placeBoss(int r, int col)
{
  delete gameBoard[r][col];
  gameBoard[r][col] = NULL;
  boss = new Boss(r, col);
  gameBoard[r][col] = boss;
}

void Game::placeChest(int r, int col, Item* temp)
{
  delete gameBoard[r][col];
  gameBoard[r][col] = new Chest(r, col, temp);
}

/*this function is used to create the second phase of the game
after you kill all the initial enemies, it places the boss*/
void Game::updateBoard()
{
  int enemies = 0;
  for(int i = 0; i < rows; i++)
  {
    for(int n = 0; n < columns; n++)
    {
      if(gameBoard[i][n]->isEnemy())
        enemies++;
    }
  }

  if(enemies == 0 && Vio->getKeysSize() == 0 && bossToken == 1)//if all enemies are dead, place boss
    {
      this->placeBoss(9, 5);
      bossToken--;
    }
}
