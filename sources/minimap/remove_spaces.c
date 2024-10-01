#include "cub3D.h"

//I know map is validated so there will be no empty line after;
void    get_wall_dimension(const char **map, int *max_len, int *max_height);

void    remove_spaces(char **old_map)
{
    int i;
    int j;
    static char set[] = {'\a', '\b', '\t', '\n', '\v', ' '};
    char *tmp;
    
    j = 0;
    while (old_map[j])
    {
        i = 0;
        tmp = ft_strtrim(old_map[j], set);
        free(old_map[j]);
        old_map[j] = tmp;
        j++;
    } 
}

void    get_wall_dimension(const char **map, int *max_len, int *max_height)
{
    int i;
    int j;

    j = 0;
    while (map[j])
    {
        while (map[j][i])
        {
            if (map[j][i] == '1' && i > max_len)
            {
                if (i > max_len)
                    *max_len = i;
                if (j > max_height)
                    *max_height = j;
            }
            i++;
        }
        j++;
    }
}