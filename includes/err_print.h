/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_print.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 22:06:59 by seuyu             #+#    #+#             */
/*   Updated: 2021/07/06 22:07:01 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_PRINT_H
# define ERR_PRINT_H

# include <stdlib.h>
# include "structs.h"
# include "minishell.h"

void			print_errstr(t_cmd *cmd_list);

#endif
