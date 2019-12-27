//
//  Token.hpp
//  tokenRPN
//
//  Created by Swordfish on 11/13/18.
//  Copyright © 2018 Swordfish. All rights reserved.
//

#ifndef Token_hpp
#define Token_hpp
#include <iostream>
#include <stdio.h>

using namespace std;

class Token{
    
public:
    Token(){
        _type = 0;
        
    }
    Token(int type){
        _type = type;
        
    }
    
    int getType(){
        return _type;
    }
    
    friend ostream& operator << (ostream& outs, Token*& t){
        t->print(outs);
        return outs;
    }
    
    virtual ostream& print(ostream& outs)const {
        outs << "Need to define print function for subclass. This is the token print function.";
        return outs;
    }
    
    virtual char getOperator(){return '\0';};
    
private:
    int _type;
    
    enum typeOfToken { anOperand = 0 , anOperator = 1 , aVariable = 2, aParenthesis = 3, aFunction = 4};
};

#endif /* Token_hpp */
