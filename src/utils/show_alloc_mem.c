#include "../../include/mem.h"

void	show_heap(t_heap *heap)
{
	t_block	*block;
	t_user_space	*user_space;
	size_t	total_size = 0;

	block = heap->start_block;
	while (block)
	{
		user_space = block->user_space;
		while (user_space)
		{
			write(1, user_space->start_user_space, 8);
			write(1, " - ", 3);
			write(1, user_space->start_user_space + user_space->size_allocated, 8);
			write(1, " : ", 3);
			write(1, user_space->size_allocated, 8);
			write(1, " bytes\n", 7);
			total_size += user_space->size_allocated;
			user_space = user_space->next;
		}
		block = block->next;
	}
}

void	show_alloc_mem()
{
	t_heap_large	*large_heap;
	size_t			total_size = 0;
	
	write(1, "TINY", 4);
	show_heap(data->tiny_heap);
	write(1, "SMALL", 5);
	show_heap(data->small_heap);
	large_heap = data->large_heap;
	while (large_heap)
	{
		write(1, large_heap->start_user_space, 8);
		write(1, " - ", 3);
		write(1, large_heap->start_user_space + large_heap->size_allocated, 8);
		write(1, " : ", 3);
		write(1, large_heap->size_allocated, 8);
		write(1, " bytes\n", 7);
		total_size += large_heap->size_allocated;
		large_heap = large_heap->next;
	}

	write(1, "Total : ", 8);
	write(1, total_size, 8);
	write(1, " bytes\n", 7);

}