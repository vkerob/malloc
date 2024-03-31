#include "../../include/mem.h"

void	allocate(t_data *data, t_heap *heap, size_t size, size_t type)
{
	t_mem_block		*block_tmp;
	t_mem_block		*block_prev = NULL;

	if (heap == NULL)
	{
		heap = mmap(NULL, sizeof(t_heap), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		if (heap == MAP_FAILED)
		{
			data->error = true;
			return ;
		}
		initialize_heap(heap, type);
	}
	block_tmp = heap->start_block;
	if (block_tmp != NULL)
	{
		while (block_tmp->next)
			block_tmp = block_tmp->next;
		block_prev = block_tmp;
		block_tmp = block_tmp->next;
	}
	block_tmp = mmap(NULL, sizeof(t_mem_block) + getpagesize() * type, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (block_tmp == MAP_FAILED)
	{
		data->error = true;
		munmap(heap, sizeof(t_heap));
		return ;
	}
	initialize_block(block_tmp, type, block_prev);
	heap->count_blocks++;
	block_tmp->free_area = mmap(NULL, sizeof(t_free_space), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	block_tmp->free_area->start = block_tmp->start_user_space + size;
	block_tmp->free_area->size -= size;
	block_tmp->free_area->next = NULL;
	if (block_prev != NULL)
		block_tmp->free_area->prev = block_prev->free_area;
	else
		block_tmp->free_area->prev = NULL;

}



void	allocate_large(t_data *data, size_t size)
{
	(void)data;
	(void)size;
}