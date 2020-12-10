#include "Object.h"
#include "EventCollision.h"
#include "EventView.h"

#define INVINCIBLE_POWERUP "invincible-powerup"
#define JUMP_POWERUP "jump-powerup"
#define SLOW_POWERUP "slow-powerup"
#define SPEED_POWERUP "speed-powerup"

class Powerup : public df::Object {

public:
    Powerup(std::string spriteName);
    ~Powerup();
    int eventHandler(const df::Event* p_e);
    void moveToStart(double y);
    void out();
    void hit(const df::EventCollision* p_c);
};