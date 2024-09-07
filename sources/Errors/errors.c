#include "cub3D.h"

void	print_error_msg(int err_code)
{
	ft_printf2("Error\n");
    if (err_code == ERR_TOO_MANY_PLYR)
		ft_printf2("Too many players were found !\n");
	else if (err_code == ERR_ZERO_PLAYER)
		ft_printf2("No players were found !\n");
	else if (err_code == ERR_INVALID_CHAR_MAP)
		ft_printf2("An invalid char was found on the map!\n");
    else if (err_code == ERR_TOO_MANY_PATHS)
		ft_printf2("Too many possible texture paths !\n");
    else if (err_code == ERR_PATH_TOO_BIG)
		ft_printf2("Path name is too long !\n");
    else if (err_code == ERR_DEFINED_TWICE)
		ft_printf2("Value defined twice !\n");
    else if (err_code == ERR_RGB_WRONG_FORMAT)
		ft_printf2("Wrong RGB format !\n");
    else if (err_code == ERR_RGB_NaN)
		ft_printf2("RGB is not a number !\n");
    else if (err_code == ERR_MAP_TOO_SOON)
		ft_printf2("Game Map starting before all values are set !\n");
    else if (err_code == ERR_TOO_FEW_CHARS)
		ft_printf2("Not enough characteres to be a viable value !\n");
    else if (err_code == ERR_INVALID_CHAR)
		ft_printf2("Character isnt valid code for value !\n");
}