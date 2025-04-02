#include "agents-env/Anthill.hpp"
#include "agents-env/Environment.hpp"
#include "agents-env/Food.hpp"
#include "renderer/Renderer.hpp"
#include "utils/Timer.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>
#include <time.h>
static unsigned int windowWidth() { return 1024; }
static unsigned int windowHeight() { return 700; }

/// <summary>
/// called each time a key is pressed.
/// </summary>
/// <param name="key">The key.</param>
/// <param name="environment">The environment.</param>
void onKeyPressed(char key, Environment *environment) {
  if (key == 'f') {
    // Génère une quantité de nourriture aléatoire entre 200 et 2000
    float quantity = MathUtils::random(200, 2000);
    // Génère une position aléatoire
    Vector2<float> position = environment->randomPosition();
    // Crée une nouvelle instance de nourriture
    new Food(environment, position, quantity);
  } else if (key == 'd') {
    // Supprime une instance aléatoire de nourriture
    std::vector<Food *> allFood = environment->getAllInstancesOf<Food>();
    if (!allFood.empty())
      allFood[0]->setStatus(Agent::destroy);
  } else if (key == 't') {
    // Prends une quantité aléatoire de nourriture
    float quantity = MathUtils::random(15, 50);
    std::vector<Food *> allFood = environment->getAllInstancesOf<Food>();
    if (!allFood.empty()) {
      allFood[0]->collectFood(quantity);
    }
  } else if (key == 'a') {
    Vector2<float> position = environment->randomPosition();
    new Anthill(environment, position);
  }
}

/// <summary>
/// Called at each time step.
/// </summary>
void onSimulate() { Agent::simulate(); }

/// <summary>
/// The main program.
/// </summary>
/// <param name="argc">The number of arguments.</param>
/// <param name="argv">The arguments.</param>
/// <returns></returns>
int main(int /*argc*/, char ** /*argv*/) {
  // 1 - Initialization of SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS /* | SDL_INIT_AUDIO*/) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return 1;
  }
  // 2 - Initialization of the renderer
  Renderer::initialize(windowWidth(), windowHeight());

  // 3 - Creation of an environment
  Environment environment(windowWidth(), windowHeight());

  // 4 - We change the seed of the random number generator
  srand((unsigned int)time(NULL));

  // The main event loop...
  SDL_Event event;
  bool exit = false;
  
  while (!exit) {
    // 1 - We handle events
    while (SDL_PollEvent(&event)) {
      if ((event.type == SDL_QUIT) || (event.type == SDL_KEYDOWN && event.key.keysym.sym == 'q')) {
        ::std::cout << "Exit signal detected" << ::std::endl;
        exit = true;
        break;
      }
      if (event.type == SDL_KEYDOWN) {
        onKeyPressed((char)event.key.keysym.sym, &environment);
      }
    }
    // 2 - We update the simulation
    Timer::update(0.5);
    onSimulate();
    // 3 - We render the scene
    Renderer::getInstance()->flush();
  }

  std::cout << "Shutting down renderer..." << std::endl;
  Renderer::finalize();

  std::cout << "Shutting down SDL" << std::endl;
  SDL_Quit();

  std::cout << "Nettoyage des agents" << std::endl;
  Agent::finalize();
  return 0;
}
