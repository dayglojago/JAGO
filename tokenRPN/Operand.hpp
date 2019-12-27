//
//  Operand.hpp
//  tokenRPN
//
//  Created by Swordfish on 11/13/18.
//  Copyright © 2018 Swordfish. All rights reserved.
//

#ifndef Operand_hpp
#define Operand_hpp

#include <stdio.h>
#include "Token.hpp"
#include <iostream>

using namespace std;

class Operand : public Token {
    
public:
    Operand():Token(0)
    {
        _value = 0;
    }
    
    Operand(double value):Token(0){
        _value = value;
    }
    
    ostream& print(ostream& outs=cout)const {
        outs << _value << " ";
        return outs;
    }
    
    double getValue();
    
    double result(double lhs, double rhs);
    
    void setValue(double value);
    
private:
    
    double _value;
    
};
#endif /* Operand_hpp */
