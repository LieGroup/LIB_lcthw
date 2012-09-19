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
	// TODO: 考虑有相同元素的情况
	List *result = List_create(); // 存放排序好的List

	// 分别指向两个List
	ListNode *cur1 = list1->first;
	ListNode *cur2 = list2->first;

	// 如果list1的数据小，则push之，并将list1的指针向前移动
	// 否则，push list2的数据，并将list2的指针向前移动
	while(cur1 != NULL && cur2 != NULL)
	{
		if(cmp((char *)cur1->value , (char *)cur2->value) > 0)
		{
			List_push(result, cur2->value);
			cur2=cur2->next;
		}
		else
		{
			List_push(result, cur1->value);
			cur1=cur1->next;
		}
	}

	// push剩余的数据
	if(cur1 == NULL)
	{
		while(cur2 != NULL)
		{
			List_push(result, cur2->value);
			cur2=cur2->next;
		}
	}
	else
	{
		while(cur1 != NULL)
		{
			List_push(result, cur1->value);
			cur1=cur1->next;
		}
	
	}
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

	List_merge_sort(left, cmp);
	List_merge_sort(right, cmp);
	

	// merge
	return List_merge(left, right, cmp);

}
