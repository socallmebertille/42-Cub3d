# 42-Cub3d : My first RayCaster with miniLibX

Cub3D est un projet graphique en C inspiré du jeu classique Wolfenstein 3D, développé dans le cadre du cursus de l'école 42. Le projet génère une visualisation 3D à partir d'une carte 2D définie par l'utilisateur dans un fichier .cub.


## Étapes du parsing

### Vérification initiale (check_map_file) :

#### Vérification de l'extension du fichier (.cub).

####Ouverture et lecture du fichier (read_map).

### Lecture des paramètres :

####Extraction des textures (map_texture, map_texture2).

####Vérification des chemins vers les textures (path_texture).

####Extraction et validation des couleurs plafond et sol (map_color, check_colors, check_value).

### Création de la carte (map_file_parse, recup_map):

####Stockage de la carte en mémoire (malloc_map).

####Vérification des caractères valides et du joueur unique (check_char).

### Vérification de l'intégrité de la carte (flood_fill_check):

####Utilisation de l'algorithme Flood-Fill pour s'assurer que tous les espaces accessibles sont entourés de murs (comme pour so_long).

## Logique du Raycasting

Initialisation du joueur (init_player, recup_player):

Position initiale du joueur définie par des coordonnées précises (x, y).

Orientation initiale du joueur (Nord, Sud, Est ou Ouest).

Bases théoriques du Raycasting :

Le raycasting est une technique graphique pour simuler un environnement 3D à partir d’une carte 2D en lançant des rayons virtuels depuis la position du joueur vers les murs environnants.

Principe :

Chaque rayon lancé depuis le joueur correspond à une colonne verticale à l’écran.

La distance entre le joueur et le mur rencontré par chaque rayon détermine la hauteur apparente du mur : plus le mur est loin, plus il apparaît petit.


1. Lancement des rayons (put_img):

Calcul de l'angle de chaque rayon à partir du champ de vision du joueur.

Lancement d'un rayon pour chaque colonne de pixels, couvrant ainsi tout le champ visuel.

2. Détection de collisions (choice_side_wall, init_ray):

Détermination des intersections entre les rayons et les murs.

Calcul des distances parcourues par chaque rayon (distances horizontales et verticales : side_dist, delta).

3. Sélection des textures (choice_pic):

Sélection des textures adéquates en fonction du côté du mur touché par le rayon (Nord, Sud, Est ou Ouest).

4. Calcul et affichage de la hauteur des murs (draw_column):

Utilisation de la distance calculée pour déterminer la hauteur du mur sur l’écran.

Division de chaque colonne en trois parties : plafond (couleur définie), mur (texture choisie), sol (couleur définie).

Contrôles du jeu

W : Avancer

S : Reculer

A : Déplacement latéral gauche

D : Déplacement latéral droit

Flèches gauche/droite : Rotation de la caméra

ESC : Quitter le jeu

Fonctions clés

Parsing et gestion des erreurs : check_map_file, map_file_parse, flood_fill_check

Gestion des textures et couleurs : map_texture, path_texture, check_colors

Gestion du joueur et déplacement : move_north, move_south, move_west, move_east

Raycasting et rendu graphique : render_game, put_img, draw_column
