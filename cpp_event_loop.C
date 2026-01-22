#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TMath.h>
#include <vector>
#include <cmath>

using namespace std;

void cpp_event_loop() {

  TFile* f = TFile::Open("mc20_13TeV.root");
  TTree* t = (TTree*)f->Get("analysis");

  vector<float>* CaloJet_pt  = nullptr;
  vector<float>* CaloJet_eta = nullptr;
  vector<float>* CaloJet_phi = nullptr;

  t->SetBranchAddress("CaloJet_pt",  &CaloJet_pt);
  t->SetBranchAddress("CaloJet_eta", &CaloJet_eta);
  t->SetBranchAddress("CaloJet_phi", &CaloJet_phi);

  TH1D* h = new TH1D("m_jj", "Dijet invariant mass; m_{jj} [GeV]; Entries",
                     200, 0, 400);

  const Long64_t nEntries = t->GetEntries();

  for (Long64_t i = 0; i < nEntries; ++i) {
    t->GetEntry(i);

    if (CaloJet_pt->size() < 2) continue;

    double pT1  = CaloJet_pt ->at(0);
    double pT2  = CaloJet_pt ->at(1);
    double eta1 = CaloJet_eta->at(0);
    double eta2 = CaloJet_eta->at(1);
    double phi1 = CaloJet_phi->at(0);
    double phi2 = CaloJet_phi->at(1);

    double m2 = 2.0 * pT1 * pT2 *  (cosh(eta1 - eta2) - cos(phi1 - phi2));

    if (m2 <= 0) continue;

    h->Fill(sqrt(m2));
  }

  TCanvas* c = new TCanvas("c", "Dijet mass", 800, 600);
  h->Draw("HIST");
}

