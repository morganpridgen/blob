#ifndef stateh
#define stateh
#include <TEXEL/texel.h>

class GameState {
  public:
    virtual bool init() = 0;
    virtual GameState *update(TXL_Controller*[4]) = 0;
    virtual void render() = 0;
    virtual void end() = 0;
};

#endif