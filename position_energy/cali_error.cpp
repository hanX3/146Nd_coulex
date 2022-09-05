#define PI 3.14159265

// Ge
double theta_ge = 90.;
double phi_ge[8] = {22.5, 67.5, 112.5, 157.5, 202.5, 247.5, 292.5, 337.5}; //unit degree
double d1 = 200.; //unit mm
double r_ge = 25.; //ge detector

// Si
double d2 = 10; //unit mm

void cali_error()
{
  //data
  int simu_ge = 10000;
  int simu_si = 100;

  double ring_si[24];
  for(int i=0;i<24;i++){
    ring_si[i] = 11. + (double)i*1.;
  }
  double phi_si[32];
  for(int i=0;i<32;i++){
    phi_si[i] = (double)i*11.25;
  }

  double x_ge_used = 0;
  double y_ge_used = 0;
  double z_ge_used = 0;
  double x_si_used = 0;
  double y_si_used = 0;
  double z_si_used = 0;
  double theta_used[8*24*32];
  memset(theta_used, 0, 8*24*32);

  for(int i=0;i<8;i++){//ge
    x_ge_used = d1*sin(theta_ge*PI/180.)*cos(phi_ge[i]*PI/180.);
    y_ge_used = d1*sin(theta_ge*PI/180.)*sin(phi_ge[i]*PI/180.);
    z_ge_used = d1*cos(theta_ge*PI/180.);
    if(i==0){
      //cout << "ge(x:y:z)  " << x_ge_used << " : " << y_ge_used << " : " << z_ge_used << endl;
    }
    for(int j=0;j<24;j++){//sir
      if(i==0){
        cout << endl;
      }
      for(int k=0;k<32;k++){//sis
        x_si_used = (ring_si[j]+0.5)*cos((phi_si[k]+5.625)*PI/180.);
        y_si_used = (ring_si[j]+0.5)*sin((phi_si[k]+5.625)*PI/180.);
        z_si_used = d2;
        theta_used[32*24*i+32*j+k] = acos((x_ge_used*x_si_used+y_ge_used*y_si_used+z_ge_used*z_si_used)/sqrt(x_ge_used*x_ge_used+y_ge_used*y_ge_used+z_ge_used*z_ge_used)/sqrt(x_si_used*x_si_used+y_si_used*y_si_used+z_si_used*z_si_used))*180./PI;
      }
    }
  }
  //data end


  TFile *fi = TFile::Open("point_pg_10mm.root");

  TTree *tr_ge = (TTree*)fi->Get("tree_ge");
  int id_ge;
  double x_ge;
  double y_ge;
  double z_ge;
  TBranch *b_id_ge = tr_ge->GetBranch("id_ge");
  TBranch *b_x_ge = tr_ge->GetBranch("x_ge");
  TBranch *b_y_ge = tr_ge->GetBranch("y_ge");
  TBranch *b_z_ge = tr_ge->GetBranch("z_ge");
  b_id_ge->SetAddress(&id_ge);
  b_x_ge->SetAddress(&x_ge);
  b_y_ge->SetAddress(&y_ge);
  b_z_ge->SetAddress(&z_ge);

  TTree *tr_si = (TTree*)fi->Get("tree_si");
  int id_sir;
  int id_sis;
  double x_si;
  double y_si;
  double z_si;
  TBranch *b_id_sir = tr_si->GetBranch("id_sir");
  TBranch *b_id_sis = tr_si->GetBranch("id_sis");
  TBranch *b_x_si = tr_si->GetBranch("x_si");
  TBranch *b_y_si = tr_si->GetBranch("y_si");
  TBranch *b_z_si = tr_si->GetBranch("z_si");
  b_id_sir->SetAddress(&id_sir);
  b_id_sis->SetAddress(&id_sis);
  b_x_si->SetAddress(&x_si);
  b_y_si->SetAddress(&y_si);
  b_z_si->SetAddress(&z_si);

  //analysis
  Long64_t entry_ge = tr_ge->GetEntries();
  Long64_t entry_si = tr_si->GetEntries();
  cout << "ge entries  " << entry_ge << endl;
  cout << "si entries  " << entry_si << endl;

  /*
    //test
  TGraph2D *g = new TGraph2D();
  for(Long64_t i=0;i<entry_ge;i++){
    trge->GetEntry(i);
    g->SetPoint(i, x_si, y_si, z_si);
  }
  for(Long64_t i=0;i<entry_si;i++){
    trsi->GetEntry(i);
    g->SetPoint(i+entry_ge, x_ge, y_ge, z_ge);
  }
  g->SetMarkerStyle(1);
  g->Draw("p");
    //test done
  */


  TFile *fo = new TFile("theta_pg_error.root", "recreate");
  TH1D *herror[8*24*32];
  stringstream ss;
  TDirectory *dir_ge[8];
  TDirectory *dir_ge_sir[8*24];
  for(int i=0;i<8;i++){
    ss.str("");
    ss << "ge" << i;
    dir_ge[i] = fo->mkdir(ss.str().c_str());
    for(int j=0;j<24;j++){
      ss.str("");
      ss << "ge" << i << "sir" << j;
      dir_ge_sir[24*i+j] = dir_ge[i]->mkdir(ss.str().c_str());
    }
  }

  double theta_temp;
  double theta_min_temp;
  double theta_max_temp;
  ofstream ftxt;
  ftxt.open("theta_pg_error.txt");

  ftxt << "ge.no    sir.no    sis.no    theta_used    theta_min    theta_max" << endl;

  //
  for(int i=0;i<8;i++){//ge
    dir_ge[i]->cd();

    for(int j=0;j<24;j++){//sir
      dir_ge_sir[24*i+j]->cd();

      for(int k=0;k<32;k++){//sis
        cout << "(" << i << "-" << j << "-" << k << ")" << endl;

        ss.str("");
        ss << "ge" << i << "sir" << j << "sis" << k;
        herror[32*24*i+32*j+k] = new TH1D(ss.str().c_str(), "", 720, -360, 360);
        ss.str("");
        ss << "theta used " << theta_used[32*24*i+32*j+k];
        herror[32*24*i+32*j+k]->SetTitle(ss.str().c_str());

        for(Long64_t ii=(i*simu_ge);ii<((i+1)*simu_ge);ii++){//ge entry
          tr_ge->GetEntry(ii);
          for(int jj=((32*j+k)*simu_si);jj<((32*j+k+1)*simu_si);jj++){//si entry
            tr_si->GetEntry(jj);
            theta_temp = acos((x_ge*x_si+y_ge*y_si+z_ge*z_si)/sqrt(x_ge*x_ge+y_ge*y_ge+z_ge*z_ge)/sqrt(x_si*x_si+y_si*y_si+z_si*z_si))*180./PI;
            herror[32*24*i+32*j+k]->Fill(theta_temp);

            if(ii==(i*simu_ge) && jj==((32*j+k)*simu_si)){
              theta_min_temp = theta_temp;
              theta_max_temp = theta_temp;
            }
            else{
              if(theta_temp < theta_min_temp){
                theta_min_temp = theta_temp;
              }
              if(theta_temp > theta_max_temp){
                theta_max_temp = theta_temp;
              }
            }
          }
        }
        //write txt file
        ftxt << std::setw(4) << i << std::setw(9) << j << std::setw(9) << k << std::setw(16) << theta_used[32*24*i+32*j+k] << std::setw(14) << theta_min_temp << std::setw(14) << theta_max_temp << endl;
      }
      dir_ge[i]->cd();
    }
    fo->cd();
  }

  ftxt.close();

  fi->Close();
  fo->cd();
  fo->Write();
  fo->Close();
}
































