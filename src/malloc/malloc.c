#include "../../include/mem.h"

t_data	*data = NULL;

void	*malloc(size_t size)
{
	t_heap	**heap_tmp;
	int		type;

	if (data == NULL)
		initialize_data(&data);

	if (data == NULL)
		return NULL;

	if (size <= data->page_size * SMALL || size <= data->page_size * TINY)
	{
		heap_tmp = ((size <= data->page_size * SMALL) == (TINY * data->page_size)) ? &(data->tiny_heap) : &(data->small_heap);
		type = ((size <= data->page_size * SMALL) == (TINY * data->page_size)) ? TINY : SMALL;
		found_space_or_allocate(heap_tmp, size, type);
	}
	else
		allocate_large(size);

	if (data->error == false)
		return (data->user_space_pointer);

	free_all();
	return (NULL);
}
