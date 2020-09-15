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
#include "vs-wrc003.h"

/*マクロ***********************************************************/

/*グローバル変数***********************************************************/

/*メイン関数***********************************************************/
void main(void)
{
	//制御周期の設定[単位：Hz　範囲：30.0~]
	const BYTE MainCycle = 60;
	
	Init((BYTE)MainCycle);		//CPUの初期設定
	InitSci3(CBR_115200,even,1);	//シリアル通信の設定
	BuzzerSet(0x80,0x80);		//ブザーの設定
	
	//無限ループ
	while(1){
		LED(1);		//緑のLED点灯
		Wait(1000);	//1000msec待つ
		LED(2);		//オレンジのLED点灯
		Wait(1000);	//1000msec待つ
	}
}


#ifdef __cplusplus
void abort(void)
{
	
}
#endif
