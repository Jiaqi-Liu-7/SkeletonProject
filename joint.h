////////////////////////////////////////
// joint.h
////////////////////////////////////////

#ifndef CSE169_JOINT_H
#define CSE169_JOINT_H

#include "core.h"
#include "DOF.h"
#include "tokenizer.h"
#include "matrix34.h"
#include "vector3.h"
#include <vector>

class joint {
public:
    joint();
    void Update(Matrix34 OldWorldMatrix);
    bool Load(Tokenizer& token);
    void AddChild(joint* child);
    void Draw(Matrix34 viewMatrix);
    
    std::vector<joint*> children;
    std::vector<DOF*> jointDOF;
    Vector3 offset;
    Vector3 boxmin;
    Vector3 boxmax;
    Vector3 pose;
    Matrix34 Local;
    Matrix34 World;
};

#endif
