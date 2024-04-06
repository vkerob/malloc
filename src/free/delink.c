#include "../../include/mem.h"


void defragment(t_free_space *free_area) 
{
	t_free_space *prev = free_area->prev;
	t_free_space *next = free_area->next;

	if (prev != NULL)
	{
		// if 
		if (prev->start_free_space + prev->free_size > free_area->start_free_space)
		{
			prev->free_size += free_area->free_size;
			prev->next = next;
			if (next != NULL)
				next->prev = prev;
			munmap(free_area, sizeof(t_free_space));
			defragment(prev);
		}
	}

	if (next != NULL)
	{
		if (free_area->start_free_space + free_area->free_size > next->start_free_space)
		{
			free_area->free_size += next->free_size;
			free_area->next = next->next;
			if (next->next != NULL)
				next->next->prev = free_area;
			munmap(next, sizeof(t_free_space));
			defragment(free_area);
		}
	}
}


void add_free_area_and_defragment(t_heap *heap, t_user_space *user_space)
{
	t_free_space	*free_area_tmp;
	t_free_space	*free_area_add;
	t_free_space	*free_area_prev = NULL;

	//find position of new free_area in free_area ( sorted by memory address, from largest to smallest)
	free_area_tmp = heap->free_area;
	while (free_area_tmp->start_free_space > user_space->start_user_space && free_area_tmp->next != NULL)
		free_area_tmp = free_area_tmp->next;
	{
		if (free_area_tmp->next == NULL)
			free_area_prev = free_area_tmp;
		free_area_tmp = free_area_tmp->next;
	}
	// create new free_area
	free_area_add = mmap(NULL, sizeof(t_free_space), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (free_area_add == MAP_FAILED)
	{
		data->error = true;
		return ;
	}
	free_area_add->start_free_space = user_space->start_user_space;
	free_area_add->free_size = user_space->size_allocated;

	free_area_add->next = free_area_tmp;
	free_area_add->prev = free_area_prev;

	// link free_area
	if (free_area_prev != NULL)
		free_area_prev->next = free_area_add;
	if (free_area_tmp != NULL)
		free_area_tmp->prev = free_area_add;
	

	// defragement (combine free_area if possible)
	defragment(free_area_add);
}

void	delink_user_space(t_user_space *user_space)
{
	if (user_space->prev != NULL)
		user_space->prev->next = user_space->next;
	else
		user_space->parent_block->user_space = user_space->next;
	if (user_space->next != NULL)
		user_space->next->prev = user_space->prev;
}

void	delink_heap_large(t_heap_large *heap_large)
{
	if (heap_large->prev != NULL)
		heap_large->prev->next = heap_large->next;
	else
		data->large_heap = heap_large->next;
	if (heap_large->next != NULL)
		heap_large->next->prev = heap_large->prev;
}