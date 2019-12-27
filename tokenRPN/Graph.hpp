//
//  Graph.hpp
//  tokenRPN
//
//  Created by Swordfish on 11/25/18.
//  Copyright © 2018 Swordfish. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include "Queue.hpp"

class Graph{
public:
    
    Graph();
    
    Graph(Queue<Token*>& functionToGraph);
    
    Queue<sf::Vector2f> plot(double intervalStart, double intervalEnd, double numberOfSubdivisions);
    
    void draw(sf::RenderWindow& window, sf::Font font);
    
    Queue<sf::Vector2f> transformCartesianToScreen(Queue<sf::Vector2f>& plotInCartesian);
    
    sf::Vector2f transformCartesianToScreen(sf::Vector2f pointToTransform);
    
    void setGraphView(double xBegin, double xEnd, double yBegin, double yEnd);
    
    void setSubdivisions(double numberOfSubdivisions);
    
    double evaluateToPlot(Queue<Token*>& operationQueue, double evaluateAt);
    
    void setNewFunction(Queue<Token*> postFixExpression);
    
    void clearGraph();
    
    double getYMax();
    
    double getYMin();
    
    double getXMax();
    
    double getXMin();
    
    void setDisplayFunction(string displayFunction);
    
    string getDisplayFunction();
    
    bool _badExpression;
    
private:
    
    Queue<Token*> _functionToGraph;                     //the function in postfix notation
    string _functionToDisplay;                          //the string of the function above
    Queue<sf::Vector2f> _cartesianGraph, _screenGraph;  //the graphs of the vector2fs, or points, in cartesian and screen coordinates
    double _xMax, _xMin, _yMax, _yMin;                  //my bounds for the graph window
    int _subDivisions;                                  //number of points to graph
    
};

#endif /* Graph_hpp */
