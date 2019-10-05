#ifndef tileh
#define tileh
#include <TEXEL/texel.h>
#include "player.h"

class Tile {
  public:
    virtual bool init() {return 1;}
    virtual void update(int, int, Player*) {}
    virtual void render(int, int, float, float) {}
    virtual void end() {}
    
    virtual int getType() {return -1;}
};

class FloorTile : public Tile {
  public:
    virtual void render(int, int, float, float);
    virtual int getType() {return 0;}
};

class WallTile : public Tile {
  public:
    virtual void update(int, int, Player*);
    virtual void render(int, int, float, float);
    virtual int getType() {return 1;}
};

#endif