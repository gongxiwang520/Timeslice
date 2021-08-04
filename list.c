#include "list.h"

/**
 * @brief 初始化双向链表,前节点后节点都指向本身
 * @param list：初始节点
*/
void list_init(ListObj *list)
{
  list->next = list->prev = list;
}

/**
 * @brief 在链表某节点后插入一个节点node
 * @param list：在该节点之后插入  
 * @param node：待插入的节点
 * @note  先加新的节点，再断开旧的节点
*/
void list_insert_after(ListObj *list, ListObj *node)
{
  list->next->prev = node;
  node->next = list->next;

  list->next = node;
  node->prev = list;
}

/**
 * @brief 在链表某节点前插入一个节点node    
 * @param list：在该节点之前插入  
 * @param node：待插入的节点
*/
void list_insert_before(ListObj *list, ListObj *node)
{
  list->prev->next = node;
  node->prev = list->prev;

  list->prev = node;
  node->next = list;
}

/**
 * @brief 移除某节点
 * @param node：待删除的节点
*/
void list_remove(ListObj *node)
{
  node->next->prev = node->prev;
  node->prev->next = node->next;

  node->next = node->prev = node;
}

/**
 * @brief 判断链表是否为空
 * @param list：待检验的链表
*/
int list_isEmpty(const ListObj *list)
{
  return list->next == list;
}

/**
 * @brief   判断链表长度
 * @param   list：链表本身
 * @retval  长度值
*/
unsigned int list_len(const ListObj *list)
{
  unsigned int len = 0;
  const ListObj *p = list;
  while (p->next != list)
  {
    p = p->next;
    len++;
  }

  return len;
}
