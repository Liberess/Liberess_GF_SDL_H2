#include "Ground.h"
#include "Game.h"
#include "TextureManager.h"

Ground::Ground(const LoaderParams* pParams)
  : SDLGameObject(pParams)
{
  
}

void Ground::draw()
{
  SDLGameObject::draw();
}