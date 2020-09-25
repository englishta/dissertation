#ifdef __cplusplus
extern "C" {
void abort(void);
#endif
void main(void);
#ifdef __cplusplus
}
#endif

/*�C���N���[�h***********************************************************/
#include<36064s.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "vs-wrc003lv.h"

/*�}�N��***********************************************************/

/*�O���[�o���ϐ�***********************************************************/
int cnt = 0;
int black_cnt=0;
int judge = 0;
/*���C���֐�***********************************************************/
void main(void)
{
	//��������̐ݒ�[�P�ʁFHz�@�͈́F30.0~]
	const BYTE MainCycle = 60;
	
	Init((BYTE)MainCycle);		//CPU�̏����ݒ�
	//I2C_init(void);	//IXBUS������
	
	//���[�v
	
	while(1){
		const int border = 500;
		int right = AdRead(0);
		int left = AdRead(1);
		int first_touch = AdRead(2);
		
		if(first_touch < 500){//�ǂɏ��߂Ă�����A�����]��
			Mtr_Run_lv(20000,20000,0,0,0,0);
			Wait(2000);
			Mtr_Run_lv(20000,-20000,0,0,0,0);
			Wait(1000);
			Mtr_Run_lv(-20000,-20000,0,0,0,0);
			cnt++;
			break;//���[�v�𔲂���I�I
		}
		
		if(right > border && left < border){
			LED(1);		//�΂�LED�_��
			Mtr_Run_lv(0,0,0,0,0,0);
			Wait(500);
			Mtr_Run_lv(10000, -10000,0,0,0,0);
			Wait(700);
			Mtr_Run_lv(-10000, -10000,0,0,0,0);
			Wait(700);
			judge = 0;
		}else if(right < border && left > border){
			LED(2);//�I�����W��LED�_��
			Mtr_Run_lv(0,0,0,0,0,0);
			Wait(500);
			Mtr_Run_lv(-10000, 10000,0,0,0,0);
			Wait(700);
			Mtr_Run_lv(-10000, -10000,0,0,0,0);
			Wait(700);
			judge = 0;
		}else if(right < border && left < border){
			LED(3);//����
			judge = 0;
			Mtr_Run_lv(-10000,-10000,0,0,0,0);//�O�i
		}else{
			LED(3);//����
			if(judge == 0){
				judge=1;
				black_cnt++;
				/*if(black_cnt == 5){//��������5����ƁA�����B
					int five = 0;
					BuzzerSet(100, 70);
					BuzzerStart(100, 70);
					while(1){
						five++;
						if(five > 15) break;
						Mtr_Run_lv(0,0,0,0,0,0);
						LED(1);
						Wait(100);
						LED(2);
						Wait(100);
					}
					BuzzerStop();
					Mtr_Run_lv(10000,-10000,0,0,0,0);//�����v����90�x��]����
					Wait(5000);
					Mtr_Run_lv(-10000,-10000,0,0,0,0);
				}*/
			}
			Mtr_Run_lv(-10000,-10000,0,0,0,0);//�O�i
		}
	}
	
	//�ǃG���A�����Q���ւ̃v���O����
	while(1){
		int touch = AdRead(2);
		if(touch < 500){
			cnt++;
			if(cnt >= 4){
				Mtr_Run_lv(0,0,0,0,0,0);//��~
				break;
			}
			LED(2);//��
			Mtr_Run_lv(20000,20000,0,0,0,0);
			Wait(2000);
			Mtr_Run_lv(20000,-20000,0,0,0,0);
			Wait(1000);
		}else{
			LED(1);//�I�����W�_��
			Mtr_Run_lv(20000,20000,0,0,0,0);//�O�i
		}
	}//��Q���G���A
	Mtr_Run_lv(-20000,-20000,0,0,0,30000);
	Wait(6000);
	Mtr_Run_lv(-20000,-20000,0,0,0,-30000);
	Wait(6000);
	Mtr_Run_lv(-20000,-20000,0,0,0,0);
}


#ifdef __cplusplus
void abort(void)
{
	
}
#endif