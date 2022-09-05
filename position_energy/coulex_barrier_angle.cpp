//
// 
#define PI 3.14159

#define Z_BEAM 79
#define A_BEAM 197
#define Z_TARGET 60
#define A_TARGET 146

#define SAFE_DIS 5

// angle
#define THETA_MIN 28.8
#define THETA_MAX 60.3
#define THETA_NUM 30

void coulex_barrier_angle()
{
  double a = (A_BEAM+A_TARGET)/(double)A_TARGET;
  double b = 1.25*(pow((double)A_BEAM, 1/3.)+pow((double)A_TARGET, 1/3.));
  double c = 1.44*Z_BEAM*Z_TARGET;

  double d = a*c/(b+SAFE_DIS);

  cout << "coulex barrier " << d << endl;

  // angle
  TGraph *g = new TGraph();

  double gamma = (double)A_BEAM/(double)A_TARGET;
  double rr = 1.25*(pow((double)A_BEAM, 1/3.)+pow((double)A_TARGET, 1/3.)) + SAFE_DIS;

  double theta_step = (THETA_MAX-THETA_MIN)/(double)THETA_NUM;
  double theta_lab, theta_cm, e;

  cout << asin(gamma*sin(48.75*PI/180.))/PI*180 << endl;

  for(int i=0;i<THETA_NUM;i++){
    theta_lab = THETA_MIN+i*theta_step;
    if(gamma*sin(theta_lab*PI/180.)>1)  break;
    theta_cm = theta_lab + asin(gamma*sin(theta_lab*PI/180.))/PI*180;
    e = 0.72*Z_BEAM*Z_TARGET/rr*(1+gamma)*(1+1./sin(theta_cm*PI/180./2.));

    cout << theta_lab << " " << theta_cm << " " << e << endl;

    g->SetPoint(i, theta_lab, e);
  }

  TCanvas *can = new TCanvas("can", "", 0, 0, 600, 400);
  can->cd();

  g->GetXaxis()->SetTitle("#theta_{p}(deg)");
  g->GetYaxis()->SetTitle("Energy_{max}(MeV)");
  g->SetLineWidth(4);
  g->SetTitle("");

  g->Draw();
}