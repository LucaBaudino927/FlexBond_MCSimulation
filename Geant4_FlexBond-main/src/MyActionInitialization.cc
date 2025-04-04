#include "MyActionInitialization.hh"

MyActionInitialization::MyActionInitialization() {}

MyActionInitialization::~MyActionInitialization(){}

//For Multithread...
void MyActionInitialization::BuildForMaster() const
{
    MyEventAction* eventAction = new MyEventAction();
    SetUserAction(new MyRunAction(eventAction));
}

void MyActionInitialization::Build() const{  
    MyPrimaryGenerator* generator = new MyPrimaryGenerator();
    SetUserAction(generator);
    
    MyEventAction* eventAction = new MyEventAction();
    SetUserAction(eventAction);

    MyRunAction* runAction = new MyRunAction(eventAction);
    SetUserAction(runAction);
}
