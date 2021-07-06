/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:33:46 by seuyu             #+#    #+#             */
/*   Updated: 2021/07/06 22:33:11 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/err_print.h"

void			err_write(char *err_str, char *err_cmd, char *err_cmd2)
{
	int i;
	int j;

	i = -1;
	j = -1;
	if (err_cmdline == 0 || error_str == 0)
		return ;
	while (err_str[++i])
	{
		j = -1;
		if (err_str[i] == '%' && err_str[i + 1] == 's'\
		&& err_cmdline != 0)
		{
			while (err_cmd[++j])
				write(2, &err_cmd[j], 1);
			err_cmd = err_cmd2;
			i++;
		}
		else
			write(2, &err_str[i], 1);
	}
}

void			ft_print_unset_err(t_cmd *cmd_list)
{
	int i;

	i = 1;
	while (cmd_list->cmdline[i].cmd && cmd_list->cmdline[i].rd_flg == 0)
	{
		if (ft_valid_key(cmd_list->cmdline[i].cmd) == 0)
			err_write("minishell: %s: `%s': not a valid identifier\n", \
			cmd_list->cmdline[0].cmd, cmd_list->cmdline[i].cmd);
		i++;
	}
}

void			ft_print_export_err(t_cmd *cmd_list)
{
	int i;

	i = 1;
	while (cmd_list->cmdline[i].cmd && cmd_list->cmdline[i].rd_flg == 0)
	{
		if (isvalid_export(cmd_list->cmdline[i].cmd) == 0)
			err_write("minishell: %s: `%s': not a valid identifier\n", \
			cmd_list->cmdline[0].cmd, cmd_list->cmdline[i].cmd);
		i++;
	}
}

void			print_errstr2(t_cmd *cmd_list)
{
	if (cmd_list->err.code == 5 || cmd_list->err.code == 6)
	{
		if (cmd_list->err.code == 5)
			ft_print_export_err(cmd_list);
		else
			ft_print_unset_err(cmd_list);
		g_exit_status = 1;
	}
	else if (cmd_list->err.code == 7)
	{
		if (cmd_list->err.token)
			err_write("minishell: syntax error near unexpected token `%s'\n", \
			cmd_list->err.token, 0);
		else
			err_write("minishell: syntax error near unexpected token `%s\'\n", \
			cmd_list->cmdline[cmd_list->err.idx].cmd, 0);
		g_exit_status = 258;
	}
	else if (cmd_list->err.code == 8)
	{
		err_write("minishell: syntax error near unexpected token `newline\'\n"\
		, cmd_list->cmdline[cmd_list->err.idx].cmd, 0);
		g_exit_status = 258;
	}
}

void			print_errstr(t_cmd *cmd_list)
{
	if (cmd_list->err.code == 1)
	{
		err_write("minishell: %s: command not found\n", \
		cmd_list->cmdline[0].cmd, 0);
		g_exit_status = 127;
	}
	else if (cmd_list->err.code == 2)
	{
		err_write("minishell: %s: too many arguments\n", \
		cmd_list->cmdline[0].cmd, 0);
		g_exit_status = 1;
	}
	else if (cmd_list->err.code == 3)
	{
		err_write("minishell: %s: No such file or directory\n", \
		cmd_list->cmdline[cmd_list->err.idx].cmd, 0);
		g_exit_status = 1;
	}
	else if (cmd_list->err.code == 4)
	{
		err_write("minishell: %s: %s: numeric argument required\n", \
		cmd_list->cmdline[0].cmd, cmd_list->cmdline[cmd_list->err.idx].cmd);
		g_exit_status = 255;
	}
	print_errstr2(cmd_list);
}
