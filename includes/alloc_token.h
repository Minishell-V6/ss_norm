/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_token.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 21:43:45 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/06 15:55:36 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_TOKEN_H
# define ALLOC_TOKEN_H
# include <stdlib.h>
# include "alloc_token_utils.h"

void	ft_copy_str(char *src, char *dest, char **envp);
t_token *ft_alloc_token(t_token *token, char **envp);

#endif
