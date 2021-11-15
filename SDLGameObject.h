#pragma once

#include "Game.h"
#include "GameObject.h"
#include "SDL.h"
#include "Vector2D.h"
#include "InputHandler.h"
#include <vector>
#include <algorithm>

class SDLGameObject : public GameObject
{
public:
  SDLGameObject(const LoaderParams* pParams);
  virtual void draw();
  virtual void update();
  virtual void clean();
  template <typename T1, typename T2>
  bool checkCollision(const T1& objectA, const T2& objectB);
  virtual void velocityZero();
  virtual ~SDLGameObject() {}

protected:
  std::string m_textureID;
  int m_x;
  int m_y;
  int m_width;
  int m_height;
  int m_currentRow;
  int m_currentFrame;
  SDL_RendererFlip m_flipX;
  Vector2D m_position;
  Vector2D m_direction;
  Vector2D m_acceleration;
  Vector2D m_velocity;
  bool m_isJumping;
  int m_moveSpeed;
  int m_jumpSpeed;
  bool m_isGround;
};