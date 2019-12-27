//
//  sidebar.cpp
//  tokenRPN
//
//  Created by Swordfish on 12/9/18.
//  Copyright © 2018 Swordfish. All rights reserved.
//

#include "Includes.hpp"

Sidebar::Sidebar(){
    
}

Sidebar::Sidebar(float left, float width):_left(left), _width(width){
    cout<<"Sidebar CTOR: TOP"<<endl;
    items.reserve(30);
    
    //set up the sidebar rectangle:
    rect.setFillColor(sf::Color(0,0,0)); //(192,192,192)); //silver
    rect.setPosition(sf::Vector2f(left, 0));
    rect.setSize(sf::Vector2f(width, SCREEN_HEIGHT));
    cout<<"Sidebar CTOR: about to load font."<<endl;
    
    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //the font file must be in the "working directory"
    // check projects->run->working directory
    //      [Make sure it's not pointing to the app file]
    
    if (!font.loadFromFile(resourcePath() + "Cambriai.ttf")){
        cout<<"Sidebar() CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }
    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    cout<<"Sidebar CTOR: loaded font."<<endl;
    
    //. . . . . text / font problems: . . . . . . . .
    //initializing text object in this way caused problems
    // (hangs!)
    //only when sb_text was a private member and worked fine
    //when it was a public member. Probably not releavant,
    //but still strange!
    //
    //sb_text = sf::Text("Initial String for myTextLabel", font);
    //
    //. . . . . . . . . . . . . . . . . . . . . . . . .
    cout<<"Sidebar CTOR: Text object initialized."<<endl;
    
    ////this is how you would position text on screen:
    
    //items.push_back("");
    items.push_back("Function History:");
    //Fill the items vector with empty strings so that we can use [] to read them:
    cout<<"Sidebar: CTOR: Exit."<<endl;
}

void Sidebar::pushIntoSidebar(string function){
    bool duplicate = false;
    for (vector<string>::iterator it = items.begin(); it!= items.end(); it++){
        if(function == *(it)){
            duplicate = true;
        }
    }
    if(duplicate == false){
        items.push_back(function);
    }
}

string Sidebar::getFromSidebar(int index){
    return items.at(index);
}

void Sidebar::setMouseClickValue(sf::Window& window, sf::Mouse currentMouse){
    _mouseX = currentMouse.getPosition(window).x;
    _mouseY = currentMouse.getPosition(window).y;
    //cout << _mouseX << " " << _mouseY << endl;
}

void Sidebar::draw(sf::RenderWindow& window){
    
    const double VERTICAL_LINE_SPACING = 50.0;
    const double LEFT_MARGIN = 10.0;
    
    window.draw(rect);
    float height = 10;
    
    for (vector<string>::iterator it = items.begin();
         it!= items.end(); it++){
        bool blank = false;
        //cout << "in sidebar loop" << endl;
        
        if (strlen(it->c_str()) == 0){
            //empty rows must be taken into account (getLocalBounds())
            //    but not drawn
            blank = true;
            
            sb_text.setString("");
        }
        else{
            sb_text.setString(it->c_str());
            
        }
        
        if (blank == false){
            sb_text.setPosition(sf::Vector2f(_left+LEFT_MARGIN, height));
            height += VERTICAL_LINE_SPACING;
            sb_text.setFont(font);
            sb_text.setCharacterSize(30);
            //sb_text.setStyle(sf::Text::Bold);
            sb_text.setColor(sf::Color::Yellow);
            if(sb_text.getGlobalBounds().contains(_mouseX, _mouseY)){
                //cout << "clicked an item!" << endl;
                _clickedHistoryItem = *(it);
                _clickedAnItem = true;
                _mouseX = 0;
                _mouseY = 0;
            }
            window.draw(sb_text);
        }}
}

string Sidebar::getHistoryItem(){
    return _clickedHistoryItem;
}

//string checkFunction(sf::Mouse mousePosition){
//    for(){
//
//    }
//    return items[index];
//}

string& Sidebar::operator [](int index){
    return items[index];
}
