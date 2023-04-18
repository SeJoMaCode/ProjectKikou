#include "object.hpp"
#include <SDL2/SDL_pixels.h>

Object::Object(int x, int y, int w, int h, SDL_Color c)
    : m_rect({x, y, w, h}), m_color(c) {}

Object::~Object() {}

void Object::render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
  SDL_RenderFillRect(renderer, &m_rect);
}
