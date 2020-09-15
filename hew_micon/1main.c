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
int Leftdata;
int Rightdata;
//���i�G���A�p�̕ϐ�
int leftsum = 0;//���̗ݐϘa
int rightsum = 0;//�E�̗ݐϘa
int siro = 30;//�^���ł��邱�Ƃ̊
int black = 60;//�^���ł��邱�Ƃ̊
int Lon = 1;
int Ron = 1;
//���C���g���[�X�p�̕ϐ�
int Borderr = 50;
int Borderl = 55;
/*���C���֐�***********************************************************/
void main(void)
{
	//��������̐ݒ�[�P�ʁFHz�@�͈́F30.0~]
	const BYTE MainCycle = 60;
	Init((BYTE)MainCycle);		//CPU�̏����ݒ�

	Wait(3000);//��芸����3�b�Ԓ�~
	Mtr_Run_lv(-10000,10000,0,0,0,0);//����
	while(1){
		Rightdata = AdRead(0);//�E�f�[�^�̓ǂݎ��
		Leftdata = AdRead(1);//���f�[�^�̓ǂݍ���
		if(Leftdata < siro) Lon = 0;
		if(Rightdata < siro) Ron = 0;
		if(Lon == 1){//�^�����o�������̂Ȃ�
			if(Leftdata > black){//�^���Ȃ�
				LED(2);
				leftsum++;
				Lon = 0;
			}
		}
		if(Ron == 1){//�^�����o�������̂Ȃ�
			if(Rightdata > black){//�^���Ȃ�
				LED(1);
				rightsum++;
				Ron = 0;
			}
		}
		if(leftsum == 7 && rightsum == 7){
			Mtr_Run_lv(0,0,0,0,0,0);//��~
			break;
		}
	}

	Mtr_Run_lv(-10000,10000,0,0,0,0);//����
	Wait(2000);//2�b�i��
	Mtr_Run_lv(0,0,0,0,0,0);//��~

	//���C���g���[�X�̃��[�v�J�n
	while(1){
		Rightdata = AdRead(0);
		Leftdata = AdRead(1);
		if(Rightdata > Borderr){
			LED(1);		//�΂�LED�_��
			Mtr_Run_lv(-10000,-10000,0,0,0,0);
			Wait(100);	//100msec�҂�
		}
		
		if(Leftdata>Borderl){
			LED(2);
			Mtr_Run_lv(10000,10000,0,0,0,0);
			Wait(100);		//�I�����W��LED�_��
		}
		else{
			Mtr_Run_lv(0,0,0,0,0,0);//��~
			Wait(100);
			LED(0);	
			Mtr_Run_lv(-10000,10000,0,0,0,0);//�O�i
			Wait(100);
		}
	}
}

#ifdef __cplusplus
void abort(void)
{
	
}
#endif
