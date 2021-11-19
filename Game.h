#pragma once
#ifndef __Game__
#define __Game__

#include "SDL.h"
//#include "GameObject.h"
#include "SDLGameObject.h"
#include <map>
#include <vector>

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
  void render();
  void update();
  bool running();
  void handleEvents();
  void clean();
  void quit() { m_bRunning = false; }
  SDL_Renderer* getRenderer() const { return m_pRenderer; }
  int getScreenWidth() const { return m_screenWidth; }
  int getScreenHeight() const { return m_screenHeight; }
  void instantiateBullet(Vector2D pos);
  SDL_Rect getCameraRect() const { return m_cameraRect; }
  void updateCamera();

private:
  Game() {}
  static Game* s_pInstance;
  SDL_Window* m_pWindow;
  SDL_Renderer* m_pRenderer;
  bool m_bRunning;
  std::vector<GameObject*> m_bullets;
  //std::vector<GameObject*> m_gameObjects;
  int m_levelWidth;
  int m_levelHeight;
  int m_screenWidth;
  int m_screenHeight;
  SDL_Rect m_cameraRect;
};

typedef Game TheGame;

#endif