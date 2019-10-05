#include "level.h"
#include <TEXEL/texel.h>

bool Level::init(const char *path, Player *ply) {
  lW = 0, lH = 0;
  if (!path) {
    lW = 16, lH =  16;
    tiles = new Tile*[lW * lH];
    for (int i = 0; i < lW; i++) {
      for (int j = 0; j < lH; j++) {
        if ((j == 11 && i > 3 && i < 12) || (i == 11 && j > 3 && j < 12)) tiles[i * lH + j] = new WallTile;
        else tiles[i * lH + j] = new FloorTile;
        if (!tiles[i * lH + j]->init()) return 0;
      }
    }
    outerTile = new WallTile;
    if (!outerTile->init()) return 0;
    PlayerInfo pInfo = ply->getInfo();
    pInfo.x = 1.5f * 16.0f, pInfo.y = 1.5f * 16.0f;
    ply->setInfo(pInfo);
    return 1;
  }
  return 0;
}

void Level::update(Player *ply) {
  for (int i = 0; i < lW; i++) {
    for (int j = 0; j < lH; j++) {
      tiles[i * lH + j]->update(i, j, ply);
    }
  }
  PlayerInfo pInfo = ply->getInfo();
  if (pInfo.x < 0.0f) pInfo.x = 0;
  if (pInfo.x > 16 * lW) pInfo.x = 16 * lW;
  if (pInfo.y < 0.0f) pInfo.y = 0;
  if (pInfo.y > 16 * lW) pInfo.y = 16 * lW;
  ply->setInfo(pInfo);
}

void Level::render(float cX, float cY) {
  for (int i = -1; i < 41; i++) {
    for (int j = -1; j < 24; j++) {
      int tI = i + int(cX) / 16, tJ = j + int(cY) / 16;
      if (tI < 0 || tI >= lW || tJ < 0 || tJ >= lH) outerTile->render(i, j, fmod(cX, 16), fmod(cY, 16));
      else tiles[tI * lH + tJ]->render(tI, tJ, cX, cY);
    }
  }
}

void Level::end() {
  for (int i = 0; i < lW * lH; i++) delete tiles[i];
  delete outerTile;
}