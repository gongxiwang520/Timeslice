#ifndef _LIST_H
#define _LIST_H

// type为结构体类型，表示member相对于struct起始地址的偏移
#define offset_of(type, member)             (unsigned long)&((type*)0)->member
// 节点地址 - 节点在结构体中的偏移地址 = 结构体起始地址
#define container_of(ptr, type, member)     ((type *)((char *)(ptr) - offset_of(type, member)))

typedef struct list_structure
{
  struct list_structure *next;
  struct list_structure *prev;
} ListObj;

// 宏定义方法初始化头节点
#define LIST_HEAD_INIT(name)                 {&(name), &(name)}
#define LIST_HEAD(name)                     ListObj name = LIST_HEAD_INIT(name)

#define list_entry(node, type, member)      container_of(node, type, member)

#define list_for_each(pos, head)            for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_safe(pos, n, head) \
  for (pos = (head)->next, n = pos->next; pos != (head); \
    pos = n, n = pos->next)

void list_init(ListObj *list);
void list_insert_after(ListObj *list, ListObj *node);
void list_insert_before(ListObj *list, ListObj *node);
void list_remove(ListObj *node);
int list_isEmpty(const ListObj *list);
unsigned int list_len(const ListObj *list);

#endif
