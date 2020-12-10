#include "ViewObject.h"

class DeadPlayer : public df::Object {
private:
    int time_to_live;
    void out();

public:
    DeadPlayer(df::Vector position);
    ~DeadPlayer();
    int eventHandler(const df::Event* p_e);

};