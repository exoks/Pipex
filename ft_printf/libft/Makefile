# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/20 15:57:20 by oezzaou           #+#    #+#              #
#    Updated: 2025/03/01 12:24:22 by oezzaou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

#====<[ CC compiler: ]>=========================================================
CC            = cc
CFLAGS	      = -Wall -Wextra -Werror
RM            = rm -rf

#===<[ Sources: ]>==============================================================
PROJECT       := libft
STATIC_LIB    := libft.a
SHARED_LIB    := libft.so
OBJ_DIR       := obj
SRC_DIR       := src
INCLUDE       := -Iinclude 

SRC	          := ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c\
                 ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c\
                 ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c\
                 ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c\
                 ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c\
                 ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c\
                 ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c\
                 ft_substr.c ft_tolower.c ft_toupper.c ft_strcmp.c ft_strcat.c

SRC_BNS       := ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c\
                 ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c\
                 ft_lstnew.c ft_lstsize.c get_next_line.c get_next_line_utils.c

OBJ				    := $(addprefix $(OBJ_DIR)/, ${SRC:.c=.o})
SRC				    := $(addprefix $(SRC_DIR)/, $(SRC))
OBJ_BNS		    := $(addprefix $(OBJ_DIR)/, ${SRC_BNS:.c=.o})
SRC_BNS		    := $(addprefix $(SRC_DIR)/, $(SRC)) 

#====<[ Rules: ]>===============================================================
all: static 

static: $(STATIC_LIB)

shared: $(SHARED_LIB)

$(STATIC_LIB): $(OBJ) $(OBJ_BNS) 
	@ar -rcs $@ $^
	@echo "${GREEN}[OK] ${CYAN}$(STATIC_LIB) ✔️${RESET}"

$(SHARED_LIB): $(OBJ) $(OBJ_BNS) 
	@$(CC) $(CFLAGS) -shared -o $@ $^  
	@echo "${GREEN}[OK] ${CYAN}$(SHARED_LIB) ✔️${RESET}"

bonus: $(OBJ_BNS)
	@ar -rcs $(STATIC_LIB) $<
	@echo "${GREEN}[OK]: ${CYAN}$(STATIC_LIB) ✔️${RESET}"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) 
	@$(CC) $(CFLAGS) $(INCLUDE) -fPIC -c $< -o $@
	@printf "$(GREEN)[OK]${RESET} ${PINK}Compiling${RESET} %-26s| $@\n" "$<"

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@if [ -d $(OBJ_DIR) ]; then\
		${RM} $(OBJ_DIR);\
		printf "${GREEN}[OK]${RESET} ${ORANGE}Cleaning  %-26s${RESET}| ./%s\n"\
					 "... " "$(PROJECT)/$(OBJ_DIR) ✔️";\
	else\
		printf "${RED}[KO]${RESET} ${BLUE}Not Found %-26s${RESET}| ./%s\n"\
					 "..." "$(PROJECT)/$(OBJ_DIR) ✖️";\
	fi

fclean: clean
	@if [ -f $(STATIC_LIB) ]; then\
		${RM} $(STATIC_LIB);\
		printf "${GREEN}[OK]${RESET} ${ORANGE}Cleaning  %-26s${RESET}| ./%s\n"\
				 "... " "$(PROJECT)/$(STATIC_LIB) ✔️";\
	elif [ ! -f $(STATIC_LIB) ]; then\
		printf "${RED}[KO]${RESET} ${BLUE}Not Found %-26s${RESET}| ./%s\n"\
					 "..." "$(PROJECT)/$(STATIC_LIB) ✖️";\
	fi
	@if [ -f $(SHARED_LIB) ]; then\
		${RM} $(SHARED_LIB);\
		printf "${GREEN}[OK]${RESET} ${ORANGE}Cleaning  %-26s${RESET}| ./%s\n"\
				 "... " "$(PROJECT)/$(SHARED_LIB) ✔️";\
	elif [ ! -f $(SHARED_LIB) ]; then\
		printf "${RED}[KO]${RESET} ${BLUE}Not Found %-26s${RESET}| ./%s\n"\
					 "..." "$(PROJECT)/$(SHARED_LIB) ✖️";\
	fi

re: fclean all

.SUFFIXES: .o .c .a .so 

.PHONY: all static shared bonus clean fclean re
#===============================================================================
