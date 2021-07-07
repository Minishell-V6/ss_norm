/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_builtin.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:17:37 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/07 10:04:51 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NON_BUILTIN_H
# define NON_BUILTIN_H
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include "structs.h"
# include "ft_getenv.h"
# include "utils.h"

extern int		g_exit_status;
typedef struct	s_nonbuiltin
{
	struct stat	*buf;
	char		*env_path;
	char		**paths;
	char		*tmp;
	int			i;
	int			flag;
}				t_nonbuiltin;
typedef struct	s_ae
{
	char		**argv;
	char		**envp;
}				t_ae;
int				non_builtin_exec(t_cmd *cmd_list, t_ae t_ae_data, char *path,
									int fds[]);
int				non_builtin(t_cmd *cmd_list, char *argv[], char **envp,
									int fds[]);

#endif
