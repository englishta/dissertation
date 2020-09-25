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
int black_cnt=0;
int judge = 0;
/*メイン関数***********************************************************/
void main(void)
{
	//制御周期の設定[単位：Hz　範囲：30.0~]
	const BYTE MainCycle = 60;
	
	Init((BYTE)MainCycle);		//CPUの初期設定
	//I2C_init(void);	//IXBUS初期化
	
	//ループ
	
	while(1){
		const int border = 90;
		int right = AdRead(0);
		int left = AdRead(1);
		
		if(right > border){
			Mtr_Run_lv(10000, -10000,0,0,0,0);
			Wait(100);
			LED(1);
		}
		else if(left > border){
			Mtr_Run_lv(-10000, 10000,0,0,0,0);
			Wait(100);
			LED(2);
		}else{
			LED(3);
			Mtr_Run_lv(0, 0,0,0,0,0);
			Wait(100);
			Mtr_Run_lv(-10000, -10000,0,0,0,0);
			Wait(100);
		}
			
	}

}
#ifdef __cplusplus
void abort(void)
{
	
}
#endif