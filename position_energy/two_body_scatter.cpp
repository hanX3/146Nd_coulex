//

#define A_BEAM 40
#define A_TARGET 146
#define E_BEAM 138.8

//
void two_body_scatter()
{
  double theta_cm[180];
  double theta_beam[180];
  double theta_target[180];

  double e_beam[180];
  double e_target[180];

  double v1 = sqrt(2.*E_BEAM/(double)A_BEAM);
  double v1_new, v2_new;

  for(int i=0;i<180;i++){
    theta_cm[i] = (double)i;
    theta_beam[i] = atan((double)A_TARGET*sin((double)i/180.*3.14159)/((double)A_BEAM+(double)A_TARGET*cos((double)i/180.*3.14159)))/3.14159*180.;
    if(theta_beam[i]<0){
      theta_beam[i] += 180.;
    }

    theta_target[i] = (180.-i)/2.;

    v1_new = v1*sqrt(A_BEAM*A_BEAM+A_TARGET*A_TARGET+2.*A_BEAM*A_TARGET*cos((double)i/180.*3.14159))/(A_BEAM+A_TARGET);
    e_beam[i] = 0.5*A_BEAM*v1_new*v1_new;

    v2_new = v1*2.*A_BEAM/(A_BEAM+A_TARGET)*sin((double)i/180.*3.14159/2.);
    e_target[i] = 0.5*A_TARGET*v2_new*v2_new;
  }

  TGraph *g1 = new TGraph(180, theta_cm, theta_beam);
  TGraph *g2 = new TGraph(180, theta_cm, theta_target);
  TCanvas *c1 = new TCanvas("c1", "", 0, 0, 600, 400);
  c1->cd();

  g1->GetXaxis()->SetTitle("#theta_{CM}(deg)");
  g1->GetYaxis()->SetTitle("#theta_{LAB}(deg)");

  g1->GetXaxis()->SetRangeUser(0, 180);
  g1->GetYaxis()->SetRangeUser(0, 180);
  g2->GetXaxis()->SetRangeUser(0, 180);
  g2->GetYaxis()->SetRangeUser(0, 180);

  g1->SetLineColor(2);
  g1->SetLineWidth(4);
  g1->SetMarkerColor(2);

  g2->SetLineColor(4);
  g2->SetLineWidth(4);
  g2->SetMarkerColor(4);

  g1->SetTitle("");
  g2->SetTitle("");
  g1->Draw();
  g2->Draw("same");

  TLegend *leg1 = new TLegend(0.6, 0.7, 0.89, 0.89);
  leg1->AddEntry(g1, "theta_beam", "l");
  leg1->AddEntry(g2, "theta_target", "l");
  leg1->Draw();

  //
  TGraph *g3 = new TGraph(180, theta_beam, e_beam);
  TGraph *g4 = new TGraph(180, theta_target, e_target);
  TCanvas *c2 = new TCanvas("c2", "", 0, 0, 600, 400);
  c2->cd();

  g3->GetXaxis()->SetTitle("#theta_{P.T}(deg)");
  g3->GetYaxis()->SetTitle("Energy(MeV)");

  g3->SetLineColor(2);
  g3->SetLineWidth(4);
  g3->SetMarkerColor(2);

  g4->GetXaxis()->SetTitle("#theta_{P.T}(deg)");
  g4->GetYaxis()->SetTitle("Energy(MeV)");

  g4->SetLineColor(4);
  g4->SetLineWidth(4);
  g4->SetMarkerColor(4);

  g3->SetTitle("");
  g4->SetTitle("");
  g3->Draw();
  g4->Draw("same");

  TLegend *leg2 = new TLegend(0.6, 0.7, 0.89, 0.89);
  leg2->AddEntry(g3, "theta_beam", "l");
  leg2->AddEntry(g4, "theta_target", "l");
  leg2->Draw();

  //
  TGraph *g5 = new TGraph(180, theta_target, theta_beam);

  TCanvas *c3 = new TCanvas("c3", "", 0, 0, 600, 400);
  c3->cd();

  g5->GetXaxis()->SetTitle("#theta_{target}");
  g5->GetYaxis()->SetTitle("#theta_{beam}");
  g5->SetLineWidth(4);

  g5->Draw();


  // save txt
  // ofstream file_out1, file_out2;
  // file_out1.open("angle.txt");
  // file_out2.open("energy.txt");
  // for(int i=0;i<180;i++){
  //   file_out1 << theta_cm[i] << " " << theta_beam[i] << " " << theta_target[i] << endl;
  //   file_out2 << theta_beam[i] << " " << e_beam[i] << " " << theta_target[i] << " " << e_target[i] << endl;
  // }

  // file_out1.close();
  // file_out2.close();
}