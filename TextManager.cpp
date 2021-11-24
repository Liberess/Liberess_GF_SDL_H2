#include "TextManager.h"

#include <iostream>

TextManager* TextManager::s_pInstance = 0;

void TextManager::init()
{
  TTF_Init();

  m_font = TTF_OpenFont("Assets/CookieRun Regular.ttf", 15);
  
  m_color = { 255, 255, 255 };
}

void TextManager::drawText(const char* str, int x, int y, SDL_Renderer* pRenderer)
{
  clean();
  init();

  m_surface = TTF_RenderText_Solid(m_font, str, m_color);
  m_texture = SDL_CreateTextureFromSurface(pRenderer, m_surface);

  int w = 0, h = 0;
  SDL_QueryTexture(m_texture, NULL, NULL, &w, &h);
  SDL_Rect destRect = { x, y, w, h };
  SDL_RenderCopy(pRenderer, m_texture, NULL, &destRect);
}

void TextManager::clean()
{
  SDL_DestroyTexture(m_texture);
  SDL_FreeSurface(m_surface);
  TTF_Quit();
}