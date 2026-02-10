// Codigo para hacer replicas de bootstrap con numero de Poisson

#include <iostream>
#include <vector>
#include <TRandom.h>
#include <TFile.h>
#include <TTree.h>

using namespace std;

void BootstrapAndSave(const char* inputFilename, const char* outputFilename) {
  // Open the input file and retrieve the tree
  TFile *inputFile = TFile::Open(inputFilename, "READ");
  TTree *inputTree = (TTree*)inputFile->Get("treeName");

  // Prepare the output file and tree
  TFile *outputFile = TFile::Open(outputFilename, "RECREATE");
  TTree *outputTree = inputTree->CloneTree(0);  // Create an empty clone of the input tree

  // Define the branches
  unsigned int       RunNumber;
  unsigned long long EventNumber;
  float              mcEventWeight;
  vector<float> *RecoJetEta  = nullptr;
  vector<float> *RecoJetPhi  = nullptr;
  vector<float> *RecoJetPt   = nullptr;
  vector<float> *RecoJetE    = nullptr;
  vector<float> *TruthJetEta = nullptr;
  vector<float> *TruthJetPhi = nullptr;
  vector<float> *TruthJetPt  = nullptr;
  vector<float> *TruthJetE   = nullptr;

  // Set branch addresses
  inputTree->SetBranchAddress("RunNumber",     &RunNumber);
  inputTree->SetBranchAddress("EventNumber",   &EventNumber);
  inputTree->SetBranchAddress("mcEventWeight", &mcEventWeight);
  inputTree->SetBranchAddress("RecoJetEta",    &RecoJetEta);
  inputTree->SetBranchAddress("RecoJetPhi",    &RecoJetPhi);
  inputTree->SetBranchAddress("RecoJetPt",     &RecoJetPt);
  inputTree->SetBranchAddress("RecoJetE",      &RecoJetE);
  inputTree->SetBranchAddress("TruthJetEta",   &TruthJetEta);
  inputTree->SetBranchAddress("TruthJetPhi",   &TruthJetPhi);
  inputTree->SetBranchAddress("TruthJetPt",    &TruthJetPt);
  inputTree->SetBranchAddress("TruthJetE",     &TruthJetE);

  // Create a random number generator
  TRandom randGen;

  // Loop over the events in the input tree
  Long64_t nEntries = inputTree->GetEntries();
  for (Long64_t i = 0; i < nEntries; ++i) {
    inputTree->GetEntry(i);

    // Generate a Poisson random number with mu=1
    int nCopies = randGen.Poisson(1);

    // Duplicate the event nCopies times
    for (int j = 0; j < nCopies; ++j) {
      outputTree->Fill();
    }
  }

  // Write the output tree to the file
  outputTree->Write();
  outputFile->Close();
  inputFile ->Close();

  std::cout << "Bootstrapping complete. New tree saved in " << outputFilename << std::endl;
}

int cpp_bootstrap() {
  const char* inputFilename  = "input.root";
  const char* outputFilename = "output_bootstrapped.root";
  BootstrapAndSave(inputFilename, outputFilename);
  return 0;
}
