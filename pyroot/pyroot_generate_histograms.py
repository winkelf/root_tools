import ROOT
import random

# Creo un rootfile que se llama test.root
f_out = ROOT.TFile("two_distros.root", "RECREATE")

# Crear histos
nbins = 20
xmin  = 0
xmax  = 1000
h1 = ROOT.TH1F("h1", "ExpDecay 1", nbins, xmin, xmax)
h2 = ROOT.TH1F("h2", "ExpDecay 2", nbins, xmin, xmax)

# Llenarlos con distrib exp (parecida a QCD)
for i in range(100000):
    x1 = random.expovariate(1/200.0) 
    x2 = random.expovariate(1/280.0) 

    # Lleno los histogramas, root llena una entrada por iteracion del "for"
    if x1 < xmax: h1.Fill(x1)
    if x2 < xmax: h2.Fill(x2)

# guardo el archivo
f_out.Write()
f_out.Close()

