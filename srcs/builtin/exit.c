/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 14:56:10 by seuyu             #+#    #+#             */
/*   Updated: 2021/07/07 01:17:45 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

int				check_digit(t_cmd *cmd_list)
{
	int			i;

	i = -1;
	if (cmd_list->cmdline[1].cmd[0] == '-')
		i++;
	while (cmd_list->cmdline[1].cmd[++i] != '\0')
		if (ft_isdigit(cmd_list->cmdline[1].cmd[i]) == 0)
		{
			if (cmd_list->exit_flag == 1)
			{
				cmd_list->err.code = 4;
				cmd_list->err.idx = 1;
				print_errstr(cmd_list);
				exit(-1);
			}
			else
			{
				cmd_list->err.code = 4;
				cmd_list->err.idx = 1;
				return (0);
			}
		}
	return (1);
}

void			exit_err_chk(t_cmd *cmd_list)
{
	long long	result;
	int			err_flag;

	err_flag = 0;
	if (cmd_list->exit_flag == 1)
	{
		result = ft_atoi(cmd_list->cmdline[1].cmd, &err_flag);
		if (err_flag == 1)
		{
			cmd_list->err.code = 4;
			cmd_list->err.idx = 1;
			print_errstr(cmd_list);
			exit(-1);
		}
		exit(result % 256);
	}
}

int				ft_exit(t_cmd *cmd_list)
{
	if (cmd_list->exit_flag == 1)
		printf("exit\n");
	if (cmd_list->cmdline[1].cmd != NULL)
	{
		if (check_digit(cmd_list) == 0)
			return (-1);
		if (cmd_list->cmdline[2].cmd != NULL)
		{
			cmd_list->err.code = 2;
			return (-1);
		}
	}
	else if (cmd_list->exit_flag == 1)
		exit(0);
	exit_err_chk(cmd_list);
	return (1);
}
