/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_builtin.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:17:37 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/06 22:36:58 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NON_BUILTIN_H
# define NON_BUILTIN_H
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include "structs.h"
# include "getenv.h"
# include "utils.h"

extern int g_exit_status;
int		non_builtin_exec(t_cmd *cmd_list, char *argv[], char **envp,
						char *path, int fds[]);
int		non_builtin(t_cmd *cmd_list, char *argv[], char **envp, int fds[]);

#endif
