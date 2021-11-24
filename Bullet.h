#pragma once

#include "SDLGameObject.h"

class Bullet : public SDLGameObject
{
public:
  Bullet(const LoaderParams* pParams, const Vector2D& dirc);
  virtual void draw();
  virtual void update();
  virtual void clean();
  virtual void destroy();
  bool IsOutSideScreen();
  void checkCollision();
  void setID(int id) { m_id = id; }

private:
  int m_id;
  Vector2D m_direction;
  bool m_isInteract;
};