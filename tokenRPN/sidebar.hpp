//
//  sidebar.hpp
//  tokenRPN
//
//  Created by Swordfish on 12/9/18.
//  Copyright © 2018 Swordfish. All rights reserved.
//

#ifndef sidebar_hpp
#define sidebar_hpp

#include "Includes.hpp"


class Sidebar
{
public:
    Sidebar();
    Sidebar(float left, float width);
    void draw(sf::RenderWindow& window);
    string& operator [](int index);
    void pushIntoSidebar(string function);
    string getFromSidebar(int index);
    void setMouseClickValue(sf::Window& window, sf::Mouse currentMouse);
    bool _clickedAnItem;
    string getHistoryItem();
    
private:
    sf::RectangleShape rect;            //sidebar rectangle
    vector<string> items;               //strings to place on the sidebar
    sf::Font font;                      //used to draw text
    sf::Text sb_text;                   //used to draw strings on the window object
    int _mouseX, _mouseY;
    string _clickedHistoryItem;
    float _left;
    float _width;
    
};
#endif /* sidebar_hpp */
