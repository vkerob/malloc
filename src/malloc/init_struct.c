#include "../../include/mem.h"


void	initialize_data(t_data **data)
{
	*data = (t_data *)mmap(NULL, sizeof(t_data), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (*data == MAP_FAILED)
		return ;
	(*data)->tiny_heap = NULL;
	(*data)->small_heap = NULL;
	(*data)->large_heap = NULL;
	(*data)->error = false;
	(*data)->user_space_pointer = NULL;
}

static void	initialize_user_space(t_heap  *heap, t_block **block, size_t size, size_t type)
{
	(*block)->user_space = mmap(NULL, sizeof(t_user_space), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if ((*block)->user_space == MAP_FAILED)
	{
		data->error = true;
		return ;
	}
	(*block)->user_space->start_user_space = (*block)->user_space + sizeof(t_block);
	(*block)->user_space->size_allocated = size;
	(*block)->user_space->parent_block = *block;
	(*block)->user_space->next = NULL;
	(*block)->user_space->prev = NULL;
	
	// update free_area
	heap->free_area->start_free_space = (*block)->user_space->start_user_space + size;
	heap->free_area->free_size = getpagesize() * type - size;
	data->user_space_pointer = (*block)->user_space->start_user_space;
}

static void	initialize_free_area(t_free_space **free_area)
{
	*free_area = mmap(NULL, sizeof(t_free_space), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (*free_area == MAP_FAILED)
	{
		data->error = true;
		return ;
	}
	(*free_area)->free_size = 0;
	(*free_area)->start_free_space = NULL;
	(*free_area)->next = NULL;
	(*free_area)->prev = NULL;
}

void	initialize_heap(t_heap **heap, size_t type)
{

	(*heap) = mmap(NULL, sizeof(t_heap), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (*heap == MAP_FAILED)
	{
		data->error = true;
		return ;
	}
	(*heap)->start_block = NULL;
	(*heap)->size = getpagesize() * type;
	initialize_free_area(&((*heap)->free_area));
}

void	initialize_block(t_heap *heap, t_block **block, size_t size, t_block *block_prev, size_t type)
{
	// find the last block
	(*block) = heap->start_block;
	if (*block != NULL)
	{
		while ((*block)->next)
			*block = (*block)->next;
		block_prev = *block;											// set the previous block to the last block
		*block = (*block)->next;
	}
	// allocate the block
	*block = mmap(NULL, sizeof(t_block) + getpagesize() * type, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (*block == MAP_FAILED)
	{
		data->error = true;
		return ;
	}
	// initialize the block
	if (block_prev != NULL)
	{
		(*block)->prev = block_prev;
		(*block)->prev->next = *block;
	}
	else
	{
		heap->start_block = *block;
		(*block)->prev = NULL;
	}
	(*block)->next = NULL;
	initialize_user_space(heap, block, size, type);
}