NAME := fdf
OBJECT_DIR := obj
LIBFT_DIR := libft
INCLUDE_DIR := includes
SRC_DIR := srcs
FILES := main.c \
		init_fdf.c \
		map_validation.c \
		map_allocation.c \
		utils.c	\
		close_display.c \
		frame_animation_update.c \
		render_utils.c \
		control_keys.c
SRCS := $(addprefix $(SRC_DIR)/, $(FILES))
TESTER := maps/42.fdf
UNAME := $(shell uname)
ifeq ($(UNAME),Darwin)
	MINILIBX_DIR := minilibx-macos
	MLX_PATH := $(MINILIBX_DIR)/libmlx.dylib
	LFLAGS := -L$(MINILIBX_DIR) -lmlx -framework OpenGL -framework Appkit -lz -L$(LIBFT_DIR) -lft -lm
	LEAK_TOOL := leaks -atExit --
else
	MINILIBX_DIR := minilibx-linux
	MLX_PATH := $(MINILIBX_DIR)/libmlx.a
	LFLAGS := $(MLX_PATH) -lX11 -lXext -L$(LIBFT_DIR) -lft -lm
	LEAK_TOOL := valgrind --leak-check=full
endif

CFLAGS := -Wall -Wextra -Werror -g
IFLAGS := -I$(MINILIBX_DIR) -I$(LIBFT_DIR) -I$(INCLUDE_DIR)
OBJECTS := $(addprefix $(OBJECT_DIR)/,$(FILES:.c=.o))
CC := cc

.PHONY: all 
all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT_DIR)/libft.a $(MLX_PATH)
	$(CC) $(CFLAGS) $(OBJECTS) $(LFLAGS) -o $(NAME)

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_PATH):
	$(MAKE) -C $(MINILIBX_DIR)
	cp $(MLX_PATH) .

$(OBJECT_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJECT_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@ 

.PHONY: re
re: fclean all

.PHONY: clean
clean:
	rm -rf $(OBJECT_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MINILIBX_DIR) clean
	rm -f libmlx.dylib
	rm -f libmlx.a

.PHONY: fclean
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

.PHONY: test
test: $(NAME)
	./$(NAME) ./$(TESTER)

.PHONY: leak
leak: $(NAME)
	$(LEAK_TOOL) ./$(NAME) ./$(TESTER)

