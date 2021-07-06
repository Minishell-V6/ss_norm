/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 15:29:32 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/06 15:54:50 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/alloc_token_utils.h"

int		get_envkey(char *src, char **key)
{
	int	key_len;

	key_len = env_key_size(src);
	*key = ft_substr(src, 1, key_len);
	return (key_len);
}

int		env_endchk(char *src, char **dest)
{
	if (src[1] == '\0' || src[1] == '\"')
	{
		**dest = '$';
		*dest += 1;
		return (0);
	}
	return (1);
}

int		alloc_env(char *src, char **dest, char **envp)
{
	int		src_idx;
	char	*key;
	char	*env_val;
	int		env_len;
	char	*status;

	src_idx = 0;
	if (src[1] == '?')
	{
		status = ft_itoa(g_exit_status);
		ft_memcpy(*dest, status, ft_strlen(status));
		*dest += ft_strlen(status);
		free(status);
		return (1);
	}
	if (env_endchk(src, dest) == 0)
		return (0);
	src_idx = get_envkey(src, &key);
	env_val = get_env_value(key, envp);
	env_len = ft_strlen(env_val);
	ft_memcpy(*dest, env_val, env_len);
	*dest += env_len;
	free(key);
	return (src_idx);
}

int		alloc_d_quote_cnt(char *src, char **dest, char **envp)
{
	int src_idx;

	src_idx = 1;
	while (src[src_idx] && src[src_idx] != '\"')
	{
		if (src[src_idx] == '$')
			src_idx += (alloc_env(&src[src_idx], dest, envp) + 1);
		else
		{
			**dest = src[src_idx];
			(*dest)++;
			src_idx++;
		}
	}
	return (src_idx);
}

int		alloc_s_quote_cnt(char *src, char **dest)
{
	int src_idx;
	int dest_len;

	src_idx = 1;
	dest_len = 0;
	while (src[src_idx] && src[src_idx] != '\'')
	{
		src_idx++;
		dest_len++;
	}
	ft_memcpy(*dest, src + 1, dest_len);
	*dest += dest_len;
	return (src_idx);
}
