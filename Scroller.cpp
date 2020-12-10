#include "Scroller.h"
#include "EventStep.h"
#include "WorldManager.h"
#include <stddef.h>
#include "ObjectList.h"
#include "LogManager.h"
#include "EventDeath.h"
Scroller::Scroller() {
	speed = -.25;
	registerInterest(df::STEP_EVENT);
	registerInterest(DEATH_EVENT);
	setType("Scroller");
	stepCount = 0;
}

int Scroller::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		//LM.writeLog("STEPS");
		stepCount++;
		if (stepCount % 150 == 0) {
			speed = speed - .1;
		}
	//	LM.writeLog("Speed is %.2f.\n", speed);
		step();
		return 1;
	}
	if (p_e->getType() == DEATH_EVENT) {
		//LM.writeLog("DED\n\n\n");
		speed = -.25;
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

	df::ObjectList list2;
	df::ObjectListIterator i2(&list2);
	list = WM.objectsOfType("SpeedUp");
	for (i2.first(); !i2.isDone(); i2.next()) {
		df::Object* p_o = i2.currentObject();
		df::Vector v(speed, 0);
		p_o->setVelocity(v);
	}

	df::ObjectList list3;
	df::ObjectListIterator i3(&list3);
	list = WM.objectsOfType("Invincible");
	for (i3.first(); !i3.isDone(); i3.next()) {
		df::Object* p_o = i3.currentObject();
		df::Vector v(speed, 0);
		p_o->setVelocity(v);
	}

	df::ObjectList list4;
	df::ObjectListIterator i4(&list4);
	list = WM.objectsOfType("SpeedDown");
	for (i4.first(); !i4.isDone(); i4.next()) {
		df::Object* p_o = i4.currentObject();
		df::Vector v(speed, 0);
		p_o->setVelocity(v);
	}
	df::ObjectList list5;
	df::ObjectListIterator i5(&list5);
	list = WM.objectsOfType("JumpHigh");
	for (i5.first(); !i5.isDone(); i5.next()) {
		df::Object* p_o = i5.currentObject();
		df::Vector v(speed, 0);
		p_o->setVelocity(v);
	}
}