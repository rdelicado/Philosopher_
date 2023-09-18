# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/18 19:17:24 by rdelicad          #+#    #+#              #
#    Updated: 2023/09/18 19:17:29 by rdelicad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Colors ---

BOLD      := \033[1m
BLACK     := \033[30;1m
RED       := \033[31;1m
GREEN     := \033[32;1m
YELLOW    := \033[33;1m
BLUE      := \033[34;1m
MAGENTA   := \033[35;1m
CYAN      := \033[36;1m
WHITE     := \033[37;1m
RESET     := \033[0m

NAME      := so_long
NAME_BONUS:= so_long_bonus

CC        := gcc

CFLAGS    := -g -Wall -Wextra -Werror

# --- Library ---

LIB       := ar rcs

FOLDER = obj
FOLDER_BONUS = objb

LIBFT_DIR := ./libft
LIBFT_PATH := $(LIBFT_DIR)/libft.a

MLX_DIR   := ./MLX42
MLX_PATH  := $(MLX_DIR)/libmlx42.a

LIB_SYS   := -Iinclude -lglfw -L "/Users/rdelicad/.brew/opt/glfw/lib/"

# --- Files ---

SRCS      := leaks.c so_long.c utils_struct.c utils_read_map.c utils_check_map.c\
			utils_flood_fill.c utils_main_game.c utils_img.c\
			utils_accion_player.c 

SRCS_BONUS := leaks.c so_long_bonus.c struct_bonus.c read_map_bonus.c check_map_bonus.c\
			flood_fill_bonus.c main_game_bonus.c img_bonus.c\
			accion_player_bonus.c img_accion_bonus.c moves_game_bonus.c

OBJS = $(addprefix obj/,$(SRCS:.c=.o))

OBJS_BONUS = $(addprefix objb/,$(SRCS_BONUS:.c=.o))

# --- Rules ---

$(NAME): $(OBJS) $(LIBFT_PATH) $(MLX_PATH)
	@echo "$(YELLOW)$(BOLD)Compiling so_long...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_PATH) $(LIBFT_PATH) $(LIB_SYS) -o $(NAME)
	@echo "$(GREEN)$(BOLD)Done.$(RESET)"

$(NAME_BONUS) : $(OBJS_BONUS) $(LIBFT_PATH) $(MLX_PATH)
	@echo "$(YELLOW)$(BOLD)Compiling bonus...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(MLX_PATH) $(LIBFT_PATH) $(LIB_SYS) -o $(NAME_BONUS)
	@echo "$(GREEN)$(BOLD)Done.$(RESET)"

$(OBJS) : obj/%.o: src/%.c $(FOLDER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_BONUS) : objb/%.o : srcb/%.c $(FOLDER_BONUS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_PATH):
	@make -s -C $(LIBFT_DIR)
	@make bonus -s -C $(LIBFT_DIR)

$(MLX_PATH):
	@make -s -C $(MLX_DIR)

$(FOLDER):
	mkdir obj

$(FOLDER_BONUS):
	mkdir objb

all: $(NAME)

bonus : $(NAME_BONUS)

clean:
	@echo "$(RED)$(BOLD)Cleaning objects from program...$(RESET)"
	@rm -f $(OBJS) $(OBJS_BONUS)
	@echo "$(GREEN)$(BOLD)Done.$(RESET)"
	@make clean -s -C $(MLX_DIR)
	@make clean -s -C $(LIBFT_DIR)

fclean:
	@echo "$(RED)$(BOLD)Cleaning all files from program...$(RESET)"
	@rm -f $(NAME) $(NAME_BONUS) $(LIBFT_PATH) $(MLX_PATH) $(OBJS) $(OBJS_BONUS)
	@make fclean -s -C $(MLX_DIR)
	@make fclean -s -C $(LIBFT_DIR)

re: fclean all

solong: all clean

.PHONY: all re fclean clean solong
