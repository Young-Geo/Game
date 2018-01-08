#include "work.h"


int main()
{
    /////
    ////
    gWORK->Init();
    gWORK->Start();//nei loop
    gWORK->Detach();
    return 0;
}
