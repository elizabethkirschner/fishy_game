// Engine includes.
#include "WorldManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "GameManager.h"
#include "EventKeyboard.h"
#include "Color.h"
#include "Music.h"

// Game includes.
#include "GameStart.h"
#include "Points.h"
#include "Spawner.h"
#include "Lives.h"
#include "Ground.h"
#include "HighScore.h"
#include "Player.h"
#include "Scroller.h"
#include "Background.h"
#include "Bubble.h"

GameStart::GameStart() {

  setType("GameStart");
  setSprite("gamestart");
  setLocation(df::CENTER_CENTER);

  // Register for step event.
  registerInterest(df::KEYBOARD_EVENT);
}

int GameStart::eventHandler(const df::Event *p_e) {

  if (p_e->getType() == df::KEYBOARD_EVENT) {
    df::EventKeyboard *p_keyboard_event = (df::EventKeyboard *) p_e;
    switch (p_keyboard_event->getKey()) {
      case df::Keyboard::P: 			// play
        start();
      break;
      case df::Keyboard::Q:			// quit
        GM.setGameOver();
      break;
      default: // Key is not handled.
      break;
    }
    return 1;
  }
  return 0;
}

// Override default draw so as not to display "value".
int GameStart::draw() {
  return df::Object::draw();
}

void GameStart::start() {
  //new Spawner;
  new Spawner;

  new Lives;

  // Setup heads-up display.
  new Points;	// points display
  new HighScore;

  new Ground;
  //new Background;
  new Player;

  for (int i = 0; i < 8; i++) {
    new Bubble;
  }

  new Scroller;

  // When game starts, become inactive.
  setActive(false);
}

// plays start music
void GameStart::playMusic() {
  //p_music->play();
}


