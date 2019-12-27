//
//  Operator.hpp
//  tokenRPN
//
//  Created by Swordfish on 11/13/18.
//  Copyright © 2018 Swordfish. All rights reserved.
//

#ifndef Operator_hpp
#define Operator_hpp

#include <stdio.h>
#include "Token.hpp"

class Operator : public Token {
public:
    
    Operator();
    
    Operator(char theOperator);
    
    ostream& print(ostream& outs=cout)const;
    
    double result(double rhs, double lhs);
    
    char getOperator();
    
    int getPrecedence();
    
    friend bool operator > (Operator lhs, Operator rhs);
    friend bool operator < (Operator lhs, Operator rhs);
    friend bool operator >= (Operator lhs, Operator rhs);
    friend bool operator <= (Operator lhs, Operator rhs);
    friend bool operator == (Operator lhs, Operator rhs);
    
private:
    char _operator;
    int _precedence;
};
#endif /* Operator_hpp */
