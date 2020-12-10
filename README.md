
# fishy_game

Current known issues:
 - player can still control fish after game over
 - game over animation displays twice
 - technically never have to crouch (enemy fish need modification)
 - No audio
 - Possible for the player to clip through the ground by moving rapidly back and forth in the middle
 - Crouching while powered up causes the sprite color to change back to normal (powerup is still active)
 - Increased jump too high


features to be implemented:
 - powerups as part of the spawner
 - Background art
 - music/sound effects
 - animations for player deaths etc.

Controls:
 - A and D to move left and right
 - S to crouch
 - Space to jump
 - P to play
 - Q to quit
 - U to activate speed increase
 - T to activate speed decrease
 - H to activate jump height increase
 - I to activate invincibility

Please also note that the game start art is currently temporary.
--------------------------------------------------------------------

To build:

0) Setup development environment for Windows, Linux or MacOS.
See http://dragonfly.wpi.edu/engine/index.html#setup for details.

1) Build, as appropriate for the platform (e.g., "make" on Linux or
Mac, F7 on Windows from Visual Studio).

2) Run game, as appropriate for the platform (e.g., "./game" on
Linux or Mac, F5 on Windows from Visual Studio)

--------------------------------------------------------------------

Directories:

sounds/ - contains the sound files used in Saucer shoot
sprites/ - contains the sprite files used in Saucer shoot
vs-2019/ - contains Visual Studio solution files (Microsoft Windows)