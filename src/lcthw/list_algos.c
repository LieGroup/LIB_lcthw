#include <lcthw/list_algos.h>
#include <lcthw/debug.h>

void Swap_value(ListNode *n1, ListNode *n2)
{
	// 只需要交换节点的数据域
	void *tmp = n1->value;
	n1->value = n2->value;
	n2->value = tmp;
}


int List_bubble_sort(List *list, List_compare cmp)
{
	int i = 1, j = 1;
	ListNode *cur;
	// 未初始化的List，视为不能排序
	if(list == NULL) return 1;
	// 空List和只有一个节点的List视为已经排序
	if(List_count(list) < 2) return 0;

	for(i = 1; i < List_count(list); i++)
	{	
		cur = list->first;
		for(j = 1; j < List_count(list); j++)
		{
			if(cmp((char *)cur->value, (char *)cur->next->value)>0)
			{
				// 交换节点的数据域
				Swap_value(cur, cur->next);
			}
			cur = cur->next;
		}

	}

	return 0;

}

List *List_merge(List *list1, List *list2, List_compare cmp)
{
	List *result = List_create(); // 存放排序好的List

	// 数据域
	void *val = NULL;

	// 如果list1的数据小，则push之，并unshift list1
	// 否则，push list2的数据，并unshift list2
	while(List_count(list1) > 0  && List_count(list2) > 0)
	{
		if(cmp((char *)List_first(list1) , (char *)List_first(list2)) >= 0)
		{
			val = List_unshift(list2);
			List_push(result, val);
		}
		else
		{
			val = List_unshift(list1);
			List_push(result, val);
		}
	}

	// push剩余的数据
	if(List_count(list1) > 0)
	{
		while(List_count(list1) > 0)
		{
			val =List_unshift(list1);
			List_push(result, val);
		}
	}
	else
	{
		while(List_count(list2) > 0)
		{
			val =List_unshift(list2);
			List_push(result, val);
		}
	
	}
	List_destroy(list1);
	List_destroy(list2);
	return result;
	
}

List *List_merge_sort(List *list, List_compare cmp)
{
	// 未初始化的List，视为不能排序
	if(list == NULL) return NULL;
	// 空List和只有一个节点的List视为已经排序
	if(List_count(list) < 2) return list;

	int i = 1;
	ListNode *cur = list->first;
	List *left = List_create();
	List *right= List_create();
	int middle = List_count(list) / 2;
	// 拆成两个List，分别排序
	for(i = 1; i < middle; i++)
	{
		List_push(left, cur->value);
		cur=cur->next;
	}
	for(i = 1; i <= List_count(list) - middle; i++)
	{
		List_push(right, cur->value);
		cur=cur->next;
	}

	List *sort_left = List_merge_sort(left, cmp);
	List *sort_right =	List_merge_sort(right, cmp);

	if(sort_left != left) List_destroy(left);
	if(sort_right != right) List_destroy(right);
	

	// merge
	return List_merge(sort_left, sort_right, cmp);

}
