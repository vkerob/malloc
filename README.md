
# Malloc

The project, as defined by school 42, aims to implement the malloc function from the standard libc library.

WARNING! This implementation is not that of the libc; it only follows certain principles and is therefore simplified.\
If you want to see what the libc implementation looks like, a link is provided in the Documentation section.

## More details on the structures

Here is a detailed description of the structures:

Three structures are used to manage allocations of small, medium, and large memory sizes: tiny_heap, small_heap, and large_heap. (large_heap being different, the first two points do not apply to it)
- Each structure contains a linked list of blocks.
- Each block consists of a linked list of user spaces.
- As for large_heap, it's a linked list where each link already contains the user space.

### large_heap

Here is what concerns the general information of the structures. Now, here are more details about each of them.

As for large_heap, it has its own type because it is unique. It has neither user space nor block due to the size its allocations can reach (> 2048 bytes).
```c
typedef struct large_heap
{
	void				*start_user_space;
	size_t				size_allocated;
	struct large_heap	*next;
	struct large_heap	*prev;
}				t_large_heap;
```
- start_user_space is the pointer to the beginning of the reserved space.
- size_allocated is the size of the reserved space.

### tiny/small_heap

tiny_heap and small_heap are both of type heap. Allocations from tiny_heap must be less than or equal to 128 bytes, and for small_heap, they must be less than or equal to 2048 bytes.

The reason for this is that each block must be able to contain at least 100 allocations, and the size of tiny_heap is 16384 bytes while that of small_heap is 262144 bytes.
```c
typedef struct heap
{
	size_t				size;
	struct block		*start_block;
}				t_heap;
```
- size represents its size (tiny/small heap).
- start_block is a pointer to the first block.

### block

The blocks are exclusively contained either in tiny_heap or in small_heap.

```c
typedef struct block
{
	struct user_space	*used_user_space;
	struct heap			*parent_heap;
	size_t				free_size;
	size_t				size_after;
	struct block		*next;
	struct block		*prev;
	
}				t_block;
```
- user_space is a pointer to the first user_space.
- parent_heap is a pointer to its heap (tiny_heap or small_heap).
- free_size is the total remaining free space within it.
- size_after is the space between it and the next block or user_space.

### user_space

The user_spaces are exclusively contained within blocks.

```c
typedef struct user_space
{
	void				*start_user_space;
	size_t				size_after;
	size_t				size_allocated;
	struct block		*parent_block;
	struct user_space	*next;
	struct user_space	*prev;
}				t_user_space;
```
- start_user_space is the pointer to the beginning of the reserved space.
- size_allocated is the size of the reserved space.
- size_after is the space between it and the next block or user_space.
- parent_block is a pointer to its block.


The data structure being quite self-explanatory, I won't detail it here. (See mem.h)

## More details on the search free_space function

Why this function? Understanding it will help in understanding the others.

In broad strokes, as its name suggests, its purpose is to search for free space.\
Next, I'll delve into the complexity of the function, which involves assigning size_to_add_to_align_address.

An important point to note is that the memory I'm using (mmap) must be aligned with the rest.\
Let me explain: in memory, for performance reasons mainly related to memory access, alignment must be done.\
If you want more information, go to the Documentation section. Furthermore, I've aligned this on 16, but this might not be the right alignment depending on your processor, etc...

Before coming back to size_to_add_to_align_address, here's what the memory could look like:
```
general view:
+----------------+------------------+---------------+----------+------------------+
|     block      | used_user_space1 | ask space(10) | align(6) | used_user_space2 | 
+----------------+------------------+---------------+----------+------------------+
^                ^        ^         ^               ^          ^                  ^
|                |        |         |               |          |                  |
0                48     struct      96              106        112                160
```
As we can see, I had to align after the requested space, and size_to_add_to_align_address represents this alignment that I will have to perform.

To calculate this alignment, I first started from the end of used_user_space1, which represents "start_user_space" (for example: 0x7ffff7fb6060). Then, I added the requested space (10) and called the align_address function, which rounds up to the nearest alignment. Finally, I subtracted the same thing without calling the function.

This results in (0x7ffff7fb6060 + 10 + 6) - (0x7ffff7fb6060 + 10) = 6 in our case.

I deliberately omitted the alignment of struct block (ALIGN_BLOCK) or user_space (ALIGN_USER_SPACE) for clarity.

###
```c
bool	search_free_space(t_heap *heap, size_t size)
{
	t_block			*block;
	t_user_space	*before_new_used_user_space;
	size_t			size_to_add_to_align_address;


	if (heap == NULL)
		return (NULL);
	block = heap->start_block;
	while (block)
	{

		// if after the block there is enough space to allocate the size
		if (block->free_size >= size)
		{
			size_to_add_to_align_address = (size_t)align_address((void *)block + ALLIGN_BLOCK + size) - (size_t)block - ALLIGN_BLOCK - size;
			if (block->size_after >= size + size_to_add_to_align_address + ALLIGN_USER_SPACE)
			{
				set_new_used_user_space(block, size, size_to_add_to_align_address, 1); // block->used_user_space = new_used_user_space
				return (true);
			}

			// if after a used_user_space there is enough space to allocate the size
			before_new_used_user_space = block->used_user_space;
			while (before_new_used_user_space)
			{
				size_to_add_to_align_address = (size_t)align_address((void *)before_new_used_user_space->start_user_space + ALLIGN_USER_SPACE + size) - (size_t)before_new_used_user_space->start_user_space - ALLIGN_USER_SPACE - size;
				if (before_new_used_user_space->size_after >= size + size_to_add_to_align_address + ALLIGN_USER_SPACE)
				{
					set_new_used_user_space(before_new_used_user_space, size, size_to_add_to_align_address, 0);
					return (true);
				}
				before_new_used_user_space = before_new_used_user_space->next;
			}
		}
		block = block->next;
	}
	return (false);
}
```

## Documentation

[memory alignement](https://fr.wikipedia.org/wiki/Alignement_en_m%C3%A9moire)\
[Memory Alignment and Performance](https://fylux.github.io/2017/07/11/Memory_Alignment/)\
[struct memory alignement](https://en.wikipedia.org/wiki/Data_structure_alignment)\
[libc](https://code.launchpad.net/~adconrad/glibc/+git/glibc)
