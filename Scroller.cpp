#include "Scroller.h"
#include "EventStep.h"
#include "WorldManager.h"
#include <stddef.h>
#include "ObjectList.h"
#include "LogManager.h"
Scroller::Scroller() {
	speed = -.25;
	registerInterest(df::STEP_EVENT);
	setType("Scroller");
}

int Scroller::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		//LM.writeLog("STEPS");
		step();
		return 1;
	}
	return 0;
}

void Scroller::step() {
	df::ObjectList list;
	df::ObjectListIterator i(&list);
	list = WM.objectsOfType("Enemy");
	for (i.first(); !i.isDone(); i.next()) {
		df::Object* p_o = i.currentObject();
		df::Vector v(speed, 0);
		p_o->setVelocity(v);
	}
}