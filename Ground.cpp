#include "DisplayManager.h"
#include "EventMouse.h"
#include "EventStep.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "EventStep.h"

#include "Enemy.h"
#include "GameOver.h"
#include "Spawner.h"
#include "Explosion.h"
#include <stdlib.h>
#include "Ground.h"

Ground::Ground() {

	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::MSE_EVENT);
	registerInterest(df::STEP_EVENT);
	setSprite("ground");
	setType("Ground");

	int world_horiz = (int)DM.getHorizontal();
	int world_vert = (int)DM.getVertical();
	df::Vector p((float)(0), 21);
	setPosition(p);

	//setSolidness(df::SPECTRAL);
	setAltitude(df::MAX_ALTITUDE - 1);
}

