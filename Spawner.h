#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Object.h"

class Spawner : public df::Object {

 private:
  void mouse(const df::EventMouse *p_mouse_event);
  void kbd(const df::EventKeyboard *keyboard_event);
  void spawn();
  //void powerup();

 public:
  Spawner();
  ~Spawner();
  int eventHandler(const df::Event *p_e);
  void powerup();

};
