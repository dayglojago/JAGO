//
//  Function.cpp
//  tokenRPN
//
//  Created by Swordfish on 11/26/18.
//  Copyright © 2018 Swordfish. All rights reserved.
//

#include "Function.hpp"
#include <cmath>

Function::Function():Token(4){
    _functionName = "\0";
}

Function::Function(string functionName):Token(4){
    
    //functionName = verifyAndFormatFunctionName(functionName);
    _functionName = functionName;
    
}

double Function::resultOneArg(double argument){
    //all functions returned in radians
    if(_functionName == "sin"){
        
        return sin(argument);
        
    }else if(_functionName == "cos"){
        
        return cos(argument);
        
    }else if(_functionName == "tan"){
        
        return sin(argument)/cos(argument);
        
    }else if(_functionName == "sec"){
        
        return 1 / cos(argument);
        
    }else if(_functionName == "csc"){
        
        return 1 / sin(argument);
        
    }else if(_functionName == "cot"){
        
        return cos(argument)/sin(argument);
        
    }else if(_functionName == "sinh"){
        
        return ( exp( argument ) - exp( argument * - 1 ) ) / 2;
        
    }else if(_functionName == "cosh"){
        
        return (exp(argument) + exp(argument * -1))/2;
        
    }else if(_functionName == "tanh"){
        
        return ( ( exp( argument ) - exp( argument * -1 ) ) / 2 ) / ( ( exp( argument ) + exp( argument * -1 ) ) / 2 );
        
    }else if(_functionName == "csch"){
        
        return 1/( ( exp( argument ) - exp( argument * - 1 ) ) / 2 );
        
    }else if(_functionName == "sech"){
        
        return 1/( ( exp( argument ) + exp( argument * - 1 ) ) / 2 );
        
    }else if(_functionName == "coth"){
        
        return ( ( exp( argument ) + exp( argument * -1 ) ) / 2 ) / ( ( exp( argument ) - exp( argument * -1 ) ) / 2 );
        
    }else if(_functionName == "log"){
        
        return log10(argument);
        
    }else if(_functionName == "ln"){
        
        return log(argument);
        
    }else if(_functionName == "-"){
        //unary operator
        return (-1 * argument);
    }
    else{
        cout << "Yeah, this isn't supposed to happen. Ever." << endl;
        exit(2001);
    }
}
double Function::resultTwoArgs(double rhs, double lhs){
    return 0;
}

string Function::verifyAndFormatFunctionName(string functionName){
    
    for(int i = 0; i < functionName.length(); i++){
        functionName[i] = tolower(functionName[i]);
    }
    
    if(functionName == "sin" || functionName == "cos" || functionName == "tan" || functionName == "sec" || functionName == "csc" || functionName == "cot" || functionName == "sinh" || functionName == "cosh" || functionName == "tanh" || functionName == "csch" || functionName == "sech" || functionName == "ln" || functionName == "log"){
        
    }
    
    return functionName;
}

ostream& Function::print(ostream& outs)const{
    outs << _functionName;
    return outs;
}
