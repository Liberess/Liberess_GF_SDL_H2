#include "Background.h"
#include "Game.h"
#include "TextureManager.h"

Background::Background(const LoaderParams* pParams)
  : SDLGameObject(pParams)
{

}

void Background::draw()
{
  //TheTextureManager::Instance()->drawFrame(m_textureID, m_position.getX() - TheGame::Instance()->getCameraRect().x, m_position.getY() - TheGame::Instance()->getCameraRect().y, m_width, m_height, 1, 1, m_destRect, TheGame::Instance()->getRenderer(), m_flipX);

  SDLGameObject::draw();
}