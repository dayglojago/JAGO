//
//  GraphViewer.cpp
//  tokenRPN
//
//  Created by Swordfish on 12/9/18.
//  Copyright © 2018 Swordfish. All rights reserved.
//

#include "GraphViewer.hpp"
#include "Includes.hpp"

//Graph Viewer Constructor: sets up the window, sets the maximum framerate, and initializes the FunctionToGraph string to nothing. Also, loads the font.
GraphViewer::GraphViewer():sidebar(WORK_PANEL, SIDE_BAR)
{
    
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Jago's Amazing Grapher with Operands (JAGO)");
    
    //VideoMode class has functions to detect screen size etc.
    //RenderWindow constructor has a third argumnet to set style
    //of the window: resize, fullscreen etc.
    
    //System will be implemented to manage a vector of objects to be animated.
    //  at that point, the constructor of the System class will take a vector
    //  of objects created by the animate object.
    //  animate will
    
    window.setFramerateLimit(200);
    
    //cout<< "GraphViewer CTOR. preparing to load the font." <<endl;
    //--- FONT ----------
    //font file must be in the "working directory:
    //      debug folder
    //Make sure working directory is where it should be and not
    //  inside the app file:
    //  Project->RUN->Working Folder
    //
    //font must be a member of the class.
    //  Will not work with a local declaration
    
    if (!font.loadFromFile(resourcePath() + "Cambriai.ttf")){
        cout << "GraphViewer() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }
    
    functionToGraph = "";
    
}


//draws the components of "system," in this case, a Graph object
void GraphViewer::draw(){
    //Look at the data and based on the data, draw shapes on window object.
    currentGraph.draw(window, font);

    sidebar.draw(window);
    //- - - - - - - - - - - - - - - - - - -
    //getPosition() gives you screen coords, getPosition(window) gives you window coords
    //cout<<"mosue pos: "<<sf::Mouse::getPosition(window).x<<", "<<sf::Mouse::getPosition(window).y<<endl;
    //- - - - - - - - - - - - - - - - - - -
    
    //drawing Test: . . . . . . . . . . . .
    //This is how you draw text :)
    
    //set up my function label on the graph, or error label, as it may be
    functionOrErrorLabel = sf::Text(currentGraph.getDisplayFunction(), font);
    functionOrErrorLabel.setCharacterSize(30);
    functionOrErrorLabel.setStyle(sf::Text::Bold);
    
    functionOrErrorLabel.setPosition(sf::Vector2f(15, SCREEN_HEIGHT-functionOrErrorLabel.getLocalBounds().height-50));
    
    //draws the error in red if the expression is bad
    if(currentGraph._badExpression == true){
        functionOrErrorLabel.setColor(sf::Color::Red);
        window.draw(functionOrErrorLabel);
    }else{
        functionOrErrorLabel.setColor(sf::Color::Blue);
        window.draw(functionOrErrorLabel);
    }
    
    myCurrentFunction = sf::Text(functionToGraph, font);
    myCurrentFunction.setCharacterSize(30);
    myCurrentFunction.setStyle(sf::Text::Bold);
    myCurrentFunction.setColor(sf::Color::White);
    myCurrentFunction.setPosition(sf::Vector2f(WORK_PANEL+SIDE_BAR-myCurrentFunction.getLocalBounds().width-15, SCREEN_HEIGHT-myCurrentFunction.getLocalBounds().height-50));
    
    window.draw(myCurrentFunction);
    //. . . . . . . . . . . . . . . . . . .
}

void GraphViewer::update(){
    //cause changes to the data for the next frame
    
    //sidebar text for function you're currently typing:
    //sidebar[SB_MOUSE_POSITION] = functionToGraph;
    
    
}

void GraphViewer::render(){
    window.clear(sf::Color::White);
    draw();
    window.display();
}



void GraphViewer::processEvents()
{
    const bool debug = false;
    sf::Event event;
    while (window.pollEvent(event))//or waitEvent
    {
        //this reads characters as they're being typed. It checks the unicode code against the conditions in the if statement. If it's not a backspace (8), enter (10), left Bracket (91) or Right Bracket (93) (which are used for zoom,) it prints the text to the sidebar.
        if (event.type == sf::Event::TextEntered)
        {
            if (event.text.unicode < 128 && event.text.unicode != 8 && event.text.unicode != 91 && event.text.unicode != 93){
                functionToGraph += static_cast<char>(event.text.unicode);
            }
            
        }
        // check the type of the event...
        switch (event.type)
        {
                // window closed
            case sf::Event::Closed:
                window.close();
                break;
                
                //this checks for special keys pressed -> enter, backspace, left, right, up, down
            case sf::Event::KeyPressed:
                
                switch(event.key.code){
                        
                    case sf::Keyboard::Left:
                        //sidebar[SB_KEY_PRESSED] = "PANNING LEFT";
                        currentGraph.setGraphView(currentGraph.getXMin()-1, currentGraph.getXMax()-1, currentGraph.getYMin(), currentGraph.getYMax());
                        
                        break;
                    case sf::Keyboard::Right:
                        //sidebar[SB_KEY_PRESSED] = "PANNING RIGHT";
                        currentGraph.setGraphView(currentGraph.getXMin()+1, currentGraph.getXMax()+1, currentGraph.getYMin(), currentGraph.getYMax());
                        
                        break;
                    case sf::Keyboard::Escape:
                        //sidebar[SB_KEY_PRESSED] = "ESC: EXIT";
                        window.close();
                        break;
                        
                    case sf::Keyboard::Tab:
                        //sidebar[SB_KEY_PRESSED] = "RESET VIEW TO DEFAULT";
                        currentGraph.setGraphView(-10, 10, -10, 10);
                        break;
                        
                    case sf::Keyboard::LAlt:
                        //sidebar[SB_KEY_PRESSED] = "CLEAR GRAPH";
                        currentGraph._badExpression = false;
                        currentGraph.clearGraph();
                        break;
                        //when you press enter it takes the string of your input as shoves it inside the parseinput function, then sets the postfix it finds as the new graph, unless the expression is bad.
                    case sf::Keyboard::Enter:
                    {
                        Queue<Token*> infixExpression;
                        stringstream lineStream(functionToGraph);
                        infixExpression = parseInput(lineStream);
                        currentGraph.setNewFunction(infixToPostfix(infixExpression));
                        if(currentGraph._badExpression == false){
                            sidebar.pushIntoSidebar(functionToGraph);
                        }
                        if(currentGraph._badExpression == true){
                            functionToGraph = "Invalid expression. Please re-enter.";
                        }
                        currentGraph.setDisplayFunction(functionToGraph);
                        functionToGraph = "";
                        break;
                    }
                    case sf::Keyboard::Backspace:
                        //truncate the string by one from the right, simulating a backspace
                        if(functionToGraph.length() >= 1){
                            functionToGraph.resize(functionToGraph.length()-1);
                        }
                        break;
                    case sf::Keyboard::Up:
                        //sidebar[SB_KEY_PRESSED] = "PANNING UP";
                        //panning up simply takes the graph view and changes the bounds, adding 1 to each of y Min and yMax
                        currentGraph.setGraphView(currentGraph.getXMin(), currentGraph.getXMax(), currentGraph.getYMin()+1, currentGraph.getYMax()+1);
                        if(debug){
                            cout << "pressed up; xMax/xMin now: " << currentGraph.getXMax() << "/" <<  currentGraph.getXMin() << endl;
                            cout << "yMax/yMin now: " << currentGraph.getYMax() << "/" <<  currentGraph.getYMin() << endl;
                        }
                        break;
                    case sf::Keyboard::Down:
                        //similarly, panning down does the same, except subtracting 1 from both
                        //sidebar[SB_KEY_PRESSED] = "PANNING DOWN";
                        currentGraph.setGraphView(currentGraph.getXMin(), currentGraph.getXMax(), currentGraph.getYMin()-1, currentGraph.getYMax()-1);
                        if(debug){
                            cout << "pressed down; xMax/xMin now: " << currentGraph.getXMax() << "/" <<  currentGraph.getXMin() << endl;
                        }
                        break;
                    case sf::Keyboard::LBracket:
                        //sidebar[SB_KEY_PRESSED] = "ZOOMING IN 10%";
                        //this view zooms in by 10%, giving some wacky bound numbers, but isn't that half the fun? Make it weird!
                        currentGraph.setGraphView(currentGraph.getXMin()*.9, currentGraph.getXMax()*.9, currentGraph.getYMin()*.9, currentGraph.getYMax()*.9);
                        break;
                    case sf::Keyboard::RBracket:
                        //sidebar[SB_KEY_PRESSED] = "ZOOMING OUT 10%";
                        //zooms out, cause sometimes you need to see the big picture.
                        currentGraph.setGraphView(currentGraph.getXMin()*1.1, currentGraph.getXMax()*1.1, currentGraph.getYMin()*1.1, currentGraph.getYMax()*1.1);
                        break;
                }
                
                break;
                //left here because I wanted to implement dragging, but that didn't work out like, super well.
            case sf::Event::MouseEntered:
                break;
                
            case sf::Event::MouseButtonPressed:
                sf::Mouse mouseObject;
                sidebar.setMouseClickValue(window, mouseObject);
                if(sidebar._clickedAnItem == true){
                    functionToGraph = sidebar.getHistoryItem();
                    Queue<Token*> infixExpression;
                    stringstream lineStream(functionToGraph);
                    infixExpression = parseInput(lineStream);
                    currentGraph.setNewFunction(infixToPostfix(infixExpression));
                    if(currentGraph._badExpression == false){
                        sidebar.pushIntoSidebar(functionToGraph);
                    }
                    if(currentGraph._badExpression == true){
                        functionToGraph = "Invalid expression. Please re-enter.";
                    }
                    currentGraph.setDisplayFunction(functionToGraph);
                    functionToGraph = "";
                }
                break;
                
            case sf::Event::MouseMoved:
                //Do something with it if you need to...
                break;
            case sf::Event::MouseButtonReleased:
                
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    //sidebar[SB_MOUSE_CLICKED] = "RIGHT CLICK";
                    
                }
                else{
                    //sidebar[SB_MOUSE_CLICKED] = "LEFT CLICK";
                }
                break;
                
            default:
                break;
        }
    }
}
//controls the whole damn shebang, listening for events, updating the sidebar, and randering (drawing) all the shiz
void GraphViewer::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render(); //clear/draw/display
    }
    //cout<<endl<<"-------ANIMATE MAIN LOOP EXITING ------------"<<endl;
}

