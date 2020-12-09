#include "Enemy.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventOut.h"
#include "Explosion.h"
#include "EventCollision.h"
#include "Points.h"
#include "EventDeath.h"
#include "Lives.h"

Enemy::Enemy(std::string spriteName) {
  setSprite(spriteName);
  setType("Enemy");

  if (spriteName == FISH_ENEMY){
      moveToStart(15.2);
      }
  else if (spriteName == SEAWEED_ENEMY) {
      moveToStart(18);
  }
}

int Enemy::eventHandler(const df::Event *p_e) {
  if (p_e->getType() == df::OUT_EVENT) {
    out();
    return 1;
  }

  if (p_e->getType() == df::COLLISION_EVENT) {
    const df::EventCollision *p_collision_event = 
      dynamic_cast <df::EventCollision const *> (p_e);
    hit(p_collision_event);
    return 1;
  }
  return 0;
}

void Enemy::out() {
  if (getPosition().getX() >= 0)
    return;

  WM.markForDelete(this);
}

void Enemy::moveToStart(float y) {
  df::Vector temp_pos;

  float world_horiz = WM.getBoundary().getHorizontal();
  float world_vert = WM.getBoundary().getVertical();

  // TODO: maybe move back to spawner
  temp_pos.setX(world_horiz);

  // y is in vertical range.
  // TODO: make this a global declared elsewhere
  temp_pos.setY(y);

  // If collision, move right slightly until empty space.
  df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
  while (!collision_list.isEmpty()) {
    temp_pos.setX(temp_pos.getX()+1);
    collision_list = WM.getCollisions(this, temp_pos);
  }

  WM.moveObject(this, temp_pos);
}

void Enemy::hit(const df::EventCollision *p_c) {

  if ((p_c -> getObject1() -> getType() == "Enemy") &&
      (p_c -> getObject2() -> getType() == "Enemy")) {
    return;
  }  

  /*
  // If Bullet...
  if ((p_c -> getObject1() -> getType() == "Bullet") ||
      (p_c -> getObject2() -> getType() == "Bullet")) {
    
    isDeath = false;

    // Create an explosion.
    Explosion *p_explosion = new Explosion;
    p_explosion -> setPosition(this -> getPosition());

    // Enemys appear stay around perpetually.
    new Enemy;

    // Play "explode" sound.
    df::Sound *p_sound = RM.getSound("explode");
    p_sound->play();
  }
  */

  if (((p_c -> getObject1() -> getType()) == "Player") || 
      ((p_c -> getObject2() -> getType()) == "Player")) {

    // lose 50 points for loss of life
   // df::EventView evPoints(POINTS_STRING, -50, true);
    //WM.onEvent(&evPoints);

      df::EventView evLives(LIVES_STRING, -1, true);
      WM.onEvent(&evLives);

    EventDeath death;
    WM.onEvent(&death);

    if (p_c->getObject1()->getType() == "Player") {
        WM.markForDelete(p_c->getObject2());
    }
    else WM.markForDelete(p_c -> getObject1());
  }
}

Enemy::~Enemy() { }
