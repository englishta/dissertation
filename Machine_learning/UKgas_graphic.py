#UKgas.cvsのファイルを読み込み、グラフを出力するプログラム
#実行方法　python.exe (name).py


import pandas as pd
UKgas = pd.read_csv("UKgas.csv") # データの読込み
import matplotlib.pyplot as plt
#%matplotlib inline # コンソール画面内部に図を表示
plt.plot(UKgas.x)
plt.show()