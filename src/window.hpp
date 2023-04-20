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

  bool pollEvents();

  void clear();
  void render(Object &obj);
  void render(std::vector<Object *> &objs);
  void display();

protected:
  SDL_Window *m_window;
  SDL_Renderer *m_renderer;
};

#endif // WINDOW_HPP
