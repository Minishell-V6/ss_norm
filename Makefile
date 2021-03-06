# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/25 19:30:48 by seuyu             #+#    #+#              #
#    Updated: 2021/07/07 15:37:59 by seuyu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 				= gcc
RM				= rm -rf
CFLAGS 			= -Wall -Wextra -Werror
NAME 			= minishell

READLINE_LIB 	= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
READLINE_INC	= -I /Users/$(USER)/.brew/opt/readline/include

LIBFT		= libft.a
LIBFT_DIR	= libft

SRC_DIR 	= srcs

SRC 	= srcs/parser/cmd_split.c srcs/parser/cmd_split_utils.c \
		  srcs/parser/alloc_token.c srcs/parser/alloc_token_utils.c \
		  srcs/parser/get_parse_size.c srcs/parser/get_parse_size_utils.c \
		  srcs/parser/parser.c \
		  srcs/execute/exec.c srcs/execute/exec_func.c srcs/execute/non_builtin.c \
		  srcs/minishell.c srcs/utils.c \
		  srcs/builtin/echo.c srcs/builtin/unset.c srcs/builtin/env.c \
		  srcs/builtin/pwd.c srcs/builtin/export.c srcs/builtin/cd.c \
		  srcs/builtin/export_utils.c srcs/builtin/exit.c \
		  srcs/redirect/redirect.c srcs/redirect/redirect_check.c \
		  srcs/redirect/redir_chk.c \
	  	  srcs/err_print.c \
		  srcs/signal_handle.c \
		  srcs/getenv.c \

OBJ_DIR 	= objs
OBJ 		= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all : 		$(NAME)

$(NAME) : 	$(LIBFT) $(OBJ)
			$(CC) $(CFLAGS) -o $@ $(OBJ) $(READLINE_LIB) $(READLINE_INC) \
			$(LIBFT)

$(LIBFT) :
			cd $(LIBFT_DIR); make
			cp $(LIBFT_DIR)/$(LIBFT) ./
			mkdir -p $(OBJ_DIR)/builtin
			mkdir -p $(OBJ_DIR)/parser
			mkdir -p $(OBJ_DIR)/execute
			mkdir -p $(OBJ_DIR)/redirect

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
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
