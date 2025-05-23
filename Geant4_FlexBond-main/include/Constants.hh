#ifndef CONSTANTS_HH
#define CONSTANTS_HH

#include "globals.hh"

/***********************************************************************************************************************************
*	NofMySensitiveDetector = 6          se ho alpide, colla, kapton e rame							   *
*	NofMySensitiveDetector = 6+(#pad*2) se ho alpide, colla, kapton, rame e pad dell'alpide					   *
*	NofMySensitiveDetector = 6+(#pad*3) se ho alpide, colla, kapton, rame, pad dell'alpide e solder balls per ogni pad	   *
*	NofMySensitiveDetector = 9+(#pad*3) se ho alpide, colla, kapton, rame, pad dell'alpide, solder balls per ogni pad e PCB	   *
************************************************************************************************************************************/
//constexpr G4int NofMySensitiveDetector = 6 + (21 + 15 + 15 + 8 + 8 + 7)*2; // per ora non configurabile
constexpr G4int NofPads = (21 + 15 + 15 + 8 + 8 + 7);
//constexpr G4int NofPCBSensitiveDetector = 1;
constexpr G4double Pi = 3.141592653589793238462643383279502884;
const std::vector<G4ThreeVector> padCoordinates = { {1057.62*um, 525.*um, 0.},		//B00
						    {2157.62*um, 525.*um, 0.},
						    {4357.62*um, 525.*um, 0.},
						    {5457.62*um, 525.*um, 0.},
						    {6557.62*um, 525.*um, 0.},
						    {7657.62*um, 525.*um, 0.},
						    {8757.62*um, 525.*um, 0.},
						    {9857.62*um, 525.*um, 0.},
						    {12057.62*um, 525.*um, 0.},
						    {13157.62*um, 525.*um, 0.},
						    {16897.62*um, 525.*um, 0.},
						    {17997.62*um, 525.*um, 0.},
						    {20197.62*um, 525.*um, 0.},
						    {21297.62*um, 525.*um, 0.},
						    {22397.62*um, 525.*um, 0.},
						    {23497.62*um, 525.*um, 0.},
						    {24597.62*um, 525.*um, 0.},
						    {25697.62*um, 525.*um, 0.},
						    {26797.62*um, 525.*um, 0.},
						    {27897.62*um, 525.*um, 0.},
						    {28997.62*um, 525.*um, 0.},		//B20
						    
						    {2105.16*um, 7890.88*um, 0.},	//C00
						    {3947.28*um, 7890.88*um, 0.},
						    {5789.4*um, 7890.88*um, 0.},
						    {7631.52*um, 7890.88*um, 0.},
						    {9473.64*um, 7890.88*um, 0.},
						    {11315.76*um, 7890.88*um, 0.},
						    {13157.88*um, 7890.88*um, 0.},
						    {15000.*um, 7890.88*um, 0.},
						    {16842.12*um, 7890.88*um, 0.},
						    {18684.24*um, 7890.88*um, 0.},
						    {20526.36*um, 7890.88*um, 0.},
						    {22368.48*um, 7890.88*um, 0.},
						    {24210.6*um, 7890.88*um, 0.},
						    {26052.72*um, 7890.88*um, 0.},
						    {27894.84*um, 7890.88*um, 0.},	//C14
						    
						    {2105.16*um, 9906.88*um, 0.},	//D00
						    {3947.28*um, 9906.88*um, 0.},
						    {5789.4*um, 9906.88*um, 0.},
						    {7631.52*um, 9906.88*um, 0.},
						    {9473.64*um, 9906.88*um, 0.},
						    {11315.76*um, 9906.88*um, 0.},
						    {13157.88*um, 9906.88*um, 0.},
						    {15000.*um, 9906.88*um, 0.},
						    {16842.12*um, 9906.88*um, 0.},
						    {18684.24*um, 9906.88*um, 0.},
						    {20526.36*um, 9906.88*um, 0.},
						    {22368.48*um, 9906.88*um, 0.},
						    {24210.6*um, 9906.88*um, 0.},
						    {26052.72*um, 9906.88*um, 0.},
						    {27894.84*um, 9906.88*um, 0.},	//D14
						    
						    {2105.16*um, 11465.92*um, 0.},	//E00
						    {5789.4*um, 11465.92*um, 0.},
						    {9473.64*um, 11465.92*um, 0.},
						    {13157.88*um, 11465.92*um, 0.},
						    {16842.12*um, 11465.92*um, 0.},
						    {20526.36*um, 11465.92*um, 0.},
						    {24210.6*um, 11465.92*um, 0.},
						    {27894.84*um, 11465.92*um, 0.},	//E07
						    
						    {2105.16*um, 13723.84*um, 0.},	//F00
						    {5789.4*um, 13723.84*um, 0.},
						    {9473.64*um, 13723.84*um, 0.},
						    {13157.88*um, 13723.84*um, 0.},
						    {16842.12*um, 13723.84*um, 0.},
						    {20526.36*um, 13723.84*um, 0.},
						    {24210.6*um, 13723.84*um, 0.},
						    {27894.84*um, 13723.84*um, 0.}, 	//F07
						    
						    {3947.28*um, 14395.84*um, 0.},	//G00
						    {7631.52*um, 14395.84*um, 0.},
						    {11315.76*um, 14395.84*um, 0.},
						    {15000.*um, 14395.84*um, 0.},
						    {18684.24*um, 14395.84*um, 0.},
						    {22368.48*um, 14395.84*um, 0.},
						    {26052.72*um, 14395.84*um, 0.}	//G06
						    
						    };
	       
