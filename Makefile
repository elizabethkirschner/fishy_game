#
# Makefile for saucer shoot game using Dragonfly
#
# Copyright Mark Claypool and WPI, 2016
#
# 'make depend' to generate new dependency list
# 'make clean' to remove all constructed files
# 'make' to build executable
#
# Variables of interest:
#   GAMESRC is the source code files for the game
#   GAME is the game main() source
#

CC= g++ 

### Uncomment only 1 of the below! ###

# 1) Uncomment below for Linux (64-bit)
#LINKLIB= -ldragonfly-linux64 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lrt
#LINKDIR= -L../dragonfly/lib/ # path to dragonfly library
#INCDIR= -I../dragonfly/include/ # path to dragonfly includes

# 2) Uncomment below for Mac (64-bit)
LINKLIB= -ldragonfly-mac64 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 
LINKDIR= -L/usr/local/Cellar/sfml/2.5.1/lib/ -L../dragonfly/lib/ 
INCDIR= -I/usr/local/Cellar/sfml/2.5_1/include/ -I../dragonfly/include/

######

GAMESRC= \

GAME= game.cpp Spawner.cpp GameOver.cpp GameStart.cpp Explosion.cpp Points.cpp Enemy.cpp Lives.cpp EventDeath.cpp HighScore.cpp Scroller.cpp Ground.cpp Player.cpp Background.cpp Bubble.cpp
EXECUTABLE= game
OBJECTS= $(GAMESRC:.cpp=.o)
CFLAGS:= $(CFLAGS) -std=c++11

all: $(EXECUTABLE) Makefile

$(EXECUTABLE): $(ENGINE) $(OBJECTS) $(GAME) $(GAMESRC) 
	$(CC) $(CFLAGS) $(GAME) $(OBJECTS) -o $@ $(INCDIR) $(LINKDIR) $(LINKLIB) 

.cpp.o: 
	$(CC) $(CFLAGS) -c $(INCDIR) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) core dragonfly.log Makefile.bak *~

depend: 
	makedepend *.cpp 2> /dev/null

# DO NOT DELETE
