#include "state.h"
#include <TEXEL/texel.h>
#include "level.h"

bool PlayState::init() {
  cX = 0, cY = 0;
  if (!ply.init()) return 0;
  if (!lvl.init(nullptr, &ply)) return 0;
  return 1;
}

GameState *PlayState::update(TXL_Controller *ctrls[4]) {
  ply.update(ctrls[0]);
  ply.moveCamera(&cX, &cY);
  lvl.update(&ply);
  return nullptr;
}

void PlayState::render() {
  /*for (int i = -2; i < 42; i++) {
    for (int j = -2; j < 25; j++) {
      TXL_RenderQuad({i * 16 - fmod(cX, 32), j * 16 - fmod(cY, 32), 16, 16}, {0, fmod(i + j + 5, 2) / 2.0f + 0.5f, 0, 1});
      TXL_RenderQuad({i * 16 - fmod(cX, 32) + 2, j * 16 - fmod(cY, 32) + 2, 12, 12}, {0, fmod(i + j + 4, 2) / 2.0f + 0.5f, 0, 1});
    }
  }*/
  lvl.render(cX, cY);
  ply.render(cX, cY);
}

void PlayState::end() {
  lvl.end();
  ply.end();
}