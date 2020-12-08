#include "Lives.h"

Lives::Lives() {
	setLocation(df::BOTTOM_RIGHT);
	setViewString(LIVES_STRING);
	setColor(df::YELLOW);
	setValue(3);
}