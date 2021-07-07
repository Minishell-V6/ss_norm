/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 16:33:35 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/06 22:06:03 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <stdlib.h>
# include "structs.h"
# include "cmd_split.h"
# include "alloc_token.h"

typedef struct	s_parser
{
	int			i;
	int			start;
	int			pipe_flag;
	t_cmd		*tmp;
	t_cmd		*new;
	int			quote_flag;
}				t_parser;
void			parser(t_cmd **cmd_list, char *line, char **envp);

#endif
