#include "timeslice.h"

// 定义一个链表头，前、后节点都指向timeslice_task_list
static LIST_HEAD(timeslice_task_list);

/**
 * @brief 遍历任务链表执行任务
 * @note 任务执行后将状态改为 TASK_STOP
*/
void timeslice_exec(void)
{
  ListObj *node;
  TimesliceTaskObj *task;

  // 插入时使用前插法,	timeslice_task_list是最后一个节点
  list_for_each(node, &timeslice_task_list)   // for(node = (&timeslice_task_list)->next; node != (&timeslice_task_list); node = node->next)
  {
    task = list_entry(node, TimesliceTaskObj, timeslice_task_list); // 查找结构体起始地址

    if (task->is_run = TASK_RUN)
    {
      task->task_hdl();
      task->is_run = TASK_STOP;
    }
  }
}

/**
 * @brief   时间片到期后执行任务
 * @retval  时间片到期后，时间片重新复位
*/
void timeslice_tick(void)
{
  ListObj *node;
  TimesliceTaskObj *task;

  list_for_each(node, &timeslice_task_list)
  {
    task = list_entry(node, TimesliceTaskObj, timeslice_task_list);
    if (task->timer != 0)
    {
      task->timer--;
      if (task->timer == 0)
      {
        task->is_run = TASK_RUN;
        task->timer = task->timeslice_len;
      }
    }
  }
}

/**
 * @brief   获取时间片任务数量
 * @retval  任务数
*/
unsigned int timeslice_get_task_num(void)
{
  return list_len(&timeslice_task_list);
}

/**
 * @brief 时间片任务初始化   
 * @param obj：时间片任务结构体
 * @param task_hdl：任务函数
 * @param id：任务id
 * @param timeslice_len：任务执行间隔时间
*/
void timeslice_task_init(TimesliceTaskObj *obj, void (*task_hdl)(void), unsigned int id, unsigned int timeslice_len)
{
  obj->id = id;
  obj->is_run = TASK_STOP;
  obj->task_hdl = task_hdl;
  obj->timer = timeslice_len;
  obj->timeslice_len = timeslice_len;
}

/**
 * @brief 时间片任务添加函数
 * @param obj：时间片任务
 * @note  将时间片任务结构体中的链表管理为双向链表，使用前插法
*/
void timeslice_task_add(TimesliceTaskObj *obj)
{
  list_insert_before(&timeslice_task_list, &obj->timeslice_task_list);
}

unsigned char timeslice_task_isexist(TimesliceTaskObj *obj)
{
  unsigned char isexist = 0;
  ListObj *node;
  TimesliceTaskObj *task;

  list_for_each(node, &timeslice_task_list)
  {
    task = list_entry(node, TimesliceTaskObj, timeslice_task_list);
    if (obj->id == task->id)
      isexist = 1;
  }

  return isexist;
}

/**
 * @brief 删除时间片任务
 * @param obj：时间片任务结构体
 * @note  从任务管理链表中删除
*/
void timeslice_task_del(TimesliceTaskObj *obj)
{
  if (timeslice_task_isexist(obj))
    list_remove(&obj->timeslice_task_list);
  else
    return ;
}

/**
 * @brief   查看时间片任务的间隔执行时间
 * @param   obj：时间片任务结构体
 * @retval  任务执行时间片
 * 
*/
unsigned int timeslice_get_task_timeslice_len(TimesliceTaskObj *obj)
{
  return obj->timeslice_len;
}








