/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 19:39:32 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/06 22:00:59 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "exec_func.h"

typedef	struct	s_exec
{
	int			fds[2];
	int			status;
	pid_t		pid;
	int			tmp;
}				t_exec;
int				exec(t_cmd *cmd_list, char *argv[], char **envp[]);

#endif
