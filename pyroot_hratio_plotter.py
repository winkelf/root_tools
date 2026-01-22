import ROOT

ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetPadTickX(1)
ROOT.gStyle.SetPadTickY(1)

# Input file
f = ROOT.TFile.Open("two_distros.root")

# Get histograms
h1 = f.Get("h1")
h2 = f.Get("h2")

# Compute ratio (tag / antitag)
h_diff = h1.Clone("h_diff")
h_diff.Divide(h2)

# --- Canvas and pads setup ---
c = ROOT.TCanvas("c", "", 600, 600)

pad1 = ROOT.TPad("pad1", "", 0, 0.3, 1, 1)
pad1.SetLogy()
pad1.SetBottomMargin(0.01)
pad1.Draw()
pad1.cd()

# --- Upper pad: normalized histograms ---
h1.SetLineColor(ROOT.kRed)
h1.SetLineWidth(3)
h2.SetLineColor(ROOT.kBlue)
h2.SetLineWidth(3)
h2.SetLineStyle(ROOT.kDashed)

h1.GetYaxis().SetTitle("Number of entries")
h1.GetYaxis().SetTitleOffset(1.4)
h1.Draw("HIST")
h2.Draw("HIST SAME")

offsetx = 0.1

atlasText = ROOT.TLatex()
atlasText.SetNDC(True)
atlasText.SetTextFont(72)
atlasText.SetTextSize(0.05)
atlasText.DrawLatex(offsetx+0.18, 0.77, "ATLAS")

atlasText2 = ROOT.TLatex()
atlasText2.SetNDC(True)
atlasText2.SetTextFont(42)
atlasText2.SetTextSize(0.05)
atlasText2.DrawLatex(offsetx+0.29, 0.77, " Simulation")

atlasText3 = ROOT.TLatex()
atlasText3.SetNDC(True)
atlasText3.SetTextFont(42)
atlasText3.SetTextSize(0.04)
atlasText3.DrawLatex(offsetx+0.18, 0.71, "#sqrt{s} = 13 TeV")

# --- Legend ---
leg = ROOT.TLegend(0.60, 0.70, 0.88, 0.86)
leg.SetBorderSize(0)
leg.SetFillStyle(0)
leg.SetTextFont(42)
leg.SetTextSize(0.035)
leg.AddEntry(h1, "hist 1", "l")
leg.AddEntry(h2, "hist 2", "l")
leg.Draw()

# --- Bottom pad: ratio ---
c.cd()
pad2 = ROOT.TPad("pad2", "", 0, 0, 1, 0.3)
pad2.SetTopMargin(0.02)
pad2.SetBottomMargin(0.3)
pad2.Draw()
pad2.cd()

h_diff.GetYaxis().SetRangeUser(0, 2)
h_diff.SetMarkerStyle(20)
h_diff.SetLineWidth(2)
h_diff.SetLineColor(ROOT.kBlack)
h_diff.SetTitle("")
h_diff.GetYaxis().SetTitle("h1 / h2")
h_diff.GetXaxis().SetTitle("Jet pT [GeV]")

# Adjust axis label sizes
h_diff.GetYaxis().SetTitleOffset(0.4)
h_diff.GetYaxis().SetTitleSize(0.1)
h_diff.GetYaxis().SetLabelSize(0.08)
h_diff.GetXaxis().SetTitleSize(0.12)
h_diff.GetXaxis().SetLabelSize(0.10)

h_diff.Draw("E")

# Reference line at ratio = 1
line = ROOT.TLine(h_diff.GetXaxis().GetXmin(), 1, h_diff.GetXaxis().GetXmax(), 1)
line.SetLineColor(ROOT.kGray + 2)
line.SetLineStyle(2)
line.Draw("same")

# Save plot
c.SaveAs("QCD_ratio.pdf")

