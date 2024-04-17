#include "../../include/mem.h"
#include <unistd.h>


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
	(*data)->page_size = getpagesize();
}

//---------------------------------free_area initialization---------------------------------//

static void	initialize_free_area(t_free_area **free_area, t_user_space *user_space, size_t size, size_t type)
{
	*free_area = mmap(NULL, sizeof(t_free_area), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (*free_area == MAP_FAILED)
	{
		data->error = true;
		return ;
	}
	(*free_area)->free_size = data->page_size * type - size;
	(*free_area)->start_free_area = user_space->start_user_space + size;
	(*free_area)->ptr_defragment = user_space->ptr_defragment;
	(*free_area)->next = NULL;
	(*free_area)->prev = NULL;
	(*free_area)->parent_heap = user_space->parent_block->parent_heap;
}

static void	add_free_area(t_heap *heap, t_user_space *user_space, size_t size, size_t type)
{
	t_free_area	*free_area_tmp;

	free_area_tmp = heap->free_area;
	while (free_area_tmp->next)
		free_area_tmp = free_area_tmp->next;
	free_area_tmp->next = mmap(NULL, sizeof(t_free_area), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	free_area_tmp->next->start_free_area = user_space->start_user_space + size;
	free_area_tmp->next->ptr_defragment = user_space->ptr_defragment;
	free_area_tmp->next->free_size = data->page_size * type - size;
	free_area_tmp->next->next = NULL;
	free_area_tmp->next->prev = free_area_tmp;
	free_area_tmp->next->parent_heap = user_space->parent_block->parent_heap;
}

//--------------------------------------------------------------------------------------------//

static void	initialize_user_space(t_heap *heap, t_block *block, size_t size, size_t type)
{
	// add new user_space
	block->user_space = mmap(NULL, sizeof(t_user_space), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (block->user_space == MAP_FAILED)
	{
		data->error = true;
		return ;
	}
	block->user_space->start_user_space = (void *)block + sizeof(t_block);
	block->user_space->ptr_defragment = block->user_space->start_user_space;
	block->user_space->size_allocated = size;
	block->user_space->parent_block = block;
	block->user_space->next = NULL;
	block->user_space->prev = NULL;

	// add new free_area or initialize the first free_area
	if (heap->free_area == NULL)
		initialize_free_area(&(heap->free_area), block->user_space, size, type);
	else
		add_free_area(heap, block->user_space, size, type);

	// set the user_space_pointer to the start of the user_space
	data->user_space_pointer = block->user_space->start_user_space;
}

void	initialize_block(t_heap *heap, size_t size, size_t type)
{
	t_block	*block = NULL;
	t_block	*block_prev = NULL;

	// find the last block
	block = heap->start_block;
	if (block != NULL)
	{
		while (block->next)
			block = block->next;
		block_prev = block;			// set the previous block to the last block
		block = block->next;
	}

	// allocate the block
	block = mmap(NULL, sizeof(t_block) + data->page_size * type, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (block == MAP_FAILED)
	{
		data->error = true;
		return ;
	}
	block->parent_heap = heap;

	// initialize the block
	if (block_prev != NULL)
	{
		block->prev = block_prev;
		block->prev->next = block;
	}
	else
	{
		heap->start_block = block;
		block->prev = NULL;
	}
	block->next = NULL;
	initialize_user_space(heap, block, size, type);
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
	(*heap)->size = data->page_size * type;
}

void	initialize_large_heap(t_large_heap **new_large_heap, t_large_heap *large_heap_prev, size_t size)
{
	(*new_large_heap) = mmap(NULL, sizeof(t_large_heap) + size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (new_large_heap == MAP_FAILED)
	{
		data->error = true;
		return ;
	}
	// initialize the new node large_heap
	(*new_large_heap)->start_user_space = (void *)(*new_large_heap) + sizeof(t_large_heap);
	(*new_large_heap)->size_allocated = size;

	// link the new node large_heap
	link_large_heap((*new_large_heap), large_heap_prev);
}
