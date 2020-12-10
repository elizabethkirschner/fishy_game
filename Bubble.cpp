#include <stdlib.h>	

// Engine includes.
#include "EventOut.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "LogManager.h"

// Game includes.
#include "Bubble.h"

Bubble::Bubble() {
    setType("Bubble");
    setSolidness(df::SPECTRAL);
    setAltitude(0);

    setVelocity(df::Vector(0, -0.25 / (rand() % 4 + 1)));

    df::Vector p((float)(rand() % (int)WM.getBoundary().getHorizontal()),
        (float)WM.getBoundary().getVertical() + (rand() % 9));
    setPosition(p);
}

// Draw Bubble on window.
int Bubble::draw() {
    return DM.drawCh(getPosition(), BUBBLE_CHAR, df::WHITE);
}

// Handle event.
// Return 0 if ignored, else 1.
int Bubble::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::OUT_EVENT) {
        out();
        return 1;
    }

    // If get here, have ignored this event.
    return 0;
}

// If Bubble moved off window, move back to far right.
void Bubble::out() {
    df::Vector p((float)(rand() % (int)WM.getBoundary().getHorizontal()),
        (float)WM.getBoundary().getVertical() + (rand() % 9));
    setPosition(p);
    setVelocity(df::Vector(0, -0.25 / (rand() % 4 + 1)));
}