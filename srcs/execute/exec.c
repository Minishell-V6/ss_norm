/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 18:06:01 by seuyu             #+#    #+#             */
/*   Updated: 2021/07/07 15:37:59 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_recur(t_cmd *cmd_list, char *argv[], char **envp[],
				t_exec *t_exec_data)
{
	pid_t wpid;

	if (t_exec_data->pid == 0)
	{
		dup2(t_exec_data->fds[0], 0);
		close(t_exec_data->fds[0]);
		close(t_exec_data->fds[1]);
		g_exit_status = exec(cmd_list->next, argv, envp);
		exit(g_exit_status);
	}
	else
	{
		close(t_exec_data->fds[1]);
		close(t_exec_data->fds[0]);
		wpid = waitpid(t_exec_data->pid, &(t_exec_data->status), 0);
		g_exit_status = t_exec_data->status >> 8;
		return (g_exit_status);
	}
}

int	exec(t_cmd *cmd_list, char *argv[], char **envp[])
{
	t_exec	t_exec_data;

	pipe(t_exec_data.fds);
	if ((t_exec_data.tmp = exec_function(cmd_list, argv, envp, t_exec_data.fds))
			== -1)
		print_errstr(cmd_list);
	else if (t_exec_data.tmp == 1)
		g_exit_status = 0;
	dup2(100, STDOUT);
	dup2(101, STDIN);
	if (cmd_list->pipe_flag == 1)
	{
		if ((t_exec_data.pid = fork()) < 0)
		{
			cmd_list->err.code = 1;
			print_errstr(cmd_list);
			return (g_exit_status);
		}
	}
	else
		return (g_exit_status);
	return (exec_recur(cmd_list, argv, envp, &t_exec_data));
}
