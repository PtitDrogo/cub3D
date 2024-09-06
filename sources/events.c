#include "parsing.h"

int	no_events(t_info *w)
{
	(void)w;
	return (0);
}

int	deal_key(int id_key, t_info *w)
{
	if (id_key == XK_Escape)
		free_window(w);
	if (id_key == XK_s || id_key == XK_w)
		return (0); // avant arriere
	if (id_key == XK_d || id_key == XK_a)
		return (0); // droite gauche
	return (0);
}


