#include "HighScore.h"

HighScore::HighScore() {
    setLocation(df::TOP_LEFT);
    setViewString(HIGHSCORE_STRING);
    setColor(df::YELLOW);
    setValue(0);
}
