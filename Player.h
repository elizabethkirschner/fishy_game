#include "EventKeyboard.h"
#include "Object.h"

class Player : public df::Object {

private:
	int move_slowdown;
	int move_countdown;
	float move_speed;
	void kbd(const df::EventKeyboard* p_keyboard_event);
	void step();
	void move(int dx);
	void jump();
	int canJump;
	float gravity;
	bool speedUp;
	int speedUpCount;
	bool slowDown;
	int slowDownCount;
	bool isInvinc;
	int invincCount;
	bool gotHops;
	int hopsCount;

public:
	Player();
	~Player();
	int eventHandler(const df::Event* p_e);
};


