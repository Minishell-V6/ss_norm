/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_func.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 19:55:36 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/06 20:57:29 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_FUNC_H
# define EXEC_FUNC_H
# include "../libft/libft.h"
# include "structs.h"
# include "builtin.h"
# include "non_builtin.h"

int	exec_function(t_cmd *cmd_list, char *argv[], char **envp[], int fds[]);

#endif
