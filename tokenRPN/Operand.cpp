//
//  Operand.cpp
//  tokenRPN
//
//  Created by Swordfish on 11/13/18.
//  Copyright © 2018 Swordfish. All rights reserved.
//

#include "Operand.hpp"

void Operand::setValue(double value){
    _value = value;
    
}

double Operand::getValue(){
    return _value;
}
