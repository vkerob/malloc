#include "../../include/mem.h"


void	*find_free_space(t_heap *heap, size_t size)
{
	t_mem_block		*block;
	t_free_space	*free_area;

	if (heap == NULL)
		return (NULL);
	block = heap->start_block;
	while (block)
	{
		free_area = block->free_area;
		while (free_area)
		{
			if (free_area->size >= size)
			{
				if (free_area->size - size == 0)
				{
					free_area->prev->next = free_area->next;
					free_area->next->prev = free_area->prev;
					munmap(free_area, sizeof(t_free_space));
				}
				else
				{
					free_area->start += size;
					free_area->size -= size;
				}
				return (free_area->start);
			}
			free_area = free_area->next;
		}
		block = block->next;
	}
	return (NULL);
}