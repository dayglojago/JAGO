//
//  Parenthesis.cpp
//  tokenRPN
//
//  Created by Swordfish on 11/25/18.
//  Copyright © 2018 Swordfish. All rights reserved.
//

#include "Parenthesis.hpp"

Parenthesis::Parenthesis():Token(3){
    _paren = '(';
    _open = true;
}

Parenthesis::Parenthesis(bool open):Token(3){
    if(open == true){
        _paren = '(';
        _open = true;
    }
    else{
        _paren = ')';
        _open = false;
    }
}

bool Parenthesis::open(){
    return _open;
}

ostream& Parenthesis::print(ostream& outs)const {
    
    outs << _paren;
    return outs;
}