//this function takes as an input a Token Queue in the form of an infix expression and spits out an RPN version that the computer likes better.
Queue<Token*> GraphViewer::infixToPostfix(Queue<Token*>& infixQueue){
    //infixQueue.printTheList();
    Queue<Token*> outputQueue;
    Stack<Token*> operatorStack;
    //cout << "inside infixToPostfix... " << infixQueue.front()->getType() << endl;
    const int anOperand = 0, anOperator = 1, aVariable = 2, aParenthesis = 3, aFunction = 4;
    
    while( !(infixQueue.empty()) ) {
        //cout << "inside infixToPostfix while loop..." << infixQueue.front()->getType() << endl;
        while(!(infixQueue.empty()) && (infixQueue.front()->getType() == anOperand || infixQueue.front()->getType() == aVariable)){
            //cout << "pushing an operand" << endl;
            outputQueue.push(infixQueue.pop());
        }
        
        if((!(infixQueue.empty()) && infixQueue.front()->getType() == aParenthesis)){
            
            Parenthesis* aParen = static_cast<Parenthesis*>(infixQueue.front());
            
            if(aParen->open()){
                //cout << "pushing a paren" << endl;
                operatorStack.push(infixQueue.pop());
                if(infixQueue.empty() == true){
                    currentGraph._badExpression = true;
                    break;
                }
            }
            
            if( !aParen->open() ){
                if(operatorStack.empty() == true){
                    currentGraph._badExpression = true;
                    break;
                }
                while(operatorStack.top()->getType() != aParenthesis){
                    outputQueue.push(operatorStack.pop());
                }
                
                operatorStack.pop();
                infixQueue.pop();
            }
            
        }
        
        
        if((!(infixQueue.empty()) && infixQueue.front()->getType() == aFunction)){
            
            operatorStack.push(infixQueue.pop());
            
            //cout << "popped function into the infix Queue..." << endl;
        }
        
        
        while( !(infixQueue.empty()) && ( infixQueue.front()->getType() == anOperator ) ){
            
            if(!operatorStack.empty()){
                
                Operator* inQueue = nullptr;
                Operator* inStack = nullptr;
                
                if(operatorStack.top()->getType() == anOperator && infixQueue.front()->getType() == anOperator){
                    
                    Operator* inQueueHolder = static_cast<Operator*>(infixQueue.front());
                    Operator* inStackHolder = static_cast<Operator*>(operatorStack.top());
                    inQueue = inQueueHolder;
                    inStack = inStackHolder;
                    
                }
                //if there's a function on the operator stack and an operator in the Queue, push the function into the postFix Queue because it has higher precedence
                if(operatorStack.top()->getType() == aFunction && infixQueue.front()->getType() == anOperator){
                    outputQueue.push( operatorStack.pop() );
                    operatorStack.push(infixQueue.pop());
                }
                
                if(operatorStack.top()->getType() == aParenthesis){
                    //cout << "pushing an operator after paren" << endl;
                    operatorStack.push(infixQueue.pop());
                }
                else if(inStack != NULL && inQueue != NULL && inQueue->getOperator() == '^' && inStack->getOperator() == '^'){
                    //cout << "pushing a consecutive caret" << endl;
                    operatorStack.push(infixQueue.pop());
                }
                
                else if (inStack != NULL && inQueue != NULL && *inQueue > *inStack){
                    //cout << "pushing an operator with higher precedence" << endl;
                    operatorStack.push(infixQueue.pop());
                }
                
                else if(inStack != NULL && inQueue != NULL && *inQueue <= *inStack){
                    //cout << "pushing an operator after popping one with lower or equal precedence" << endl;
                    outputQueue.push(operatorStack.pop());
                    operatorStack.push(infixQueue.pop());
                }
                
            }
            else{
                //cout << "pushing an operator into an empty stack" << endl;
                operatorStack.push(infixQueue.pop());
            }
        }
        
    }
    while(!operatorStack.empty()){
        outputQueue.push(operatorStack.pop());
    }
    
    //outputQueue.printTheList();
    return outputQueue;
}

