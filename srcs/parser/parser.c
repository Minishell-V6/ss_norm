/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 14:57:25 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/06 22:36:41 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_cmd	*ft_new(char *line, int pipe_flag, char **envp, int exit_flag)
{
	t_cmd	*result;

	if (!(result = (t_cmd*)malloc(sizeof(t_cmd))))
		return (NULL);
	result->cmdline = cmd_split(line);
	ft_alloc_token(result->cmdline, envp);
	result->pipe_flag = pipe_flag;
	if (exit_flag == 0 && pipe_flag == 0)
		result->exit_flag = 1;
	else
		result->exit_flag = 0;
	result->err.code = 0;
	result->err.idx = 0;
	result->err.token = NULL;
	result->next = NULL;
	return (result);
}

int		add_newnode(t_cmd **cmd_list, char *line, char **envp, t_parser *t_par)
{
	if ((t_par->new = ft_new(&line[t_par->start], t_par->pipe_flag, envp,
					t_par->start)) == 0)
		return (-1);
	if (t_par->start == 0)
	{
		*cmd_list = t_par->new;
		t_par->tmp = *cmd_list;
	}
	else
	{
		(*cmd_list)->next = t_par->new;
		*cmd_list = (*cmd_list)->next;
	}
	if (t_par->pipe_flag == 0)
		return (0);
	return (1);
}

void	set_parser(t_parser *t_par)
{
	t_par->i = 0;
	t_par->start = 0;
	t_par->pipe_flag = 1;
	t_par->tmp = NULL;
	t_par->new = NULL;
	t_par->quote_flag = 0;
}

void	quote_flag_chk(char *line, t_parser *t_par)
{
	if ((line[t_par->i] == '\"' || line[t_par->i] == '\'')
			&& t_par->quote_flag == 0)
		t_par->quote_flag = 1;
	else if ((line[t_par->i] == '\"' || line[t_par->i] == '\'')
			&& t_par->quote_flag == 1)
		t_par->quote_flag = 0;
}

void	parser(t_cmd **cmd_list, char *line, char **envp)
{
	t_parser	t_par;
	int			node_chk;

	set_parser(&t_par);
	node_chk = 0;
	while (1)
	{
		quote_flag_chk(line, &t_par);
		if (line[t_par.i] == '\0' || (line[t_par.i] == '|'
					&& t_par.quote_flag == 0))
		{
			if (line[t_par.i] == '|')
				line[t_par.i] = '\0';
			else
				t_par.pipe_flag = 0;
			node_chk = add_newnode(cmd_list, line, envp, &t_par);
			if (node_chk == -1)
				return ;
			else if (node_chk == 0)
				break ;
			t_par.start = t_par.i + 1;
		}
		(t_par.i)++;
	}
	*cmd_list = t_par.tmp;
}
