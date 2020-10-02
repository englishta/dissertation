import pandas as pd
import pyper
r = pyper.R()
nikkei = pd.read_csv("data_nikkei.csv", header=0)
x = list(nikkei["end"])
r.assign('data', x)
#r.assign("data", x)‚É‚·‚é‚ÆƒGƒ‰[''‚Å‚È‚¯‚ê‚Î‚È‚ç‚È‚¢
r("heikin <- mean(data)")
r("saisho <- min(data)")
r("saidai <- max(data)")
Heikin = r.get("heikin")
Saisho = r.get("saisho")
Saidai = r.get("saidai")
print("Heikin = ", Heikin)
print("Saisho = ", Saisho)
print("Saidai = ", Saidai)
