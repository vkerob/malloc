#include "../include/mem.h"

void	initialize_data(t_data **data)
{
	*data = (t_data *)mmap(NULL, sizeof(t_data), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	(*data)->tiny = NULL;
	(*data)->small = NULL;
	(*data)->large = NULL;
	(*data)->error = false;
	(*data)->return_user_space = NULL;
}

void	initialize_heap(t_heap *heap, size_t size)
{
	heap->size = size;
	heap->count_blocks = 0;
	heap->start_block = NULL;
}

void	initialize_block(t_mem_block *block, size_t size, t_mem_block *block_prev)
{
	block->user_space = mmap(NULL, sizeof(t_user_space), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	block->user_space->start_user_space = block->user_space + sizeof(t_user_space);
	block->user_space->size_allocated = size;
	block->user_space->next = NULL;
	block->free_area = NULL;
	if (block_prev != NULL)
	{
		block->prev = block_prev;
		block->prev->next = block;
	}
	else
		block->prev = NULL;
	block->next = NULL;
}

void	*find_free_space(t_heap *heap, size_t size)
{
	t_mem_block		*block;
	t_free_space	*free_area;
	t_user_space	*user_space;
	void			*start_user_space;

	if (heap == NULL)
		return (NULL);
	block = heap->start_block;
	while (block)
	{
		free_area = block->free_area;
		while (free_area)
		{
			if (free_area->free_size >= size)
			{
				if (free_area->free_size - size == 0)
				{
					free_area->prev->next = free_area->next;
					free_area->next->prev = free_area->prev;
					munmap(free_area, sizeof(t_free_space));
				}
				else
				{
					user_space = block->user_space;
					while (user_space)
						user_space = user_space->next;
					user_space = mmap(NULL, sizeof(t_user_space), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
					user_space->start_user_space = free_area->start_free_space;
					user_space->size_allocated = size;
					user_space->next = NULL;
					start_user_space = free_area->start_free_space;
					free_area->start_free_space += size;
					free_area->free_size -= size;
				}
				return (start_user_space);
			}
			free_area = free_area->next;
		}
		block = block->next;
	}
	return (NULL);
}