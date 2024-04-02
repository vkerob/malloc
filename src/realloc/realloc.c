#include "../../include/mem.h"
#include <unistd.h>




void	find_area_or_allocate(t_heap *heap, size_t size, size_t type)
{
	void	*start_user_space_tmp;

	start_user_space_tmp = find_free_space(data->tiny, size);
	if (start_user_space_tmp != NULL)										// if we found a free space
		data->return_user_space = start_user_space_tmp;						// set the start_user_space to the start of the free space
	else
		allocate(data, &heap, size, type);
}

void	*realloc(void *ptr, size_t size)
{
	t_mem_block	*tiny_tmp;
	//t_mem_block	*small_tmp;
	size_t		i;
	size_t		page_size = getpagesize();

	// find space for the new size
	if (size <= page_size * TINY)
	{
		find_area_or_allocate(data->tiny, size, TINY);			// find the area or allocate a new one
		tiny_tmp = data->tiny->start_block;
		while (tiny_tmp)
		{
			if (tiny_tmp->user_space->start_user_space == ptr)							// if we found the block
				break ;
			tiny_tmp = tiny_tmp->next;
		}
		i = 0;
		while (i < tiny_tmp->user_space->size_allocated)
		{
			((char *)data->return_user_space)[i] = ((char *)ptr)[i];
			i++;
		}
		munmap(tiny_tmp->user_space->start_user_space, tiny_tmp->user_space->size_allocated);
	}
	else if (size <= page_size * SMALL)
	{
		find_area_or_allocate(data->small, size, SMALL);
	}
	else
		allocate_large(data, size);
	// copy the data from the old space to the new space
	


	// free the old space
	
	if (data->error)
		return (NULL);
	return (data->return_user_space);
}