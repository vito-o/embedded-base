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

// 任务3的配置
#define TASK3_STACK 128
#define TASK3_PRIORITY 4
TaskHandle_t task3_handler;
void task3(void *pvParameters);

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
  xTaskCreate(
    (TaskFunction_t) task3,                // 任务函数的地址
    (char *) "task3",                      // 任务名称           
    (configSTACK_DEPTH_TYPE) TASK3_STACK,  // 任务堆栈大小，默认最小128，单位4字节  
    (void *) NULL,                              // 传递给任务的参数
    (UBaseType_t) TASK3_PRIORITY,          // 任务优先级
    (TaskHandle_t *) &task3_handler         // 任务句柄的地址
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
  while (1)
  {
    //printf("task1 is running\n");
    LED_Toggle(LED1_Pin);
    vTaskDelay(500);
  }
}

/**
 * 任务二：实现LED2每500ms闪烁一次
 */
void task2(void *pvParameters)
{
  while (1)
  {
    //printf("task2 is running\n");
    LED_Toggle(LED2_Pin);
    vTaskDelay(500);
  }
}

char task_info[500]; // 定义一个字符数组，用于接收任务信息字符串
/**
* 任务三：判断按键按下逻辑，key1按下，挂起task1，按下key2在任务中恢复task1，key3按下，挂起调度器，key4按下，恢复调度器
 */
void task3(void *pvParameters)
{
  uint8_t key = 0;
  while (1)
  {
    key = Key_Detect();
		// key1按下，挂起task1
    if (key == KEY1_PRESS)
    {	
      vTaskSuspend(task1_handler);
    }
		// 按下key2在任务中恢复task1
		else if (key == KEY2_PRESS)
		{
			vTaskResume(task1_handler);
		}
		// key3按下，挂起调度器，挂起调度器表示任务不再切换
		else if (key == KEY3_PRESS)
		{
			vTaskSuspendAll();
		}
		// key4按下，恢复调度器，恢复调度器表示任务开始切换
		else if (key == KEY4_PRESS)
		{
			xTaskResumeAll();
		}
		
		vTaskList(task_info);
		//printf("%s\r\n", task_info);
		
    vTaskDelay(500);
  }
}

