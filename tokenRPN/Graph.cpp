//
//  Graph.cpp
//  tokenRPN
//
//  Created by Swordfish on 11/25/18.
//  Copyright © 2018 Swordfish. All rights reserved.
//
#include "Includes.hpp"

//default constructor, sets the minimum stuff that needs to be set.
Graph::Graph(){
    
    _yMax = 10;
    _yMin = -10;
    _xMax = 10;
    _xMin = -10;
    _subDivisions = 5000;
    _badExpression = false;
    
}

////constructor that's no longer used
//Graph::Graph(Queue<Token*>& functionToGraph){
//    _yMax = 10;
//    _yMin = -10;
//    _xMax = 10;
//    _xMin = -10;
//    _subDivisions = 12500;
//    _functionToGraph = functionToGraph;
//    _cartesianGraph = plot(_xMin, _xMax, _subDivisions);
//    _screenGraph = transformCartesianToScreen(_cartesianGraph);
//    _badExpression = false;
//}

//change the function and regenerate the point Queues. Used whenever we enter a new function into the program
void Graph::setNewFunction(Queue<Token*> postFixExpression){
    
    if(_badExpression == false){
        _functionToGraph = postFixExpression;
        _cartesianGraph = plot(_xMin, _xMax, _subDivisions);
        _screenGraph = transformCartesianToScreen(_cartesianGraph);
    }
}

//set the function display, the blue label that tells you what graph you're looking at
void Graph::setDisplayFunction(string displayFunction){
    _functionToDisplay = displayFunction;
}

//gets the function that's displayed in the corner of the graph
string Graph::getDisplayFunction(){
    return _functionToDisplay;
}

//takes a set of points and fills a Queue with a set of cartesian corresponding to the function private queue's expression
Queue<sf::Vector2f> Graph::plot(double intervalStart, double intervalEnd,
                                double numberOfSubdivisions){
    _xMax = intervalEnd;
    
    _xMin = intervalStart;
    
    //add .1 to start because if not the graph stops right before the edge of the screen, which looks ugly
    double intervalStep = (intervalEnd - intervalStart+.1) / numberOfSubdivisions;
    
    double xCoordinate = intervalStart, yCoordinate = 0;
    
    Queue<sf::Vector2f> plotQueue, plotToScreenQueue;
    
    Queue<Token*> expressionHolder;
    //cout << "numberOfSubdivisions: " << numberOfSubdivisions << endl;
    for(int i = 0; i <= numberOfSubdivisions; i++){
        expressionHolder = _functionToGraph;
        
        //evaluate expression with variable equal to whatever
        yCoordinate = evaluateToPlot(expressionHolder, xCoordinate);
        
        //cout << xCoordinate << "  " << yCoordinate << endl;
        //push vector2f with resultant points to queue
        plotQueue.push(sf::Vector2f(xCoordinate, yCoordinate));
        
        
        xCoordinate += intervalStep;
        
    }
    
    return plotQueue;
}

//transforms a Queue of cartesian coordinates to screen coordinates, accounting for whatever window size is there.
Queue<sf::Vector2f> Graph::transformCartesianToScreen(Queue<sf::Vector2f>& plotInCartesian){
    
    sf::Vector2f pointToTransform;
    Queue<sf::Vector2f> transformedPlot;
    
    double transformedX, transformedY;
    
    while( ! ( plotInCartesian.empty() ) ) {

        
        pointToTransform = plotInCartesian.pop();
        
        //need to assign to double; performing operation on  as a directly returned value makes it go crazy
        double screenHeight = HALF_DESKTOP.height;
        
        //cout << "Transforming from Cartesian: (" << pointToTransform.x << "," << pointToTransform.y << ")" << endl;
        
        transformedX = (WORK_PANEL / (_xMax - _xMin)) * (pointToTransform.x - _xMin);
        transformedY = ( (screenHeight * -1) /  (_yMax - _yMin) ) * (pointToTransform.y - _yMax);
        
        sf::Vector2f transformedPoint(transformedX, transformedY);
        
        //cout << "To Screen: (" << transformedPoint.x << "," << transformedPoint.y << ")" << endl;
        //cout << "******************************************" << endl << endl;
        
        transformedPlot.push(transformedPoint);
        
    }
    
    return transformedPlot;
}

