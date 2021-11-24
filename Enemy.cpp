#include "Enemy.h"
#include "Game.h"
#include "TextureManager.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
  m_isHit = true;
}

void Enemy::draw()
{
  SDLGameObject::draw();
}

void Enemy::update()
{
  // hit();
  
  checkCollision();
  
  static float currentVelocityY = 0;

  currentVelocityY += 0.02f * 9.8f;

  SDLGameObject::update();
  
  m_currentFrame = (SDL_GetTicks() / 100) % 5;

  // If Grounded
  if(m_isGround)
  {
    m_velocity.setY(0);
    m_acceleration.setY(0);
    currentVelocityY = 0.0f;
  }
  else
  {
    m_velocity.setY(currentVelocityY);
  }
}

void Enemy::checkCollision()
{
  if(TheGame::Instance()->m_gameObjects["ground1"] != 0)
  {
    if(SDLGameObject::checkCollision(TheGame::Instance()->m_gameObjects["ground1"]->getDestRect()))
    {
      m_isGround = true;
    }
    else
    {
      m_isGround = false;
    }
  }
}

void Enemy::hit()
{
  if(!m_isHit)
    return;

  if(m_timer.done())
    destroy();
}

void Enemy::clean()
{
   
}

void Enemy::destroy()
{
  if(!m_isHit)
  {
    m_isHit = true;
    // m_timer.setInterval(1500);
    // m_timer.start();
    m_currentRow = 1;
    
    return;
  }

  TheGame::Instance()->destroyGameObject("enemy");
  //TheTextureManager::Instance()->destroyTexture(m_textureID);
}