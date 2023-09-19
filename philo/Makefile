# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/18 19:17:24 by rdelicad          #+#    #+#              #
#    Updated: 2023/09/19 08:55:37 by rdelicad         ###   ########.fr        #
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

# --- Name & flags ---

NAME      := philo

CC        := gcc

CFLAGS    := -g -Wall -Wextra -Werror -pthread

# --- Library ---



# --- Files ---

SRCS      := leaks.c philo.c utils_philo.c

OBJS = $(addprefix obj/,$(SRCS:.c=.o))



# --- Rules ---

$(NAME): $(OBJS) $(LIBFT_PATH) $(MLX_PATH)
	@echo "$(YELLOW)$(BOLD)Compiling philo...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_PATH) $(LIBFT_PATH) $(LIB_SYS) -o $(NAME)
	@echo "$(GREEN)$(BOLD)Done.$(RESET)"


$(OBJS) : obj/%.o: src/%.c $(FOLDER)
	@$(CC) $(CFLAGS) -c $< -o $@


$(FOLDER):
	mkdir obj


all: $(NAME)

bonus : $(NAME_BONUS)

clean:
	@echo "$(RED)$(BOLD)Cleaning objects from program...$(RESET)"
	@rm -f $(OBJS) 
	@echo "$(GREEN)$(BOLD)Done.$(RESET)"
	@make clean -s -C $(MLX_DIR)
	@make clean -s -C $(LIBFT_DIR)

fclean:
	@echo "$(RED)$(BOLD)Cleaning all files from program...$(RESET)"
	@rm -f $(NAME) $(OBJS)
	

re: fclean all

solong: all clean

.PHONY: all re fclean clean philo