//transform, for when it's more convenient to do it for a single point. Which it is, often.
sf::Vector2f Graph::transformCartesianToScreen(sf::Vector2f pointToTransform){
    
    double transformedX, transformedY;
    //need to assign to double; performing operation on  as a directly returned value makes it go crazy
    double screenHeight = HALF_DESKTOP.height;
    
    //cout << "Transforming from Cartesian: (" << pointToTransform.x << "," << pointToTransform.y << ")" << endl;
    
    transformedX = (WORK_PANEL / (_xMax - _xMin)) * (pointToTransform.x - _xMin);
    transformedY = ( (screenHeight * -1) /  (_yMax - _yMin) ) * (pointToTransform.y - _yMax);
    
    sf::Vector2f transformedPoint(transformedX, transformedY);
    return transformedPoint;
}

//sets the bounds of the graph, and recalculates all the points in the graph to compensate. used in panning and zooming. And draggin, if I ever get that to work.
void Graph::setGraphView(double xBegin, double xEnd, double yBegin, double yEnd){
    _xMin = xBegin;
    _xMax = xEnd;
    _yMin = yBegin;
    _yMax = yEnd;
    if(!_functionToGraph.empty()){
        _cartesianGraph = plot(_xMin, _xMax, _subDivisions);
        _screenGraph = transformCartesianToScreen(_cartesianGraph);
    }
    
}

//set the number of subdivisions; correctponds to the number of circles that get drawn. Currently set at 125k
void Graph::setSubdivisions(double numberOfSubdivisions){
    _subDivisions = numberOfSubdivisions;
}

//I mean, does this need explanation?
double Graph::getYMax(){
    return _yMax;
}
//it gets the named variable
double Graph::getYMin(){
    return _yMin;
}
//seems pretty self-expalantory, but hey
double Graph::getXMax(){
    return _xMax;
}
//maybe in the future I have a traumatic brain injury or something
double Graph::getXMin(){
    return _xMin;
}

//used to clear the graph. Clears the screengraph which tells draw to draw a hidden point instead of a graph
void Graph::clearGraph(){
    while(!_functionToGraph.empty()){
        _functionToGraph.pop();
    }
    while(!_screenGraph.empty()){
        _screenGraph.pop();
    }
    _functionToDisplay = "";
}

