#ifdef __cplusplus
extern "C" {
void abort(void);
#endif
void main(void);
#ifdef __cplusplus
}
#endif

/*インクルード***********************************************************/
#include<36064s.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "vs-wrc003lv.h"

/*マクロ***********************************************************/

/*グローバル変数***********************************************************/
int Leftdata;
int Rightdata;
//直進エリア用の変数
int leftsum = 0;//左の累積和
int rightsum = 0;//右の累積和
int siro = 30;//真白であることの基準
int black = 60;//真黒であることの基準
int Lon = 1;
int Ron = 1;
//ライントレース用の変数
int Borderr = 50;
int Borderl = 55;
/*メイン関数***********************************************************/
void main(void)
{
	//制御周期の設定[単位：Hz　範囲：30.0~]
	const BYTE MainCycle = 60;
	Init((BYTE)MainCycle);		//CPUの初期設定

	Wait(3000);//取り敢えず3秒間停止
	Mtr_Run_lv(-10000,10000,0,0,0,0);//発車
	while(1){
		Rightdata = AdRead(0);//右データの読み取り
		Leftdata = AdRead(1);//左データの読み込み
		if(Leftdata < siro) Lon = 0;
		if(Rightdata < siro) Ron = 0;
		if(Lon == 1){//真白を経験したのなら
			if(Leftdata > black){//真黒なら
				LED(2);
				leftsum++;
				Lon = 0;
			}
		}
		if(Ron == 1){//真白を経験したのなら
			if(Rightdata > black){//真黒なら
				LED(1);
				rightsum++;
				Ron = 0;
			}
		}
		if(leftsum == 7 && rightsum == 7){
			Mtr_Run_lv(0,0,0,0,0,0);//停止
			break;
		}
	}

	Mtr_Run_lv(-10000,10000,0,0,0,0);//発車
	Wait(2000);//2秒進む
	Mtr_Run_lv(0,0,0,0,0,0);//停止

	//ライントレースのループ開始
	while(1){
		Rightdata = AdRead(0);
		Leftdata = AdRead(1);
		if(Rightdata > Borderr){
			LED(1);		//緑のLED点灯
			Mtr_Run_lv(-10000,-10000,0,0,0,0);
			Wait(100);	//100msec待つ
		}
		
		if(Leftdata>Borderl){
			LED(2);
			Mtr_Run_lv(10000,10000,0,0,0,0);
			Wait(100);		//オレンジのLED点灯
		}
		else{
			Mtr_Run_lv(0,0,0,0,0,0);//停止
			Wait(100);
			LED(0);	
			Mtr_Run_lv(-10000,10000,0,0,0,0);//前進
			Wait(100);
		}
	}
}

#ifdef __cplusplus
void abort(void)
{
	
}
#endif
