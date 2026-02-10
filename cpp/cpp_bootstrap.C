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
  TTree *inputTree = (TTree*)inputFile->Get("analysis");

  // Prepare the output file and tree
  TFile *outputFile = TFile::Open(outputFilename, "RECREATE");
  TTree *outputTree = inputTree->CloneTree(0);  // Create an empty clone of the input tree

  // Define the branches
  vector<float> *RecoJetEta  = nullptr;
  vector<float> *RecoJetPhi  = nullptr;
  vector<float> *RecoJetPt   = nullptr;

  // Set branch addresses
  inputTree->SetBranchAddress("CaloJet_pt" ,    &RecoJetEta);
  inputTree->SetBranchAddress("CaloJet_eta",    &RecoJetPhi);
  inputTree->SetBranchAddress("CaloJet_phi",    &RecoJetPt);

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
  const char* inputFilename  = "mc20_13TeV.root";
  const char* outputFilename = "output_bootstrapped.root";
  BootstrapAndSave(inputFilename, outputFilename);
  return 0;
}
