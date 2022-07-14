// void	skip_delim(char **line, char *delim, t_token **strlst)
// {
// 	while (ft_strchr(delim, **line) && **line != '\0')
// 	{
// 		if (**line == '|')
// 			add_to_strlst(strlst, init_strlst(ft_strdup("|")));
// 		else if (ft_strncmp(*line, "<<", 2) == 0)
// 		{
// 			add_to_strlst(strlst, init_strlst(ft_strdup("<<")));
// 			(*line)++;
// 		}
// 		else if (ft_strncmp(*line, ">>", 2) == 0)
// 		{
// 			add_to_strlst(strlst, init_strlst(ft_strdup(">>")));
// 			(*line)++;
// 		}
// 		else if (**line == '<')
// 			add_to_strlst(strlst, init_strlst(ft_strdup("<")));
// 		else if (**line == '>')
// 			add_to_strlst(strlst, init_strlst(ft_strdup(">")));
// 		(*line)++;
// 	}
// }

// void	check_type(t_token *pretok)
// {
// 	char	*str;

// 	while (pretok)
// 	{
// 		str = pretok->str;
// 		if (!ft_strncmp(str, "<", ft_strlen(str)))
// 			pretok->type = T_RDR_IN;
// 		else if (!ft_strncmp(str, "<<", ft_strlen(str)))
// 			pretok->type = T_RDR_HD;
// 		else if (!ft_strncmp(str, ">", ft_strlen(str)))
// 			pretok->type = T_RDR_OUT;
// 		else if (!ft_strncmp(str, ">>", ft_strlen(str)))
// 			pretok->type = T_RDR_AP;
// 		else if (!ft_strncmp(str, "|", ft_strlen(str)))
// 			pretok->type = T_PIPE;
// 		else
// 			pretok->type = T_OFF;
// 		pretok = pretok->next;
// 	}
// }
