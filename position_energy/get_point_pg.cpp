
#define PI 3.14159265

// Ge detector info
double phi_ge[8] = {22.5, 67.5, 112.5, 157.5, 202.5, 247.5, 292.5, 337.5}; //unit degree
double d1 = 200.; //unit mm
double r_ge = 25.; //ge detector

// Si detector info
double d2 = 10;

void get_point_pg()
{
  TFile *fi = new TFile("point_pg_10mm.root", "recreate");
  TTree *tree_ge = new TTree("tree_ge", "ge point info");
  TTree *tree_si = new TTree("tree_si", "si point info");

  int id_ge;
  double x_ge;
  double y_ge;
  double z_ge;

  tree_ge->Branch("id_ge", &id_ge, "id_ge/I");
  tree_ge->Branch("x_ge", &x_ge, "x_ge/D");
  tree_ge->Branch("y_ge", &y_ge, "y_ge/D");
  tree_ge->Branch("z_ge", &z_ge, "z_ge/D");

  int id_sir;
  int id_sis;
  double x_si;
  double y_si;
  double z_si;

  tree_si->Branch("id_sir", &id_sir, "id_sir/I");
  tree_si->Branch("id_sis", &id_sis, "id_sis/I");
  tree_si->Branch("x_si", &x_si, "x_si/D");
  tree_si->Branch("y_si", &y_si, "y_si/D");
  tree_si->Branch("z_si", &z_si, "z_si/D");

  //
  double ring_si[24];
  for(int i=0;i<24;i++){
    ring_si[i] = 11. + (double)i*1.;
  }
  double phi_si[32];
  for(int i=0;i<32;i++){
    phi_si[i] = (double)i*11.25;
  }

  TRandom3 *rd = new TRandom3(0);
  double xx_ge = 0.;
  double yy_ge = 0.;
  double zz_ge = 0.;
  double xx_si = 0.;
  double yy_si = 0.;
  double zz_si = 0.;

  int n_ge = 10000;
  int n_si = 100;

  int k = 0;
  int k_ge = 0;
  int k_si = 0;
  double rr_ge = 0.;
  double rr_si = 0.;
  double phi_si_temp = 0.;

  double xx_si_mean = 0;
  double yy_si_mean = 0;
  double zz_si_mean = 0;
  double x_cross = 0;
  double y_cross = 0;
  double z_cross = 0;

  TGraph2D *g1 = new TGraph2D();
  TGraph2D *g2 = new TGraph2D();
  g1->SetName("g1");
  g1->SetTitle("g1");
  g1->GetXaxis()->SetTitle("x");
  g1->GetYaxis()->SetTitle("y");
  g1->GetZaxis()->SetTitle("z");

  g2->SetName("g2");
  g2->SetTitle("g2");

  int n_ge_temp = 0;
  for(int i=0;i<8;i++){
    //ge
    n_ge_temp = 0;
    while(1){
      if(n_ge_temp >= n_ge){
        break;
      }

      rr_ge = 0;
      xx_ge = d1*cos(phi_ge[i]*PI/180.) + 2.*r_ge*(rd->Rndm()-0.5);
      yy_ge = (d1-xx_ge*cos(phi_ge[i]*PI/180.))/sin(phi_ge[i]*PI/180.);
      zz_ge = 2.*r_ge*(rd->Rndm()-0.5);

      rr_ge += (xx_ge-d1*cos(phi_ge[i]*PI/180.))*(xx_ge-d1*cos(phi_ge[i]*PI/180.));
      rr_ge += (yy_ge-d1*sin(phi_ge[i]*PI/180.))*(yy_ge-d1*sin(phi_ge[i]*PI/180.));
      rr_ge += zz_ge*zz_ge;

      if(rr_ge <= r_ge*r_ge){
        g1->SetPoint(k, xx_ge, yy_ge, zz_ge);
        k++;
        k_ge++;
        n_ge_temp++;

        //treege fill
        id_ge = i;
        x_ge = xx_ge;
        y_ge = yy_ge;
        z_ge = zz_ge;

        tree_ge->Fill();
      }
    }
  }

  //si
  for(int ir=0;ir<24;ir++){
    for(int is=0;is<32;is++){
      for(int jj=0;jj<n_si;jj++){
        phi_si_temp = phi_si[is] + 11.25*rd->Rndm();
        rr_si = ring_si[ir]+rd->Rndm();
        xx_si = rr_si*cos(phi_si_temp*PI/180.);
        yy_si = rr_si*sin(phi_si_temp*PI/180.);
        zz_si = d2;

        g2->SetPoint(k_si, xx_si, yy_si, zz_si);
        k++;
        k_si++;

        //treesi fill
        id_sir = ir;
        id_sis = is;
        x_si = xx_si;
        y_si = yy_si;
        z_si = zz_si;

        tree_si->Fill();
      }
    }
  }

  cout << "k " << k << endl;
  g1->SetPoint(k, 0, 0, -200);
  g1->SetPoint(k+1, 0, 0, 200);
  g1->SetPoint(k+2, -200, 0, 0);
  g1->SetPoint(k+3, 200, 0, 0);
  g1->SetPoint(k+4, 0, -200, 0);
  g1->SetPoint(k+5, 0, 200, 0);

  cout << "k_ge  " << k_ge << endl;
  cout << "k_si  " << k_si << endl;
  TCanvas *c0 = new TCanvas("c0", "c0", 0, 0, 660, 600);
  c0->cd();
  g1->SetMarkerColor(4);
  g1->SetMarkerStyle(1);
  // g1->Draw("p");

  g2->SetMarkerStyle(1);
  g2->SetMarkerColor(2);
  // g2->Draw("p same");

  fi->cd();
  g1->Write();
  g2->Write();
  tree_ge->Write();
  tree_si->Write();
  fi->Close();
}
