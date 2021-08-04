#ifndef _TIMESLICE_H
#define _TIMESLICE_H

#include "list.h"

typedef enum
{
  TASK_STOP,
  TASK_RUN,
} IsTaskRun;

typedef struct timeslice
{
  unsigned int id;                  // 任务id
  void (*task_hdl)(void);           // 任务函数
  IsTaskRun is_run;                 // 任务执行状态
  unsigned int timer;               // 任务时间片实时时间
  unsigned int timeslice_len;       // 任务时间片周期时间
  ListObj timeslice_task_list;      // 任务链表
} TimesliceTaskObj;

void timeslice_exec(void);
void timeslice_tick(void);
void timeslice_task_init(TimesliceTaskObj *obj, void (*task_hdl)(void), unsigned int id, unsigned int timeslice_len);
unsigned int timeslice_get_task_num(void);
void timeslice_task_add(TimesliceTaskObj *obj);
unsigned char timeslice_task_isexist(TimesliceTaskObj *obj);
void timeslice_task_del(TimesliceTaskObj *obj);
unsigned int timeslice_get_task_timeslice_len(TimesliceTaskObj *obj);

#endif
