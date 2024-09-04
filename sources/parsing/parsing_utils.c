#include "parsing.h"

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
	while (s[i] || is_white_space(s[i]) == false)
	{
		i++;
	}
	return (i);
}

