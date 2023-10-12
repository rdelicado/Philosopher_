# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/18 19:17:24 by rdelicad          #+#    #+#              #
#    Updated: 2023/10/12 13:48:58 by rdelicad         ###   ########.fr        #
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

NAME      := philo_bonus

CC        := gcc

CFLAGS    := -g -Wall -Wextra -Werror -pthread -fsanitize=thread

# --- Library ---



# --- Files ---

SRCS      := leaks.c philo.c utils_philo.c utils_phtreads.c utils_simulator.c\
			utils_rutine.c create_processes.c 

OBJS = $(addprefix obj/,$(SRCS:.c=.o))



# --- Rules ---

$(NAME): $(OBJS)
	@echo "$(YELLOW)$(BOLD)Compiling philo_bonus...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(BOLD)Done.$(RESET)"


$(OBJS) : obj/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@


all: $(NAME)

clean:
	@echo "$(RED)$(BOLD)Cleaning objects from program...$(RESET)"
	@rm -f $(OBJS) 
	@echo "$(GREEN)$(BOLD)Done.$(RESET)"

fclean:
	@echo "$(RED)$(BOLD)Cleaning all files from program...$(RESET)"
	@rm -f $(NAME) $(OBJS)
	@echo "$(GREEN)$(BOLD)Done.$(RESET)"
	

re: fclean all

.PHONY: all re fclean clean
