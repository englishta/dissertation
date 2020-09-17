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

/*���C���֐�***********************************************************/
void main(void)
{
	//��������̐ݒ�[�P�ʁFHz�@�͈́F30.0~]
	const BYTE MainCycle = 60;
	
	Init((BYTE)MainCycle);		//CPU�̏����ݒ�
	//I2C_init(void);	//IXBUS������
	
	//���[�v
	
	while(1){
		int border = 100;
		int right = AdRead(0);
		int left = AdRead(1);
		
		if(right > border && left < border){
			LED(1);		//�΂�LED�_��
			Mtr_Run_lv(20000,0,0,0,0,0);//�������O�i,���v���
		}else if(right < border && left > border){
			LED(2);//�I�����W��LED�_��
			Mtr_Run_lv(0,20000,0,0,0,0);//�E�����O�i,�����v���
		}else if(right < border && left < border){
			LED(3);//�����_��
			Mtr_Run_lv(20000,20000,0,0,0,0);//�O�i
		}else{
			LED(3);
			Mtr_Run_lv(20000,20000,0,0,0,0);//�O�i
		}
	}
}


#ifdef __cplusplus
void abort(void)
{
	
}
#endif
