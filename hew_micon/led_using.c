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
#include "vs-wrc003.h"

/*�}�N��***********************************************************/

/*�O���[�o���ϐ�***********************************************************/

/*���C���֐�***********************************************************/
void main(void)
{
	//��������̐ݒ�[�P�ʁFHz�@�͈́F30.0~]
	const BYTE MainCycle = 60;
	
	Init((BYTE)MainCycle);		//CPU�̏����ݒ�
	InitSci3(CBR_115200,even,1);	//�V���A���ʐM�̐ݒ�
	BuzzerSet(0x80,0x80);		//�u�U�[�̐ݒ�
	
	//�������[�v
	while(1){
		LED(1);		//�΂�LED�_��
		Wait(1000);	//1000msec�҂�
		LED(2);		//�I�����W��LED�_��
		Wait(1000);	//1000msec�҂�
	}
}


#ifdef __cplusplus
void abort(void)
{
	
}
#endif
