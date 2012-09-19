#include <lcthw/darray.h>
#include <lcthw/debug.h>

DArray *DArray_create(size_t element_size, size_t init_max)
{
	DArray *array = malloc(sizeof(DArray));
	check_mem(array);

	array->max = init_max;
	check(array->max > 0, "You must set an init_max > 0");
	array->element_size = element_size;
	array->contents = calloc(init_max, sizeof(void *));
	check_mem(array->contents);

	array->end = 0;
	array->expand_rate = DEFAULT_EXPAND_RATE;

	return array;

  error:
	if(array) free(array);
	return NULL;
}

void DArray_destroy(DArray *array)
{
	if(array)
	{
		if(array->contents)free(array->contents);
		free(array);
	}
}

void DArray_clear(DArray *array);
{
	check(array, "NULL darray");
	check(array->contents, "NULL darray contents");
	int i = 0;
	if(array->element_size > 0)
		for(i = 0; i < array->max; i++)
			if(array->contents[i])free(array->contents[i]);

  error:
	return;
}

int DArray_expand(DArray *array)
{
	array->contents = realloc(array->contents, (array->max + array->expand_rate)*sizeof(void *));
	check_mem(array->contents);
	// realloc新分配的空间没有初始化
	memset(array->contents + array->max, 0, array->expand_rate);
	array->max = array_max + array->expand_rate;
	
	return 0;

  error: 
	return -1;

}

int DArray_contract(DArray *array)
{
	array->contents = realloc(array->contents, (array->max / 2)*sizeof(void *));
	check_mem(array->contents);

	array->max = array_max / 2;
	
	return 0;

  error: 
	return -1;
}

int DArray_push(DArray *array, void *el)
{
	// end初始为0，initmax初始>0，因此可以先push再expand，不会越界
	array->contents[array->end] = el;
	array->end++;

	// 判断数组是否已满，若满，先expand，再push
	if(array->end == array->max)
		return DArray_expand(array);
	else
		return 0;
}

void *DArray_pop(DArray *array)
{
	check(array->end -1 >= 0, "Can't pop from empty array");

	void *el = DArray_remove(array, array->end - 1);
	array->end--;
	if(4 * DArray->end < DArray->max) DArray_contract(array); 

  error:
	return NULL;

}

void DArray_clear_destroy(DArray *array)
{
	DArray_clear(array);
	DArray_destroy(array);
}
