// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "EventView.h"
#include "EventCollision.h"
#include "ObjectList.h"

// Game includes.
#include "Player.h"
#include "Explosion.h"

Player::Player() {

	setSprite("player");
	setType("Player");

	registerInterest(df::STEP_EVENT);
	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::COLLISION_EVENT);

	df::Vector p(6.5, WM.getBoundary().getVertical() / 2);
	setPosition(p);

	move_slowdown = 2;
	move_countdown = move_slowdown;

	canJump = 0;
	move_speed = 2;
	gravity = .01;

	speedUp = false;
	slowDown = false;
	isInvinc = false;
	gotHops = false;

	speedUpCount = 150;
	slowDownCount = 150;
	invincCount = 150;
	hopsCount = 150;
	
}

Player::~Player() { 
  // Make a big explosion with particles.
  // df::addParticles(df::SPARKS, getPosition(), 2, df::BLUE);
  // df::addParticles(df::SPARKS, getPosition(), 2, df::YELLOW);
  // df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
  // df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
}

int Player::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event = dynamic_cast <const df::EventKeyboard*> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}

	if (p_e->getType() == df::STEP_EVENT) {
		//LM.writeLog("STEPS");
		step();
		return 1;
	}
	
	if (p_e->getType() == df::COLLISION_EVENT) {
		df::EventCollision* ec = (df::EventCollision*) p_e;
		if ((ec->getObject1()->getType() == "Ground") || (ec->getObject2()->getType() == "Ground")) {
			canJump = 1;
			df::Vector velocity = getVelocity();
			setVelocity(df::Vector(velocity.getX(), 0));
		}
	}

	return 0;
}

void Player::kbd(const df::EventKeyboard* p_keyboard_event) {
	switch (p_keyboard_event->getKey()) {
	case df::Keyboard::A:       // left
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			move(-move_speed);
		break;
	case df::Keyboard::D:       // right
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			move(+move_speed);
		break;
	case df::Keyboard::SPACE:   // jump
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED){
			if (canJump > 0) {
				setVelocity(df::Vector(getVelocity().getX(), -.3));
				canJump--;
			}
		}
		  break;
	case df::Keyboard::S:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			setSprite("player-crouch");
			setPosition(df::Vector(getPosition().getX(), getPosition().getY() + 0.5));
		}
		if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
			setSprite("player");
			setPosition(df::Vector(getPosition().getX(), getPosition().getY() - 0.5));
		}
		break;
	case df::Keyboard::U:
		if ((p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) && (speedUp == false)) {

			setSprite("powered-up");
			speedUp = true;
			move_speed = 4;
		}
		break;
	case df::Keyboard::T:
		if ((p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) && (slowDown == false)) {
			slowDown = true;
			move_speed = 1;
			setSprite("powered-up");

		}
		break;
	case df::Keyboard::H:
		if ((p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) && (gotHops == false)) {
			gotHops = true;
			gravity = .001;
			setSprite("powered-up");

		}
		break;
	case df::Keyboard::I:
		if ((p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) && (isInvinc == false)) {
			isInvinc = true;
			setSprite("powered-up");

			df::ObjectList list;
			df::ObjectListIterator i(&list);
			list = WM.objectsOfType("Enemy");
			for (i.first(); !i.isDone(); i.next()) {
				df::Object* p_o = i.currentObject();
				p_o->setSolidness(df::Solidness::SPECTRAL);
			}
		}
		break;
	  case df::Keyboard::Q:        // quit
		  if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			  WM.markForDelete(this);
		  break;
	  default: // Key not handled.
		  return;
	};

	return;
}

void Player::move(int dx) {
	if (move_countdown > 0) {
		return;
	}
	move_countdown = move_slowdown;

	df::Vector new_pos(getPosition().getX() + dx, getPosition().getY());
	if ((new_pos.getX() > 3) && (new_pos.getX() < WM.getBoundary().getHorizontal() - 1)) {
		WM.moveObject(this, new_pos);
	}
}

void Player::step() {

	//LM.writeLog("%d", speedUpCount);
	move_countdown--;
	if (move_countdown < 0) {
		move_countdown = 0;
	}

	if (speedUp == true) {
		speedUpCount--;
		if (speedUpCount <= 0) {
			speedUp = false;
			move_speed = 2;
			speedUpCount = 150;
			setSprite("player");
		}
	}

	if (slowDown == true) {
		slowDownCount--;
		if (slowDownCount <= 0) {
			slowDown = false;
			move_speed = 2;
			slowDownCount = 150;
			setSprite("player");
		}
	}

	if (gotHops == true) {
		hopsCount--;
		if (hopsCount <= 0) {
			gotHops = false;
			gravity = .01;
			hopsCount = 150;
			setSprite("player");
		}
	}

	if (isInvinc == true) {
		invincCount--;
		if (invincCount <= 0) {
			setSprite("player");

			isInvinc = false;
			df::ObjectList list;
			df::ObjectListIterator i(&list);
			list = WM.objectsOfType("Enemy");
			for (i.first(); !i.isDone(); i.next()) {
				df::Object* p_o = i.currentObject();
				p_o->setSolidness(df::Solidness::SPECTRAL);
			}
			invincCount = 150;

		}
	}

	df::Vector velocity = getVelocity();
	if (canJump == 0) {
		setVelocity(df::Vector(velocity.getX(), velocity.getY() + gravity));
	}
	else {
		setVelocity(df::Vector(velocity.getX(), velocity.getY()));
	}

}