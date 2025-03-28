#ifndef MY_RUN_ACTION_HH
#define MY_RUN_ACTION_HH

#include <vector>
#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "G4Threading.hh"

class MyRunAction : public G4UserRunAction
{  
  
public:
    
        MyRunAction();
        ~MyRunAction();
        
        virtual void BeginOfRunAction(const G4Run*);
        virtual void EndOfRunAction(const G4Run*);
        
        void AddToHistoNames(G4String name) { histoNames.push_back(name); }
	G4String GetHistoNameByIndex(G4int index)  { return histoNames[index]; }
        std::vector<G4String> GetHistoNames() { return histoNames; }
        
private:

	std::vector<G4String> histoNames;

};

#endif
