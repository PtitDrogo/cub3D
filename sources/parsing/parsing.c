/*
    - On avance dans les whitespace au debut de chaque ligne
    - On check le First character.
    - On strcmp avec avec "NO " / "SO " "F " etc
    - On CHECK si la variable n'a pas deja ete set up;
    
    //GERER LES VARIABLES TEXTURES
    - apres EA/NO etc, on traverse les whitespaces
    - On remplis le premier mot trouver dans la variable prevu a cet effet
    - On traverse les whites spaces
    - Si on voit autre chose qu'un \n, erreur;

    //GERER LES RGB
    - On garde le format xxx,xxx,xxx;
    - On traverse jusqu'a une virgule
    - si la chaine de char est > 3 ou les chars sont NaN, c'est faux
    - On passe ca dans un itoa; (is it safe ? 007 ? a voir)
    - si le nombre is => 0 && <= 255, its good;
    - pour le dernier nombre, on itere jusqua white space ou \n;

    //GERER LA MAP
    - Si on voit un 1 - 0 - W/N/E/S, on start le map checking;
    - BIEN CHECK QUIL NY A PAS DEUX JOUEURS.
    - Si un char est invalide, map est fausse. (check full map en bourrin)
    - Si tous nos param ne sont pas definis, c'est faux;
    - Checker si tous les 0 sont bien a coters d'un 0 ou 1.
    - Verifier que le joueur est en tourer de 1 ou 0
    - bien verifier qu'il y a un span de joueur sinon c'est faux;
    - Difficulter, gerer le debut et fin de map;
    - si on est a x = 0 ou y = 0, ne pas check x/y - 1 !
    - si on est a x = map_width, ne pas check x + 1; same for y = map_heigth;
    
    //LES INFOS QUON FILE A LEXEC
    (ce sera sa propre struct)
    - Map heigth map width;
    - Les textures;
    - Les couleurs;

    - toute autre info potentiel dans la struct parsing;

    //Verifier que la map est bien un .cub;
    printf("awaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
        aaaaaaaaaaaaaaaaaaaaaaaaaaa")

    - This is viable map;
    111
    101
    111

    11111111111
    1000000W001
    11111111111
*/
