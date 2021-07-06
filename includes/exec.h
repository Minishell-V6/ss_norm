/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 19:39:32 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/06 20:20:59 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "exec_func.h"

int				non_builtin_exec(t_cmd *cmd_list, char *argv[], char **envp, char *path, int fds[]);
int				non_builtin(t_cmd *cmd_list, char *argv[], char **envp, int fds[]);
int				exec(t_cmd *cmd_list, char *argv[], char **envp[]);

#endif
