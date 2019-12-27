//
//  Constants.hpp
//  tokenRPN
//
//  Created by Swordfish on 11/27/18.
//  Copyright © 2018 Swordfish. All rights reserved.
//

#ifndef Constants_hpp
#define Constants_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

const sf::VideoMode DESKTOP = sf::VideoMode::getDesktopMode();
const sf::VideoMode HALF_DESKTOP((DESKTOP.width)/2, (DESKTOP.height)/2, DESKTOP.bitsPerPixel);

const float SCREEN_WIDTH = HALF_DESKTOP.width;
const float SCREEN_HEIGHT = HALF_DESKTOP.height;
const float WORK_PANEL = SCREEN_WIDTH*4/5;
const float SIDE_BAR = SCREEN_WIDTH*1/5;

const int SB_MOUSE_POSITION = 0;
const int SB_MOUSE_CLICKED = SB_MOUSE_POSITION + 1;
const int SB_KEY_PRESSED = SB_MOUSE_CLICKED + 1;
#endif /* Constants_hpp */
