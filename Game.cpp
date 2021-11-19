#include "Game.h"
#include "TextureManager.h"
#include "Ground.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Background.h"
#include "Vector2D.h"

Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
  {
    m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

    if (m_pWindow != 0)
    {
      m_levelWidth = 1280;
      m_levelHeight = 720;
      
      m_screenWidth = width;
      m_screenHeight = height;

      std::cout << "rect x : " << m_cameraRect.x << std::endl;
  std::cout << "rect y : " << m_cameraRect.y << std::endl;      
      
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

  if (!TheTextureManager::Instance()->load("Assets/background.png", "background", m_pRenderer))
  {
    return false;
  }

  if (!TheTextureManager::Instance()->load("Assets/animate.png", "animate", m_pRenderer))
  {
    return false;
  }

  if (!TheTextureManager::Instance()->load("Assets/ground1.png", "ground1", m_pRenderer))
  {
    return false;
  }

  if (!TheTextureManager::Instance()->load("Assets/ground2.png", "ground2", m_pRenderer))
  {
    return false;
  }

  if (!TheTextureManager::Instance()->load("Assets/wall.png", "wall", m_pRenderer))
  {
    return false;
  }

  if (!TheTextureManager::Instance()->load("Assets/bullet.png", "bullet", m_pRenderer))
  {
    return false;
  }

  m_gameObjects["background"] = new Background(new LoaderParams(0, 0, 640, 480, "background"));
  m_gameObjects["ground1"] = new Ground(new LoaderParams(0, 430, 640, 50, "ground1"));
  m_gameObjects["ground2"] = new Ground(new LoaderParams(300, 300, 150, 50, "ground2"));
  m_gameObjects["wall"] = new Ground(new LoaderParams(500, 330, 50, 150, "wall"));
  m_gameObjects["player"] = new Player(new LoaderParams(0, 0, 128, 82, "animate"));
  m_gameObjects["enemy"] = new Enemy(new LoaderParams(300, 100, 128, 82, "animate"));
  
  m_bRunning = true;
  return true;
}

void Game::render()
{
  SDL_RenderClear(m_pRenderer);

  for(auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
    it->second->draw();

  SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
  for(auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
    it->second->update();

  updateCamera();
}

void Game::updateCamera()
{
  SDL_Rect playerRect = { m_gameObjects["player"]->getX(), m_gameObjects["player"]->getY(), m_gameObjects["player"]->getWidth(), m_gameObjects["player"]->getHeight() };

  m_cameraRect.x = (playerRect.x + playerRect.w / 2) - m_screenWidth / 2;
  m_cameraRect.y = (playerRect.y + playerRect.h / 2) - m_screenHeight / 2;

  if( m_cameraRect.x < 0 )
		m_cameraRect.x = 0;
	if( m_cameraRect.y < 0 )
		m_cameraRect.y = 0;
	if( m_cameraRect.x > m_levelWidth - m_cameraRect.w )
    m_cameraRect.x = m_levelWidth - m_cameraRect.w;
	if( m_cameraRect.y > m_levelHeight - m_cameraRect.h )
		m_cameraRect.y = m_levelHeight - m_cameraRect.h;
}

bool Game::running()
{
  return m_bRunning;
}

void Game::handleEvents()
{
  TheInputHandler::Instance()->Update();
}

void Game::instantiateBullet(Vector2D pos)
{
  m_bullets.push_back(new Bullet(new LoaderParams(pos.getX(), pos.getY(), 32, 32, "bullet")));
}

void Game::clean()
{
  SDL_DestroyWindow(m_pWindow);
  SDL_DestroyRenderer(m_pRenderer);
  SDL_Quit();
}