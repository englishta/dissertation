#UKgas.cvs�̃t�@�C����ǂݍ��݁A�O���t���o�͂���v���O����
#���s���@�@python.exe (name).py


import pandas as pd
UKgas = pd.read_csv("UKgas.csv") # �f�[�^�̓Ǎ���
import matplotlib.pyplot as plt
#%matplotlib inline # �R���\�[����ʓ����ɐ}��\��
plt.plot(UKgas.x)
plt.show()