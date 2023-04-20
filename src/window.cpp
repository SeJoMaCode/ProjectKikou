#include "window.hpp"
#include "object.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <vector>

Window::Window(const char *title, int width, int height) {
  SDL_Init(SDL_INIT_EVERYTHING);

  m_window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       width, height, SDL_WINDOW_SHOWN);

  if (m_window == nullptr) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
  }

  m_renderer = SDL_CreateRenderer(
      m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (m_renderer == nullptr) {
    SDL_Log("Failed to create renderer: %s", SDL_GetError());
  }
}

Window::~Window() {
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);

  SDL_Quit();
}

bool Window::pollEvents() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      return true;
    }
  }
  return false;
}

SDL_Renderer *Window::getRenderer() const { return m_renderer; }

void Window::clear() {
  SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
  SDL_RenderClear(m_renderer);
}

void Window::render(Object &obj) { obj.render(m_renderer); }

void Window::render(std::vector<Object *> &objs) {
  for (auto &obj : objs) {
    obj->render(m_renderer);
  }
}

void Window::display() { SDL_RenderPresent(m_renderer); }
