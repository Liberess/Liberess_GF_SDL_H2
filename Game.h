#pragma once
#ifndef __Game__
#define __Game__

#include "SDL.h"
//#include "GameObject.h"
#include "Bullet.h"
#include "Vector2D.h"
#include "SDLGameObject.h"
#include <map>
#include <vector>
#include <iostream>

class Game
{
public:
  std::map<std::string, SDLGameObject*> m_gameObjects;
  static Game* Instance()
  {
    if (s_pInstance == 0) s_pInstance = new Game();
    return s_pInstance;
  }
  ~Game() {}
  bool init(const char* title, int xpos, int ypos, int height, int width, int flags);
  void parseSprite(std::string path, std::string id);
  void render();
  void update();
  bool running() const { return m_bRunning; };
  void handleEvents() { TheInputHandler::Instance()->Update(); };
  void clean();
  void quit() { m_bRunning = false; }
  SDL_Renderer* getRenderer() const { return m_pRenderer; }
  int getScreenWidth() const { return m_screenWidth; }
  int getScreenHeight() const { return m_screenHeight; }
  void instantiateBullet(const SDL_Rect& rect, const Vector2D& dirc);
  SDL_Rect getCameraRect() const { return m_cameraRect; }
  void updateCamera();
  void destroyBullet(int id);
  void destroyGameObject(std::string key);

private:
  Game() {}
  static Game* s_pInstance;
  SDL_Window* m_pWindow;
  SDL_Renderer* m_pRenderer;
  bool m_bRunning;
  std::vector<Bullet*> m_bullets;
  //std::vector<GameObject*> m_gameObjects;
  const static int LEVEL_WIDTH = 640;
  const static int LEVEL_HEIGHT = 480;
  int m_screenWidth, m_screenHeight;
  SDL_Rect m_cameraRect;
  int m_bulletID;
  const static int MAX_BULLET = 3;
};

typedef Game TheGame;

#endif