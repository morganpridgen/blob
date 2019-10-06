#include "tile.h"
#include <cmath>
#include <TEXEL/texel.h>

void FloorTile::render(int tX, int tY, float cX, float cY) {
  TXL_RenderQuad({float(tX) * 16.0f - cX, float(tY) * 16.0f - cY, 16, 16}, {0, fmod(tX + tY + 5, 2) / 2.0f + 0.5f, 0, 1});
  TXL_RenderQuad({float(tX) * 16.0f - cX + 2, float(tY) * 16.0f - cY + 2, 12, 12}, {0, fmod(tX + tY + 4, 2) / 2.0f + 0.5f, 0, 1});
}


void WallTile::update(int tX, int tY, Player *ply) {
  float rX = float(tX) * 16.0f + 8.0f, rY = float(tY) * 16.0f + 8.0f;
  float pX = ply->getInfo().x, pY = ply->getInfo().y;
  if ((rX - pX >= -8.0f && rX - pX <= 8.0f) && (rY - pY >= -8.0f && rY - pY <= 8.0f)) {
    float pXV = ply->getInfo().fVel * cos(ply->getInfo().r);
    float pYV = ply->getInfo().fVel * sin(ply->getInfo().r);
    if (rX - (pX - pXV) <= -8.0f || rX - (pX - pXV) >= 8.0f) {
      pX -= pXV;
      pXV = 0;
    }
    if (rY - (pY - pYV) <= -8.0f || rY - (pY - pYV) >= 8.0f) {
      pY -= pYV;
      pYV = 0;
    }
    PlayerInfo pInfo = ply->getInfo();
    pInfo.x = pX, pInfo.y = pY, pInfo.r = atan2(pYV, pXV), pInfo.fVel = sqrt(pXV * pXV + pYV * pYV);
    ply->setInfo(pInfo);
  }
}

void WallTile::render(int tX, int tY, float cX, float cY) {
  TXL_RenderQuad({float(tX) * 16.0f - cX, float(tY) * 16.0f - cY, 16, 16}, {0.5f, 0.5f, 0.5f, 1.0f});
  TXL_RenderQuad({float(tX) * 16.0f - cX + 2, float(tY) * 16.0f - cY + 2, 12, 12}, {0.25f, 0.25f, 0.25f, 1.0f});
}



Tile *newTileId(int tId) {
  Tile *out = nullptr;
  switch (tId) {
    case 0:
      out = new FloorTile;
      break;
    case 1:
      out = new WallTile;
      break;
    default:
      out = new Tile;
      break;
  }
  return out;
}