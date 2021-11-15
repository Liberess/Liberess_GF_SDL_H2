#pragma once
#ifndef __Game__
#define __Game__

#include "SDL.h"
#include "GameObject.h"
#include <map>
#include <vector>

class Game
{
public:
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
  vector getGameObjVector() const { return m_gameObjects; }

private:
  Game() {}
  static Game* s_pInstance;
  SDL_Window* m_pWindow;
  SDL_Renderer* m_pRenderer;
  bool m_bRunning;
  std::map<std::string, GameObject*> m_gameObjects;
  //std::vector<GameObject*> m_gameObjects;
  int m_screenWidth;
  int m_screenHeight;
};
typedef Game TheGame;

#endif