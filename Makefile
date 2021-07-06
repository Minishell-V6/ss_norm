# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/25 19:30:48 by djeon             #+#    #+#              #
#    Updated: 2021/07/06 17:52:50 by sejpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#CC 				= gcc
CC 				= gcc -g -fsanitize=address
RM				= rm -rf
CFLAGS 			= -Wall -Wextra -Werror
NAME 			= minishell

#READLINE_LIB 	= -lreadline -L/usr/local/opt/readline/lib
#READLINE_INC	= -I/usr/local/opt/readline/include

READLINE_LIB 	= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
READLINE_INC	= -I /Users/$(USER)/.brew/opt/readline/include

LIBFT		= libft.a
LIBFT_DIR	= libft

SRC_DIR 	= srcs

#SRC			= $(shell find $(SRC_DIR) -name '*.c')
SRC 	= srcs/parser/cmd_split.c srcs/parser/cmd_split_utils.c \
		  srcs/parser/alloc_token.c srcs/parser/alloc_token_utils.c \
		  srcs/parser/get_parse_size.c srcs/parser/get_parse_size_utils.c \
		  srcs/parser/parser.c \
		  srcs/minishell.c srcs/utils.c srcs/exec.c \
	  	  srcs/error_management.c srcs/ft_cd.c srcs/ft_exit.c \
		  srcs/ft_env.c srcs/ft_pwd.c srcs/ft_export.c srcs/export_utils.c \
		  srcs/signal_handle.c \
		  srcs/redir_chk.c srcs/ft_getenv.c \
		  srcs/redirect.c srcs/redirect_check.c \
		  srcs/ft_echo.c srcs/unset.c

OBJ_DIR 	= objs
OBJ 		= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all : 		$(NAME)

$(NAME) : 	$(LIBFT) $(OBJ)
			$(CC) $(CFLAGS) -o $@ $(OBJ) $(READLINE_LIB) $(READLINE_INC) \
			$(LIBFT)

$(LIBFT) :
			cd $(LIBFT_DIR); make
			cp $(LIBFT_DIR)/$(LIBFT) ./

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
			mkdir -p $(OBJ_DIR)
			mkdir -p $(OBJ_DIR)/parser 
			$(CC) $(CFLAGS) -c $< -o $(<:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) \
			$(READLINE_INC)

clean :
			cd $(LIBFT_DIR); make clean
			$(RM) $(OBJ) $(OBJ_DIR)

fclean : 	clean
			cd $(LIBFT_DIR); make fclean
			$(RM) $(NAME) $(LIBFT)

re : 		fclean all

.PHONY :	all clean fclean
