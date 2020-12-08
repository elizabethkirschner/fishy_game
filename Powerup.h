#include "Object.h"
#include "EventCollision.h"
#include "EventView.h"

#define PLACEHOLDER_POWERUP "bullet"
#define PLACEHOLDER_POWERUP_2 "ship"

class Powerup : public df::Object {

public:
    Powerup(std::string spriteName);
    ~Powerup();
    int eventHandler(const df::Event* p_e);
    void moveToStart(int y);
    void out();
    void hit(const df::EventCollision* p_c);
};