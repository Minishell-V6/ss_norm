/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_print.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 11:01:12 by seuyu             #+#    #+#             */
/*   Updated: 2021/07/07 11:01:41 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_PRINT_H
# define ERR_PRINT_H

# include <stdlib.h>
# include "structs.h"
# include "minishell.h"

void	print_errstr(t_cmd *cmd_list);

#endif
