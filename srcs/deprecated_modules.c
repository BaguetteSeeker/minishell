/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deprecated_modules.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:08:06 by epinaud           #+#    #+#             */
/*   Updated: 2025/06/09 12:16:52 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// void	expand_token(t_token *tokens)
// {
// 	static int	last_token = -1;

// 	if (tokens->type == WORD)
// 	{
// 		if (last_token == DLESS)
// 		{
// 			if (is_expandable(tokens->value))
// 				tokens->value = expand(tokens->value, XPD_HDOC);
// 		}
// 		else if (in_array(last_token, (int []){LESS, GREAT, DGREAT}, 3))
// 			tokens->value = strip_outquotes(expand(tokens->value, XPD_REDIR));
// 		else
// 			tokens->value = strip_outquotes(expand(tokens->value, XPD_ALL));
// 	}
// 	last_token = tokens->type;
// }

/* char	*lst_injectreplace(char *val_tofind, t_token *newlst)
{
	t_token	*prev;
	t_token	*curr;
	t_token	*next;

	prev = NULL;
	curr = g_getset(NULL)->tokens;
	// Find the token to replace and its previous node
	while (curr && curr->value != val_tofind)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		put_err("Lst val not found");
	next = curr->next;
	lstdelone_tokens(curr, free_token_value);
	// Insert newlst at the position of curr or define new head
	if (prev)
		prev->next = newlst;
	else
		g_getset(NULL)->tokens = newlst;
	msh_lstlast(newlst)->next = (t_list *)next;
	return (next ? newlst->value : NULL);
}

char	*get_path(char *pcdr)
{
	DIR				*dir;
	struct dirent	*entry;
	t_token			*paths;
	t_token			*path;

	path = NULL;
	paths = NULL;
	dir = opendir(".");
	if (!dir)
		return (put_err("Expander: Malloc Faillure"), NULL);
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			return (closedir(dir), lst_injectreplace(pcdr, path));
		if (match_pattern(pcdr, entry->d_name))
		{
			path = chkalloc(malloc(sizeof(t_token)), 
				"Expander: Malloc Faillure");
			*path = (t_token){0};
			path->value = ft_strdup(entry->d_name);
			if (!path->value)
				put_err("Expander: Malloc Faillure");
			msh_lstaddback(&paths, path);
		}
	}
} */

//Former get_exitcode function that preserved `$?` outside of execution
// static char	*get_exitcode(char *str, size_t *i)
// {
// 	char	*exitcode;

// 	if (g_getset(NULL)->state == MSH_EXECUTING)
// 	{
// 		exitcode = ft_itoa(g_getset(NULL)->last_exitcode);
// 		if (!exitcode)
// 			put_err("Expand : Failled to alloc memory for exitcode;");
// 		str = concat_expansion(str, str + *i, exitcode, TYPE_CODE);
// 	}
// 	else
// 		*i += 2;
// 	return (str);
// }

/* ——— Memory Modules used to mimic a garbage collector ——— */
// # define NO_DUP 0
// # define DUP_BUFF 1
/* char	*new_mem(char *buff, char *errmsg, size_t dup_buff)
{
	char		*new_mem;
	t_memory	*mem_node;

	new_mem = NULL;
	if (dup_buff)
		new_mem = chkalloc(ft_strdup(buff), errmsg);
	else
		new_mem = buff;
	mem_node = malloc(sizeof(t_memory));
	if (!mem_node)
	{
		if (dup_buff)
			free(new_mem);
		put_err("t_memory : mem_node");
	}
	// *mem_node = (t_memory){0};
	mem_node->mem = new_mem;
	msh_lstaddback(&g_getset(NULL)->mem_lst, mem_node);
	return (new_mem);
}

void	del_mem(char *buff)
{
	t_memory	*prev;
	t_memory	*curr;
	t_memory	*next;

	prev = NULL;
	curr = g_getset(NULL)->mem_lst;
	// Find the node to remove and its previous node
	while (curr && curr->mem != buff)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		ft_putendl_fd("del_mem: can't find provided buffer", STDERR_FILENO);
	next = curr->next;
	msh_lstdelone(curr, free_token_value);
	// Reattach the list or do nothing
	if (prev)
		prev->next = next;
	free(buff);
	if (buff == curr->mem)
		g_getset(NULL)->mem_lst = NULL;
}
 */
