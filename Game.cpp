#include "Game.h"
#include "TextureManager.h"
#include "Ground.h"
#include "Player.h"
#include "Enemy.h"

Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
  {
    m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

    if (m_pWindow != 0)
    {
      m_screenWidth = width;
      m_screenHeight = height;
      
      m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

      if (m_pRenderer != 0)
      {
        SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
      } else return false;
    } else return false;
  }
  else
  {
    return false;
  }

  if (!TheTextureManager::Instance()->load("Assets/animate-alpha.png", "animate", m_pRenderer))
  {
    return false;
  }

  if (!TheTextureManager::Instance()->load("Assets/ground.png", "ground1", m_pRenderer))
  {
    return false;
  }

  /* m_gameObjects["ground1"] = new Ground(new LoaderParams(0, 430, 640, 50, "ground1"));
  m_gameObjects["player"] = new Player(new LoaderParams(100, 100, 128, 82, "player"));
  m_gameObjects["enemy"] = new Enemy(new LoaderParams(300, 300, 128, 82, "enemy")); */

  m_gameObjects.push_back(new Ground(new LoaderParams(0, 430, 640, 50, "ground1")));
  m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 128, 82, "animate")));
  m_gameObjects.push_back(new Enemy(new LoaderParams(300, 300, 128, 82, "animate")));

  m_bRunning = true;
  return true;
}

void Game::render()
{
  SDL_RenderClear(m_pRenderer);

  for(int i = 0; i < m_gameObjects.size(); i++)
    m_gameObjects[i]->draw();

  SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
  for(int i = 0; i < m_gameObjects.size(); i++)
    m_gameObjects[i]->update();
}

bool Game::running()
{
  return m_bRunning;
}

void Game::handleEvents()
{
  TheInputHandler::Instance()->Update();
}

void Game::clean()
{
  SDL_DestroyWindow(m_pWindow);
  SDL_DestroyRenderer(m_pRenderer);
  SDL_Quit();
}