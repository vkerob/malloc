#include "../../include/mem.h"

void defragment(t_free_area *free_area, size_t heap_size) 
{
	t_free_area *prev = free_area->prev;
	t_free_area *next = free_area->next;

	if (prev != NULL)
	{
		if (prev->ptr_defragment - heap_size < free_area->ptr_defragment)
		{
			free_area->free_size += prev->free_size;
			free_area->start_free_area = prev->start_free_area;
			free_area->ptr_defragment = prev->ptr_defragment;
			free_area->prev = prev->prev;
			munmap(prev, sizeof(t_free_area));
			defragment(free_area, heap_size);
		}
	}

	if (next != NULL && free_area != NULL)
	{
		if (free_area->ptr_defragment - heap_size < next->ptr_defragment)
		{
			free_area->free_size += next->free_size;
			free_area->next = next->next;
			if (next->next != NULL)
				next->next->prev = free_area;
			munmap(next, sizeof(t_free_area));
			defragment(free_area, heap_size);
		}
	}
}

//---------------------------------------------------------------add_free_area utils---------------------------------------------------------------//

static void link_after_current(t_free_area *free_area_current, t_free_area *free_area_add)
{
	free_area_add->next = free_area_current->next;
	if (free_area_current->next != NULL)
		free_area_current->next->prev = free_area_add;
	if (free_area_current == NULL)
		free_area_add->parent_heap->free_area = free_area_add;
	else
		free_area_add->prev = free_area_current;
}

static void link_before_current(t_free_area *free_area_current, t_free_area *free_area_add)
{
	free_area_add->prev = free_area_current->prev;
	if (free_area_current->prev != NULL)
		free_area_current->prev->next = free_area_add;
	else
		free_area_add->parent_heap->free_area = free_area_add;
	free_area_add->next = free_area_current;
}

static void initialize_new_free_area(t_user_space *user_space, t_free_area **free_area_add, t_free_area *free_area_current, bool add_after)
{
	*free_area_add = mmap(NULL, sizeof(t_free_area), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (*free_area_add == MAP_FAILED)
	{
		data->error = true;
		return ;
	}
	(*free_area_add)->start_free_area = user_space->start_user_space;
	(*free_area_add)->ptr_defragment = user_space->ptr_defragment;
	(*free_area_add)->parent_heap = user_space->parent_block->parent_heap;
	(*free_area_add)->free_size = user_space->size_allocated;

	// link new free_area
	if (add_after == true)
		link_after_current(free_area_current, *free_area_add);
	else
		link_before_current(free_area_current, *free_area_add);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------//

// add free_area before or after free_area_current and defragment
void add_free_area_and_defragment(t_user_space *user_space)
{
	t_free_area	*free_area_current; // free_area_current is the free_area who will be after or before free_area_add
	t_free_area	*free_area_add;
	bool			add_after = false;

	// find position of new free_area in free_area ( sorted by memory address, from largest to smallest memory address)
	free_area_current = user_space->parent_block->parent_heap->free_area;
	if (free_area_current != NULL)
	{
		if (user_space->start_user_space < free_area_current->start_free_area)
			add_after = true;
		while (user_space->start_user_space > free_area_current->start_free_area && free_area_current->next != NULL)
			free_area_current = free_area_current->next;
	}
	else
		add_after = true; // if free_area is empty, free_area becomes the first free_area

	// create new free_area
	initialize_new_free_area(user_space, &free_area_add, free_area_current, add_after);
	if (data->error)
		return ;

	// defragement (combine free_area if possible)
	defragment(free_area_add, free_area_add->parent_heap->size);
}
