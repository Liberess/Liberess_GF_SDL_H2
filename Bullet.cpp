#include "Bullet.h"
#include "Game.h"

Bullet::Bullet(const LoaderParams* pParams) : SDLGameObject(pParams)
{

}

void Bullet::draw()
{
  SDLGameObject::draw();
}

void Bullet::update()
{
  m_x += 1;
  m_y += 1;

  SDLGameObject::update();
  
  m_currentFrame = (SDL_GetTicks() / 100) % 6;
}

void Bullet::checkCollision()
{
  if(TheGame::Instance()->m_gameObjects["enemy"] != 0)
  {
    if(SDLGameObject::checkCollision(TheGame::Instance()->m_gameObjects["enemy"]->getDestRect()))
    {
      std::cout << "enemy랑 닿음" << std::endl;
    }
  }
}

void Bullet::clean()
{
  
}

void Bullet::destroy()
{
  TheGame::Instance()->m_gameObjects.erase("bullet");
}