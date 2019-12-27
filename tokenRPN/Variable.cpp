//
//  Variable.cpp
//  tokenRPN
//
//  Created by Swordfish on 11/25/18.
//  Copyright © 2018 Swordfish. All rights reserved.
//

#include "Variable.hpp"

Variable::Variable():Token(2){
    _varLetter = 'x';
    _evalFlag = false;
    _evalAt = 0;
}

Variable::Variable(char var):Token(2){
    _varLetter = var;
    _evalFlag = true;
    _evalAt = 0;
}

Variable::Variable(char var, double evalAt):Token(2){
    _varLetter = var;
    _evalFlag = true;
    _evalAt = evalAt;
}

void Variable::setEvaluationFlag(bool flagValue){
    _evalFlag = flagValue;
}

bool Variable::getEvaluationFlag(){
    return _evalFlag;
}

void Variable::setEvaluationValue(double value){
    _evalAt = value;
}

double Variable::getEvaluationValue(){
    return _evalAt;
}

ostream& Variable::print(ostream& outs)const {
    outs << _varLetter;
    if(_evalFlag == true){
        outs << "=" << _evalAt;
    }
    return outs;
    }
