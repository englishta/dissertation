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

/*メイン関数***********************************************************/
void main(void)
{
	//制御周期の設定[単位：Hz　範囲：30.0~]
	const BYTE MainCycle = 60;
	
	Init((BYTE)MainCycle);		//CPUの初期設定
	//I2C_init(void);	//IXBUS初期化
	
	//ループ
	
	while(1){
		int border = 100;
		int right = AdRead(0);
		int left = AdRead(1);
		
		if(right > border && left < border){
			LED(1);		//緑のLED点灯
			Mtr_Run_lv(20000,0,0,0,0,0);//左だけ前進,時計回り
		}else if(right < border && left > border){
			LED(2);//オレンジのLED点灯
			Mtr_Run_lv(0,20000,0,0,0,0);//右だけ前進,半時計回り
		}else if(right < border && left < border){
			LED(3);//両方点灯
			Mtr_Run_lv(20000,20000,0,0,0,0);//前進
		}else{
			LED(3);
			Mtr_Run_lv(20000,20000,0,0,0,0);//前進
		}
	}
}


#ifdef __cplusplus
void abort(void)
{
	
}
#endif
