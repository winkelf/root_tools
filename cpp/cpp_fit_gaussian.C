#include <TCanvas.h>
#include <TH1F.h>
#include <TF1.h>
#include <TMath.h>
#include <iostream>

double gaussFunc(double* x, double* par) {
  return TMath::Gaus(x[0], par[0], par[1], true); // mean, sigma, normalized
}

void cpp_fit_gaussian() {
  TCanvas* c1 = new TCanvas("c1", "Gaussian Fit", 800, 600);

  TH1F* h = new TH1F("h", "Gaussian Distribution", 50, -10, 10);

  // Fill histogram with Gaussian-like data
  for (int i = 0; i < 1000; ++i) {
    h->Fill(gRandom->Gaus(0, 2));
  }

  // Format histogram
  h->SetStats(0);
  h->GetXaxis()->SetTitle("x");
  h->GetYaxis()->SetTitle("Probability density");
  h->Scale(1.0 / h->Integral("width"));
  h->Draw("HIST");

  // Define Gaussian fit function
  TF1* fitFunc = new TF1("fitFunc", gaussFunc, -10, 10, 2);
  fitFunc->SetParameters(0, 2); // initial guess: mean, sigma
  fitFunc->SetLineColor(kRed);
  fitFunc->SetLineWidth(2);

  // Perform the fit
  h->Fit(fitFunc, "R");
  fitFunc->Draw("SAME");

  std::cout << "Fitted mean:  " << fitFunc->GetParameter(0) << std::endl;
  std::cout << "Fitted sigma: " << fitFunc->GetParameter(1) << std::endl;
}

