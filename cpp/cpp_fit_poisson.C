#include <TCanvas.h>
#include <TH1F.h>
#include <TF1.h>
#include <TMath.h>
#include <iostream>

double poissonFunc(double* x, double* par) { return TMath::Poisson(x[0], par[0]); }

void cpp_fit_poisson() {
  TCanvas* c1 = new TCanvas("c1", "Poisson Fit", 800, 600);
  
  TH1F* h3 = new TH1F("h3", "Poisson Distribution", 20, 0, 20);
  
  // Fill histogram with some Poisson-like data
  for (int i = 0; i < 1000; ++i) { h3->Fill(gRandom->Poisson(5)); }
  
  // Format histogram
  h3->SetStats(0);
  h3->GetXaxis()->SetTitle("k");
  h3->GetYaxis()->SetTitle("Number of entries");
  h3->Scale(1/h3->Integral("width"));
  h3->Draw("HIST");
  
  // Define Poisson fit function
  TF1* fitFunc = new TF1("fitFunc", poissonFunc, 0, 20, 1);
  fitFunc->SetParameter(0, 5);  // Initial guess for lambda
  fitFunc->SetLineColor(kRed); // Set color for visibility
  fitFunc->SetLineWidth(2);
  
  // Perform the fit
  h3->Fit(fitFunc, "R");
  fitFunc->Draw("SAME"); // Draw the fit on top of the histogram
  
  // Retrieve fitted parameter (mean)
  double mu_fitted = fitFunc->GetParameter(0);
  std::cout << "Fitted mu: " << mu_fitted << std::endl;
}

