/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:31:31 by epinaud           #+#    #+#             */
/*   Updated: 2025/01/25 16:30:59 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _DEFAULT_SOURCE
//# define LL_TYP /* Remplacer ce commentaire par le nom de la structure chainée voulue au sein du projet*/
//Définir impérativement la struct chainée avant l'include libft qui en fera usage
# include <libft.h>
# include <signal.h>
# include <stdbool.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>


# include "struct_cmds.h"
# include "system_utils.h"
# include "cmd_errors.h"
# include "cmd_utils.h"
# include "cmd_exec.h"

#endif