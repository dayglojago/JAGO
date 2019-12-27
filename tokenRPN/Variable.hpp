//
//  Variable.hpp
//  tokenRPN
//
//  Created by Swordfish on 11/25/18.
//  Copyright © 2018 Swordfish. All rights reserved.
//

#ifndef Variable_hpp
#define Variable_hpp

#include <stdio.h>
#include "Token.hpp"

class Variable : public Token {
    
public:
    
    Variable();
    Variable(char var);
    Variable(char var, double evalAt);
    
    void setEvaluationFlag(bool flagValue=true);
    
    bool getEvaluationFlag();
    
    void setEvaluationValue(double value);
    
    double getEvaluationValue();
    
    ostream& print(ostream& outs)const;
    
private:
    
    char _varLetter;
    bool _evalFlag;
    double _evalAt;
    
};

#endif /* Variable_hpp */
