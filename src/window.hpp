#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "object.hpp"
#include "player.hpp"
#include <SDL2/SDL.h>
#include <vector>

class Window {
public:
  Window(const char *title, int width, int height);
  ~Window();

  bool pollEvents(Player &player);

  void addRenderObject(Object &obj);
  void addRenderObjects(std::vector<Object *> &objs);
  void removeRenderObject(Object &obj);
  void clearRenderObjects();

  void render();

protected:
  SDL_Window *m_window;
  SDL_Renderer *m_renderer;
  std::vector<Object *> m_renderObjects;
};

#endif // WINDOW_HPP
