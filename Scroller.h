#include "WorldManager.h"
#include "Object.h"
class Scroller : public df::Object{

private:

public:
	Scroller();
	float speed;
	int eventHandler(const df::Event* p_e);
	void step();
};

