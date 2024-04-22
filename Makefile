CC=gcc

CFLAGS= -Wall -Wextra -Werror -fPIC -g

SRC=	src/malloc/malloc.c \
		src/malloc/init_struct.c \
        src/malloc/allocate.c \
		src/realloc/realloc.c \
		src/realloc/find_old_area_copy_and_free.c \
		src/free/free.c \
		src/free/delete.c \
		src/free/link_new_unused_user_space_and_defragment.c \
		src/utils/show_alloc_mem.c \
		src/utils/find_used_user_space_ptr.c \
		src/utils/search_free_space.c \
		src/utils/free_all.c \
		src/utils/link.c \
		src/utils/unlink.c


OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
SRC_TEST= $(SRC) src/main.c
OBJ_TEST = $(addprefix $(OBJ_DIR)/, $(SRC_TEST:.c=.o))

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

test: $(OBJ_TEST)
	$(CC) $(CFLAGS) -o test $(OBJ_TEST)

clean:
	rm -f $(OBJ) $(OBJ_TEST) libft_malloc_$(HOSTTYPE).so test

fclean: clean
	rm -rf libft_malloc.so obj

re: fclean all

.PHONY: all clean fclean re test

#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)