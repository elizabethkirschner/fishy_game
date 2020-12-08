#include "ViewObject.h"
#include "Music.h"

class GameStart : public df::ViewObject {
  private:
    void start();

  public:
    GameStart();
    int draw();
    int eventHandler(const df::Event *p_e);
    void playMusic();
};