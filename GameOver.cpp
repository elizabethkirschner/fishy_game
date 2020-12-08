
#include "GameOver.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "GameStart.h"
#include "LogManager.h"

GameOver::GameOver() {

  setType("GameOver");

  // Link to "message" sprite.
  if (setSprite("gameover") == 0)
    time_to_live = getAnimation().getSprite()->getFrameCount() * getAnimation().getSprite()->getSlowdown();
  else
    time_to_live = 0;

  // Put in center of window.
  setLocation(df::CENTER_CENTER);

  // Register for step event.
  registerInterest(df::STEP_EVENT);
  setAltitude(df::MAX_ALTITUDE);

  // Play "game over" sound.
  //df::Sound *p_sound = RM.getSound("game over");
  //p_sound->play();

}

// Count down to end of message.
void GameOver::step() {
  time_to_live--;
  if (time_to_live <= 0) 
    WM.markForDelete(this);
}

int GameOver::eventHandler(const df::Event *p_e) {
  if (p_e->getType() == df::STEP_EVENT) {
    step();
    return 1;
  }
  return 0;
}

// Override default draw so as not to display "value".
int GameOver::draw() {
  return df::Object::draw();
}

GameOver::~GameOver() {
  // Remove Saucers and ViewObjects, re-activate GameStart.
  df::ObjectList object_list = WM.getAllObjects(true);
  df::ObjectListIterator i(&object_list);
  for (i.first(); !i.isDone(); i.next()) {
    df::Object *p_o = i.currentObject();
    if (p_o -> getType() == "Spawner" || p_o -> getType() == "ViewObject" || p_o -> getType() == "Enemy" || p_o->getType() == "Player" || p_o->getType() == "Ground")
      WM.markForDelete(p_o);
    if (p_o -> getType() == "GameStart") {
      p_o -> setActive(true);
      //dynamic_cast <GameStart *> (p_o) -> playMusic(); // Resume start music.
    }
  }
}
