#include "Object.h"

#define BUBBLE_CHAR 'o'

class Bubble : public df::Object {

private:
	void out();

public:
	Bubble();
	int draw(void);
	int eventHandler(const df::Event* p_e);
};