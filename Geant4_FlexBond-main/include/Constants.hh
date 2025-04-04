#ifndef CONSTANTS_HH
#define CONSTANTS_HH

#include "globals.hh"

constexpr G4int NofMySensitiveDetector = 21; // per ora non configurabile
constexpr G4int NofPads = 5;
const std::vector<G4ThreeVector> padCoordinates = { {-0.*mm, -0.*mm, 0.}, 
						    {-1.*mm, -1.*mm, 0.}, 
						    {-1.*mm, +1.*mm, 0.}, 
						    {+1.*mm, -1.*mm, 0.}, 
						    {+1.*mm, +1.*mm, 0.} };

							       
//constexpr G4int NofObservables = 3;

#endif
