#data_nikkei.cvs�̃f�[�^��ǂݎ��A�ő�l�A�ŏ��l�A���ϒl���o�͂���v���O����
#���Ȃ݂ɁAR����ƘA�g���Ă���A����Python�����ł��o����
#���s���@
#python3 (name).py

import pandas as pd
import pyper
r = pyper.R()
nikkei = pd.read_csv("data_nikkei.csv", header=0)
x = list(nikkei["end"])
r.assign('data', x)
#r.assign("data", x)�ɂ���ƃG���[''�łȂ���΂Ȃ�Ȃ�
r("heikin <- mean(data)")
r("saisho <- min(data)")
r("saidai <- max(data)")
Heikin = r.get("heikin")
Saisho = r.get("saisho")
Saidai = r.get("saidai")
print("Heikin = ", Heikin)
print("Saisho = ", Saisho)
print("Saidai = ", Saidai)