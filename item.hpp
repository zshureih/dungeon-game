//item header file
#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>
using namespace std;

class Item
{
  friend class Character;
  int quantity;
public:
  Item()
  {quantity = 1;}

  virtual int use() = 0;

};

class Weapon : public Item
{
private:
  int damage;
public:
  Weapon(int d) : Item()
  {damage = d;}

  int use()
  {return damage;}
};

class Potion : public Item
{
private:
  int healing;
public:
  Potion() : Item()
  {healing = 5;}

  int use()
  {return healing;}
};

class Key : public Item
{
private:
  int ID;
public:
  Key() : Item()
  {ID = (2 * rand() % 2) + 1;}
  //I make ID a random odd int as a lame attempt to create some sort of "secrurity"
  int use()
  {return ID;}

};
#endif
