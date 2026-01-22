#include <TCanvas.h>
#include <TH1F.h>
#include <TF1.h>
#include <TMath.h>
#include <iostream>

double binomialFunc(double* x, double* par) {
  int k = (int)x[0];
  int n = (int)par[0];
  double p = par[1];
  return TMath::Binomial(n, k) * TMath::Power(p, k) * TMath::Power(1 - p, n - k);
}

void cpp_fit_binomial() {
  TCanvas* c1 = new TCanvas("c1", "Binomial Fit", 800, 600);

  const int nTrials = 20;

  TH1F* h = new TH1F("h", "Binomial Distribution", nTrials + 1, -0.5, nTrials + 0.5);

  // Fill histogram with Binomial-like data
  for (int i = 0; i < 1000; ++i) {
    h->Fill(gRandom->Binomial(nTrials, 0.3));
  }

  // Format histogram
  h->SetStats(0);
  h->GetXaxis()->SetTitle("k");
  h->GetYaxis()->SetTitle("Probability");
  h->Scale(1.0 / h->Integral("width"));
  h->Draw("HIST");

  // Define Binomial fit function
  TF1* fitFunc = new TF1("fitFunc", binomialFunc, 0, nTrials, 2);
  fitFunc->SetParameters(nTrials, 0.5); // n fixed, initial guess for p
  fitFunc->FixParameter(0, nTrials);    // fix n
  fitFunc->SetLineColor(kRed);
  fitFunc->SetLineWidth(2);

  // Perform the fit
  h->Fit(fitFunc, "R");
  fitFunc->Draw("SAME");

  std::cout << "Fitted p: " << fitFunc->GetParameter(1) << std::endl;
}

