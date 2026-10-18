/*
 * ASRPRO 语音关灯 —— 单舵机 · 机械按压两个翘板开关
 *
 * 硬件：ASRPRO + MG90S
 * 接线：舵机 红→5V，棕→GND，橙→IO13；5V/GND 并 1000µF
 *
 * 命令：
 *   唤醒词“牢大” → 命令词“关灯”
 *   舵机 90° → 70°（左）→ 110°（右）→ 90°
 *
 * 说明：
 *   - 下面 //{...} 行由天问Block生成，请勿手改
 *   - case 1 对应“关灯”命令的 ID；如果命令词重新排列，请同步修改
 */

#include "asr.h"
extern "C"{ void * __dso_handle = 0 ;}
#include "setup.h"
#include "myLib/asr_servo.h"

uint32_t snid;
Servo servo_13;
void ASR_CODE();

//{speak:小蝶-清新女声,vol:10,speed:10,platform:haohaodada}

/* 舵机参数：按实际装配调整 */
const int REST_ANGLE        = 90;    // 回中/静止
const int LEFT_PRESS_ANGLE  = 70;    // 左开关按压角
const int RIGHT_PRESS_ANGLE = 110;   // 右开关按压角
const int PRESS_MS          = 1000;  // 每个位置保持时间(ms)

void ASR_CODE(){
  set_state_enter_wakeup(10000);
  switch (snid) {
   case 1:                           // 关灯（命令词 ID 1）
    servo_13.write(LEFT_PRESS_ANGLE);
    delay(PRESS_MS);
    servo_13.write(RIGHT_PRESS_ANGLE);
    delay(PRESS_MS);
    servo_13.write(REST_ANGLE);
    exit_wakeup_deal(0);
    break;
  }
}

void hardware_init(){
  vol_set(7);                        // 音频/系统音量，0~7
  vTaskDelete(NULL);
}

void setup()
{
  // 以下 ID 由天问Block生成，ID 以实际生成为准
  //{ID:0,keyword:"唤醒词",ASR:"牢大",ASRTO:"man"}
  //{ID:1,keyword:"命令词",ASR:"关灯",ASRTO:"笑"}
  //{ID:3,keyword:"命令词",ASR:"想你了",ASRTO:"唱歌"}
  //{ID:4,keyword:"命令词",ASR:"咕咕嘎嘎",ASRTO:"咕咕嘎嘎"}
  servo_13.attach(13);
  servo_13.write(REST_ANGLE);        // attach 后先回中
}
