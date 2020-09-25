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
int cnt = 0;

/*メイン関数***********************************************************/
void main(void)
{
	//制御周期の設定[単位：Hz　範囲：30.0~]
	const BYTE MainCycle = 60;
	
	Init((BYTE)MainCycle);		//CPUの初期設定
	//I2C_init(void);	//IXBUS初期化
	
	//ループ
	while(1){
		int touch = AdRead(2);
		if(touch < 500){
			cnt++;
			if(cnt >= 4){
				Mtr_Run_lv(0,0,0,0,0,0);//停止
				break;
			}
			LED(2);//緑
			Mtr_Run_lv(-20000,-20000,0,0,0,0);
			Wait(2000);
			Mtr_Run_lv(-20000,20000,0,0,0,0);
			Wait(1000);
		}else{
			LED(1);//オレンジ点灯
			Mtr_Run_lv(-20000,-20000,0,0,0,0);//前進
		}
	}
	Mtr_Run_lv(20000,20000,0,0,0,30000);
	Wait(6000);
	Mtr_Run_lv(20000,-20000,0,0,0,-30000);
	Wait(6000);
	Mtr_Run_lv(-20000,-20000,0,0,0,0);
}


#ifdef __cplusplus
void abort(void)
{
	
}
#endif