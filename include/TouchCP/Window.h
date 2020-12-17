#pragma once
#include <SDL2/SDL.h>
#include <exception>
#include <string>
#include "SDLException.h"

/**
 * @brief The main window object
*/
class Window
{
public:
    /**
     * @brief Create a window object
     * @param width The window width
     * @param height The window height
     * @param color The window color
    */
    Window(int width, int height, SDL_Color color);
    ~Window();
    /**
     * @brief Get the native SDL window object
     * @return The native SDL window
    */
    SDL_Window* getWindowObject() const;
    /**
     * @brief Get the native SDL surface
     * @return The native SDL surface
    */
    SDL_Surface* getSurface() const;
    /**
     * @brief Get the native SDL renderer
     * @return The SDL renderer
    */
    SDL_Renderer* getRenderer() const;
    void update();
private:
    SDL_Window* window = nullptr;
    SDL_Surface* screenSurf = nullptr;
    SDL_Renderer* renderer = nullptr;
    int WIDTH, HEIGHT;
};

