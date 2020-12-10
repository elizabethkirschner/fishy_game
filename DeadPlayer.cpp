// Engine includes.
#include "WorldManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "EventOut.h"

// Game includes.
#include "DeadPlayer.h"
#include "GameStart.h"  

DeadPlayer::DeadPlayer(df::Vector position) {
    setType("DeadPlayer");
    setSprite("dead-player");

    setAltitude(df::MAX_ALTITUDE);
    setPosition(position);
    setVelocity(df::Vector(0, -0.15));

    df::ObjectList spawner = WM.objectsOfType("Spawner");
    df::ObjectListIterator s(&spawner);
    for (s.first(); !s.isDone(); s.next()) {
        df::Object* p_o = s.currentObject();
        WM.markForDelete(p_o);
    }

    df::ObjectList player = WM.objectsOfType("Player");
    df::ObjectListIterator p(&player);
    for (p.first(); !p.isDone(); p.next()) {
        df::Object* p_o = p.currentObject();
        WM.markForDelete(p_o);
    }
}

int DeadPlayer::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::OUT_EVENT) {
        out();
        return 1;
    }
    return 0;
}

void DeadPlayer::out() {
    if (getPosition().getY() < 0) {
        WM.markForDelete(this);
    }
}

// Override default draw so as not to display "value".
// int DeadPlayer::draw() {
//   return df::Object::draw();
// }

DeadPlayer::~DeadPlayer() {
    // Remove Enemys and ViewObjects, re-activate GameStart.
    df::ObjectList object_list = WM.getAllObjects(true);
    df::ObjectListIterator i(&object_list);
    for (i.first(); !i.isDone(); i.next()) {
        df::Object* p_o = i.currentObject();
        if (p_o->getType() == "GameStart") {
            p_o->setActive(true);
            //dynamic_cast <GameStart *> (p_o) -> playMusic(); // Resume start music.
        }
        else {
            WM.markForDelete(p_o);
        }
    }
}