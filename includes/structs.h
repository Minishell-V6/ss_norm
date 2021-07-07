/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 17:39:39 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/07 16:20:41 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct		s_err
{
	int				code;
	int				idx;
	char			*token;
}					t_err;

typedef struct		s_token
{
	char			*cmd;
	char			rd_flg;
}					t_token;

typedef struct		s_cmd
{
	t_token			*cmdline;
	int				pipe_flag;
	int				exit_flag;
	int				right_flag;
	char			quote;
	char			*(rd_buf[4]);
	struct s_err	err;
	struct s_cmd	*next;
}					t_cmd;

#endif
