#include "player.hpp"
#include "object.hpp"
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <cmath>
#include <iostream>
#include <vector>

Player::Player(int x, int y, int w, int h)
    : Object(x, y, w, h, {255, 255, 255, 255}), m_health(100),
      m_speed(2), m_velocity{0, 0}, m_heading(0.0), m_fov(1.f) {
  for (int i = 0; i < 10; i++) {
    m_inventory[i] = 0;
  }
}

Player::~Player() {}

void Player::render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
  SDL_RenderFillRect(renderer, &m_rect);
  int xCenter = m_rect.x + m_rect.w / 2;
  int yCenter = m_rect.y + m_rect.h / 2;
  SDL_RenderDrawLine(renderer, xCenter, yCenter,
                     xCenter + (std::cos(m_heading) * 10),
                     yCenter + (std::sin(m_heading) * 10));
}

void Player::useItem(int itemId) {}

void Player::handleInput() {
  const Uint8 *keystates = SDL_GetKeyboardState(nullptr);

  if (keystates[SDL_SCANCODE_UP]) {
    m_velocity[0] = 1;
  }
  if (keystates[SDL_SCANCODE_DOWN]) {
    m_velocity[0] = -1;
  }
  if (keystates[SDL_SCANCODE_LEFT]) {
    changeHeading(-1);
  }
  if (keystates[SDL_SCANCODE_RIGHT]) {
    changeHeading(1);
  }
  if (!keystates[SDL_SCANCODE_UP] && !keystates[SDL_SCANCODE_DOWN]) {
    m_velocity[0] = 0;
  }
}

int Player::getHealth() const { return m_health; }

void Player::setHealth(int health) { m_health = health; }

bool Player::checkCollision(std::vector<Object *> &objs) {

  for (auto obj : objs) {
    if (SDL_HasIntersection(&m_rect, obj->getRect())) {
      return true;
    }
  }

  return false;
}

void Player::move(std::vector<Object *> &objs) {
  SDL_Rect oldRect = m_rect;

  m_rect.x += std::round(std::cos(m_heading) * m_speed * m_velocity[0]);
  m_rect.y += std::round(std::sin(m_heading) * m_speed * m_velocity[0]);

  if (checkCollision(objs)) {
    m_rect = oldRect;
    m_rect.x += std::round(std::cos(m_heading) * m_velocity[0]);
    if (checkCollision(objs)) {
      m_rect = oldRect;
    } else {
      oldRect.x = m_rect.x;
    }
    m_rect.y += std::round(std::sin(m_heading) * m_velocity[0]);
    if (checkCollision(objs)) {
      m_rect = oldRect;
    }
  }
}

void Player::changeHeading(float a) { m_heading += a * 0.05f; }

bool rayEnd(float x, float y, std::vector<Object *> &objs) {
  for (auto obj : objs) {
    SDL_Rect *objRect = obj->getRect();
    if (x > objRect->x and x < objRect->x + objRect->w) {
      if (y > objRect->y and y < objRect->y + objRect->h) {
        return true;
      }
    }
  }
  return false;
}

void Player::renderFPV(SDL_Renderer *renderer, std::vector<Object *> &objs) {
  int viewWidth = 800;

  for (int x = 0; x < viewWidth; x++) {
    float rayAngle =
        (m_heading - m_fov / 2.f) + ((float)x / (float)viewWidth) * m_fov;
    float rayX = std::cos(rayAngle);
    float rayY = std::sin(rayAngle);
    // float rayX = std::cos(rayAngle * M_PI / 180.f);
    // float rayY = std::sin(rayAngle * M_PI / 180.f);

    float dist = 0.f;
    float maxDist = 800.f;
    while (dist < maxDist) {
      float testX = m_rect.x + m_rect.w / 2.f + rayX * dist;
      float testY = m_rect.y + m_rect.h / 2.f + rayY * dist;

      if (rayEnd(testX, testY, objs)) {
        int color = 255 - (int)(0.f + ((155.f - 0.f) / 800.f) * dist);
        SDL_SetRenderDrawColor(renderer, color, 0, 0, 255);
        SDL_RenderDrawLine(renderer, x, 300 - (maxDist - dist) / 4, x,
                           300 + (maxDist - dist) / 4);
        break;
      }

      dist += 1.f;
    }
  }
}
