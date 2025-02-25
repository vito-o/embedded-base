#include "freertos_demo.h"
// freertos相关头文件
#include "FreeRTOS.h"
#include "task.h"

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


/**
 * 启动FreeRTOS
 */
void freertos_start(void)
{
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
 * 任务一：用于按键扫描，当检测到按键KEY1被按下时，将发送任务通知。
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
      // 发送任务通知
      res = xTaskNotify(
        task2_handler,          // 接收方的任务句柄
        EVENTBIT_0,             // 要发送的通知值，需要位置的bit置1
        eSetBits                // 写入的行为：设置bit位
      );
      if (res == pdPASS)
      {
        printf("press key1 to set bit0 to 1\r\n");
      }
    }
    else if (key == KEY2_PRESS)
    {	
      // 发送任务通知
      res = xTaskNotify(
        task2_handler,          // 接收方的任务句柄
        EVENTBIT_1,             // 要发送的通知值，需要位置的bit置1
        eSetBits                // 写入的行为：设置bit位
      );
      if (res == pdPASS)
      {
        printf("press key2 to set bit0 to 1\r\n");
      }
    }
    vTaskDelay(500);
  }
}

/**
 * 任务二：用于接收任务通知，并打印相关提示信息。
 */
void task2(void *pvParameters)
{
  uint32_t notify_value = 0;
  uint32_t expect_value = 0;
  BaseType_t res = 0;
  while (1)
  {
    printf("task2 is running\n");
    
    res = xTaskNotifyWait(
      0x00000000,     // 接收到通知前是否清理之前的通知值，全0，表示32bit都是0，不清零
      0xffffffff,     // 接收所有通知值后，是否清理通知值，全1，表示32bit都是1，都要清零
      &notify_value,  // 用于存储接收到的通知值
      portMAX_DELAY   // 等待任务通知的最大阻塞时间
    );

    // 如果bit0 = 1，表示接收到了任务1的通知
    if (notify_value & EVENTBIT_0)
    {
      printf("task2 receive bit0 value: 1\r\n");
      expect_value |= EVENTBIT_0;
    }
    // 如果bit1 = 1，表示接收到了任务2的通知
    if (notify_value & EVENTBIT_1)
    {
      printf("task2 receive bit0 value: 1\r\n");
      expect_value |= EVENTBIT_1;
    }

    if (expect_value == 3)
    {
      printf("task2 receive all notify value: 3\r\n");
    }

    vTaskDelay(500);
  }
}
