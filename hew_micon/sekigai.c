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
		int border = 50;
		int right = AdRead(0);
		
		if(right > border){
			LED(1);		//�΂�LED�_��
		}else{
			LED(2);//�I�����W��LED�_��
		}
	}
}


#ifdef __cplusplus
void abort(void)
{
	
}
#endif
