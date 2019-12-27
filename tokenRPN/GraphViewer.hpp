//
//  GraphViewer.hpp
//  tokenRPN
//
//  Created by Swordfish on 12/9/18.
//  Copyright © 2018 Swordfish. All rights reserved.
//

#ifndef GraphViewer_hpp
#define GraphViewer_hpp

#include "Includes.hpp"

class GraphViewer{
public:
    
    GraphViewer();
    void run();
    void processEvents();
    void update();
    void render();
    void draw();
    Queue<Token*> parseInput(stringstream& lineStream);
    Queue<Token*> infixToPostfix(Queue<Token*>& infixQueue);
    
private:
    sf::RenderWindow window;            //container for the graph
    Graph currentGraph;                 //the graph object which sits inside WORK_PANEL
    sf::Font font;                      //font to draw on main screen
    sf::Text functionOrErrorLabel;      //text to draw on main screen
    sf::Text myCurrentFunction;         //blue text that shows the function currently being displayed
    Sidebar sidebar;                    //rectangular message sidebar
    string functionToGraph;             //the function string as it's being typed
};

#endif /* GraphViewer_hpp */
