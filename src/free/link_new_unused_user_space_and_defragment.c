#include "../../include/mem.h"

static void defragment(t_user_space *new_unused_user_space) 
{
	t_user_space *prev = new_unused_user_space->prev;
	t_user_space *next = new_unused_user_space->next;

	if (prev != NULL)
	{
		if (prev->parent_block == new_unused_user_space->parent_block)
		{
			prev->size_allocated += new_unused_user_space->size_allocated;
			prev->next = next;
			if (next != NULL)
				next->prev = prev;
			defragment(prev);
		}
	}
	if (next != NULL && new_unused_user_space != NULL)
	{
		if (new_unused_user_space->parent_block == next->parent_block)
		{
			new_unused_user_space->size_allocated += next->size_allocated;
			new_unused_user_space->next = next->next;
			if (next->next != NULL)
				next->next->prev = new_unused_user_space;
			defragment(new_unused_user_space);
		}
	}
}

static void link_after_current(t_user_space *used_user_space, t_user_space *current_unused_user_space)
{
	if (current_unused_user_space == NULL)
	{
		used_user_space->next = NULL;
		used_user_space->prev = NULL;
		used_user_space->parent_block->unused_user_space = used_user_space;
		return ;
	}
	else
	{
		used_user_space->next = current_unused_user_space->next;
		used_user_space->prev = current_unused_user_space;
		if (current_unused_user_space->next != NULL)
			current_unused_user_space->next->prev = used_user_space;
		current_unused_user_space->next = used_user_space;
	}
}

static void link_before_current(t_user_space *used_user_space, t_user_space *current_unused_user_space)
{
	used_user_space->prev = current_unused_user_space->prev;
	used_user_space->next = current_unused_user_space;
	if (current_unused_user_space->prev != NULL)
		current_unused_user_space->prev->next = used_user_space;
	else
		used_user_space->parent_block->unused_user_space = used_user_space;
	current_unused_user_space->prev = used_user_space;
}

void link_new_unused_user_space_and_defragment(t_user_space *used_user_space)
{
	bool			add_after = false;
	t_user_space	*current_unused_user_space;

	// find position of new unused_user_space in unused_user_space ( sorted by memory address, from smallest to largest memory address)
	current_unused_user_space =  used_user_space->parent_block->unused_user_space;
	if (current_unused_user_space != NULL)
	{
		if (used_user_space->start_user_space > current_unused_user_space->start_user_space)
			add_after = true;
		while (used_user_space->start_user_space > current_unused_user_space->start_user_space && current_unused_user_space->next != NULL)
			current_unused_user_space = current_unused_user_space->next;
	}
	else
		add_after = true; // if unused_user_space is empty, unused_user_space becomes the first unused_user_space

	if (add_after == true)
		link_after_current(used_user_space, current_unused_user_space);
	else
		link_before_current(used_user_space, current_unused_user_space);
	if (data->error)
		return ;
		
	// defragement (combine new unused_free_space if possible)
	defragment(used_user_space);
}
