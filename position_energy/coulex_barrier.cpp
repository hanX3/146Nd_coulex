//
// 
#define PI 3.14159

#define Z_BEAM 20
#define A_BEAM 40
#define Z_TARGET 60
#define A_TARGET 146

#define SAFE_DIS 5

//
void coulex_barrier()
{
  double a = (A_BEAM+A_TARGET)/(double)A_TARGET;
  double b = 1.25*(pow((double)A_BEAM, 1/3.)+pow((double)A_TARGET, 1/3.));
  double c = 1.44*Z_BEAM*Z_TARGET;

  double d = a*c/(b+SAFE_DIS);

  cout << "coulex barrier " << d << endl;
}