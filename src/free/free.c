#include "../../include/mem.h"

void	defragement_prev(t_free_space *free_area)
{
	t_free_space	*free_area_prev;

	free_area_prev = free_area->prev;
	if (free_area_prev != NULL)
	{
		free_area_prev->free_size += free_area->free_size;
		free_area_prev->next = free_area->next;
		if (free_area->next != NULL)
			free_area->next->prev = free_area_prev;
		munmap(free_area, sizeof(t_free_space));
		defragement_prev(free_area_prev);
	}
}

void	defragement_next(t_free_space *free_area)
{
	t_free_space	*free_area_next;

	free_area_next = free_area->next;
	if (free_area_next != NULL)
	{
		free_area->free_size += free_area_next->free_size;
		free_area->next = free_area_next->next;
		if (free_area_next->next != NULL)
			free_area_next->next->prev = free_area;
		munmap(free_area_next, sizeof(t_free_space));
		defragement_next(free_area);
	}
}

void	free(void *ptr)
{
	t_user_space	*user_space_tmp;
	t_heap_large	*heap_large_tmp;
	t_free_space	*free_area_prev = NULL;
	t_free_space	*free_area_tmp;
	t_free_space	*free_area_add;
	t_mem_block		*block_tmp;
	size_t			page_size = getpagesize();
	size_t			type;

	find_ptr(&user_space_tmp, &heap_large_tmp, ptr, &type);
	if (user_space_tmp)
	{
		// unlink user_space
		if (user_space_tmp->prev != NULL)
			user_space_tmp->prev->next = user_space_tmp->next;
		if (user_space_tmp->next != NULL)
			user_space_tmp->next->prev = user_space_tmp->prev;
		
		//find position of new free_area in free_area ( sorted by memory address, from largest to smallest)
		free_area_tmp = user_space_tmp->parent_block->free_area;
		while (free_area_tmp->start_free_space < user_space_tmp->start_user_space)
		{
			if (free_area_tmp->next == NULL)
				free_area_prev = free_area_tmp;
			free_area_tmp = free_area_tmp->next;
		}
		// create new free_area
		free_area_add =  mmap(NULL, sizeof(t_free_space), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		free_area_add->start_free_space = user_space_tmp->start_user_space;
		free_area_add->free_size = user_space_tmp->size_allocated;
		free_area_add->next = free_area_tmp->next;
		free_area_add->prev = free_area_prev;

		// link free_area
		free_area_tmp->prev = free_area_add;
		if (free_area_prev != NULL)
			free_area_prev->next = free_area_add;
		else
			user_space_tmp->parent_block->free_area = free_area_add;

		// defragement, combine free_area if possible
		defragement_prev(free_area_add);
		defragement_next(free_area_add);
		if (type == TINY)
		{
			if (free_area_add->free_size == page_size * TINY)
			{
				// free block if no user_space
				block_tmp = user_space_tmp->parent_block;

				munmap(user_space_tmp->parent_block->user_space, sizeof(t_user_space) + page_size * TINY);
				munmap(free_area_add, sizeof(t_free_space));
				
				// unlink block
				if (block_tmp->prev != NULL)
					block_tmp->prev->next = block_tmp->next;
				if (block_tmp->next != NULL)
					block_tmp->next->prev = block_tmp->prev;
				
				munmap(block_tmp, sizeof(t_mem_block));
				block_tmp = NULL;
				// free heap if no user_space
				if (data->tiny->start_block == NULL)
				{
					munmap(data->tiny, sizeof(t_heap));
					data->tiny = NULL;
				}
			}
		}
		else
		{
			if (free_area_add->free_size == page_size * SMALL)
			{
				block_tmp = user_space_tmp->parent_block;

				munmap(user_space_tmp->parent_block->user_space, sizeof(t_user_space) + page_size * SMALL);
				munmap(free_area_add, sizeof(t_free_space));
				
				// unlink block
				if (block_tmp->prev != NULL)
					block_tmp->prev->next = block_tmp->next;
				if (block_tmp->next != NULL)
					block_tmp->next->prev = block_tmp->prev;
				
				munmap(block_tmp, sizeof(t_mem_block));
				block_tmp = NULL;
				if (data->small->start_block == NULL)
				{
					munmap(data->small, sizeof(t_heap));
					data->small = NULL;
				}
			}
		}
		
		munmap(user_space_tmp->start_user_space, user_space_tmp->size_allocated);
	}
	else
	{
		// unlink heap_large
		if (heap_large_tmp->prev != NULL)
			heap_large_tmp->prev->next = heap_large_tmp->next;
		if (heap_large_tmp->next != NULL)
			heap_large_tmp->next->prev = heap_large_tmp->prev;
		// free heap_large
		munmap(heap_large_tmp->start_user_space, heap_large_tmp->size_allocated);
		munmap(heap_large_tmp, sizeof(t_heap_large) + page_size * LARGE);
		heap_large_tmp = NULL;
		// free heap if no user_space
		if (data->large == NULL)
		{
			munmap(data->large, sizeof(t_heap_large));
			data->large = NULL;
		}
	}
}