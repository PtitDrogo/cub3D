# include <../libft/includes/libft.h>

int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;
    //DO Parsing

    //do the Cube
    
    //Random functions test;

    //ft_printf2 test;
    ft_printf2("Yo la team est ce que l'espace\
        de ouf est la\n"); // Mettre un \ marche pas ouuin

    //safe gnl test
    int gnl_status = 0; //Il manque une ligne pour init ca dans gnl :/
    char *gnl_test;
    gnl_test = get_next_line_safe(0, &gnl_status);
    ft_printf2("gnl status = %i\n", gnl_status);
    free(gnl_test);
    //end gnl test
    return 0;
}
