
from math import sin
from array import array

c1 = ROOT.TCanvas("c1","The distribution", 1000, 10, 1000, 700); 
c2 = ROOT.TCanvas("c2","The histogram", 10, 10, 1000, 700);

c1.cd()
h = ROOT.TH1F("myHist", "myTitle", 64, -4, 4)
h.FillRandom("gaus")
h.Draw()

c2.cd()
n= 20
x, y = array( 'd' ), array( 'd' )
for i in range( n ):
   x.append( 0.1*i )
   y.append( 10*sin( x[i]+0.2 ) )
gr = ROOT.TGraph( n, x, y )
gr.Draw( 'ACP' )