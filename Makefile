CC=gcc

CFLAGS= -Wall -Wextra -Werror -fPIC -g

SRC=	src/main.c \
		src/malloc/malloc.c \
		src/malloc/init_struct.c \
        src/malloc/allocate.c \
		src/realloc/realloc.c \
		src/realloc/find_old_area_copy_and_free.c \
		src/free/free.c \
		src/free/delete.c \
		src/free/delink.c \
		src/utils/show_alloc_mem.c \
		src/utils/find_ptr.c \
		src/utils/search_free_space.c \
		src/utils/free_all.c


OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

all: libft_malloc_$(HOSTTYPE).so
	ln -sf libft_malloc_$(HOSTTYPE).so libft_malloc.so

libft_malloc_$(HOSTTYPE).so: $(OBJ)
	$(CC) $(CFLAGS) -shared -o $@ $(OBJ)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

test: libft_malloc_$(HOSTTYPE).so
	$(CC) $(CFLAGS) -L. -lft_malloc -o test src/main.c

clean:
	rm -f $(OBJ) libft_malloc_$(HOSTTYPE).so test 

fclean: clean
	rm -rf libft_malloc.so obj

re: fclean all

#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)