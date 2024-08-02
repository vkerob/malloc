#include "../../include/mem.h"

static void	ft_putnbr_base_fd(unsigned long nbr, char *base, int fd)
{
	unsigned long	len_base;

	len_base = 0;
	while (base[len_base])
		len_base++;
	if (nbr < len_base)
		ft_putchar_fd(base[nbr % len_base], fd);
	else
	{
		ft_putnbr_base_fd(nbr / len_base, base, fd);
		ft_putchar_fd(base[nbr % len_base], fd);
	}
}

static void	show_heap(t_heap *heap, size_t *total_size)
{
	t_block	*block;
	t_chunk	*chunk;
	int		i = 0;

	block = heap->start;
	while (block)
	{
		i++;
		chunk = block->chunk;
		while (chunk)
		{
			ft_putstr_fd("0x", 1);
			ft_putnbr_base_fd((unsigned long)(chunk->start), "0123456789ABCDEF", 1);
			ft_putstr_fd(" - ", 1);
			ft_putstr_fd("0x", 1);
			size_t size_to_add_to_total = (size_t)align_address((void *)chunk->start + chunk->size_allocated) - (size_t)chunk->start;
			ft_putnbr_base_fd((unsigned long)((size_t)align_address((void *)chunk->start + chunk->size_allocated)), "0123456789ABCDEF", 1);
			ft_putstr_fd(" : ", 1);
			ft_putnbr_base_fd(chunk->size_allocated, "0123456789", 1);
			ft_putstr_fd(" bytes\n", 1);
			*total_size += size_to_add_to_total + ALLIGN_CHUNK;
			chunk = chunk->next;
		}
		*total_size += ALLIGN_BLOCK;
		block = block->next;
	}
}

void	show_large_heap(size_t *total_size)
{
	t_large_heap	*large_heap;

	large_heap = data->large_heap;
	while (large_heap)
	{
		ft_putstr_fd("0x", 1);
		ft_putnbr_base_fd((unsigned long)(large_heap->start), "0123456789ABCDEF", 1);
		ft_putstr_fd(" - ", 1);
		ft_putstr_fd("0x", 1);
		size_t size_to_add_to_total = (size_t)align_address((void *)large_heap->start + large_heap->size_allocated) - (size_t)large_heap->start;
		ft_putnbr_base_fd((unsigned long)((size_t)align_address((void *)large_heap->start + large_heap->size_allocated)), "0123456789ABCDEF", 1);
		ft_putstr_fd(" : ", 1);
		ft_putnbr_base_fd(large_heap->size_allocated, "0123456789", 1);
		ft_putstr_fd(" bytes\n", 1);
		*total_size += size_to_add_to_total + ALLIGN_LARGE_HEAP;
		large_heap = large_heap->next;
	}
}

void	show_alloc_mem()
{
	size_t			total_size = 0;

	pthread_mutex_lock(&lock);
	if (data == NULL)
	{
		pthread_mutex_unlock(&lock);
		return ;
	}
	if (data->tiny_heap && data->tiny_heap->start && data->tiny_heap->start->chunk)
	{
		ft_putstr_fd("TINY", 1);
		ft_putstr_fd(" : ", 1);
		ft_putstr_fd("0x", 1);
		ft_putnbr_base_fd((unsigned long)(data->tiny_heap->start), "0123456789ABCDEF", 1);
		ft_putstr_fd("\n", 1);
		show_heap(data->tiny_heap, &total_size);
	}
	if (data->small_heap && data->small_heap->start && data->small_heap->start->chunk)
	{
		ft_putstr_fd("SMALL", 1);
		ft_putstr_fd(" : ", 1);
		ft_putstr_fd("0x", 1);
		ft_putnbr_base_fd((unsigned long)(data->small_heap->start), "0123456789ABCDEF", 1);
		ft_putstr_fd("\n", 1);
		show_heap(data->small_heap, &total_size);
	}
	if (data->large_heap)
	{
		ft_putstr_fd("LARGE", 1);
		ft_putstr_fd(" : ", 1);
		ft_putstr_fd("0x", 1);
		ft_putnbr_base_fd((unsigned long)(data->large_heap), "0123456789ABCDEF", 1);
		ft_putstr_fd("\n", 1);
		show_large_heap(&total_size);
	}
	ft_putstr_fd("Total : ", 1);
	ft_putnbr_base_fd(total_size, "0123456789", 1);
	ft_putstr_fd(" bytes\n", 1);
	pthread_mutex_unlock(&lock);
}
