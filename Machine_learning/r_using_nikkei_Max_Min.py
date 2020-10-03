#data_nikkei.cvsのデータを読み取り、最大値、最小値、平均値を出力するプログラム
#ちなみに、R言語と連携している、正直Pythonだけでも出来る
#実行方法
#python3 (name).py

import pandas as pd
import pyper
r = pyper.R()
nikkei = pd.read_csv("data_nikkei.csv", header=0)
x = list(nikkei["end"])
r.assign('data', x)
#r.assign("data", x)にするとエラー''でなければならない
r("heikin <- mean(data)")
r("saisho <- min(data)")
r("saidai <- max(data)")
Heikin = r.get("heikin")
Saisho = r.get("saisho")
Saidai = r.get("saidai")
print("Heikin = ", Heikin)
print("Saisho = ", Saisho)
print("Saidai = ", Saidai)