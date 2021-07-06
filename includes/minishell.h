/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 19:54:23 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/06 20:36:40 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include "../libft/libft.h"
# include "structs.h"
# include "alloc_token.h"
# include "builtin.h"
# include "parser.h"
# include "exec.h"


# define STDIN 			0
# define STDOUT 		1
# define STDERR 		2

extern int	g_exit_status;
void		print_errstr(t_cmd *cmd_list);
//int			exec_function(t_cmd *cmd_list, char *argv[], char **envp[], int fds[]);
//char		*strjoin_path(char const *s1, char const *s2);
//int			check_whitespace(char *line);
//int			exec(t_cmd *cmp_list, char *argv[], char **envp[]);
//void		free_list(t_cmd *cmd_list);

//signal
void		set_signal(void);

//redirect
int					redirect(t_cmd *cmd_list, int **fds, int *last_index);
int					redirect_check(t_cmd *cmd_list, int **fds);
#endif