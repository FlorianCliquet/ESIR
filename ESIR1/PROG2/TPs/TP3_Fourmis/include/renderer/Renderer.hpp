#ifndef _Renderer_H
#define _Renderer_H

#include "utils/Vector2.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

/// <summary>
/// Class used to render 2D graphics.
/// </summary>
class Renderer {
public:
  /// <summary>
  /// A RGBA (Red, Green, Blue, Alpha) color. Alpha is the transparency channel. Each value is in
  /// the interval [0;255]. For the alpha channel, 255 means opaque, 0 means transparent.
  /// </summary>
  class Color {
    union {
      Uint32 m_colorValue;
      Uint8 m_color[4];
    };

  public:
    /// <summary>
    /// Initializes a new instance of the <see cref="Color"/> class.
    /// </summary>
    /// <param name="red">The red value in interval [0;255].</param>
    /// <param name="green">The green value in interval [0;255].</param>
    /// <param name="blue">The blue value in interval [0;255].</param>
    /// <param name="alpha">The alpha value in interval [0;255].</param>
    Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255) {
      m_color[0] = red;
      m_color[1] = green;
      m_color[2] = blue;
      m_color[3] = alpha;
    }

    /// <summary>
    /// Gets the value associated with the red (0), green (1), blue (2) or alpha (3) channel.
    /// </summary>
    /// <param name="index">The index.</param>
    /// <returns></returns>
    Uint8 &operator[](unsigned int index) { return m_color[index]; }

    /// <summary>
    /// Gets the value associated with the red (0), green (1), blue (2) or alpha (3) channel.
    /// </summary>
    /// <param name="index">The index.</param>
    /// <returns></returns>
    Sint8 operator[](unsigned int index) const { return m_color[index]; }

    /// <summary>
    /// Lexicographical comparison between two colors (mainly for internal use).
    /// </summary>
    /// <param name="color">The color.</param>
    /// <returns></returns>
    bool operator<(const Color &color) const { return m_colorValue < color.m_colorValue; }

    /// <summary>
    /// Equality comparator.
    /// </summary>
    /// <param name="color">The color.</param>
    /// <returns></returns>
    bool operator==(const Color &color) const { return m_colorValue == color.m_colorValue; }
  };

protected:
  /// <summary>
  /// Internal representation of a string displayed on the screen
  /// </summary>
  struct String {
    Vector2<float> position;
    Color color;
    std::string string;
  };

  /// <summary>
  /// Internal representation of a circle
  /// </summary>
  struct Circle {
    Vector2<float> center;
    float radius;
    Color color;
  };

  static std::unique_ptr<Renderer> m_singleton;

  /// <summary>
  /// The height and width of the rendering window
  /// </summary>
  unsigned int m_width, m_height;
  /// <summary>
  /// The rendering window (provided by SDL)
  /// </summary>
  SDL_Window *window;
  /// <summary>
  /// The internal renderer (provided by SDL)
  /// </summary>
  SDL_Renderer *renderer;

  /// <summary>
  /// The pixels that should be displayed
  /// </summary>
  ::std::vector<::std::pair<Color, SDL_Point>> m_pixels;
  /// <summary>
  /// The strings that should be displayed
  /// </summary>
  ::std::vector<String> m_strings;
  /// <summary>
  /// The circles that should be displayed
  /// </summary>
  ::std::vector<Circle> m_circles;

  /// <summary>
  /// Initializes a new instance of the <see cref="Renderer"/> class.
  /// </summary>
  /// <param name="width">The width of the render window.</param>
  /// <param name="height">The height of the render window.</param>
  Renderer(unsigned int width, unsigned int height);

  /// <summary>
  /// Draws the pixels.
  /// </summary>
  void flushPixels();

  /// <summary>
  /// Draws the strings.
  /// </summary>
  void flushStrings();

  /// <summary>
  /// Draws the circles.
  /// </summary>
  void flushCircles();

public:
  /// <summary>
  /// Finalizes an instance of the <see cref="Renderer"/> class.
  /// </summary>
  ~Renderer();

  /// <summary>
  /// Gets the internal SDL renderer.
  /// </summary>
  /// <returns></returns>
  SDL_Renderer *getSdlRenderer() const { return renderer; }

  /// <summary>
  /// The width of the rendering window
  /// </summary>
  /// <returns></returns>
  unsigned int width() const { return m_width; }

  /// <summary>
  /// The height of the rendering window.
  /// </summary>
  /// <returns></returns>
  unsigned int height() const { return m_height; }

  /// <summary>
  /// Draws a pixel.
  /// </summary>
  /// <param name="coordinates">The coordinates.</param>
  /// <param name="color">The color.</param>
  void drawPixel(Vector2<float> const &coordinates, const Color &color);

  /// <summary>
  /// Draws a circle.
  /// </summary>
  /// <param name="center">The center.</param>
  /// <param name="radius">The radius.</param>
  /// <param name="color">The color.</param>
  void drawCircle(Vector2<float> const &center, float radius, const Color &color);

  /// <summary>
  /// Draws a string.
  /// </summary>
  /// <param name="position">The position.</param>
  /// <param name="str">The string.</param>
  /// <param name="color">The color.</param>
  void drawString(Vector2<float> const &position, const ::std::string &str,
                  const Color &color = Color(255, 255, 255, 255));

  /// <summary>
  /// Draws everything on the screen.
  /// </summary>
  void flush();

  /// <summary>
  /// Initializes the renderer (singleton).
  /// </summary>
  /// <param name="width">The width.</param>
  /// <param name="height">The height.</param>
  static void initialize(unsigned int width, unsigned int height);

  /// <summary>
  /// Finalizes the instance of Renderer.
  /// </summary>
  static void finalize();

  /// <summary>
  /// Gets the instance of the renderer.
  /// </summary>
  /// <returns></returns>
  static Renderer *getInstance() { return m_singleton.get(); }
};

#endif
