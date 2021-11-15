#include "SDLGameObject.h"
#include "Game.h"
#include "TextureManager.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) : GameObject(pParams), m_position(pParams->getX(), pParams->getY()), m_velocity(0, 0), m_acceleration(0, 0), m_direction(0, 0)
{
  m_x = pParams->getX();
  m_y = pParams->getY();
  m_width = pParams->getWidth();
  m_height = pParams->getHeight();
  m_textureID = pParams->getTextureID();
  m_currentRow = 0;
  m_currentFrame = 0;
  m_flipX = pParams->getFlipX();
  m_isJumping = false;
  m_moveSpeed = 0;
  m_jumpSpeed = 0;
  m_isGround = true;
}

void SDLGameObject::draw()
{
  TheTextureManager::Instance()
    ->drawFrame
        (
          m_textureID,
          (int)m_position.getX(), (int)m_position.getY(),
          m_width, m_height,
          m_currentRow, m_currentFrame,
          TheGame::Instance()->getRenderer(),
          m_flipX
        );
}

void SDLGameObject::update()
{
  m_velocity += m_acceleration;
  m_position += m_velocity;
}

template <typename T1, typename T2>
bool SDLGameObject::checkCollision(const T1& objectA, const T2& objectB)
{
  int leftA, leftB;
  int rightA, rightB;
  int topA, topB;
  int bottomA, bottomB;

  leftA = objectA.getX();
  rightA = objectA.getX() + objectA.getWidth();
  topA = objectA.getY();
  bottomA = objectA.getY() + objectA.getHeight();

  leftB = objectB.getX();
  rightB = objectB.getX() + objectB.getWidth();
  topB = objectB.getY();
  bottomB = objectB.getY() + objectB.getHeight();

  if(bottomA <= topB)
    return false;

  if(topA >= bottomB)
    return false;

  if(rightA <= leftB)
    return false;

  if(leftA >= rightB)
    return false;

  return true;
}

void SDLGameObject::clean()
{
  
}

void SDLGameObject::velocityZero()
{
  m_velocity.setX(0);
  m_velocity.setY(0);
}