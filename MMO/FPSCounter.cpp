//
//  FPSCounter.cpp
//  MMO
//
//  Created by Cole Faust on 2/3/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#include "FPSCounter.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>

FPSCounter::FPSCounter()
{
    ticksum = 0;
    tickindex = 0;
    lastFrameTime = SDL_GetTicks();
    
    for (int i=0; i<TICKLISTSIZE; i++) {
        ticklist[i] = 0;
    }
}
void FPSCounter::nextFrame()
{
    //https://stackoverflow.com/questions/87304/calculating-frames-per-second-in-a-game
    Uint32 newTick = SDL_GetTicks()-lastFrameTime;
    ticksum -= ticklist[tickindex];
    ticksum += newTick;
    ticklist[tickindex] = newTick;
    if (++tickindex == TICKLISTSIZE)
    {
        tickindex = 0;
    }
    lastFrameTime = SDL_GetTicks();
}

float FPSCounter::getFPS()
{
    //Thousands of a second per frame, on average
    float result = (float)ticksum / (float)TICKLISTSIZE;
    //seconds per frame
    result /= 1000;
    //frames per second
    result = 1 / result;
    return result;
}
void FPSCounter::limitTo(int fps)
{
    float tickAverage = (float)ticksum / (float)TICKLISTSIZE;
    //seconds per frame
    float tpf = 1.0f/(float)fps;
    //ticks per frame
    tpf *= 1000;
    
    //std::cout << "FPS: "<< getFPS() << " TickAverage: " << tickAverage << std::endl;
    
    int i = tickindex-1;
    if (i < 0)
    {
        i = TICKLISTSIZE-1;
    }
    if (tickAverage < tpf)
    {
        //std::cout << "wait: " << ceil(tpf-tickAverage) << std::endl;
        SDL_Delay(ceil(tpf-tickAverage));
    }
}