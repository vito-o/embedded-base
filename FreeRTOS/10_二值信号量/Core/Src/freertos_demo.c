#include "freertos_demo.h"
// freertos相关头文件
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

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

QueueHandle_t semphore_handle;


/**
 * 启动FreeRTOS
 */
void freertos_start(void)
{
  vSemaphoreCreateBinary(semphore_handle);
  if (semphore_handle == NULL)
  {
    printf("Create semphore failed\r\n");
  }
  else
  {
    printf("Create semphore success\r\n");
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

/**
 * 任务一：释放二值信号量
 */
void task1(void *pvParameters)
{
  uint8_t key = 0;
  uint8_t res = 0;
  while (1)
  {
    key = Key_Detect();
		// key1按下，挂起task1
    if (key == KEY1_PRESS)
    {	
      if (semphore_handle != NULL)
      {
        res = xSemaphoreGive(semphore_handle);
        if (res == pdTRUE)
        {
          printf("task1 give sem success\r\n");
        }
        else
        {
          printf("task1 give sem failure\r\n");
        }
      }
    }
  }
}

/**
 * 任务二：获取二值信号量
 */
void task2(void *pvParameters)
{
  uint8_t res = 0;
  while (1)
  {
    res = xSemaphoreTake(semphore_handle, portMAX_DELAY);
    if (res == pdTRUE)
    {
      printf("task2 give sem success\r\n");
    }
    else
    {
      printf("task2 give sem failure\r\n");
    }
  }
}
