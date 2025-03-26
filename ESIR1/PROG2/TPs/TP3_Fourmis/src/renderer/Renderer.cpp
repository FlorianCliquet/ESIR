#include <renderer/Renderer.hpp>

/// <summary>
/// The singleton
/// </summary>
std::unique_ptr<Renderer> Renderer::m_singleton = nullptr;

/// <summary>
/// Initializes a new instance of the <see cref="Renderer"/> class.
/// </summary>
/// <param name="width">The width of the render window.</param>
/// <param name="height">The height of the render window.</param>

Renderer::Renderer(unsigned int width, unsigned int height) : m_width(width), m_height(height) {
  if (SDL_CreateWindowAndRenderer(m_width, m_height, SDL_WINDOW_SHOWN, &window, &renderer)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s",
                 SDL_GetError());
    exit(3);
  }
}

Renderer::~Renderer() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

/// <summary>
/// Draws the pixels.
/// </summary>

void Renderer::flushPixels() {
  if (m_pixels.size() > 0) {
    auto compare = [](const std::pair<Color, SDL_Point> &v1,
                      const std::pair<Color, SDL_Point> &v2) { return v1.first < v2.first; };
    ::std::sort(m_pixels.begin(), m_pixels.end(), compare);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    ::std::vector<SDL_Point> tmp;
    Color lastColor = m_pixels[0].first;
    tmp.push_back(m_pixels[0].second);
    for (size_t cpt = 0; cpt < m_pixels.size(); ++cpt) {
      if (m_pixels[cpt].first == lastColor) {
        tmp.push_back(m_pixels[cpt].second);
      } else {
        SDL_Point *points = &tmp[0];
        SDL_SetRenderDrawColor(renderer, lastColor[0], lastColor[1], lastColor[2], lastColor[3]);
        SDL_RenderDrawPoints(renderer, points, tmp.size());
        tmp.erase(tmp.begin(), tmp.end());
        lastColor = m_pixels[cpt].first;
        tmp.push_back(m_pixels[cpt].second);
      }
    }
    SDL_Point *points = &tmp[0];
    SDL_SetRenderDrawColor(renderer, lastColor[0], lastColor[1], lastColor[2], lastColor[3]);
    SDL_RenderDrawPoints(renderer, points, tmp.size());
    m_pixels.erase(m_pixels.begin(), m_pixels.end());
  }
}

/// <summary>
/// Draws the strings.
/// </summary>

void Renderer::flushStrings() {
  for (auto it = m_strings.begin(), end = m_strings.end(); it != end; ++it) {
    stringRGBA(getSdlRenderer(), (Sint16)it->position[0], (Sint16)it->position[1],
               it->string.c_str(), it->color[0], it->color[1], it->color[2], it->color[3]);
  }
  m_strings.erase(m_strings.begin(), m_strings.end());
}

/// <summary>
/// Draws the circles.
/// </summary>

void Renderer::flushCircles() {
  for (auto it = m_circles.begin(), end = m_circles.end(); it != end; ++it) {
    filledCircleRGBA(getSdlRenderer(), (Sint16)it->center[0], (Sint16)it->center[1],
                     (Sint16)it->radius, it->color[0], it->color[1], it->color[2], it->color[3]);
  }
  m_circles.erase(m_circles.begin(), m_circles.end());
}

/// <summary>
/// Draws a pixel.
/// </summary>
/// <param name="coordinates">The coordinates.</param>
/// <param name="color">The color.</param>

void Renderer::drawPixel(Vector2<float> const &coordinates, const Color &color) {
  m_pixels.push_back({color, {(Sint16)coordinates[0], (Sint16)coordinates[1]}});
}

/// <summary>
/// Draws a circle.
/// </summary>
/// <param name="center">The center.</param>
/// <param name="radius">The radius.</param>
/// <param name="color">The color.</param>

void Renderer::drawCircle(Vector2<float> const &center, float radius, const Color &color) {
  Circle circle = {center, radius, color};
  m_circles.push_back(circle);
}

/// <summary>
/// Draws a string.
/// </summary>
/// <param name="position">The position.</param>
/// <param name="str">The string.</param>
/// <param name="color">The color.</param>

void Renderer::drawString(Vector2<float> const &position, const ::std::string &str,
                          const Color &color) {
  String tmp = {position, color, str};
  m_strings.push_back(tmp);
}

/// <summary>
/// Draws everything on the screen.
/// </summary>

void Renderer::flush() {
  // We draw anything needed
  flushCircles();
  flushPixels();
  flushStrings();
  // After drawing
  SDL_RenderPresent(renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

/// <summary>
/// Initializes the renderer (singleton).
/// </summary>
/// <param name="width">The width.</param>
/// <param name="height">The height.</param>

void Renderer::initialize(unsigned int width, unsigned int height) {
  m_singleton = std::unique_ptr<Renderer>(new Renderer(width, height));
}

void Renderer::finalize() { m_singleton = nullptr; }
