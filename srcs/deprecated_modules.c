/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deprecated_modules.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:08:06 by epinaud           #+#    #+#             */
/*   Updated: 2025/06/01 15:29:12 by epinaud          ###   ########.fr       */
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
	lstlast_tokens(newlst)->next = (t_list *)next;
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
			lstadd_back_tokens(&paths, path);
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
