//
//  Parenthesis.hpp
//  tokenRPN
//
//  Created by Swordfish on 11/25/18.
//  Copyright © 2018 Swordfish. All rights reserved.
//

#ifndef Parenthesis_hpp
#define Parenthesis_hpp

#include "Token.hpp"
#include <stdio.h>

class Parenthesis : public Token {
public:
    
    Parenthesis();
    Parenthesis(bool open);
    
    bool open();
    
    ostream& print(ostream& outs)const;
    
private:
    
    char _paren;
    bool _open;
    
};
#endif /* Parenthesis_hpp */
