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
	t_user_space	*user_space;

	block = heap->start_block;
	while (block)
	{
		user_space = block->used_user_space;
		while (user_space)
		{
			ft_putstr_fd("0x", 1);
			ft_putnbr_base_fd((unsigned long)(user_space->start_user_space), "0123456789ABCDEF", 1);
			ft_putstr_fd(" - ", 1);
			ft_putstr_fd("0x", 1);
			ft_putnbr_base_fd((unsigned long)(user_space->start_user_space + (size_t)align_address((void *)user_space->start_user_space + user_space->size_allocated)), "0123456789ABCDEF", 1);
			ft_putstr_fd(" : ", 1);
			ft_putnbr_base_fd(user_space->size_allocated, "0123456789", 1);
			ft_putstr_fd(" bytes\n", 1);
			*total_size += user_space->size_allocated;
			user_space = user_space->next;
		}
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
		ft_putnbr_base_fd((unsigned long)(large_heap->start_user_space), "0123456789ABCDEF", 1);
		ft_putstr_fd(" - ", 1);
		ft_putstr_fd("0x", 1);
		ft_putnbr_base_fd((unsigned long)(large_heap->start_user_space + large_heap->size_allocated), "0123456789ABCDEF", 1);
		ft_putstr_fd(" : ", 1);
		ft_putnbr_base_fd(large_heap->size_allocated, "0123456789", 1);
		ft_putstr_fd(" bytes\n", 1);
		*total_size += large_heap->size_allocated;
		large_heap = large_heap->next;
	}
}

void	show_alloc_mem()
{
	size_t			total_size = 0;

	if (data == NULL)
		return ;
	if (data->tiny_heap)
	{
		ft_putstr_fd("TINY", 1);
		ft_putstr_fd(" : ", 1);
		ft_putstr_fd("0x", 1);
		ft_putnbr_base_fd((unsigned long)(data->tiny_heap->start_block), "0123456789ABCDEF", 1);
		ft_putstr_fd("\n", 1);
		show_heap(data->tiny_heap, &total_size);
	}
	if (data->small_heap)
	{
		ft_putstr_fd("SMALL", 1);
		ft_putstr_fd(" : ", 1);
		ft_putstr_fd("0x", 1);
		ft_putnbr_base_fd((unsigned long)(data->small_heap->start_block), "0123456789ABCDEF", 1);
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
}
