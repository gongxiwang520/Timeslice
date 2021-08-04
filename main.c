//#include <threads.h>
#include <stdio.h>
#include <windows.h>
#include "timeslice.h"


// 创建任务对象
TimesliceTaskObj task_1, task_2, task_3, task_4, task_5;

void task1_hdl(void)
{
  printf(">> task 1 is running...\n");
}

void task2_hdl(void)
{
  printf(">> task 2 is running...\n");
}

void task3_hdl(void)
{
  printf(">> task 3 is running...\n");
}

void task4_hdl(void)
{
  printf(">> task 4 is running...\n");
}

void task5_hdl(void)
{
  printf(">> task 5 is running...\n");
}

void task_init(void)
{
  timeslice_task_init(&task_1, task1_hdl, 1, 10);
  timeslice_task_init(&task_2, task2_hdl, 2, 20);
  timeslice_task_init(&task_3, task3_hdl, 3, 30);
  timeslice_task_init(&task_4, task4_hdl, 4, 40);
  timeslice_task_init(&task_5, task5_hdl, 5, 50);
  timeslice_task_add(&task_1);
  timeslice_task_add(&task_2);
  timeslice_task_add(&task_3);
  timeslice_task_add(&task_4);
  timeslice_task_add(&task_5);
}


int main(int argc, char *argv[])
{
  task_init();

  printf(">> task num: %d\n", timeslice_get_task_num());
  printf(">> task len: %d\n", timeslice_get_task_timeslice_len(&task_3));

  timeslice_task_del(&task_2);
  printf(">> delete task 2\n");
  printf(">> task 2 is exist: %d\n", timeslice_task_isexist(&task_2));

  printf(">> task num: %d\n", timeslice_get_task_num());

  timeslice_task_del(&task_5);
  printf(">> delete task 5\n");

  printf(">> task num: %d\n", timeslice_get_task_num());

  printf(">> task 3 is exist: %d\n", timeslice_task_isexist(&task_3));  
  timeslice_task_add(&task_2);
  printf(">> add task 2\n");
  printf(">> task 2 is exist: %d\n", timeslice_task_isexist(&task_2));

  timeslice_task_add(&task_5);
  printf(">> add task 5\n");  

  printf(">> task num: %d\n", timeslice_get_task_num());


  timeslice_exec();
  
  timeslice_tick();
  Sleep(10);
}