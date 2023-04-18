#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>

class Object {
public:
  Object(int x, int y, int w, int h, SDL_Color c);
  virtual ~Object();

  virtual void render(SDL_Renderer *renderer);

protected:
  SDL_Rect m_rect;
  SDL_Color m_color;
};

#endif // OBJECT_HPP
