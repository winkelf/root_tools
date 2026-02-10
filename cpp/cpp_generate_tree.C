#include <TFile.h>
#include <TTree.h>
#include <TRandom3.h>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
    
struct Jet { float pt, eta, phi; };

void cpp_generate_tree() {

  TFile* f = new TFile("mc20_13TeV.root", "RECREATE");
  TTree* t = new TTree("analysis", "Toy jet sample");

  vector<float>* CaloJet_pt  = new vector<float>();
  vector<float>* CaloJet_eta = new vector<float>();
  vector<float>* CaloJet_phi = new vector<float>();

  t->Branch("CaloJet_pt",  &CaloJet_pt);
  t->Branch("CaloJet_eta", &CaloJet_eta);
  t->Branch("CaloJet_phi", &CaloJet_phi);

  TRandom3 rng(42);

  const int nEvents = 100000;

  for (int ievt = 0; ievt < nEvents; ++ievt) {

    CaloJet_pt->clear();
    CaloJet_eta->clear();
    CaloJet_phi->clear();

    int nJets = rng.Integer(3) + 2; // 2–4 jets

    //struct Jet { float pt, eta, phi; };
    vector<Jet> jets;

    for (int j = 0; j < nJets; ++j) {

      // QCD-like pT spectrum
      double u   = rng.Uniform();
      double pT0 = 20.0;
      double n   = 5.0;
      double pt  = pT0 * pow(u, -1.0 / n);
      if (pt > 500) pt = 500;

      double eta = rng.Gaus(0.0, 1.5);
      double phi = rng.Uniform(-M_PI, M_PI);

      jets.push_back({(float)pt, (float)eta, (float)phi});
    }

    // sort by pT
    sort(jets.begin(), jets.end(), [](const Jet& a, const Jet& b) { return a.pt > b.pt; });

    for (const auto& j : jets) {
      CaloJet_pt ->push_back(j.pt);
      CaloJet_eta->push_back(j.eta);
      CaloJet_phi->push_back(j.phi);
    }

    t->Fill();
  }

  t->Write();
  f->Close();
}

