#include "state.h"
#include <TEXEL/texel.h>

bool PlayState::init() {
  cX = 0, cY = 0;
  if (!ply.init()) return 0;
  return 1;
}

GameState *PlayState::update(TXL_Controller *ctrls[4]) {
  ply.update(ctrls[0]);
  return nullptr;
}

void PlayState::render() {
  for (int i = -2; i < 42; i++) {
    for (int j = -2; j < 25; j++) {
      TXL_RenderQuad({(i - fmod(cX, 2)) * 16, (j - fmod(cY, 2)) * 16, 16, 16}, {0, fmod(i + j + 4, 2) / 2.0f + 0.5f, 0, 1});
    }
  }
  ply.render();
}

void PlayState::end() {
  ply.end();
}