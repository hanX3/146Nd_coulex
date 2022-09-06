//

// 78Kr 2+ --> 0+
// #define I1 2  
// #define I2 0
// #define LIFETIME 32.9 // ps, NNDC
// #define ENERGY 0.455 // MeV
// #define BR 1 // branch ration 
// #define CR 0.004 // ANU BRICC website

// 146Nd 2+ --> 0+
// #define I1 2  
// #define I2 0
// #define LIFETIME 27.9 // ps, NNDC
// #define ENERGY 0.454 // MeV
// #define BR 1 // branch ration 
// #define CR 0.015 // ANU BRICC website

// 146Nd 2+ --> 0+
#define I1 4 
#define I2 2
#define LIFETIME 3.8 // ps, NNDC
#define ENERGY 0.589 // MeV
#define BR 1 // branch ration 
#define CR 0.008 // ANU BRICC website


void lifetime2matrix()
{
  double be2_down = 0.08163*BR/(pow(ENERGY, 5.)*LIFETIME*(1+CR));
  cout << be2_down << endl;

  double be2_up = (2.*I1+1)/(2.*I2+1)*be2_down;
  cout << be2_up << endl;

  double matrix = sqrt((2.*I1+1)*be2_down);
  cout << matrix << endl;

}