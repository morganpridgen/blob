#include "tile.h"
#include <cmath>
#include <TEXEL/texel.h>

void Tile::render(int tX, int tY, float cX, float cY) {
  TXL_RenderQuad({float(tX) * 16.0f - cX, float(tY) * 16.0f - cY, 16, 16}, {0.5f, 0.5f, 0.5f, 1.0f});
  TXL_RenderQuad({float(tX) * 16.0f - cX + 2, float(tY) * 16.0f - cY + 2, 12, 12}, {0.25f, 0.25f, 0.25f, 1.0f});
}

void FloorTile::render(int tX, int tY, float cX, float cY) {
  TXL_RenderQuad({float(tX) * 16.0f - cX, float(tY) * 16.0f - cY, 16, 16}, {0, fmod(tX + tY + 5, 2) / 2.0f + 0.5f, 0, 1});
  TXL_RenderQuad({float(tX) * 16.0f - cX + 2, float(tY) * 16.0f - cY + 2, 12, 12}, {0, fmod(tX + tY + 4, 2) / 2.0f + 0.5f, 0, 1});
}