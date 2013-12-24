//
//  ResourcePath.m
//  MMO
//
//  Created by Cole Faust on 12/19/13.
//  Copyright (c) 2013 Cole Faust. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "ResourcePath.h"


std::string resourcePath = "";

std::string getResourcePath()
{
    if(resourcePath != "")
        return resourcePath;
    resourcePath = [[[NSBundle mainBundle] resourcePath] UTF8String];
    resourcePath += "/";
    return resourcePath;
}
