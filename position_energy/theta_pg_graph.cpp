
void theta_pg_graph()
{
  ifstream fi;
  fi.open("theta_pg_error_10mm.txt");

  char temp[256];
  fi.getline(temp, 256);
  int id_ge;
  int id_sir;
  int id_sis;
  double theta_used;
  double theta_min;
  double theta_max;

  TCanvas *ce[8];
  ce[0] = new TCanvas("ce0", "ge0", 0, 0, 1600, 320);
  ce[1] = new TCanvas("ce1", "ge1", 0, 0, 1600, 320);
  ce[2] = new TCanvas("ce2", "ge2", 0, 0, 1600, 320);
  ce[3] = new TCanvas("ce3", "ge3", 0, 0, 1600, 320);
  ce[4] = new TCanvas("ce4", "ge4", 0, 0, 1600, 320);
  ce[5] = new TCanvas("ce5", "ge5", 0, 0, 1600, 320);
  ce[6] = new TCanvas("ce6", "ge6", 0, 0, 1600, 320);
  ce[7] = new TCanvas("ce7", "ge7", 0, 0, 1600, 320);
  TCanvas *c[8];
  c[0] = new TCanvas("c0", "ge_error_0", 0, 0, 1600, 320);
  c[1] = new TCanvas("c1", "ge_error_1", 0, 0, 1600, 320);
  c[2] = new TCanvas("c2", "ge_error_2", 0, 0, 1600, 320);
  c[3] = new TCanvas("c3", "ge_error_3", 0, 0, 1600, 320);
  c[4] = new TCanvas("c4", "ge_error_4", 0, 0, 1600, 320);
  c[5] = new TCanvas("c5", "ge_error_5", 0, 0, 1600, 320);
  c[6] = new TCanvas("c6", "ge_error_6", 0, 0, 1600, 320);
  c[7] = new TCanvas("c7", "ge_error_7", 0, 0, 1600, 320);

  TGraphErrors *ge[8];
  TGraph *g[8];
  double ee[8];

  TLine *lle[8*24];
  TLine *ll[8*24];
  stringstream ss_temp;
  for(int i=0;i<8;i++){
    ge[i] = new TGraphErrors();
    g[i] = new TGraph();
    ee[i] = 0.;

    for(int j=0;j<24*32;j++){
      fi >> id_ge >> id_sir >> id_sis >> theta_used >> theta_min >> theta_max;
      ge[i]->SetPoint(j, j+1, theta_used);
      ge[i]->SetPointError(j, 0, (theta_max-theta_min)/2.);
      g[i]->SetPoint(j, j+1, (theta_max-theta_min)/2.);

      ee[i] += (theta_max-theta_min)/2.;
    }

    ee[i] = ee[i]/24./32.;
    cout << ee[i] << endl; 

    ce[i]->cd();
    ss_temp.str("");
    ss_temp << "ge" << i << "theta";
    ge[i]->SetTitle(ss_temp.str().c_str());
    ge[i]->GetXaxis()->SetTitle("si channel");
    ge[i]->GetYaxis()->SetTitle("theta");
    ge[i]->Draw();
    for(int k=0;k<24+1;k++){
      lle[24*i+k] = new TLine(32*k, 20, 32*k, 160.);
      lle[24*i+k]->SetLineColor(2);
      lle[24*i+k]->SetLineWidth(2);
      lle[24*i+k]->Draw("");
    }
    
    ss_temp.str("");
    ss_temp << "fig347" << (char)(97+i) << ".png";
    ce[i]->SaveAs(ss_temp.str().c_str());

    c[i]->cd();
    ss_temp.str("");
    ss_temp << "ge" << i << "theta error";
    g[i]->SetTitle(ss_temp.str().c_str());
    g[i]->GetXaxis()->SetTitle("si channel");
    g[i]->GetYaxis()->SetTitle("theta error");
    g[i]->Draw("");
    for(int k=0;k<24+1;k++){
      ll[24*i+k] = new TLine(32*k, 8., 32*k, 11.);
      ll[24*i+k]->SetLineColor(2);
      ll[24*i+k]->SetLineWidth(2);
      ll[24*i+k]->Draw("");
    }
    ss_temp.str("");
    ss_temp << "fig348" << (char)(97+i) << ".png";
    c[i]->SaveAs(ss_temp.str().c_str());
  }

  fi.close();
}
