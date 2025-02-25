#include "freertos_demo.h"
// freertos相关头文件
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

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

// 队列句柄
QueueHandle_t queue1;
QueueHandle_t big_queue;

/**
 * 启动FreeRTOS
 */
void freertos_start(void)
{
  // 在创建任务之前，先创建好需要的队列
  // 创建一个存放key值编号的小队列queue1
  queue1 = xQueueCreate(2, sizeof(uint8_t));
  if (queue1 != NULL)
  {
    printf("queue1 create success\r\n");
  }
  else
  {
    printf("queue1 create failed\r\n");
  }

  // 创建一个存放大数据的队列big_queue ===> 存放地址就好
  big_queue = xQueueCreate(1, sizeof(char *));
  if (big_queue != NULL)
  {
    printf("big_queue create success\r\n");
  }
  else
  {
    printf("big_queue create failed\r\n");
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
 * 任务一：当按键key1或key2按下，将键值拷贝到队列queue1（入队）；当按键key3按下，将传输大数据，这里拷贝大数据的地址到队列big_queue中
 */
void task1(void *pvParameters)
{
  char *big_data = "aaslkfjaslkdjflkasjdf3045843095830498509348@#$%**()*^%$";
  uint8_t key = 0;
  uint8_t res = 0;

  while (1)
  {
    key = Key_Detect();
    if (key == KEY1_PRESS/*  || key == KEY2_PRESS */)
    {
      res = xQueueSend(queue1, &key, portMAX_DELAY);
      if (res == pdPASS)
      {
        printf("send key data [%d] to queue1 success\r\n", key);
      }
      else
      {
        printf("send key data to queue1 failed\r\n");
      }
    }
    else if (key == KEY2_PRESS/* key == KEY3_PRESS */)
    {
      res = xQueueSend(big_queue, &big_data, portMAX_DELAY);
      if (res == pdPASS)
      {
        printf("send big data to big_queue success\r\n");
      }
      else
      {
        printf("send big data to big_queue failed\r\n");
      }
    }
    vTaskDelay(500);
  }
}

/**
 * 任务二：读取队列queue1中的消息（出队），打印出接收到的键值
 */
void task2(void *pvParameters)
{
  uint8_t receive = 0;
  uint8_t res = 0;
  while (1)
  {
    res = xQueueReceive(queue1, &receive, portMAX_DELAY);
    if (res == pdPASS)
    {
      printf("task2 receive key data [%d] from queue1 success\r\n", receive);
    }
    else
    {
      printf("task2 receive key data from queue1 failed\r\n");
    }
  }
}

/**
  * 任务三：从队列big_queue读取大数据地址，通过地址访问大数据
  */
void task3(void *pvParameters)
{
  char *receive_buff;
  uint8_t res = 0;
  while (1)
  {
    res = xQueueReceive(big_queue, &receive_buff, portMAX_DELAY);
    if (res == pdPASS)
    {
      printf("task3 receive key data [%s] from queue1 success\r\n", receive_buff);
    }
    else
    {
      printf("task3 receive key data from queue1 failed\r\n");
    }
  }
}

