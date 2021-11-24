#include "Background.h"
#include "Game.h"
#include "TextureManager.h"

Background::Background(const LoaderParams* pParams)
  : SDLGameObject(pParams)
{

}

void Background::draw()
{
  SDLGameObject::draw();
}