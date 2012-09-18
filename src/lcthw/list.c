#include <lcthw/list.h>
#include <lcthw/debug.h>

List *List_create()
{
	// 分配大小为1*sizeof(List)的内存空间
	return calloc(1, sizeof(List));
}

void List_destroy(List *list)
{
	// 遍历List，free每个节点的前一个节点
	LIST_FOREACH(list, first, next, cur)
	{
		if(cur->prev)
		{
			free(cur->prev);
		}
	}

	free(list->last);
	free(list);
}

void List_clear(List *list)
{
	LIST_FOREACH(list, first, next, cur)
	{
		free(cur->value);
	}
}

void List_clear_destroy(List *list)
{

	List_clear(list);
	List_destroy(list);
/*
	LIST_FOREACH(list, first, next, cur)
	{
		free(cur->value);
		if(cur->prev)
		{
			free(cur->prev);
		}
	}
*/
}

void List_push(List *list, void *value)
{
	ListNode *node = calloc(1, sizeof(ListNode));
	check_mem(node);

	node->value = value;

	if(list->last == NULL)
	{
		list->first = node;
		list->last = node;
	}
	else
	{
		list->last->next = node;
		node->prev = list->last;
		list->last = node;
	}

	list->count++;

  error:
	return;

}

void *List_pop(List *list)
{
	ListNode *node = list->last;
	return node != NULL?List_remove(list, node):NULL;
}


void List_shift(List *list, void *value)
{
	ListNode *node = calloc(1, sizeof(ListNode));
	check_mem(node);

	node->value = value;

	if(list->first == NULL)
	{
		list->first = node;
		list->last = node;
	}
	else
	{
		node->next = list->first;
		list->first->prev = node;
		list->first = node;
	}

	list->count++;

  error:
	return;

}

void *List_unshift(List *list)
{
	ListNode *node = list->first;
	return node != NULL?List_remove(list, node):NULL;
}


void *List_remove(List *list, ListNode *node)
{
// TODO: find out why my version of List_remove produce segfault
/*
	LIST_FOREACH(list, first, next, cur)
	{
		if(cur == NULL)
		{
			return NULL;
		}
		else if(cur == node)
		{
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
		}
	}
	list->count--;
	void *result = node->value;
	free(node);
	return result;
*/
void *result = NULL;

    check(list->first && list->last, "List is empty.");
    check(node, "node can't be NULL");

    if(node == list->first && node == list->last) {
        list->first = NULL;
        list->last = NULL;
    } else if(node == list->first) {
        list->first = node->next;
        check(list->first != NULL, "Invalid list, somehow got a first that is NULL.");
        list->first->prev = NULL;
    } else if (node == list->last) {
        list->last = node->prev;
        check(list->last != NULL, "Invalid list, somehow got a next that is NULL.");
        list->last->next = NULL;
    } else {
        ListNode *after = node->next;
        ListNode *before = node->prev;
        after->prev = before;
        before->next = after;
    }

    list->count--;
    result = node->value;
    free(node);

error:
    return result;

}
