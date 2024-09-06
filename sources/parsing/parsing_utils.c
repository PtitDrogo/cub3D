#include "cub3D.h"

bool is_white_space(char c)
{
    return ((c >= 9 && c <= 13) || c == 32);
}

size_t strlen_until_whitespace(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] && is_white_space(s[i]) == false)
	{
		i++;
	}
	return (i);
}

void    update_status(int err_value, int *status)
{
    *status = err_value;
    return ;
}
//with index being at the start of a word, moves to the index to the first char of the next word
void	skip_word(const char *line, size_t *index)
{
	while (is_white_space(line[*index]) == false)
		(*index)++;
	while (is_white_space(line[*index]))
		(*index)++;
}

