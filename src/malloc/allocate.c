#include "../../include/mem.h"

void	allocate(t_data *data, t_heap **heap, size_t size, size_t type)
{
	t_mem_block		*block_tmp;
	t_mem_block		*block_prev = NULL;

	write(1, "allocate\n", 9);
	if (*heap == NULL)
	{
		(*heap) = mmap(NULL, sizeof(t_heap), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		if (*heap == MAP_FAILED)
		{
			data->error = true;
			return ;
		}
		initialize_heap(*heap, type);
	}
	block_tmp = (*heap)->start_block;
	if (block_tmp != NULL)
	{
		while (block_tmp->next)
			block_tmp = block_tmp->next;
		block_prev = block_tmp;											// set the previous block to the last block

	}
	block_tmp = mmap(NULL, sizeof(t_mem_block) + getpagesize() * type, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (block_tmp == MAP_FAILED)
	{
		data->error = true;
		munmap(heap, sizeof(t_heap));
		return ;
	}
	initialize_block(block_tmp, type, block_prev);
	(*heap)->count_blocks++;
	block_tmp->free_area = mmap(NULL, sizeof(t_free_space), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	block_tmp->free_area->start = block_tmp->start_user_space + size;	// set the start of the free space to the end of the allocated space
	data->start_user_space = block_tmp->free_area->start;
	block_tmp->free_area->size -= size;
	if (block_prev != NULL)												// if there is a previous block
	{
		block_tmp->free_area->prev = block_prev->free_area;				// set the previous free space to the previous block's free space
		block_tmp->free_area->prev->next = block_tmp->free_area;		// set the previous free space's next to the current free space
		block_prev->next = block_tmp;									// set the previous block's next to the current block
	}
	else																// if there is no previous block
	{
		block_tmp->free_area->next = NULL;
		block_tmp->free_area->prev = NULL;
		(*heap)->start_block = block_tmp;								// set the start block to the current block
	}

}



void	allocate_large(t_data *data, size_t size)
{
	(void)data;
	(void)size;
}