#include "freertos_demo.h"
// freertos相关头文件
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
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


// 队列句柄
QueueHandle_t queue1;
QueueHandle_t sem_handle;
QueueSetHandle_t queue_set_handle;

/**
 * 启动FreeRTOS
 */
void freertos_start(void)
{
  BaseType_t res;

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

  // 创建二值信号量，创建完不主动释放
  sem_handle = xSemaphoreCreateBinary();
  if (sem_handle != NULL)
  {
    printf("sem_handle create success\r\n");
  }
  else
  {
    printf("sem_handle create failed\r\n");
  }

  // 创建一个队列集合
  queue_set_handle = xQueueCreateSet(2);
  if (queue_set_handle != NULL)
  {
    printf("queue_set_handle create success\r\n");
  }
 
  // 将队列、信号量添加到队列集合中：添加时，队列/信号量 需要为空
  res = xQueueAddToSet(queue1, queue_set_handle);
  if (res == pdPASS)
  {
    printf("queue1 add to queue_set_handle success\r\n");
  }
  
  res = xQueueAddToSet(sem_handle, queue_set_handle);
  if (res == pdPASS)
  {
    printf("sem_handle add to queue_set_handle success\r\n");
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
 * 任务一：用于扫描按键，当KEY1按下，往队列写入数据，当KEY2按下，释放二值信号量。
 */
void task1(void *pvParameters)
{
  uint8_t key = 0;
  uint8_t res = 0;

  while (1)
  {
    key = Key_Detect();
    if (key == KEY1_PRESS)
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
    else if (key == KEY2_PRESS)
    {
      res = xSemaphoreGive(sem_handle);
      if (res == pdPASS)
      {
        printf("Give sem success\r\n");
      }
      else
      {
        printf("Give sem failed\r\n");
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
  QueueSetMemberHandle_t member_handle;
  uint8_t receive = 0;
  uint8_t res = 0;
  while (1)
  {
    // 查看哪个队列有数据来了, 这里会阻塞等待
    member_handle = xQueueSelectFromSet(queue_set_handle, portMAX_DELAY);
    // 根据对应队列，去获取数据
    if (member_handle == queue1)
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
    else if (member_handle == sem_handle)
    {
      res = xSemaphoreTake(sem_handle, portMAX_DELAY);
      if (res == pdPASS)
      {
        printf("task2 take sem success\r\n");
      }
    }
    else
    {
      printf("failed to retrieve information from queue set");
    }
  }
}
