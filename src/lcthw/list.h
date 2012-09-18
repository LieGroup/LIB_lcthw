#ifndef lcthw_List_h
#define lcthw_List_h

#include <stdlib.h>

//struct ListNode;

// 定义List的节点
typedef struct ListNode
{
	struct ListNode *next;// 后继节点
	struct ListNode *prev;// 前驱节点
	void *value;// 节点的数据域
} ListNode;

// 定义List
typedef struct List
{
	int count;// List包含的节点数
	ListNode *first;// 首节点
	ListNode *last;// 末节点
} List;


List *List_create();// 创建一个空List
void List_destroy(List *list);// 销毁List
void List_clear(List *list);// 清空List中每个节点的数据域
void List_clear_destroy(List *list);// 清空List中每个节点的数据域并销毁List

#define List_count(A) ((A)->count) 
#define List_first(A) ((A)->first != NULL?(A)->first->value:NULL)
#define List_last(A)  ((A)->last != NULL?(A)->last->value:NULL)

void List_push(List *list, void *value);// 在List的末节点后插入一个节点
void *List_pop(List *list);// 删除List的末节点并返回其数据域的值

void List_shift(List *list, void *value);// 在List首节点之前插入新节点
void *List_unshift(List *list);// 返回List的首节点

void *List_remove(List *list, ListNode *node);// 删除List中的node节点

// 方便遍历List的macro
#define LIST_FOREACH(L, S, M, V) ListNode *_node = NULL;		\
	ListNode *V = NULL;											\
	for(V = _node = L->S; _node != NULL; V = _node = _node->M)

#endif
