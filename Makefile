NAME := fdf
BONUS_NAME := fdf_bonus
OBJECT_DIR := obj
BONUS_OBJECTS_DIR := obj_bonus
LIBFT_DIR := libft
INCLUDE_DIR := includes
BONUS_DIR := srcs_bonus
SRC_DIR := srcs
FILES := main.c \
		init_fdf.c \
		map_allocation.c \
		map_free.c \
		map_transform.c \
		map_validation.c \
		utils.c	\
		close_display.c \
		draw_map.c \
		frame_update.c \
		pixel_utils.c \
		line_utils.c \
		control_keys.c
BONUS_FILES := main_bonus.c \
		init_fdf_bonus.c \
		map_allocation_bonus.c \
		map_free_bonus.c \
		map_transform_bonus.c \
		map_validation_bonus.c \
		utils_bonus.c	\
		close_display_bonus.c \
		draw_map_bonus.c \
		projections_bonus.c \
		rotation_bonus.c \
		frame_update_bonus.c \
		pixel_utils_bonus.c \
		line_utils_bonus.c \
		control_keys_bonus.c
MAP ?= maps/42.fdf
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
BONUS_OBJECTS := $(addprefix $(BONUS_OBJECTS_DIR)/,$(BONUS_FILES:.c=.o))
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

$(BONUS_NAME): $(BONUS_OBJECTS) $(LIBFT_DIR)/libft.a $(MLX_PATH)
	$(CC) $(CFLAGS) $(BONUS_OBJECTS) $(LFLAGS) -o $(BONUS_NAME)

$(BONUS_OBJECTS_DIR)/%.o: $(BONUS_DIR)/%.c
	mkdir -p $(BONUS_OBJECTS_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

.PHONY: bonus
bonus: $(BONUS_NAME)

.PHONY: re
re: fclean all

.PHONY: clean
clean:
	rm -rf $(OBJECT_DIR)
	rm -rf $(BONUS_OBJECTS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MINILIBX_DIR) clean
	rm -f libmlx.dylib
	rm -f libmlx.a

.PHONY: fclean
fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

.PHONY: test
test: $(NAME)
	./$(NAME) $(MAP)

.PHONY: leak
leak: $(NAME)
	$(LEAK_TOOL) ./$(NAME) $(MAP)

