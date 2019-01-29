////////////////////////////////////////
// skeleton.h
////////////////////////////////////////

#ifndef CSE169_SKELETON_H
#define CSE169_SKELETON_H

#include "core.h"
#include "DOF.h"
#include "joint.h"
#include "tokenizer.h"
#include "matrix34.h"
#include "vector3.h"
#include <vector>

class skeleton {
public:
    skeleton();
    
    void Update(Matrix34 OldWorldMatrix);
    bool Load(const char *file);
    void Draw(Matrix34 viewMatrix);
    
    joint* root;
};

#endif