//constexpr G4int NofObservables = 3;

#endif

/**********************************************************************
				ALPIDE PADS
Pad Id Net Pad Geometry x [μm] y [μm]
B00 SUB B 1057.62 525
B01 SUB B 2157.62 525
B02 MCLK P B 4357.62 525
B03 MCLK N B 5457.62 525
B04 RST N B 6557.62 525
B05 POR DIS N B 7657.62 525
B06 DCTRL P B 8757.62 525
B07 DCTRL N B 9857.62 525
B08 DCLK P B 12057.62 525
B09 DCLK N B 13157.62 525
B10 HSDATA P B 16897.62 525
B11 HSDATA N B 17997.62 525
B12 CTRL B 20197.62 525
B13 DATA[3] B 21297.62 525
B14 DATA[2] B 22397.62 525
B15 DATA[1] B 23497.62 525
B16 DATA[0] B 24597.62 525
B17 BUSY B 25697.62 525
B18 DACMONI B 26797.62 525
B19 DACMONV B 27897.62 525
B20 SUB B 28997.62 525

C00 DVSS B 2105.16 7890.88
C01 CHIPID[6] B 3947.28 7890.88
C02 DVSS B 5789.4 7890.88
C03 CHIPID[5] B 7631.52 7890.88
C04 DVSS B 9473.64 7890.88
C05 CHIPID[4] B 11315.76 7890.88
C06 PVSS B 13157.88 7890.88
C07 CHIPID[3] B 15000 7890.88
C08 PVSS B 16842.12 7890.88
C09 CHIPID[2] B 18684.24 7890.88
C10 DVSS B 20526.36 7890.88
C11 CHIPID[1] B 22368.48 7890.88
C12 DVSS B 24210.6 7890.88
C13 CHIPID[0] B 26052.72 7890.88
C14 DVSS B 27894.84 7890.88

D00 DVDD B 2105.16 9906.88
D01 CHIPID[6] B 3947.28 9906.88
D02 DVDD B 5789.4 9906.88
D03 CHIPID[5] B 7631.52 9906.88
D04 DVDD B 9473.64 9906.88
D05 CHIPID[4] B 11315.76 9906.88
D06 PVDD B 13157.88 9906.88
D07 CHIPID[3] B 15000 9906.88
D08 PVDD B 16842.12 9906.88
D09 CHIPID[2] B 18684.24 9906.88
D10 DVDD B 20526.36 9906.88
D11 CHIPID[1] B 22368.48 9906.88
D12 DVDD B 24210.6 9906.88
D13 CHIPID[0] B 26052.72 9906.88
D14 DVDD B 27894.84 9906.88

E00 AVSS B 2105.16 11465.92
E01 AVSS B 5789.4 11465.92
E02 AVSS B 9473.64 11465.92
E03 AVSS B 13157.88 11465.92
E04 AVSS B 16842.12 11465.92
E05 AVSS B 20526.36 11465.92
E06 AVSS B 24210.6 11465.92
E07 AVSS B 27894.84 11465.92

F00 AVDD B 2105.16 13723.84
F01 AVDD B 5789.4 13723.84
F02 AVDD B 9473.64 13723.84
F03 AVDD B 13157.88 13723.84
F04 AVDD B 16842.12 13723.84
F05 AVDD B 20526.36 13723.84
F06 AVDD B 24210.6 13723.84
F07 AVDD B 27894.84 13723.84

G00 PWELL B 3947.28 14395.84
G01 SUB B 7631.52 14395.84
G02 PWELL B 11315.76 14395.84
G03 SUB B 15000 14395.84
G04 PWELL B 18684.24 14395.84
G05 SUB B 22368.48 14395.84
G06 PWELL B 26052.72 14395.84

**********************************************************************/
