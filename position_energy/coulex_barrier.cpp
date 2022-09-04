//
// 146Nd + 208Pb

#define Z_BEAM 60  // Nd
#define A_BEAM 146
#define Z_TARGET 79 // Pb
#define A_TARGET 197

void coulex_barrier()
{
  double a = (A_BEAM+A_TARGET)/(double)A_TARGET;
  double b = 1.25*(pow((double)A_BEAM, 1/3.)+pow((double)A_TARGET, 1/3.));
  double c = 1.44*Z_BEAM*Z_TARGET;

  double d = a*c/(b+5.);

  cout << d << endl;
}