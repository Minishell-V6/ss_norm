/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_builtin.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:17:37 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/06 20:34:00 by sejpark          ###   ########.fr       */
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

extern int g_exit_status;
int		non_builtin_exec(t_cmd *cmd_list, char *argv[], char **envp,
						char *path, int fds[]);
int		non_builtin(t_cmd *cmd_list, char *argv[], char **envp, int fds[]);

#endif
