//character class header file
//this is the character class header file. It contains headers for all characters
#ifndef CHARACTERS_HPP
#define CHARACTERS_HPP

#include "space.hpp"
#include "item.hpp"
#include <iostream>
#include <queue>
using namespace std;

class Character : public Space
{
private:
  int HP;
  int ATK;
  int DEF;

public:
  Character() : Space()
  {
    this->setHP(0);
    this->setATK(0);
    this->setDEF(0);
  }

  virtual int attack();
  virtual void defend(int);

  int getHP()
  {return HP;}
  int getATK()
  {return ATK;}
  int getDEF()
  {return DEF;}

  void setHP(int str)
  {HP = str;}
  void setATK(int str)
  {ATK = str;}
  void setDEF(int str)
  {DEF = str;}

  bool isEmpty()
  {return false;}

  bool moveCheck()
  {return true;}
};

class Player : public Character
{
private:
  Item* sword;
  int bagSize;
  queue<Potion> bag;
  queue<Key> keys;
public:

  Player(int r, int col) : Character()
  {
    this->setHP(10);
    this->setATK(3);
    this->setDEF(2);
    this->bagSize = 3;
    this->setX(col);
    this->setY(r);
    this->sword = NULL;
    for(int i = 0; i < bagSize; i++)//start full
    {
      Potion temp;
      bag.push(temp);
    }
    if(keys.size() > 0)//keeps keys at 0 to start
    {
      for(int i = 0; i < keys.size(); i++)
        keys.pop();
    }
  }

  void setSword(Item* swrd);
  void usePotion();
  int useKey();
  void pickUpKey();
  void pickUpPotion();
  int getBagSize()
  {return bag.size();}
  int getKeysSize()
  {return keys.size();}


  int attack();
  Space* move(char);
  bool isPlayer()
  {return true;}
};

class Boss : public Character
{
private:
  bool secondPhase;
public:
  Boss(int r, int col) : Character()
  {
    this->setHP(20);
    this->setATK(5);
    this->setDEF(3);
    this->setX(col);
    this->setY(r);
    secondPhase = true;
  }

  int attack();
  void defend(int);
  bool isBoss()
  {return true;}
};

class Enemy : public Character
{
public:
  Enemy(int r, int col) : Character()
  {
    this->setHP(8);
    this->setATK(4);
    this->setDEF(2);
    this->setX(col);
    this->setY(r);
  }

  Space* move();
  bool isEnemy()
  {return true;}
};
#endif
