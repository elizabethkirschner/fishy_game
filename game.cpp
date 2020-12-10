#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "Explosion.h"
#include "Color.h"
#include "GameStart.h"
#include "Pause.h"
#include "Bubble.h"

void loadResources(void);
void populateWorld(void);

int main(int argc, char* argv[]) {

    // Start up game manager.
    if (GM.startUp()) {
        LM.writeLog("Error starting game manager!");
        GM.shutDown();
        return 0;
    }

    LM.setFlush(true);

    df::splash();

    loadResources();
    populateWorld();

    new df::Pause(df::Keyboard::F10);

    GM.run();
    GM.shutDown();
}

void loadResources(void) {
    RM.loadSprite("sprites/saucer-spr.txt", "saucer");
    RM.loadSprite("sprites/ship-spr.txt", "ship");
    RM.loadSprite("sprites/bullet-spr.txt", "bullet");
    RM.loadSprite("sprites/explosion-spr.txt", "explosion");
    RM.loadSprite("sprites/gameover-spr.txt", "gameover");
    RM.loadSprite("sprites/gamestart-spr.txt", "gamestart");
    RM.loadSprite("sprites/ground-spr.txt", "ground");
    RM.loadSprite("sprites/enemy-fish-spr.txt", "enemy-fish");
    RM.loadSprite("sprites/enemy-seaweed-spr.txt", "enemy-seaweed");
    RM.loadSprite("sprites/player-spr.txt", "player");
    RM.loadSprite("sprites/player-crouch-spr.txt", "player-crouch");
    RM.loadSprite("sprites/player-powered-spr.txt", "powered-up");
    RM.loadSprite("sprites/background1-spr.txt", "background");
    RM.loadSprite("sprites/dead-player-spr.txt", "dead-player");

    RM.loadSprite("sprites/powerups/invincible-powerup-spr.txt", "invincible-powerup");
    RM.loadSprite("sprites/powerups/jump-powerup-spr.txt", "jump-powerup");
    RM.loadSprite("sprites/powerups/slow-powerup-spr.txt", "slow-powerup");
    RM.loadSprite("sprites/powerups/speed-powerup-spr.txt", "speed-powerup");
    // RM.loadSound("sounds/fire.wav", "fire");
    // RM.loadSound("sounds/explode.wav", "explode");
    // RM.loadSound("sounds/nuke.wav", "nuke");
    // RM.loadSound("sounds/game-over.wav", "game over");

    // RM.loadMusic("sounds/start-music.wav", "start music");
}

void populateWorld(void) {



    // Spawn GameStart object.
    new GameStart();
}
