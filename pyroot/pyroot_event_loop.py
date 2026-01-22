##############################################
#  Script for basic invariant mass plotting. #
##############################################

import ROOT
import numpy as np

# Input file and tree names
fName    = 'toymc_jets.root' 
treeName = 'analysis' 

# Inputs
inputFile = ROOT.TFile.Open(fName)
tree      = inputFile.Get(treeName)

# Histogram booking
hist  = ROOT.TH1D('m_{jj}','Dijet invariant mass', 200, 0, 400)

# Main loop (put proper branch names)
for entry in tree:
    if len(tree.CaloJet_pt)<2: continue
    pT1  = tree.CaloJet_pt[0]
    pT2  = tree.CaloJet_pt[1]
    eta1 = tree.CaloJet_eta[0]
    eta2 = tree.CaloJet_eta[1]
    phi1 = tree.CaloJet_phi[0] 
    phi2 = tree.CaloJet_phi[1]

    # Massless case
    m2   = 2*pT1*pT2*( np.cosh(eta1-eta2) - np.cos(phi1-phi2)  )

    if np.sqrt(m2)==0 : continue

    hist.Fill(np.sqrt(m2))

# Plotting and printing
c = ROOT.TCanvas()
c.cd()

ROOT.gPad.SetGrid()
ROOT.gStyle.SetOptStat(0)

hist.Scale(1/hist.Integral())
hist.SetLineColor(ROOT.kBlue)
hist.GetXaxis().SetTitle(hist.GetName()+" [GeV]")
hist.Draw('HIST SAME')

l = ROOT.TLegend(0.8,0.8,0.6,0.6)
l.AddEntry(hist,'AntiKt4 jets')
l.Draw('SAME')

c.Print("mjj.pdf")


