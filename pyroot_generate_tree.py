import ROOT
import numpy as np
from array import array

# Output file
outFile = ROOT.TFile("toymc_jets.root", "RECREATE")
tree    = ROOT.TTree("analysis", "Toy jet sample")

# Jet branches (std::vector<float>)
CaloJet_pt  = ROOT.std.vector('float')()
CaloJet_eta = ROOT.std.vector('float')()
CaloJet_phi = ROOT.std.vector('float')()

tree.Branch("CaloJet_pt",  CaloJet_pt)
tree.Branch("CaloJet_eta", CaloJet_eta)
tree.Branch("CaloJet_phi", CaloJet_phi)

# Random generator
rng = ROOT.TRandom3(42)

# Number of events
nEvents = 100000

for _ in range(nEvents):

    # Clear vectors
    CaloJet_pt.clear()
    CaloJet_eta.clear()
    CaloJet_phi.clear()

    # Number of jets per event (2–4)
    nJets = rng.Integer(3) + 2

    jets = []

    for j in range(nJets):

        # --- pT: falling spectrum (QCD-like) ---
        # Inverse power-law: pT ~ (pT0 / u)^(1/n)
        u   = rng.Uniform()
        pT0 = 20.0     # GeV (turn-on)
        n   = 5.0
        pT  = pT0 * (u ** (-1.0 / n))

        # Cap very rare huge pT values
        if pT > 500:
            pT = 500

        # --- eta: roughly central ---
        eta = rng.Gaus(0.0, 1.5)

        # --- phi: uniform ---
        phi = rng.Uniform(-np.pi, np.pi)

        jets.append((pT, eta, phi))

    # Sort jets by descending pT (important!)
    jets.sort(key=lambda x: x[0], reverse=True)

    # Fill branches
    for pT, eta, phi in jets:
        CaloJet_pt.push_back(pT)
        CaloJet_eta.push_back(eta)
        CaloJet_phi.push_back(phi)

    tree.Fill()

# Write file
tree.Write()
outFile.Close()

