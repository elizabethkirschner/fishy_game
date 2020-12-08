  #include "Object.h"
  #include "EventCollision.h"
  #include "EventView.h"

#define FISH_ENEMY "enemy-fish"
#define SEAWEED_ENEMY "enemy-seaweed"

class Enemy : public df::Object {

   public:
    Enemy(std::string spriteName);
    ~Enemy();
    int eventHandler(const df::Event *p_e);
    void moveToStart(int y);
    void out();
    void hit(const df::EventCollision *p_c);

  };