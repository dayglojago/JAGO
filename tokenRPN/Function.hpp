//
//  Function.hpp
//  tokenRPN
//
//  Created by Swordfish on 11/26/18.
//  Copyright © 2018 Swordfish. All rights reserved.
//

#ifndef Function_hpp
#define Function_hpp

#include <stdio.h>
#include "Token.hpp"

class Function : public Token {
public:
    
    //sin, cos, tan, cot, csc, sec, sinh, cosh, tanh, csch, sech, coth
    
    Function();
    
    Function(string functionName);
    
    double resultOneArg(double argument);
    
    double resultTwoArgs(double rhs, double lhs);
    
    ostream& print(ostream& outs)const;
    
private:
    
    string verifyAndFormatFunctionName(string functionName);
    
    string _functionName;
    
    static const int _precedence = 6;
};

#endif /* Function_hpp */
