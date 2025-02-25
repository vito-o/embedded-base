#include "freertos_demo.h"
// freertos相关头文件
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

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

// 任务2的配置
#define TASK2_STACK 128
#define TASK2_PRIORITY 3
TaskHandle_t task2_handler;
void task2(void *pvParameters);

EventGroupHandle_t event_group_handle;

/**
 * 启动FreeRTOS
 */
void freertos_start(void)
{
  // 创建事件标志组
  event_group_handle = xEventGroupCreate();
  if (event_group_handle != NULL)
  {
    printf("the event group is created successfully\r\n");
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
  xTaskCreate(
    (TaskFunction_t) task2,                // 任务函数的地址
    (char *) "task2",                      // 任务名称           
    (configSTACK_DEPTH_TYPE) TASK2_STACK,  // 任务堆栈大小，默认最小128，单位4字节  
    (void *) NULL,                              // 传递给任务的参数
    (UBaseType_t) TASK2_PRIORITY,          // 任务优先级
    (TaskHandle_t *) &task2_handler         // 任务句柄的地址
  );

  // 启动任务只需要执行一次即可，用完就删除自己，不再占用资源
  vTaskDelete(NULL);

  // 退出临界区
  taskEXIT_CRITICAL();
}


#define EVENTBIT_0 (1 << 0)
#define EVENTBIT_1 (1 << 1)

/**
 * 任务一：实现LED1每500ms闪烁一次
 */
void task1(void *pvParameters)
{
  uint8_t key = 0;
  while (1)
  {
    key = Key_Detect();
    if (key == KEY1_PRESS)
    {
      // 按下按键1，对bit0置1
      xEventGroupSetBits(event_group_handle, EVENTBIT_0);
      printf("key1 press, set bit0\r\n");
    }
    else if (key == KEY2_PRESS)
    {
      // 按下按键2，对bit1置1
      xEventGroupSetBits(event_group_handle, EVENTBIT_1);
      printf("key2 press, set bit1\r\n");
    }

    vTaskDelay(500);
  }
}

/**
 * 任务二：同时等待事件标志组中的多个事件位，当这些事件位都置 1 的话就执行相应的处理
 */
void task2(void *pvParameters)
{
  EventBits_t event_bits = 0;
  while (1)
  {
    event_bits = xEventGroupWaitBits(
      event_group_handle,       // 事件标志组的句柄
      EVENTBIT_0 | EVENTBIT_1,  // 需要等待的事件位
      pdTRUE,                   // 事件位全部置1才返回
      pdTRUE,                   // 事件位置1后自动清零
      portMAX_DELAY             // 一直等待
    );
    // 打印十六进制的事件位
    printf("task2 received event bits: %#x......\r\n", event_bits);
  }
}

