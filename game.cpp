#include "GameManager.h"
#include "LogManager.h"

int main(int argc, char *argv[]) {

  // Start up game manager.
  df::GameManager &game_manager = df::GameManager::getInstance();
  if (game_manager.startUp())  {
    df::LogManager &log_manager = df::LogManager::getInstance();
    log_manager.writeLog("Error starting game manager!");
    game_manager.shutDown();
    return 0;
  }

  df::splash();

  game_manager.shutDown();
}
