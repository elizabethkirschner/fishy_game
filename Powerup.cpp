
#include "Powerup.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventOut.h"
#include "Explosion.h"
#include "EventCollision.h"
#include "Points.h"
#include "EventDeath.h"
#include "Lives.h"

Powerup::Powerup(std::string spriteName) {
    setSprite(spriteName);
    setType("Powerup");

    if (spriteName == PLACEHOLDER_POWERUP) {
        moveToStart(15);
    }
    else if (spriteName == PLACEHOLDER_POWERUP_2) {
        moveToStart(18);
    }

    // TODO: do this elsewhere
    setVelocity(df::Vector(-0.25, 0)); // 1 space left every 4 frames

}

int Powerup::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::OUT_EVENT) {
        out();
        return 1;
    }

    if (p_e->getType() == df::COLLISION_EVENT) {
        const df::EventCollision* p_collision_event =
            dynamic_cast <df::EventCollision const*> (p_e);
        hit(p_collision_event);
        return 1;
    }
    return 0;
}

void Powerup::out() {
    if (getPosition().getX() >= 0)
        return;

    WM.markForDelete(this);
}

void Powerup::moveToStart(int y) {
    df::Vector temp_pos;

    float world_horiz = WM.getBoundary().getHorizontal();
    float world_vert = WM.getBoundary().getVertical();

    // TODO: maybe move back to spawner
    temp_pos.setX(world_horiz);//world_horiz + rand() % (int) world_horiz + 3.0f);

    // y is in vertical range.
    // TODO: make this a global declared elsewhere
    temp_pos.setY(y);

    // If collision, move right slightly until empty space.
    df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
    while (!collision_list.isEmpty()) {
        temp_pos.setX(temp_pos.getX() + 1);
        collision_list = WM.getCollisions(this, temp_pos);
    }

    WM.moveObject(this, temp_pos);
}

void Powerup::hit(const df::EventCollision* p_c) {

    if ((p_c->getObject1()->getType() == "Powerup") &&
        (p_c->getObject2()->getType() == "Powerup")) {
        return;
    }

    if (((p_c->getObject1()->getType()) == "Player") ||
        ((p_c->getObject2()->getType()) == "Player")) {

        // do powerup things
    }
}

Powerup::~Powerup() {}