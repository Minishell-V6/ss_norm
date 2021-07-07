/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 22:07:14 by seuyu             #+#    #+#             */
/*   Updated: 2021/07/06 22:07:14 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "structs.h"
# include "err_print.h"

int			ft_echo(t_cmd *cmd_list, int fd);
int			ft_pwd(int fd);
int			ft_exit(t_cmd *cmd_list);
int			ft_cd(t_cmd *cmd_list);
int			ft_env(char **envp, int fd);
char		**copy_envp(char **envs);
int			ft_export(t_cmd *cmd_list, char ***envp, int fd);
int			add_envp(char *cmd, char ***envp);
int			isvalid_export(char *line);
int			cnt_envp_row(char **envp);
char		**sort_env(char **envp);
int			haveequal(char *line);
void		add_key_envp(char ***envp, char *cmd, int keyindex);
int			ft_valid_key(char *key);
int			ft_unset(t_cmd *cmd_list, char **envp);

#endif
