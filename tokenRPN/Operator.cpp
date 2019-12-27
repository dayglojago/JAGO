//
//  Operator.cpp
//  tokenRPN
//
//  Created by Swordfish on 11/13/18.
//  Copyright © 2018 Swordfish. All rights reserved.
//
#include <cmath>
#include "Operator.hpp"

Operator::Operator():Token(1){
    _operator = '\0';
}

Operator::Operator(char theOperator):Token(1){
    
    _operator = theOperator;
    
    switch(theOperator){
        case '*':
            _precedence = 3;
            break;
        case '/':
            _precedence = 3;
            break;
        case '+':
            _precedence = 2;
            break;
        case '-':
            _precedence = 2;
            break;
        case '^':
            _precedence = 4;
            break;
        default:
            cout << "Precedence error" << endl;
            _precedence = -1;
            break;
    }
}

double Operator::result(double rhs, double lhs){
    
    switch(_operator){
        case '*':
            return lhs*rhs;
            break;
        case '/':
            return lhs/rhs;
            break;
        case '+':
            return lhs+rhs;
            break;
        case '-':
            return lhs-rhs;
            break;
        case '^':
            return pow(lhs, rhs);
            break;
        default:
            cout << "Uh... this is bad! Operator::result switch here." << endl;
            return 0;
            break;
    }
    
}

char Operator::getOperator(){
    return _operator;
}

int Operator::getPrecedence(){
    return _precedence;
}

ostream& Operator::print(ostream& outs)const {
    outs << _operator;
    return outs;
}

bool operator > (Operator lhs, Operator rhs){
    return lhs._precedence > rhs._precedence;
}
bool operator < (Operator lhs, Operator rhs){
    return lhs._precedence < rhs._precedence;
}
bool operator >= (Operator lhs, Operator rhs){
    return lhs._precedence >= rhs._precedence;
}
bool operator <= (Operator lhs, Operator rhs){
    return lhs._precedence <= rhs._precedence;
}
bool operator == (Operator lhs, Operator rhs){
    return lhs._precedence == rhs._precedence;
}
