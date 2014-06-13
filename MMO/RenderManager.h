//
//  RenderManager.h
//  MMO
//
//  Created by Cole Faust on 12/19/13.
//  Copyright (c) 2013 Cole Faust. All rights reserved.
//

#ifndef __MMO__RenderManager__
#define __MMO__RenderManager__

#include "SDL2.h"
#include <iostream>

class RenderManager
{
public:
    SDL_Surface* loadSurface(std::string path);
    SDL_Texture* loadTexture(std::string path, int* width, int* height);
    SDL_Texture* loadTexture(std::string path);
    SDL_Texture* createTextureFromSurface(SDL_Surface* surface);
    SDL_Surface* createSDLSurface(int width, int height);
    void scaleRenderer(float x, float y);
    float getScaleX();
    float getScaleY();
    int getScreenX();
    int getScreenY();
    int getScaledScreenX();
    int getScaledScreenY();
    void clearScreen();
    void updateScreen();
    void init(SDL_Window* window);
    void cleanup();
    static RenderManager* getInstance()
    {
        static RenderManager* instance;
        if(instance == NULL)
            instance = new RenderManager();
        return instance;
    }
    SDL_Renderer *renderer;
private:
    RenderManager() {};
    RenderManager(RenderManager const&);  // Don't Implement
    void operator=(RenderManager const&); // Don't implement
    
    SDL_Window *window;
    float scaleX;
    float scaleY;
    int screenX = 640;
    int screenY = 480;
};

#endif /* defined(__MMO__RenderManager__) */
