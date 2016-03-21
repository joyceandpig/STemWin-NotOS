#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "ILI93xx.h"
#include "key.h"
#include "malloc.h" 
#include "usmart.h" 
#include "GUI.h"
#include "GUIDEMO.h"
#include "touch.h"
#include "timer.h"
//ALIENTEK Mini STM32开发板范例代码27
//内存管理实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司 
extern void _MY_GetTouchPos(void);
int main(void)
{
	NVIC_Configuration();	 
	delay_init();	    			 //延时函数初始化	  
	uart_init(115200);	 		//串口初始化为9600
	LED_Init();		  				//初始化与LED连接的硬件接口
 	KEY_Init();							//按键初始化 
	TFTLCD_Init();			   	//初始化LCD		 
	tp_dev.init();
//	tp_dev.adjust();
	mem_init();				//初始化内存池

	TIM3_Int_Init(999,71);	//1KHZ 定时器1ms 
	TIM6_Int_Init(999,719);	//10ms中断
	

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);
	WM_SetCreateFlags(WM_CF_MEMDEV);//开启存储设备 加快gui速度
  GUI_Init();
#if 0
	 _MY_GetTouchPos();
#endif
	GUI_SetBkColor(GUI_BLACK);
	GUI_SetColor(GUI_WHITE);
	GUI_DispStringAt("Hello World!", 30, 200);
	GUI_DispStringAt("Hello emWin!", 30, 216);
	GUI_DrawRoundedRect(0,0,200,200,5);
	GUI_DrawRoundedFrame(2,2,180,20,5,2);
	GUI_Delay(3000);
#if 1
	GUIDEMO_Main();
#endif

 while(1)
 {
	tp_dev.scan(0);
	 if(tp_dev.x[0] >0 && tp_dev.x[0]<240 && tp_dev.y[0]>0 && tp_dev.y[0]<320){
		 GUI_DrawPoint(tp_dev.x[0],tp_dev.y[0]);
	 }
	 LED0 = !LED0;
	 GUI_Delay(10);
 }
}











