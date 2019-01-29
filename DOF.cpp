////////////////////////////////////////
// DOF.cpp
////////////////////////////////////////


#include "DOF.h"

////////////////////////////////////////////////////////////////////////////////

DOF::DOF() {
    // Initialize data
    value = 0.0f;
    min = -100000.0f;
    max = 100000.0f;
}

////////////////////////////////////////////////////////////////////////////////

void DOF::SetValue(float inputValue){
    if(inputValue < min){
        inputValue = min;
    }
    if(inputValue > max){
        inputValue = max;
    }
    value = inputValue;
}

float DOF::GetValue(){
    return value;
}

void DOF::SetMinMax(float minValue, float maxValue){
    min = minValue;
    max = maxValue;
}
