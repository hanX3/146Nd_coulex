#define PI 3.14159265

void delta_energy()
{
  double beta = 0.1;
  double beta_error = 0.01;
  double theta_error = 10.2;//unit degree
  double hpge_error = 0.0015;

  TCanvas *c0 = new TCanvas("c0", "c0", 0, 0, 800, 320);
  TCanvas *c1 = new TCanvas("c1", "c1", 820, 0, 800, 320);
  TCanvas *c2 = new TCanvas("c2", "c2", 0, 360, 800, 320);
  TCanvas *c3 = new TCanvas("c3", "c3", 820, 360, 800, 320);

  TGraph *g0 = new TGraph();
  TGraph *g1 = new TGraph();
  TGraph *g2 = new TGraph();
  TGraph *g3 = new TGraph();

  double theta[180];
  double delta_part1[180];
  double delta_part2[180];
  double delta_part3[180];
  double delta_all[180];

  for(int i=0;i<180;i++){
    theta[i] = (double)i;
    delta_part1[i] = beta*sin(theta[i]*PI/180.)/(1-beta*cos(theta[i]*PI/180.))*(theta_error*PI/180.);
    g0->SetPoint(i, i, delta_part1[i]);

    delta_part2[i] = abs((-beta+cos(theta[i]*PI/180.))/(1-beta*beta)/(1-beta*cos(theta[i]*PI/180.))*beta_error);
    g1->SetPoint(i, i, delta_part2[i]);

    delta_part3[i] = hpge_error;
    g2->SetPoint(i, i, delta_part3[i]);

    delta_all[i] = sqrt(delta_part1[i]*delta_part1[i] + delta_part2[i]*delta_part2[i] + delta_part3[i]*delta_part3[i]);
    g3->SetPoint(i, i, delta_all[i]);
  }

  c0->cd();
  g0->SetTitle("theta contribution");
  g0->GetXaxis()->SetTitle("theta");
  g0->GetYaxis()->SetTitle("dleta E / E");
  g0->GetXaxis()->SetRangeUser(0, 190.);
  g0->SetLineColor(2);
  g0->SetLineWidth(2);
  g0->Draw("AC");

  c1->cd();
  g1->SetTitle("beta contribution");
  g1->GetXaxis()->SetTitle("theta");
  g1->GetYaxis()->SetTitle("dleta E / E");
  g1->GetXaxis()->SetRangeUser(0, 190.);
  g1->SetLineColor(3);
  g1->SetLineWidth(2);
  g1->Draw("AC");

  c2->cd();
  g2->SetTitle("hoge init contribution");
  g2->GetXaxis()->SetTitle("theta");
  g2->GetYaxis()->SetTitle("dleta E / E");
  g2->GetXaxis()->SetRangeUser(0, 190.);
  g2->SetLineColor(4);
  g2->SetLineWidth(2);
  g2->Draw("AC");

  c3->cd();
  g3->SetTitle("total uncertainty");;
  g3->SetLineColor(1);
  g3->SetLineWidth(2);
  g3->GetYaxis()->SetRangeUser(0, 0.016);
  g3->Draw();
  g0->Draw("same");
  g1->Draw("same");
  g2->Draw("same");

  TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
  leg->AddEntry(g0);
  leg->AddEntry(g1);
  leg->AddEntry(g2);
  leg->AddEntry(g3);
  leg->Draw();
}
