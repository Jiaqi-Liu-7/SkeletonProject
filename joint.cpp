
#include "joint.h"

////////////////////////////////////////////////////////////////////////////////

joint::joint(){
    offset.Set(0.0f, 0.0f, 0.0f);
    boxmin.Set(0.0f, 0.0f, 0.0f);
    boxmax.Set(0.0f, 0.0f, 0.0f);
    pose.Set(0.0f, 0.0f, 0.0f);
    Local = Matrix34::IDENTITY;
    World = Matrix34::IDENTITY;
    
    DOF* xDOF = new DOF();
    DOF* yDOF = new DOF();
    DOF* zDOF = new DOF();
    jointDOF.push_back(xDOF);
    jointDOF.push_back(yDOF);
    jointDOF.push_back(zDOF);
}

////////////////////////////////////////////////////////////////////////////////

bool joint::Load(Tokenizer& token){
    float min, max;
    token.FindToken("{");
    while(true){
        char temp[256];
        token.GetToken(temp);
        if(strcmp(temp,"offset")==0){
            offset.x = token.GetFloat();
            offset.y = token.GetFloat();
            offset.z = token.GetFloat();
        }
        else if(strcmp(temp,"boxmin")==0){
            boxmin.x = token.GetFloat();
            boxmin.y = token.GetFloat();
            boxmin.z = token.GetFloat();
        }
        else if(strcmp(temp,"boxmax")==0){
            boxmax.x = token.GetFloat();
            boxmax.y = token.GetFloat();
            boxmax.z = token.GetFloat();
        }
        else if(strcmp(temp,"rotxlimit")==0){
            min = token.GetFloat();
            max = token.GetFloat();
            jointDOF[0]->SetMinMax(min, max);
        }
        else if(strcmp(temp,"rotylimit")==0){
            min = token.GetFloat();
            max = token.GetFloat();
            jointDOF[1]->SetMinMax(min, max);
        }
        else if(strcmp(temp,"rotzlimit")==0){
            min = token.GetFloat();
            max = token.GetFloat();
            jointDOF[2]->SetMinMax(min, max);
        }
        else if(strcmp(temp,"pose")==0){
            jointDOF[0]->SetValue(token.GetFloat());
            jointDOF[1]->SetValue(token.GetFloat());
            jointDOF[2]->SetValue(token.GetFloat());
        }
        else if(strcmp(temp,"balljoint")==0){
            joint* childJoint = new joint();
            childJoint->Load(token);
            AddChild(childJoint);
        }
        else if(strcmp(temp,"}")==0){
            return true;
        }
        else{
            token.SkipLine();
        }
    }
}
    
////////////////////////////////////////////////////////////////////////////////
    
void joint::Update(Matrix34 OldWorldMatrix){
    float x = jointDOF[0]->GetValue();
    float y = jointDOF[1]->GetValue();
    float z = jointDOF[2]->GetValue();
    
    float cx = cosf(x), sx = sinf(x);
    float cy = cosf(y), sy = sinf(y);
    float cz = cosf(z), sz = sinf(z);
    
    Local = Matrix34(cy*cz,sx*sy*cz-cx*sz,cx*sy*cz+sx*sz,offset.x,
                     cy*sz,sx*sy*sz+cx*cz,cx*sy*sz-sx*cz,offset.y,
                     -sy,sx*cy,cx*cy,offset.z);
    World.Dot(OldWorldMatrix,Local);
    for(unsigned int i = 0; i < children.size(); i++){
        children[i]->Update(World);
    }
}

////////////////////////////////////////////////////////////////////////////////
void joint::AddChild(joint* child){
    children.push_back(child);
}

////////////////////////////////////////////////////////////////////////////////
void joint::Draw(Matrix34 viewMatrix){
    //drawWireBox(boxmin.x,boxmin.y,boxmin.z,boxmax.x,boxmax.y,boxmax.z);
    glPushMatrix();
    glMultMatrixf(World);
    glTranslatef(0.5f*(boxmin.x+boxmax.x),0.5f*(boxmin.y+boxmax.y),0.5f*(boxmin.z+boxmax.z));
    glScalef(boxmax.x-boxmin.x,boxmax.y-boxmin.y,boxmax.z-boxmin.z);
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    glutWireCube(1.0f);
    glPopMatrix();
    for(unsigned int i = 0; i < children.size();i++){
        children[i]->Draw(viewMatrix);
    }
}
