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
		const int border = 500;
		int right = AdRead(0);
		int left = AdRead(1);
		int first_touch = AdRead(2);
		
		if(first_touch < 500){//壁に初めてあたる、方向転換
			Mtr_Run_lv(20000,20000,0,0,0,0);
			Wait(2000);
			Mtr_Run_lv(20000,-20000,0,0,0,0);
			Wait(1000);
			Mtr_Run_lv(-20000,-20000,0,0,0,0);
			cnt++;
			break;//ループを抜ける！！
		}
		
		if(right > border && left < border){
			LED(1);		//緑のLED点灯
			Mtr_Run_lv(0,0,0,0,0,0);
			Wait(500);
			Mtr_Run_lv(10000, -10000,0,0,0,0);
			Wait(700);
			Mtr_Run_lv(-10000, -10000,0,0,0,0);
			Wait(700);
			judge = 0;
		}else if(right < border && left > border){
			LED(2);//オレンジのLED点灯
			Mtr_Run_lv(0,0,0,0,0,0);
			Wait(500);
			Mtr_Run_lv(-10000, 10000,0,0,0,0);
			Wait(700);
			Mtr_Run_lv(-10000, -10000,0,0,0,0);
			Wait(700);
			judge = 0;
		}else if(right < border && left < border){
			LED(3);//白白
			judge = 0;
			Mtr_Run_lv(-10000,-10000,0,0,0,0);//前進
		}else{
			LED(3);//黒黒
			if(judge == 0){
				judge=1;
				black_cnt++;
				/*if(black_cnt == 5){//白→黒を5回やると、発動。
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
					Mtr_Run_lv(10000,-10000,0,0,0,0);//半時計回りに90度回転する
					Wait(5000);
					Mtr_Run_lv(-10000,-10000,0,0,0,0);
				}*/
			}
			Mtr_Run_lv(-10000,-10000,0,0,0,0);//前進
		}
	}
	
	//壁エリアから障害物へのプログラム
	while(1){
		int touch = AdRead(2);
		if(touch < 500){
			cnt++;
			if(cnt >= 4){
				Mtr_Run_lv(0,0,0,0,0,0);//停止
				break;
			}
			LED(2);//緑
			Mtr_Run_lv(20000,20000,0,0,0,0);
			Wait(2000);
			Mtr_Run_lv(20000,-20000,0,0,0,0);
			Wait(1000);
		}else{
			LED(1);//オレンジ点灯
			Mtr_Run_lv(20000,20000,0,0,0,0);//前進
		}
	}//障害物エリア
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