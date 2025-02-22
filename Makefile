# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 13:03:13 by oezzaou           #+#    #+#              #
#    Updated: 2022/12/16 18:16:19 by oezzaou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#====<[ CC compiler: ]>=========================================================
CC 						:= cc
CFLAGS 				:= -Wall -Wextra -Werror
RM						:= rm -rf

#====<[ Colors: ]>==============================================================
GREEN					= \033[1;32m
RED						= \033[1;31m
BLUE					= \033[34m
CYAN					= \033[1;36m
GRAY					= \033[0;90m
PURPLE				= \033[0;35m
YELLOW				= \033[0;93m
BLACK  				= \033[20m
MAGENTA 			= \033[35m
WHITE  				= \033[37m
PINK					= \033[0;38;5;199m
ORANGE 				= \033[38;5;214m
LIGHT_BLACK  	= \033[90m
LIGHT_RED    	= \033[91m
LIGHT_GREEN  	= \033[92m
LIGHT_YELLOW 	= \033[93m
LIGHT_BLUE   	= \033[94m
LIGHT_MAGENTA = \033[95m
LIGHT_CYAN   	= \033[96m
LIGHT_WHITE  	= \033[97m
LIGHT_BLUE		= \033[38;5;45m
RESET					= \033[1;0m

#===<[ Sources: ]>==============================================================
PROJECT				:= Pipex
NAME 					:= pipex
OBJ_DIR				:= obj
SRC_DIR				:= src
FT_PRINTF			:= ft_printf
LIBFTPRINTF		:= $(FT_PRINTF)/libftprintf.a 
INCLUDE 			:= -Iinclude -I$(FT_PRINTF)/include -I$(FT_PRINTF)/libft/include

SRC						:= pipex.c pipex_parser.c pipex_clear.c pipex_here_doc.c

OBJ						:= $(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(basename $(SRC))))
SRC						:= $(addprefix $(SRC_DIR)/, $(SRC))

#====<[ Rules: ]>===============================================================
all: $(NAME) 

$(NAME): $(FT_PRINTF) $(OBJ) 
	@$(CC) $(CFLAGS) $(INCLUDE) $(filter-out $<, $^) $(LIBFTPRINTF) -o $@
	@echo "${GREEN}[OK]: ${CYAN}$(NAME) ✔️${RESET}"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | .create_dir 
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "$(GREEN)[OK]${RESET}: ${PINK}Compiling${RESET} %-26s| $@\n" "$<"

$(FT_PRINTF):
	@make -C $@ all

bonus: all

test:
	./$(NAME) "file1" "./hello world.sh" "cat -e" "file2" && cat file2

clean: 
	@make -C $(FT_PRINTF) fclean
	@if [ -d $(OBJ_DIR) ]; then\
		${RM} $(OBJ_DIR);\
		printf "${GREEN}[OK]${RESET}: ${ORANGE}Cleaning  %-26s${RESET}| ./%s\n"\
					 "... " "$(PROJECT)/$(OBJ_DIR) ✔️";\
	else\
		printf "${RED}[KO]${RESET}: ${BLUE}Not Found %-26s${RESET}| ./%s\n"\
					 "..." "$(PROJECT)/$(OBJ_DIR) ✖️";\
	fi

fclean: clean
	@if [ -f $(NAME) ]; then\
		${RM} $(NAME);\
		printf "${GREEN}[OK]${RESET}: ${ORANGE}Cleaning  %-26s${RESET}| ./%s\n"\
					 "... " "$(PROJECT)/$(NAME) ✔️";\
	fi

re : fclean all

$(OBJ_DIR):
	@mkdir -p $@

.create_dir: $(OBJ_DIR)

.PHONY: all clean fclean re test $(FT_PRINTF)
#===============================================================================
