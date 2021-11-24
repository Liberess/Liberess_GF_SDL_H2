#include "Game.h"
#include "TextManager.h"
#include "TextureManager.h"
#include "Ground.h"
#include "Player.h"
#include "Enemy.h"
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

  try
  {
    parseSprite("Assets/background.png", "background");
    m_gameObjects["background"] = new Background(new LoaderParams(0, 0, 640, 480, "background"));

    parseSprite("Assets/ground1.png", "ground1");
    m_gameObjects["ground1"] = new Ground(new LoaderParams(0, 430, 640, 50, "ground1"));

    parseSprite("Assets/wall.png", "wall");
    m_gameObjects["wall"] = new Ground(new LoaderParams(500, 330, 50, 150, "wall"));

    parseSprite("Assets/Ninja_Frog-export.png", "ninja_frog");
    m_gameObjects["player"] = new Player(new LoaderParams(0, 300, 64, 64, "ninja_frog"));

    parseSprite("Assets/Radish-export.png", "enemy");
    m_gameObjects["enemy"] = new Enemy(new LoaderParams(300, 300, 60, 76, "enemy"));

    parseSprite("Assets/bullet.png", "bullet");

    updateCamera();
  }
  catch(std::string expt)
  {
    std::cout << expt << std::endl;
  }

  m_bulletID = 0;

  m_bRunning = true;
  return true;
}

void Game::destroyGameObject(std::string key)
{
  std::map<std::string, SDLGameObject*>::iterator it;

  it = m_gameObjects.find(key);

  if(it != m_gameObjects.end())
  {
    delete it->second;
    m_gameObjects.erase(key);
  }
}

void Game::destroyBullet(int id)
{
  std::cout << id << "를 Game이 삭제" << std::endl;
  std::cout << "destroyBullet : " << id << std::endl;
  m_bulletArray[id] = 0;
  --m_bulletID;
}

void Game::parseSprite(std::string path, std::string id)
{
  if(!TheTextureManager::Instance()->load(path, id, m_pRenderer))
    throw path + "는 유효하지 않은 경로입니다.";
}

void Game::instantiateBullet(const SDL_Rect& rect, const Vector2D& dirc)
{
  std::cout << m_bulletID << "를 Game이 생성" << std::endl;
  m_bulletArray[m_bulletID] = new Bullet(new LoaderParams(rect.x + (rect.w / 2) - 16, rect.y + (rect.h / 2) - 16, 32, 32, "bullet"), dirc);
  m_bulletArray[m_bulletID]->setID(m_bulletID);

  ++m_bulletID;
  
  /* m_bullets.push_back(new Bullet(new LoaderParams(rect.x + (rect.w / 2) - 16, rect.y + (rect.h / 2) - 16, 32, 32, "bullet"), dirc)); */
}

// Render Update
void Game::render()
{
  SDL_RenderClear(m_pRenderer);

  for(auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
    it->second->draw();

  // for(int i = 0; i < m_bullets.size(); i++)
  //   m_bullets[i]->draw();

  int size = sizeof(m_bulletArray) / sizeof(Bullet*);

  for(int i = 0; i < size; i++)
  {
    if(m_bulletArray[i] != 0)
      m_bulletArray[i]->draw();
  }

  TheTextManager::Instance()->drawText("GameFrameWork HW2", 50, 50, m_pRenderer);

  SDL_RenderPresent(m_pRenderer);
}

// Fixed Update
void Game::update()
{
  for(auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
  {
    if(it->second != 0)
      it->second->update();
  }

  // for(int i = 0; i < m_bullets.size(); ++i)
  //   m_bullets[i]->update();

  int size = sizeof(m_bulletArray) / sizeof(Bullet*);

  for(int i = 0; i < size; i++)
  {
    if(m_bulletArray[i] != 0)
      m_bulletArray[i]->update();
  }
    
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

	if( m_cameraRect.x > (LEVEL_WIDTH - m_cameraRect.w) )
    m_cameraRect.x = LEVEL_WIDTH - m_cameraRect.w;
    
	if( m_cameraRect.y > (LEVEL_HEIGHT - m_cameraRect.h) )
		m_cameraRect.y = LEVEL_HEIGHT - m_cameraRect.h;
}

void Game::clean()
{
  SDL_DestroyWindow(m_pWindow);
  SDL_DestroyRenderer(m_pRenderer);
  SDL_Quit();
}