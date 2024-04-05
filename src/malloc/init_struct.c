#include "../../include/mem.h"


void	initialize_data(t_data **data)
{
	*data = (t_data *)mmap(NULL, sizeof(t_data), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (*data == MAP_FAILED)
		return ;
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

static void	initialize_user_space(t_mem_block *block, size_t size)
{
	block->user_space = mmap(NULL, sizeof(t_user_space), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (block->user_space == MAP_FAILED)
	{
		data->error = true;
		return ;
	}
	block->user_space->start_user_space = block->user_space + sizeof(t_mem_block);
	block->user_space->size_allocated = size;
	block->user_space->next = NULL;
	block->user_space->prev = NULL;
}

// void	ft_putchar_fd(char c, int fd)
// {
// 	write(fd, &c, 1);
// }

// void	ft_putnbr_fd(int n, int fd)
// {
// 	if (n < 0)
// 	{
// 		ft_putchar_fd('-', fd);
// 		if (n == -2147483648)
// 		{
// 			write(fd, "2147483648", 10);
// 			return ;
// 		}
// 		n = -n;
// 	}
// 	if (n < 10)
// 		ft_putchar_fd((n + 48), fd);
// 	else
// 	{
// 		ft_putnbr_fd(n / 10, fd);
// 		ft_putchar_fd(n % 10 + 48, fd);
// 	}
// }

static void	initialize_free_space(t_heap  **heap, t_mem_block *block, size_t size, t_mem_block *block_prev, size_t type)
{
	block->free_area = mmap(NULL, sizeof(t_free_space), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (block->free_area == MAP_FAILED)
	{
		data->error = true;
		return ;
	}
	block->free_area->start_free_space = block->user_space->start_user_space + size;
	block->free_area->free_size = getpagesize() * type - size;
	block->free_area->next = NULL;
	if (block_prev != NULL)										// if there is a previous block
	{
		block->free_area->prev = block_prev->free_area;
		if (block_prev->free_area != NULL)						// if there is a previous free space
			block->free_area->prev->next = block->free_area;
		block_prev->next = block;
	}
	else
	{
		block->free_area->next = NULL;
		block->free_area->prev = NULL;
		(*heap)->start_block = block;
	}
}

void	initialize_block(t_heap  **heap, t_mem_block *block, size_t size, t_mem_block *block_prev, size_t type)
{
	initialize_user_space(block, size);
	initialize_free_space(heap, block, size, block_prev, type);
	if (block_prev != NULL)
	{
		block->prev = block_prev;
		block->prev->next = block;
	}
	else
		block->prev = NULL;
	block->next = NULL;
	data->return_user_space = block->user_space->start_user_space;
	(*heap)->count_blocks++;
	block->user_space->parent_block = block;
}