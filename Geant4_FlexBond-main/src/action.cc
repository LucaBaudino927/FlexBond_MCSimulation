#include "action.hh"

MyActionInitialization::MyActionInitialization(){}

MyActionInitialization::~MyActionInitialization(){}

//For Multithread...
void MyActionInitialization::BuildForMaster() const
{
    MyRunAction *runAction = new MyRunAction();//run.hh
    SetUserAction(runAction);
}

void MyActionInitialization::Build() const{
    MyPrimaryGenerator* generator = new MyPrimaryGenerator();//generator.hh
    SetUserAction(generator);

    MyRunAction* runAction = new MyRunAction();//run.hh
    SetUserAction(runAction);

    MyEventAction *eventAction = new MyEventAction(runAction);//event.hh
    SetUserAction(eventAction);
    
    MySteppingAction *steppingAction = new MySteppingAction(eventAction);//stepping.hh
    SetUserAction(steppingAction);
}