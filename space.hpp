//space header file
#ifndef SPACE_HPP
#define SPACE_HPP

#include "item.hpp"
#include <iostream>
using namespace std;

class Space
{
private:
  int x; //x coordinate
  int y; //y coordinate
  Space* up;
  Space* down;
  Space* left;
  Space* right;

public:
  friend class Game;
  Space()
  {
    x = 0;
    y = 0;
    up = NULL;
    down = NULL;
    left = NULL;
    right = NULL;
  }
  Space(int X, int Y, Space* Up, Space* Down, Space* Left, Space* Right)
  {
    x = X;
    y = Y;
    up = Up;
    down = Down;
    left = Left;
    right = Right;
  }

  void setX(int X)
  {this->x = X;}
  void setY(int Y)
  {this->y = Y;}

  int getX()
  {return x;}
  int getY()
  {return y;}

  //keeping this for now so space is abstract
  //Honestly think this would be easier if it wasn't
  virtual bool moveCheck() = 0;


  //virtuals: i think i need to read more about inheritance
  virtual bool isSpace()
  {return true;}
  virtual bool isFlag()
  {return false;}
  virtual bool isFloor()
  {return false;}
  virtual bool isWall()
  {return false;}
  virtual bool isGate()
  {return false;}
  virtual bool isBoss()
  {return false;}
  virtual Space* move()
  {return NULL;}
  virtual bool isEmpty()
  {return false;}
  virtual bool isChest()
  {return false;}
  virtual bool isEnemy()
  {return false;}
  virtual bool isPlayer()
  {return false;}
  virtual Item* getTreasure()
  {return NULL;}
  virtual int attack()
  {return 0;}
  virtual void defend(int)
  {return;}
  virtual int getHP()
  {return 0;}

  Space* getUp()
  {return up;}
  Space* getDown()
  {return down;}
  Space* getLeft()
  {return left;}
  Space* getRight()
  {return right;}

  void setUp(Space* Up)
  {
    this->up = Up;
  }
  void setDown(Space* Down)
  {
    this->down = Down;
  }
  void setLeft(Space* Left)
  {
    this->left = Left;
  }
  void setRight(Space* Right)
  {
    this->right = Right;
  }
};

class Floor : public Space
{
public:
  Floor(int r, int col) : Space()
  {
    this->setY(r);
    this->setX(col);
  }

  bool isFloor()
  {return true;}
  bool isEmpty()
  {return true;}
  bool moveCheck()
  {return true;}
};

class Wall : public Space
{
private:
  bool canMove;

public:
  Wall(int r, int col) : Space()
  {
    canMove = false;
    this->setY(r);
    this->setX(col);
  }

  bool isWall()
  {return true;}
  bool isEmpty()
  {return false;}
  bool moveCheck()
  {return canMove;}
};

class Chest : public Space
{
private:
  Item* treasure;
public:
  Chest(int r, int col, Item* t) : Space()
  {
    treasure = t;
    this->setX(col);
    this->setY(r);
  }

  bool isChest()
  {return true;}
  bool isEmpty()
  {
    if(treasure != NULL)
      return false;
    else
      return true;
  }
  bool moveCheck()
  {return false;}

  Item* getTreasure()
  {return treasure;}
};

class Gate : public Space
{
public:
  Gate(int r, int col) : Space()
  {
    this->setX(col);
    this->setY(r);
  }

  bool isGate()
  {return true;}
  bool moveCheck()
  {return false;}
};

class Flag : public Space
{
public:
  Flag(int r, int col) : Space()
  {
    this->setX(col);
    this->setY(r);
  }

  bool isFlag()
  {return true;}
  bool moveCheck()
  {return true;}
};
#endif
