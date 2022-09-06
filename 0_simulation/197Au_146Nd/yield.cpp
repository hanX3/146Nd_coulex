//

#define DEG30_NUM 6
#define DEG60_NUM 8
#define DEG90_NUM 12
#define DEG120_NUM 8
#define DEG150_NUM 6

//
#define Z_BEAM 79.
#define A_AIM 146
#define TIME 100 // hour
#define GE_SOLID_ANGLE 0.1
#define GAMMA_EFF 0.2

// 2+ --> 0+
// #define UP_CS_DEG30 0.51328E+03
// #define UP_CS_DEG60 0.48536E+03
// #define UP_CS_DEG90 0.46385E+03
// #define UP_CS_DEG120 0.44083E+03
// #define UP_CS_DEG150 0.43428E+03

// 4+ --> 2+
// #define UP_CS_DEG30 0.18906E+03
// #define UP_CS_DEG60 0.16655E+03
// #define UP_CS_DEG90 0.15310E+03
// #define UP_CS_DEG120 0.15165E+03
// #define UP_CS_DEG150 0.15811E+03

// 3- --> 4+
// #define UP_CS_DEG30 0.10497E+00
// #define UP_CS_DEG60 0.10729E+00
// #define UP_CS_DEG90 0.10400E+00
// #define UP_CS_DEG120 0.95258E-01
// #define UP_CS_DEG150 0.86484E-01

// // 3- --> 2+
// #define UP_CS_DEG30 0.10032E+02
// #define UP_CS_DEG60 0.12027E+02
// #define UP_CS_DEG90 0.13733E+02
// #define UP_CS_DEG120 0.13743E+02
// #define UP_CS_DEG150 0.12288E+02

// // 3- --> 0+
// #define UP_CS_DEG30 0.47814E-06
// #define UP_CS_DEG60 0.38794E-06
// #define UP_CS_DEG90 0.26954E-06
// #define UP_CS_DEG120 0.38307E-06
// #define UP_CS_DEG150 0.45493E-06

// // 1- --> 2+
// #define UP_CS_DEG30 0.11573E+01
// #define UP_CS_DEG60 0.12099E+01
// #define UP_CS_DEG90 0.12752E+01
// #define UP_CS_DEG120 0.13284E+01
// #define UP_CS_DEG150 0.13562E+01

// // 1- --> 0+
#define UP_CS_DEG30 0.41367E+01
#define UP_CS_DEG60 0.45281E+01
#define UP_CS_DEG90 0.45135E+01
#define UP_CS_DEG120 0.40441E+01
#define UP_CS_DEG150 0.35061E+01

//
void yield()
{
  double y1u = 1E-30*5E-9*TIME*3600/Z_BEAM/1.6E-19*6.022E23/A_AIM*UP_CS_DEG30*GE_SOLID_ANGLE*DEG30_NUM*GAMMA_EFF;
  double y2u = 1E-30*5E-9*TIME*3600/Z_BEAM/1.6E-19*6.022E23/A_AIM*UP_CS_DEG60*GE_SOLID_ANGLE*DEG60_NUM*GAMMA_EFF;
  double y3u = 1E-30*5E-9*TIME*3600/Z_BEAM/1.6E-19*6.022E23/A_AIM*UP_CS_DEG90*GE_SOLID_ANGLE*DEG90_NUM*GAMMA_EFF;
  double y4u = 1E-30*5E-9*TIME*3600/Z_BEAM/1.6E-19*6.022E23/A_AIM*UP_CS_DEG120*GE_SOLID_ANGLE*DEG120_NUM*GAMMA_EFF;
  double y5u = 1E-30*5E-9*TIME*3600/Z_BEAM/1.6E-19*6.022E23/A_AIM*UP_CS_DEG150*GE_SOLID_ANGLE*DEG150_NUM*GAMMA_EFF;

  cout << y1u+y2u+y3u+y4u+y5u << endl;
}