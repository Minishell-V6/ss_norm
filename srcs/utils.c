/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:01:44 by djeon             #+#    #+#             */
/*   Updated: 2021/07/05 13:00:46 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				check_whitespace(char *line)
{
	int			i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != 32 && !(line[i] >= 9 && line[i] <= 13))
			return (0);
		i++;
	}
	return (1);
}

char			*strjoin_path(char const *s1, char const *s2)
{
	char		*tmp1;
	char		*tmp2;
	char		*result;
	int			i;
	int			j;

	tmp1 = (char*)s1;
	tmp2 = (char*)s2;
	i = 0;
	j = 0;
	if (!(result = (char*)malloc(ft_strlen(tmp1) + ft_strlen(tmp2) + 2)))
		return (0);
	while (tmp1[i] != '\0')
	{
		result[i] = tmp1[i];
		i++;
	}
	result[i++] = '/';
	while (tmp2[j] != '\0')
		result[i++] = tmp2[j++];
	result[i] = '\0';
	return (result);
}

void			free_list(t_cmd *cmd_list)
{
	t_cmd		*tmp;
	int			i;

	while (cmd_list->next != NULL)
	{
		i = 0;
		tmp = cmd_list;
		cmd_list = cmd_list->next;
		while (tmp->cmdline[i].cmd != NULL)
			free(tmp->cmdline[i++].cmd);
		free(tmp->cmdline);
		free(tmp->err_manage.errtoken);
		free(tmp);
	}
	i = 0;
	while (cmd_list->cmdline[i].cmd != NULL)
		free(cmd_list->cmdline[i++].cmd);
	free(cmd_list->cmdline);
	free(cmd_list->err_manage.errtoken);
	free(cmd_list);
}

t_cmd			*ft_new(char *line, int pipe_flag, char **envp, int exit_flag)
{
	t_cmd		*result;

	if (!(result = (t_cmd*)malloc(sizeof(t_cmd))))
		return (NULL);
	result->cmdline = cmd_split(line, ' ');
	ft_alloc_token(result->cmdline, envp);
	result->pipe_flag = pipe_flag;
	if (exit_flag == 0 && pipe_flag == 0)
		result->exit_flag = 1;
	else
		result->exit_flag = 0;
	result->err_manage.errcode = 0;
	result->err_manage.errindex = 0;
	result->err_manage.errtoken = NULL;
	result->next = NULL;
	return (result);
}
