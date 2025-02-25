#include "freertos_demo.h"
// freertos相关头文件
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#include "LED.h"
#include "Key.h"

// 启动任务的配置
#define START_TASK_STACK 128
#define START_TASK_PRIORITY 1
TaskHandle_t start_task_handler;
void start_task(void *pvParameters);

// 任务1的配置
#define TASK1_STACK 128
#define TASK1_PRIORITY 2
TaskHandle_t task1_handler;
void task1(void *pvParameters);

// 软件定时器的超时回调函数
void timer1_callback(TimerHandle_t xTimer); // 单次
void timer2_callback(TimerHandle_t xTimer); // 周期

// 软件定时器的句柄
TimerHandle_t timer1_handler;
TimerHandle_t timer2_handler;


/**
 * 启动FreeRTOS
 */
void freertos_start(void)
{

  timer1_handler = xTimerCreate(
    "ergou",    // 软件定时器的名称
    (TickType_t) 500, // 超时时间 = 500个RTOS时钟节拍
    pdFALSE,    // 是否自动重载： pdTRUE -- 周期型； pdFALSE -- 一次性
    (void *)1, // 定时器的唯一ID
    timer1_callback // 定时器的回调函数
  );
  if (timer1_callback != NULL)
  {
    printf("timer1 one-time timer successfully created...\r\n");
  }

  timer2_handler = xTimerCreate(
    "zhangsan",    // 软件定时器的名称
    (TickType_t) 1000, // 超时时间 = 500个RTOS时钟节拍
    pdTRUE,    // 是否自动重载： pdTRUE -- 周期型； pdFALSE -- 一次性
    (void *)2, // 定时器的唯一ID
    timer2_callback // 定时器的回调函数
  );
  if (timer2_callback != NULL)
  {
    printf("timer2 the periodic timer has been successfully created...\r\n");
  }


  //1.创建一个启动任务
  xTaskCreate(
    (TaskFunction_t) start_task,                // 任务函数的地址
    (char *) "start_task",                      // 任务名称           
    (configSTACK_DEPTH_TYPE) START_TASK_STACK,  // 任务堆栈大小，默认最小128，单位4字节  
    (void *) NULL,                              // 传递给任务的参数
    (UBaseType_t) START_TASK_PRIORITY,          // 任务优先级
    (TaskHandle_t *) &start_task_handler         // 任务句柄的地址
  );
  //2.启动调度器：会自动创建空闲任务，空闲任务会调用vTaskSuspend(NULL)挂起自己
  vTaskStartScheduler();
}


/**
 * 启动任务：用来创建其他Task
 */
void start_task(void *pvParameters)
{
  // 进入临界区，保护临界区里的代码不会被打断
  taskENTER_CRITICAL();

  // 创建三个任务
  xTaskCreate(
    (TaskFunction_t) task1,                // 任务函数的地址
    (char *) "task1",                      // 任务名称           
    (configSTACK_DEPTH_TYPE) TASK1_STACK,  // 任务堆栈大小，默认最小128，单位4字节  
    (void *) NULL,                              // 传递给任务的参数
    (UBaseType_t) TASK1_PRIORITY,          // 任务优先级
    (TaskHandle_t *) &task1_handler         // 任务句柄的地址
  );
  // 启动任务只需要执行一次即可，用完就删除自己，不再占用资源
  vTaskDelete(NULL);

  // 退出临界区
  taskEXIT_CRITICAL();
}

/**
 * 任务一：实现LED1每500ms闪烁一次
 */
void task1(void *pvParameters)
{
  uint8_t key = 0;
  BaseType_t res = 0;
  while (1)
  {
    key = Key_Detect();

    if (key == KEY1_PRESS)
    {
      // 开启软件定时器
      res = xTimerStart(timer1_handler, portMAX_DELAY);
      if (res == pdPASS)
      {
        printf("timer1 started successfully...\r\n");
      }

      res = xTimerStart(timer2_handler, portMAX_DELAY);
      if (res == pdPASS)
      {
        printf("timer2 started successfully...\r\n");
      }
    }
    else if (key == KEY2_PRESS)
    {
      // 停止软件定时器
      res = xTimerStop(timer1_handler, portMAX_DELAY);
      if (res == pdPASS)
      {
        printf("timer1 stopped successfully...\r\n");
      }

      res = xTimerStop(timer2_handler, portMAX_DELAY);
      if (res == pdPASS)
      {
        printf("timer2 stopped successfully...\r\n");
      }
    }

    vTaskDelay(500);
  }
}


void timer1_callback(TimerHandle_t xTimer)
{
  static uint16_t timer1_count = 0;
  printf("timer1 timeout callback %d times...\r\n", timer1_count++);
}

void timer2_callback(TimerHandle_t xTimer)
{
  static uint16_t timer2_count = 0;
  printf("timer2 timeout callback %d times...\r\n", timer2_count++);
}
