#include "DisplayManager.h"
#include "EventMouse.h"
#include "EventStep.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "EventStep.h"

#include "Enemy.h"
#include "Spawner.h"
#include "Explosion.h"
#include <stdlib.h>
#include "Powerup.h"

Spawner::Spawner() {
  registerInterest(df::STEP_EVENT);

  setType("Spawner");

  // Put in center of screen.
  int world_horiz = (int) DM.getHorizontal();
  int world_vert = (int) DM.getVertical();
  df::Vector p((float)(world_horiz/2.0f), (float) (world_vert/2.0f));
  setPosition(p);

  setSolidness(df::SPECTRAL);
  setAltitude(df::MAX_ALTITUDE);
}

Spawner::~Spawner() {
}

int Spawner::eventHandler(const df::Event *p_e) {

  if (p_e->getType() == df::STEP_EVENT) {
    const df::EventStep *p_step_event = 
      dynamic_cast <const df::EventStep *> (p_e);
    // TODO: vary spawn rate
    if (p_step_event -> getStepCount() % 150 == 0) {
      spawn();
    }

    if (p_step_event->getStepCount() % 300 == 0) {
        //LM.writeLog("time to spawn again");
       // powerup();
    }
    return 1;
  }
 
  return 0;
}

void Spawner::spawn() {
  int chance = rand() % 100;
  
  // TODO: create new enemy types
 if (chance <= 30) {
   new Enemy(FISH_ENEMY);
 }   
 else if (chance <= 60) {
   new Enemy(SEAWEED_ENEMY);
 }
 else if (chance <= 99) {
   //new Enemy;
 }

}

/*
void Spawner::powerup() {
    int chance = rand() % 100;

    // TODO: create new enemy types
    if (chance <= 30) {
        new Powerup(PLACEHOLDER_POWERUP);
    }

    else if (chance <= 60) {
        new Powerup(PLACEHOLDER_POWERUP_2);
    }
    else if (chance <= 99) {

    }
}*/

// Take appropriate action according to mouse action.
void Spawner::mouse(const df::EventMouse *p_mouse_event) {

  // Pressed button?
  if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
      (p_mouse_event->getMouseButton() == df::Mouse::LEFT)) {
        //fire(p_mouse_event->getMousePosition());
      }
}
