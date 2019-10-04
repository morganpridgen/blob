#ifndef levelh
#define levelh
#include "player.h"
#include "tile.h"

class Level {
  private:
    Tile **tiles;
    Tile *outerTile;
    int lW, lH;
  public:
    bool init(const char*, Player*);
    void update();
    void render(float, float);
    void end();
};

#endif