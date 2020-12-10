// Engine includes
#include "WorldManager.h"
#include "LogManager.h"
#include "EventStep.h"
#include "EventView.h"

// Game includes
#include "Points.h"
#include "GameOver.h"
#include "DeadPlayer.h"
#include "HighScore.h"
#include "EventDeath.h"


Points::Points() {
  highScore = 0;
  score = 0;
  lives = 3;
  setLocation(df::TOP_RIGHT);
  setViewString(POINTS_STRING);
  setColor(df::YELLOW);

  // Need to update score each second, so count "step" events.
  registerInterest(df::STEP_EVENT);
  registerInterest(DEATH_EVENT);
}

int Points::eventHandler(const df::Event *p_e) {

  // Parent handles event if score update.
  if (df::ViewObject::eventHandler(p_e)) {
    return 1;
  }
  if (p_e->getType() == DEATH_EVENT) {
    setValue(0);
    score = 0;
    lives--;

    if (lives == 0) {
        df::ObjectList player = WM.objectsOfType("Player");
        df::ObjectListIterator p(&player);
        for (p.first(); !p.isDone(); p.next()) {
            df::Object* p_o = p.currentObject();
            new DeadPlayer(p_o->getPosition());
        }
       // new GameOver;
    }
  }

  // If step, increment score every second (30 steps).
  if (p_e->getType() == df::STEP_EVENT) {
    if (dynamic_cast <const df::EventStep *> (p_e) 
                        -> getStepCount() % 30 == 0) {
      setValue(getValue() + 1);
      score++;
      if (score > highScore) {
        highScore++;
        df::EventView evHighScore(HIGHSCORE_STRING, +1, true);
        WM.onEvent(&evHighScore);
      }
    }
      
    return 1;
  }

  // If get here, have ignored this event.
  return 0;
}