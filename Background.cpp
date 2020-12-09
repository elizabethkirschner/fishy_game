#include <stdlib.h>

// Engine includes.
#include "DisplayManager.h"
#include "EventMouse.h"
#include "EventStep.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "EventStep.h"

// Game includes.
#include "Background.h"
#include "Enemy.h"
#include "GameOver.h"
#include "Spawner.h"
#include "Explosion.h"

Background::Background() {

	registerInterest(df::STEP_EVENT);
	setSprite("background");
	setType("Background");

	int world_horiz = (int) DM.getHorizontal();
	int world_vert = (int) DM.getVertical();
	df::Vector p((float)(world_horiz/2.0f), (float) (world_vert/2.0f));
	setPosition(p);

	setSolidness(df::SPECTRAL);
	setAltitude(0);
}

