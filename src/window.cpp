#include "window.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <algorithm>
#include <iterator>

Window::Window(const char *title, int width, int height) {
  SDL_Init(SDL_INIT_EVERYTHING);

  m_window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       width, height, SDL_WINDOW_SHOWN);

  if (m_window == nullptr) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
  }

  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

  if (m_renderer == nullptr) {
    SDL_Log("Failed to create renderer: %s", SDL_GetError());
  }
}

Window::~Window() {
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);

  SDL_Quit();
}

bool Window::pollEvents(Player &player) {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    switch (event.type) {
    case SDL_QUIT:
      return true;
    case SDL_KEYDOWN:
      if (keystates[SDL_SCANCODE_UP]) {
        player.setForwardVelocity(1);
        player.move();
      }
      if (keystates[SDL_SCANCODE_DOWN]) {
        player.setForwardVelocity(-1);
        player.move();
      }
      if (keystates[SDL_SCANCODE_LEFT]) {
        player.changeHeading(-1);
      }
      if (keystates[SDL_SCANCODE_RIGHT]) {
        player.changeHeading(1);
      }
      break;
    case SDL_KEYUP:
      if (!keystates[SDL_SCANCODE_UP] && !keystates[SDL_SCANCODE_DOWN]) {
        player.setForwardVelocity(0);
        player.move();
      }
    }
  }
  return false;
}

void Window::addRenderObject(Object &obj) { m_renderObjects.push_back(&obj); }

void Window::addRenderObjects(std::vector<Object *> &objs) {
  m_renderObjects.insert(m_renderObjects.end(), objs.begin(), objs.end());
}

void Window::removeRenderObject(Object &obj) {
  m_renderObjects.erase(
      std::remove(m_renderObjects.begin(), m_renderObjects.end(), &obj),
      m_renderObjects.end());
}

void Window::clearRenderObjects() { m_renderObjects.clear(); }

void Window::render() {
  // Clear Screen
  SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
  SDL_RenderClear(m_renderer);

  // render objects
  for (auto obj : m_renderObjects) {
    obj->render(m_renderer);
  }

  // Update screen
  SDL_RenderPresent(m_renderer);
}
