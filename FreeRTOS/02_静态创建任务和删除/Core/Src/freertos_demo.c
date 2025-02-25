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
StackType_t start_task_stack[START_TASK_STACK]; // 静态任务的任务栈，以数组形式存储
StaticTask_t start_task_tcb;                    // 静态任务的TCB结构体类型（任务控制块）
void start_task(void *pvParameters);

// 任务1的配置
#define TASK1_STACK 128
#define TASK1_PRIORITY 2
TaskHandle_t task1_handler;
StackType_t task1_stack[TASK1_STACK]; // 静态任务的任务栈，以数组形式存储
StaticTask_t task1_tcb; 
void task1(void *pvParameters);

// 任务2的配置
#define TASK2_STACK 128
#define TASK2_PRIORITY 3
TaskHandle_t task2_handler;
StackType_t task2_stack[TASK2_STACK]; // 静态任务的任务栈，以数组形式存储
StaticTask_t task2_tcb; 
void task2(void *pvParameters);

// 任务3的配置
#define TASK3_STACK 128
#define TASK3_PRIORITY 4
TaskHandle_t task3_handler;
StackType_t task3_stack[TASK3_STACK]; // 静态任务的任务栈，以数组形式存储
StaticTask_t task3_tcb; 
void task3(void *pvParameters);

// ================静态创建方式，需要手动指定2个特殊任务的资源=====================
// 空闲任务的配置
StackType_t idle_task_stack[configMINIMAL_STACK_SIZE]; // 静态任务的任务栈，以数组形式存储
StaticTask_t idle_task_tcb;                              // 静态任务的TCB结构体类型

// 软件定时器任务的配置
StackType_t timer_task_stack[configTIMER_TASK_STACK_DEPTH]; // 静态任务的任务栈，以数组形式存储
StaticTask_t timer_task_tcb;                                  // 静态任务的TCB结构体类型

// 分配空闲任务的资源
void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                    StackType_t ** ppxIdleTaskStackBuffer,
                                    uint32_t * pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &idle_task_tcb;
  *ppxIdleTaskStackBuffer = idle_task_stack;
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  
}

// 分配软件定时器任务的资源
void vApplicationGetTimerTaskMemory(StaticTask_t ** ppxTimerTaskTCBBuffer,
                                    StackType_t ** ppxTimerTaskStackBuffer,
                                    uint32_t * pulTimerTaskStackSize )
{
  *ppxTimerTaskTCBBuffer = &timer_task_tcb;
  *ppxTimerTaskStackBuffer = timer_task_stack;
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}


/**
 * 启动FreeRTOS
 */
void freertos_start(void)
{
  //1.创建启动任务
  start_task_handler = xTaskCreateStatic(
    (TaskFunction_t) start_task,                // 任务函数的地址
    (char *) "start_task",                      // 任务名称           
    (uint32_t) START_TASK_STACK,                // 任务堆栈大小，默认最小128，单位4字节  
    (void *) NULL,                              // 传递给任务的参数
    (UBaseType_t) START_TASK_PRIORITY,          // 任务优先级
    (StackType_t *) start_task_stack,           // 我们创建的任务栈（数组存储）的地址
    (StaticTask_t *) &start_task_tcb             // 我们创建的tcb的地址
  );

  //2.启动调度器：会自动创建空闲任务和软件定时器（如果开启）
  //  静态创建的方式需要去实现2个分配资源的接口函数
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
  task1_handler = xTaskCreateStatic(
    (TaskFunction_t) task1,                // 任务函数的地址
    (char *) "task1",                      // 任务名称           
    (configSTACK_DEPTH_TYPE) TASK1_STACK,  // 任务堆栈大小，默认最小128，单位4字节  
    (void *) NULL,                         // 传递给任务的参数
    (UBaseType_t) TASK1_PRIORITY,          // 任务优先级
    (StackType_t *) task1_stack,           // 我们创建的任务栈（数组存储）的地址
    (StaticTask_t *) &task1_tcb             // 我们创建的tcb的地址
  );
  task2_handler = xTaskCreateStatic(
    (TaskFunction_t) task2,                // 任务函数的地址
    (char *) "task2",                      // 任务名称           
    (configSTACK_DEPTH_TYPE) TASK2_STACK,  // 任务堆栈大小，默认最小128，单位4字节  
    (void *) NULL,                         // 传递给任务的参数
    (UBaseType_t) TASK2_PRIORITY,          // 任务优先级
    (StackType_t *) task2_stack,           // 我们创建的任务栈（数组存储）的地址
    (StaticTask_t *) &task2_tcb             // 我们创建的tcb的地址
  );
  task3_handler = xTaskCreateStatic(
    (TaskFunction_t) task3,                // 任务函数的地址
    (char *) "task3",                      // 任务名称           
    (configSTACK_DEPTH_TYPE) TASK3_STACK,  // 任务堆栈大小，默认最小128，单位4字节  
    (void *) NULL,                         // 传递给任务的参数
    (UBaseType_t) TASK3_PRIORITY,          // 任务优先级
    (StackType_t *) task3_stack,           // 我们创建的任务栈（数组存储）的地址
    (StaticTask_t *) &task3_tcb             // 我们创建的tcb的地址
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

/**
 * 任务三：判断按键key1是否按下，按下则删掉task1
 */
void task3(void *pvParameters)
{
  uint8_t key = 0;
  while (1)
  {
    //printf("task3 is running\n");

    key = Key_Detect();
    if (key == KEY1_PRESS)
    {
      if (task1_handler != NULL)
      {
        //printf("task1 is deleted\n");
        vTaskDelete(task1_handler);
        task1_handler = NULL;
      }
    }

    vTaskDelay(500);
  }
}

