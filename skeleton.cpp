#include "skeleton.h"

skeleton::skeleton(){
    root = NULL;
}

bool skeleton::Load(const char* file){
    
    Tokenizer token;
    token.Open(file);
    token.FindToken("balljoint");
    root = new joint();
    root->Load(token);
    
    token.Close();
    return true;
}

void skeleton::Update(Matrix34 OldWorldMatrix){
    root->Update(OldWorldMatrix);
}

void skeleton::Draw(Matrix34 viewMatrix){
    root->Draw(viewMatrix);
}
