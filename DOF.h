////////////////////////////////////////
// DOF.h
////////////////////////////////////////

#ifndef CSE169_DOF_H
#define CSE169_DOF_H

#include "core.h"

class DOF {
public:
    DOF();
    
    void SetValue(float inputValue);
    float GetValue();
    void SetMinMax(float minValue, float maxValue);
    
private:
    float value;
    float min;
    float max;
    
};

#endif
