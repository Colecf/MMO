//
//  FPSCounter.h
//  MMO
//
//  Created by Cole Faust on 2/3/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#ifndef __MMO__FPSCounter__
#define __MMO__FPSCounter__

#define TICKLISTSIZE 100

class FPSCounter
{
public:
    FPSCounter();
    void nextFrame();
    float getFPS();
    void limitTo(int fps);
private:
    int lastFrameTime;
    int ticksum;
    int tickindex;
    int ticklist[TICKLISTSIZE];
};

#endif /* defined(__MMO__FPSCounter__) */
