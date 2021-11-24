#include "Bullet.h"
#include "Game.h"

Bullet::Bullet(const LoaderParams* pParams, const Vector2D& dirc)
  : SDLGameObject(pParams), m_direction(dirc)
{
  m_currentRow = m_currentFrame = 0;

  m_velocity.setX(dirc.getX() * 5);
  m_velocity.setY(dirc.getY() * 5);

  m_isInteract = true;
}

void Bullet::draw()
{
  SDLGameObject::draw();
}

void Bullet::update()
{
  if(IsOutSideScreen())
    destroy();

  SDLGameObject::update();

  checkCollision();
}

void Bullet::checkCollision()
{
  if(!m_isInteract)
    return;

  if(TheGame::Instance()->m_gameObjects["enemy"] != 0)
  {
    if(SDLGameObject::checkCollision(TheGame::Instance()->m_gameObjects["enemy"]->getDestRect()))
    {
      m_isInteract = false;
      TheGame::Instance()->m_gameObjects["enemy"]->destroy();
      destroy();
    }
  }

  if(TheGame::Instance()->m_gameObjects["wall"] != 0)
  {
    if(SDLGameObject::checkCollision(TheGame::Instance()->m_gameObjects["wall"]->getDestRect()))
    {
      destroy();
    }
  }
}

bool Bullet::IsOutSideScreen()
{
  if(m_position.getX() < 0 || m_position.getY() < 0 || m_position.getX() > TheGame::Instance()->getScreenWidth() || m_position.getY() > TheGame::Instance()->getScreenHeight()) 
    return true;
  
  return false;
}

void Bullet::clean()
{
  
}

void Bullet::destroy()
{
  std::cout << m_id << "번째 총알 파괴 신호" << std::endl;
  TheGame::Instance()->destroyBullet(m_id);
  //TheGame::Instance()->m_gameObjects.erase("bullet");
}