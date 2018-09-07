//character implementation file
#include "character.hpp"
#include "space.hpp"
#include <iostream>

using namespace std;

int Player::attack()
{
  if(sword != NULL)
    return this->getATK() + sword->use();
  else
    return this->getATK();
}

Space* Player::move(char WASD)
{
  if(WASD == 'w' && this->getUp() != NULL)//up
    return this->getUp();
  if(WASD == 'a' && this->getLeft() != NULL)//Left
    return this->getLeft();
  if(WASD == 's' && this->getDown() != NULL)//Down
    return this->getDown();
  if(WASD == 'd' && this->getRight() != NULL)
    return this->getRight();
}

int Character::attack()
{
  return this->getATK();
}

void Character::defend(int atk)
{
  int dmg = atk - this->getDEF();
  if(dmg < 0)
    dmg = 0;

  int newHP = this->getHP() - dmg;
  if(newHP < 0)
    newHP = 0;
  this->setHP(newHP);
}

Space* Enemy::move()
{
  //check adjacent squares for first
  Space* w = this->getUp();
  Space* a = this->getLeft();
  Space* s = this->getDown();
  Space* d = this->getRight();
  if(w->isPlayer())//if up is player
    return w;
  else if(a->isPlayer())
    return a;
  else if(s->isPlayer())
    return s;
  else if(d->isPlayer())
    return d;
  else
  {
    int rand4 = rand() % 4 + 1;
    if(w->moveCheck() && rand4 == 1)//up
      return w;
    else if(a->moveCheck() && rand4 == 2)
      return a;
    else if(s->moveCheck() && rand4 == 3)
      return s;
    else if(d->moveCheck() && rand4 == 4)
      return d;
    else
      return NULL;
  }
}

void Player::usePotion()
{
  if(bag.size() > 0)
  {
    Potion *pot = &bag.front();
    bag.pop();
    int newHP = this->getHP() + pot->use();
    if(newHP > 10)
      newHP = 10;

    cout << "You used 1 potion, you now have " << bag.size() << " potions.\n";
    cout << "You healed " << pot->use() << " HP, you now have " << newHP << " HP\n";
    this->setHP(newHP);
  }
  else
    cout << "You are out of potions!\n";
}


int Boss::attack()
{
  int rand100 = rand() % 100 + 1;

  if(rand100 < 15)
  {
    cout << "Myke used 'Sonic Boom!'\n";
    return 2 * this->getATK();
  }
  else
    return this->getATK();
}

void Boss::defend(int atk)
{
  int dmg = atk - this->getDEF();
  if(dmg < 0)
    dmg = 0;

  int newHP = this->getHP() - dmg;
  if(newHP < 0 && secondPhase)
  {
    cout << "Myke has entered phase 2!\n";
    newHP = 20;
    secondPhase = false;
  }
  this->setHP(newHP);
}

void Player::setSword(Item* swrd)
{
  if(this->sword != NULL)
    delete this->sword;
  this->sword = swrd;
}

void Player::pickUpPotion()
{
  Potion temp;
  bag.push(temp);
}

void Player::pickUpKey()
{
  Key temp;
  keys.push(temp);
}

int Player::useKey()
{
  if(keys.size() > 0)
  {
    Key *k = &keys.front();
    keys.pop();

    return k->use();
  }
  else
    cout << "You don't have any keys!\n";
}