//this function takes string input and converts it all to tokens that can be pushed into a Queue for further processing
Queue<Token*> GraphViewer::parseInput(stringstream& lineStream){
    //resets the flag in case it's been set already by a bad expression. So, if you type cos x after typing like (, it goes back to working.
    currentGraph._badExpression = false;
    
    string nextTerm;
    
    double nextOperand;
    
    char nextChar;
    
    Token* aDigit, anOperator, aVariable;
    Queue<Token*> infixQueue;
    
    while(lineStream >> nextTerm){
        
        try{
            nextOperand = stod(nextTerm);
            aDigit = new Operand(nextOperand);
            infixQueue.push(aDigit);
        }
        
        catch(invalid_argument){
            
            for(int i = 0; i < nextTerm.length(); i++){
                nextTerm[i] = tolower(nextTerm[i]);
            }
            
            nextChar = nextTerm[0];
            
            
            switch(nextChar){
                case 'x':
                {
                    Token* aVariable = new Variable(nextChar);
                    infixQueue.push(aVariable);
                    break;
                }
                case 'e':
                {
                    Token* anOperand = new Operand(2.718281828);
                    infixQueue.push(anOperand);
                    break;
                }
                case '*':
                {
                    Token* aStar = new Operator(nextChar);
                    infixQueue.push(aStar);
                    break;
                }
                case '/':
                {
                    Token* aSlash = new Operator(nextChar);
                    infixQueue.push(aSlash);
                    break;
                }
                case '+':
                {
                    Token* aPlus = new Operator(nextChar);
                    infixQueue.push(aPlus);
                    break;
                }
                case '-':
                {
                    //cout << lineStream.peek() << endl;
                    if(infixQueue.empty()){
                        Token* unaryOperator = new Function(nextTerm);
                        infixQueue.push(unaryOperator);
                    }else{
                        Token* aMinus = new Operator(nextChar);
                        infixQueue.push(aMinus);
                    }
                    break;
                }
                case '(':
                {
                    Token* openParen = new Parenthesis(true);
                    infixQueue.push(openParen);
                    break;
                }
                case ')':
                {
                    Token* closedParen = new Parenthesis(false);
                    infixQueue.push(closedParen);
                    break;
                }
                case '^':
                {
                    Token* aCaret = new Operator(nextChar);
                    infixQueue.push(aCaret);
                    break;
                }
                case 's':
                {
                    if(nextTerm == "sin"){
                        
                        Token* aSin = new Function(nextTerm);
                        infixQueue.push(aSin);
                        
                    }else if(nextTerm == "sinh"){
                        
                        Token* aSinh = new Function(nextTerm);
                        infixQueue.push(aSinh);
                        
                    }else if(nextTerm == "sec"){
                        
                        Token* aSec = new Function(nextTerm);
                        infixQueue.push(aSec);
                        
                    }else if(nextTerm == "sech"){
                        
                        Token* aSech = new Function(nextTerm);
                        infixQueue.push(aSech);
                        
                    }else{
                        currentGraph._badExpression = true;
                    }
                    
                    break;
                }
                case 'c':
                {
                    if(nextTerm == "cos"){
                        
                        Token* aCos = new Function(nextTerm);
                        infixQueue.push(aCos);
                        
                    }else if(nextTerm == "cosh"){
                        
                        Token* aCosh = new Function(nextTerm);
                        infixQueue.push(aCosh);
                        
                    }else if(nextTerm == "csc"){
                        
                        Token* aCsc = new Function(nextTerm);
                        infixQueue.push(aCsc);
                        
                    }else if(nextTerm == "csch"){
                        
                        Token* aCsch = new Function(nextTerm);
                        infixQueue.push(aCsch);
                        
                    }else if(nextTerm == "cot"){
                        
                        Token* aCot = new Function(nextTerm);
                        infixQueue.push(aCot);
                        
                    }else if(nextTerm == "coth"){
                        
                        Token* aCoth = new Function(nextTerm);
                        infixQueue.push(aCoth);
                        
                    }else{
                        currentGraph._badExpression = true;
                    }
                    break;
                }
                case 't':
                {
                    if(nextTerm == "tan"){
                        
                        Token* aTan = new Function(nextTerm);
                        infixQueue.push(aTan);
                        
                    }else if(nextTerm == "tanh"){
                        
                        Token* aTanh = new Function(nextTerm);
                        infixQueue.push(aTanh);
                        
                    }else{
                        currentGraph._badExpression = true;
                    }
                    break;
                }
                case 'l':
                {
                    if(nextTerm == "ln"){
                        
                        Token* aLn = new Function(nextTerm);
                        infixQueue.push(aLn);
                        
                    }else if(nextTerm == "log"){
                        
                        Token* aLogBase10 = new Function(nextTerm);
                        infixQueue.push(aLogBase10);
                        
                    }else{
                        currentGraph._badExpression = true;
                    }
                    break;
                }
                case 'p':
                {
                    if(nextTerm == "pi"){
                        Token* anOperand = new Operand(3.141592653);
                        infixQueue.push(anOperand);
                    }else{
                        currentGraph._badExpression = true;
                    }
                    break;
                }//for min and max, one day...
                    //                case 'm':
                    //                {
                    //                    if(nextTerm == "min"){
                    //
                    //                    }else if(nextTerm == "max"){
                    //
                    //                    }
                    //                    break;
                    //                }
                default:
                {
                    currentGraph._badExpression = true;
                    break;
                }
                    
            }
        }
    }
    //push a null token into the queue if the expression doesn't parse correctly, so that the program doesn't crash when it tries to read an empty queue. Then set the badexpression flag.
    if(currentGraph._badExpression == true){
        Token* nullToken = new Operand(0);
        infixQueue.push(nullToken);
        return infixQueue;
    }
    //return the pretty queue
    return infixQueue;
}
