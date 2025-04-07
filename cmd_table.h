/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:28:11 by epinaud           #+#    #+#             */
/*   Updated: 2025/03/30 19:38:41 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CMD_TABLE_H
# define CMD_TABLE_H
# include "minishell.h"

enum    e_node_types
{
    CMD,
    ANDIF,
    ORIF
};

typedef struct  s_redirs
{
   size_t  infile;
   size_t  outfile;
}  t_redirs;

typedef struct  s_command
{
    int       type;
    void      *prev;
    char      *cmd;
    char      **args;
    t_redirs  io_streams;
} t_command;

typedef struct s_if_node
{
    int     type;
    void    *prev;
    void    *next_a;
    void    *next_b;
}    t_if_node;
#endif