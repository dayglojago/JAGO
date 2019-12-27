//
//  main.cpp
//  tokenRPN
//
//  Created by Swordfish on 11/13/18.
//  Copyright © 2018 Swordfish. All rights reserved.
//

#include "Includes.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    //instatiate GraphViewer object, which conatins the graph and the sidebar
    GraphViewer mainWindow;
    
    //run the app, which opens a window and draws everything and listens to input
    mainWindow.run();

    return 0;
}

//double evaluateExpression(Queue<Token*>& operationQueue);

//double evaluateToPlot(Queue<Token*>& operationQueue, double evaluateAt);


/*
 string line;
 
 cout << "Please input an infix expression (e.g. 3 + 5 - 7 * 4,)\nmaking sure to put spaces between each character:" << endl;
 
 getline(cin, line);
 
 stringstream lineStream(line);
 
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
 Token* aMinus = new Operator(nextChar);
 infixQueue.push(aMinus);
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
 
 }
 break;
 }
 case 'm':
 {
 if(nextTerm == "min"){
 
 }else if(nextTerm == "max"){
 
 }
 break;
 }
 default:
 {
 cout << "Invalid operator " << nextChar << " detected. Exiting.";
 exit(420);
 break;
 }
 
 }
 }
 }
 
 Queue<Token*> postfixQueue = infixToPostfix(infixQueue);
 
 cout << "************************** Infix **************************" << endl;
 infixQueue.printTheList();
 cout << "************************* Postfix *************************" << endl;
 postfixQueue.printTheList();
 
 //Graph testGraph(postfixQueue);
 
 
 sf::RenderWindow window(HALF_DESKTOP, "Jago's Amazing Grapher");
 
 while (window.isOpen())
 {
 // Process events
 sf::Event event;
 while (window.pollEvent(event))
 {
 // Close window: exit
 if (event.type == sf::Event::Closed) {
 window.close();
 }
 
 // Escape pressed: exit
 if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
 window.close();
 }
 
 if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Equal) {
 // Clear screen
 window.clear(sf::Color::White);
 //plotQueue = testGraph.plot(-5, 5, 20000);
 testGraph.draw(window);
 
 // Update the window
 window.display();
 }
 
 if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Hyphen) {
 // Clear screen
 window.clear(sf::Color::White);
 //plotQueue = testGraph.plot(-20, 20, 20000);
 testGraph.draw(window);
 
 // Update the window
 window.display();
 }
 
 }
 
 // Clear screen
 window.clear(sf::Color::White);
 
 testGraph.draw(window);
 
 // Update the window
 window.display();
 }
 */

//double evaluateExpression(Queue<Token*>& operationQueue){
//
//    double finalAnswer = 0, workingAnswer, rhsHolder, lhsHolder;
//    const int anOperand = 0, anOperator = 1, aVariable = 2;
//
//
//    Stack<Token*> operationStack;
//
//    while(!operationQueue.empty()){
//
//
//        while(operationQueue.front()->getType() == anOperand){
//            operationStack.push(operationQueue.pop());
//        }
//
//        //        while(operationQueue.front()->getType() == aVariable){
//        //            Variable* rawVariable = static_cast<Variable*> (operationQueue.pop());
//        //            if(rawVariable->getEvaluationFlag()){
//        //                Token* evaluatedVariable = new Operand(rawVariable->getEvaluationValue());
//        //                operationStack.push(evaluatedVariable);
//        //            }
//        //            else{
//        //                cout << "Cannot evaluate expression, evaluation flag set to false." << endl;
//        //                exit(1);
//        //            }
//        //        }
//
//        if(operationQueue.front()->getType() == anOperator){
//
//            rhsHolder = static_cast<Operand*> ( operationStack.pop() ) -> getValue();
//            lhsHolder = static_cast<Operand*> ( operationStack.pop() ) -> getValue();
//
//            Operator* operationToPerform = static_cast<Operator*> (operationQueue.pop());
//            workingAnswer = operationToPerform->result(rhsHolder, lhsHolder);
//
//            Token* workingAnswerHolder = new Operand(workingAnswer);
//            operationStack.push(workingAnswerHolder);
//
//        }
//    }
//
//    finalAnswer = static_cast<Operand*> (operationStack.pop()) -> getValue();
//    return finalAnswer;
//}
//
//double evaluateToPlot(Queue<Token*>& operationQueue, double evaluateAt){
//
//    //cout << "In evaluateToPlot:" << endl;
//    //operationQueue.printTheList();
//
//    double finalAnswer = 0, workingAnswer, rhsHolder, lhsHolder;
//    const int anOperand = 0, anOperator = 1, aVariable = 2, aFunction = 4;
//
//
//    Stack<Token*> operationStack;
//
//    while(!operationQueue.empty()){
//
//        if(!(operationQueue.empty()) && operationQueue.front()->getType() == anOperand){
//            operationStack.push(operationQueue.pop());
//        }
//
//        if(!(operationQueue.empty()) && operationQueue.front()->getType() == aVariable){
//            //cout << "in variable while loop" << endl;
//            Token* evaluatedVariable = new Operand(evaluateAt);
//            operationStack.push(evaluatedVariable);
//            operationQueue.pop();
//        }
//
//        if( !(operationQueue.empty()) && operationQueue.front()->getType() == aFunction ){
//
//            Function* someFunction = static_cast<Function*>(operationQueue.pop());
//
//            double argument = static_cast<Operand*> ( operationStack.pop() ) -> getValue();
//
//            workingAnswer = someFunction->resultOneArg(argument);
//
//            //cout << "Working Answer: " << workingAnswer << endl;
//
//            Token* functionAnswerHolder = new Operand(workingAnswer);
//
//            operationStack.push(functionAnswerHolder);
//
//        }
//
//        if(!(operationQueue.empty()) && operationQueue.front()->getType() == anOperator){
//
//            rhsHolder = static_cast<Operand*> ( operationStack.pop() ) -> getValue();
//            lhsHolder = static_cast<Operand*> ( operationStack.pop() ) -> getValue();
//            //cout << rhsHolder << " " << lhsHolder << endl;
//            Operator* operationToPerform = static_cast<Operator*> (operationQueue.pop());
//            workingAnswer = operationToPerform->result(rhsHolder, lhsHolder);
//
//            Token* workingAnswerHolder = new Operand(workingAnswer);
//            operationStack.push(workingAnswerHolder);
//
//        }
//
//    }
//
//    finalAnswer = static_cast<Operand*> (operationStack.pop()) -> getValue();
//    //cout << "x coordinate: " << evaluateAt << " y coordinate: " << finalAnswer << endl;
//    return finalAnswer;
//}
