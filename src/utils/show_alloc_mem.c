#include "../../include/mem.h"



static void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

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
		user_space = block->user_space;
		while (user_space)
		{
			ft_putstr_fd("0x", 1);
			ft_putnbr_base_fd((unsigned long)(user_space->start_user_space), "0123456789ABCDEF", 1);
			ft_putstr_fd(" - ", 1);
			ft_putstr_fd("0x", 1);
			ft_putnbr_base_fd((unsigned long)(user_space->start_user_space + user_space->size_allocated), "0123456789ABCDEF", 1);
			ft_putstr_fd(" : ", 1);
			ft_putnbr_base_fd(user_space->size_allocated, "0123456789", 1);
			ft_putstr_fd(" bytes\n", 1);
			*total_size += user_space->size_allocated;
			user_space = user_space->next;
		}
		block = block->next;
	}
}

void	show_alloc_mem()
{
	t_heap_large	*large_heap;
	size_t			total_size = 0;
	
	if (data->tiny_heap)
	{
		ft_putstr_fd("TINY\n", 1);
		show_heap(data->tiny_heap, &total_size);
	}
	if (data->small_heap)
	{
		ft_putstr_fd("SMALL\n", 1);
		show_heap(data->small_heap, &total_size);
	}
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
		total_size += large_heap->size_allocated;
		large_heap = large_heap->next;
	}

	ft_putstr_fd("Total : ", 1);
	ft_putnbr_base_fd(total_size, "0123456789", 1);
	ft_putstr_fd(" bytes\n", 1);

}