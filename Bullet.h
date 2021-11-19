#pragma once

#include "SDLGameObject.h"

class Bullet : public SDLGameObject
{
public:
  Bullet(const LoaderParams* pParams);
  virtual void draw();
  virtual void update();
  virtual void clean();
  virtual void destroy();
  void checkCollision();
};