void Graph::draw(sf::RenderWindow& window, sf::Font font){
    
    //draw the axes
    string xMax, xMin, yMax, yMin;
    Queue<sf::Vector2f> screenCoordinates;
    Queue<sf::Vector2f> axesInCartesian;
    Queue<sf::Vector2f> screenAxes;
    
    //declare my axis rectangles
    sf::RectangleShape yAxis;
    sf::RectangleShape xAxis;
    //set the origin at the center, so they're appropriately centered. Cause pretty
    yAxis.setOrigin(0, 2);
    xAxis.setOrigin(2, 0);
    
    //set the dimensions, which are, surprisingly enough, width 4 and length and height of work area, respectively
    sf::Vector2f xAxisDimensions(WORK_PANEL, 4);
    sf::Vector2f yAxisDimensions(4, SCREEN_HEIGHT);
    
    sf::Vector2f xAxisPositionCartesian(_xMin,0);
    sf::Vector2f yAxisPositionCartesian(0,_yMax);
    
    //convert my doubles to strings so I can use them as text.
    yMax = to_string(_yMax);
    yMin = to_string(_yMin);
    xMax = to_string(_xMax);
    xMin = to_string(_xMin);
    

    
    //keep the labels a consisten size depending on whether they're negative, have two digits before the decimal place
    if(_xMax < 0 && _xMax <= -10){
        xMax.resize(5);
    }else{
        xMax.resize(4);
    }
    
    if(_yMax < 0 && _yMax <= -10){
        yMax.resize(5);
    }else{
        yMax.resize(4);
    }
    
    if(_xMin < 0 && _xMin <= -10){
        xMin.resize(5);
    }else{
        xMin.resize(4);
    }
    
    if(_yMin < 0 && _yMin <= -10){
        yMin.resize(5);
    }else{
        yMin.resize(4);
    }
    
    //text declarations for our labels, using the strings we derived just above
    sf::Text yAxisTopLabel(yMax, font);
    sf::Text yAxisBottomLabel(yMin, font);
    sf::Text xAxisRightLabel(xMax, font);
    sf::Text xAxisLeftLabel(xMin, font);
    
    //create the position vectors for our labels, which have an origin in the top left-hand corner.
    sf::Vector2f xAxisRightLabelPositionCartesian(_xMax, 0);
    sf::Vector2f xAxisLeftLabelPositionCartesian(_xMin, 0);
    
    sf::Vector2f yAxisTopLabelPositionCartesian(0, _yMax);
    sf::Vector2f yAxisBottomLabelPositionCartesian(0, _yMin);
    
    //transform all our label coordinates to screen coordinates.
    sf::Vector2f xAxisRightLabelPositionScreen = transformCartesianToScreen(xAxisRightLabelPositionCartesian);
    sf::Vector2f xAxisLeftLabelPositionScreen = transformCartesianToScreen(xAxisLeftLabelPositionCartesian);
    
    sf::Vector2f yAxisTopLabelPositionScreen = transformCartesianToScreen(yAxisTopLabelPositionCartesian);
    sf::Vector2f yAxisBottomLabelPositionScreen = transformCartesianToScreen(yAxisBottomLabelPositionCartesian);
    
    //nudge the labels so that they're visible and pretty
    yAxisBottomLabelPositionScreen -= sf::Vector2f(-10, yAxisBottomLabel.getLocalBounds().height+5);
    xAxisRightLabelPositionScreen -= sf::Vector2f(xAxisRightLabel.getLocalBounds().width-10, -5);
    
    yAxisTopLabelPositionScreen += sf::Vector2f(10, 0);
    xAxisLeftLabelPositionScreen += sf::Vector2f(5, 5);
    
    //setting all the various attributes for the labels.
    xAxisRightLabel.setCharacterSize(20);
    xAxisRightLabel.setStyle(sf::Text::Bold);
    xAxisRightLabel.setColor(sf::Color::Black);
    xAxisRightLabel.setPosition(xAxisRightLabelPositionScreen);
    
    xAxisLeftLabel.setCharacterSize(20);
    xAxisLeftLabel.setStyle(sf::Text::Bold);
    xAxisLeftLabel.setColor(sf::Color::Black);
    xAxisLeftLabel.setPosition(xAxisLeftLabelPositionScreen);
    
    yAxisTopLabel.setCharacterSize(20);
    yAxisTopLabel.setStyle(sf::Text::Bold);
    yAxisTopLabel.setColor(sf::Color::Black);
    yAxisTopLabel.setPosition(yAxisTopLabelPositionScreen);
    
    yAxisBottomLabel.setCharacterSize(20);
    yAxisBottomLabel.setStyle(sf::Text::Bold);
    yAxisBottomLabel.setColor(sf::Color::Black);
    yAxisBottomLabel.setPosition(yAxisBottomLabelPositionScreen);
    
    axesInCartesian.push(xAxisPositionCartesian);
    axesInCartesian.push(yAxisPositionCartesian);
    
    screenAxes = transformCartesianToScreen(axesInCartesian);
    
    xAxis.setSize(xAxisDimensions);
    xAxis.setFillColor(sf::Color::Black);
    xAxis.setPosition(screenAxes.pop());
    
    yAxis.setSize(yAxisDimensions);
    yAxis.setFillColor(sf::Color::Black);
    yAxis.setPosition(screenAxes.pop());
    
    //if there's no graph, like when it's first loading, push a single (hidden) point onto the screen at the origin.
    if(!_screenGraph.empty()){
        screenCoordinates = _screenGraph;
    }else{
        
        screenCoordinates.push(transformCartesianToScreen(sf::Vector2f(0,0)));
    }
    
    //don't draw the graph if the expresion is bad; this helps in cases where the graph interperets garbage input as some constant, drawing a line at that value.
    if(_badExpression == false){
        while(!screenCoordinates.empty()){
            
            sf::CircleShape circle(3);
            sf::Vector2f plotPoint(screenCoordinates.pop());
            //cout << "drawing " << plotPoint.x << ", " << plotPoint.y << endl;
            circle.setFillColor(sf::Color(34, 139, 34));
            circle.setPosition( plotPoint );
            window.draw(circle);
            
        }
    }
    
    //dimensions of the gridlines; they're 1 pixel high
    sf::Vector2f xGridLineDimensions(WORK_PANEL, 1);
    sf::Vector2f yGridLineDimensions(1, SCREEN_HEIGHT);
    
    //draw all our axes and labels
    window.draw(yAxis);
    window.draw(xAxis);
    window.draw(yAxisTopLabel);
    window.draw(xAxisRightLabel);
    window.draw(yAxisBottomLabel);
    window.draw(xAxisLeftLabel);
    
    //draw gridlines parallel to the x axis
    for(int i = _yMin; i < _yMax; i++){
        //cout << "Generating xGridLines" << endl;
        sf::RectangleShape* xGridLine = new sf::RectangleShape(xGridLineDimensions);
        xGridLine->setOrigin(1,0);
        xGridLine->setSize(xGridLineDimensions);
        sf::Vector2f* xGridLineLocation = new sf::Vector2f(_xMin, i);
        *xGridLineLocation = transformCartesianToScreen(*xGridLineLocation);
        xGridLine->setPosition(*xGridLineLocation);
        xGridLine->setFillColor(sf::Color::Black);
        window.draw(*xGridLine);
        
    }
    
    //draw gridlines parallel to the y axis
    for(int i = _xMin; i < _xMax; i++){
        //cout << "Generating yGridLines" << endl;
        sf::RectangleShape* yGridLine = new sf::RectangleShape(yGridLineDimensions);
        yGridLine->setOrigin(0,1);
        yGridLine->setSize(yGridLineDimensions);
        sf::Vector2f* yGridLineLocation = new sf::Vector2f(i, _yMax);
        *yGridLineLocation = transformCartesianToScreen(*yGridLineLocation);
        yGridLine->setPosition(*yGridLineLocation);
        yGridLine->setFillColor(sf::Color::Black);
        window.draw(*(yGridLine));
        
    }
    
}
//this function takes an RPN-formatted postfix Queue and evaluates it at a given value, assuming it contains a variable (x)
double Graph::evaluateToPlot(Queue<Token*>& operationQueue, double evaluateAt){
    
    //cout << "In evaluateToPlot:" << endl;
    //operationQueue.printTheList();
    
    double finalAnswer = 0, workingAnswer = 0, rhsHolder = 0, lhsHolder = 0, argument = 0;
    const int anOperand = 0, anOperator = 1, aVariable = 2, aFunction = 4;
    
    Stack<Token*> operationStack;
    
    while(!operationQueue.empty()){
        
        if(!(operationQueue.empty()) && operationQueue.front()->getType() == anOperand){
            operationStack.push(operationQueue.pop());
        }
        
        if(!(operationQueue.empty()) && operationQueue.front()->getType() == aVariable){
            //cout << "in variable while loop" << endl;
            Token* evaluatedVariable = new Operand(evaluateAt);
            operationStack.push(evaluatedVariable);
            operationQueue.pop();
        }
        
        if( !(operationQueue.empty()) && operationQueue.front()->getType() == aFunction ){
            
            Function* someFunction = static_cast<Function*>(operationQueue.pop());
            
            if(!operationStack.empty()){
                argument = static_cast<Operand*> ( operationStack.pop() ) -> getValue();
            }
            else{
                _badExpression = true;
            }
            
            workingAnswer = someFunction->resultOneArg(argument);
            
            Token* functionAnswerHolder = new Operand(workingAnswer);
            
            operationStack.push(functionAnswerHolder);
            
        }
        
        if(!(operationQueue.empty()) && operationQueue.front()->getType() == anOperator){
            if(!operationStack.empty()){
                rhsHolder = static_cast<Operand*> ( operationStack.pop() ) -> getValue();
            }else{
                _badExpression = true;
            }
            if(!operationStack.empty()){
                lhsHolder = static_cast<Operand*> ( operationStack.pop() ) -> getValue();
            }else{
                _badExpression = true;
            }
            //cout << rhsHolder << " " << lhsHolder << endl;
            Operator* operationToPerform = static_cast<Operator*> (operationQueue.pop());
            workingAnswer = operationToPerform->result(rhsHolder, lhsHolder);
            
            Token* workingAnswerHolder = new Operand(workingAnswer);
            operationStack.push(workingAnswerHolder);
            
        }
        
    }
    
    finalAnswer = static_cast<Operand*> (operationStack.pop()) -> getValue();
    //cout << "x coordinate: " << evaluateAt << " y coordinate: " << finalAnswer << endl;
    return finalAnswer;
}
