#ifndef playerh
#define playerh

#include <TEXEL/texel.h>

struct PlayerInfo {
  float x, y;
  float r, tR;
  float fVel, rVel;
};

class Player {
  private:
    PlayerInfo info;
  public:
    bool init();
    void update(TXL_Controller*);
    void render();
    void end();
};

#endif