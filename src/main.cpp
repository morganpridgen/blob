#include <cmath>
#include <TEXEL/texel.h>
#include "state.h"

bool init();
void update();
void render();
void end();

TXL_Display disp;
TXL_Controller *ctrls[4];
GameState *state = new PlayState;
bool loop = 1;

int main(int argc, char **argv) {
  if (init()) {
    while (loop) {
      loop = TXL_Events(&disp);
      
      update();
      render();
    }
    end();
  }
  return 1;
}

bool init() {
  if (!TXL_Init()) return 0;
  TXL_InitPaths("blob");
  if (!TXL_LoadFont(TXL_DataPath("font.png"))) return 0;
  
  if (!disp.init("Blob")) return 0;
  for (int i = 0; i < 4; i++) {
    ctrls[i] = new TXL_Controller;
    if (!ctrls[i]->init()) {
      delete ctrls[i];
      ctrls[i] = nullptr;
      if (i == 0) {
        ctrls[i] = new TXL_Keyboard;
        ctrls[i]->init();
      }
    }
  }
  if (!state->init()) return 0;
  return 1;
}

void update() {
  for (int i = 0; i < 4; i++) TXL_ManageController(ctrls[i]);
  GameState *newState = state->update(ctrls);
  if (newState) {
    state->end();
    delete state;
    state = newState;
    if (!state->init()) loop = 0;
  }
}

void render() {
  state->render();
  disp.refresh();
}

void end() {
  TXL_UnloadFont();
  state->end();
  delete state;
  state = nullptr;
  for (int i = 0; i < 4; i++) {
    if (ctrls[i]) {
      ctrls[i]->end();
      delete ctrls[i];
    }
  }
  disp.end();
  TXL_End();
}