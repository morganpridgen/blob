#include "player.h"
#include <TEXEL/texel.h>
#include <cmath>

bool Player::init() {
  info.x = 0, info.y = 0, info.r = 0, info.tR = 0, info.fVel = 0, info.rVel = 0;
  return 1;
}

void Player::update(TXL_Controller *ctrl) {
  float d = sqrt((ctrl->leftJoyX() * ctrl->leftJoyX()) + (ctrl->leftJoyY() * ctrl->leftJoyY())) / 64.0f;
  if (d > 0.25f) {
    info.tR = atan2(ctrl->leftJoyY(), ctrl->leftJoyX());
    info.fVel += ((d - info.fVel) / 8.0f);
  } else info.fVel += (info.fVel / -8.0f);
  info.rVel = (info.tR - info.r + (6.28f * (ctrl->leftJoyY() < 0)));
  info.rVel += 6.28f * (info.rVel < -3.14f);
  info.rVel -= 6.28f * (info.rVel > 3.14f);
  info.rVel /= 8.0f;
  info.r += info.rVel;
  while (info.r < 0) info.r += 6.28f;
  while (info.r > 6.28f) info.r -= 6.28f;
  info.x += info.fVel * cos(info.r);
  info.y += info.fVel * sin(info.r);
}
void Player::render(float cX, float cY) {
  TXL_RenderQuad(info.x - cX, info.y - cY, 8.0f, 8.0f, {0.15f, 0.85f, 0.15f, 1.0f});
  TXL_RenderQuad(info.x - cX - 3.5f, info.y - cY, 1.0f, 8.0f, {0.075f, 0.425f, 0.075f, 1.0f});
  TXL_RenderQuad(info.x - cX, info.y - cY - 3.5f, 8.0f, 1.0f, {0.075f, 0.425f, 0.075f, 1.0f});
  TXL_RenderQuad(info.x - cX + 3.5f, info.y - cY, 1.0f, 8.0f, {0.075f, 0.425f, 0.075f, 1.0f});
  TXL_RenderQuad(info.x - cX, info.y - cY + 3.5f, 8.0f, 1.0f, {0.075f, 0.425f, 0.075f, 1.0f});
  
  TXL_RenderQuad(info.x - cX - 1.5f, info.y - cY - 0.5f, 1.0f, 1.0f, {0.075f, 0.425f, 0.075f, 1.0f});
  TXL_RenderQuad(info.x - cX + 1.5f, info.y - cY - 0.5f, 1.0f, 1.0f, {0.075f, 0.425f, 0.075f, 1.0f});
}

void Player::end() {

}

void Player::moveCamera(float *cX, float *cY) {
  *cX += (info.x - *cX - 320.0f) / 8.0f;
  *cY += (info.y - *cY - 180.0f) / 8.0f;
}