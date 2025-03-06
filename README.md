# 42-Cub3d : My first RayCaster with miniLibX

Cub3D est un projet graphique en C inspiré du jeu culte Wolfenstein 3D, généralement considéré comme le grand-père des jeux de tir en trois dimensions et plus spécifiquement des jeux de tir à la première personne.
Le projet génère une visualisation 3D à partir d'une carte 2D définie par l'utilisateur dans un fichier .cub.


## Étapes du parsing

### Premieres verification (check_map_file) :

* Vérification de l'extension du fichier fourni (.cub).

* Ouverture et lecture du fichier (via read_map).

### Lecture des paramètres :

* Identification et récupération des chemins d’accès aux textures des murs (map_texture, map_texture2).

* Validation de l’existence des fichiers de textures (path_texture).

* Lecture et vérification des couleurs définissant le plafond et le sol en format RGB (map_color, check_colors, check_value).

### Lecture de la carte (map_file_parse, recup_map):

* Allocation dynamique et stockage en mémoire de la carte 2D (malloc_map).

* Validation stricte des caractères autorisés : 0 (vide), 1 (mur), N, S, E, W (position initiale du joueur), et vérification de l'unicité du joueur (check_char).

### Vérification de l'intégrité de la carte (flood_fill_check):

* Algorithme qui parcourt récursivement la carte pour vérifier que chaque espace accessible est fermé par des murs afin d'éviter toute fuite hors de la carte (comme pour so_long).

## Raycasting

### Bases théoriques du Raycasting :

Le raycasting est une technique utilisée pour créer une illusion de 3D en projetant des rayons virtuels depuis la position du joueur dans toutes les directions visibles. Chaque rayon lancé correspond à une colonne verticale de pixels sur l'écran.

### Pourquoi le Raycasting ?

* Il permet une représentation simplifiée de la 3D à partir d’une structure 2D, limitant la complexité des calculs.

### Différence entre Raycasting et Raytracing :

* Le raycasting lance un seul rayon par colonne de pixel pour déterminer la distance au premier obstacle rencontré, simplifiant ainsi considérablement les calculs.

* Le raytracing lance plusieurs rayons par pixel, prenant en compte les rebonds, les réflexions et les réfractions de la lumière pour un rendu réaliste, mais au prix d’une complexité calculatoire beaucoup plus élevée.

### Principe technique :

* Le joueur émet un rayon pour chaque colonne de pixels.

* Lorsqu'un rayon rencontre un mur, la distance entre le joueur et ce mur définit la hauteur de la colonne affichée. Plus la distance est grande, plus la colonne sera petite, créant une impression réaliste de profondeur.

## Implémentation dans Cub3D

### 1. Initialisation du joueur (init_player, recup_player) :

* Position initiale précise (x, y).

* Orientation initiale selon un axe cardinal : Nord, Sud, Est ou Ouest.

### 2. Lancement des rayons (put_img) :

* Calcul précis de l’angle du rayon par rapport à la direction actuelle du joueur.

* Chaque colonne de l’écran correspond à un rayon spécifique couvrant tout le champ visuel horizontal du joueur.

### 3. Détection des collisions (choice_side_wall, init_ray) :

* Les rayons avancent pas à pas jusqu’à toucher un mur.

* La distance parcourue (perpwalldist) permet de déterminer la hauteur finale des murs affichés.

### 4. Choix de la texture à afficher (choice_pic) :

* Selon l’orientation du mur touché (Nord, Sud, Est ou Ouest), une texture précise est choisie.

### 5. Affichage des colonnes (draw_column) :

* L'écran est divisé verticalement en trois parties : le plafond avec une couleur spécifique, la colonne représentant le mur avec la texture choisie, et le sol avec une autre couleur spécifique.

* La hauteur de la colonne représentant le mur dépend directement de la distance calculée.

## Contrôles du jeu

* W : Avancer

* S : Reculer

* A : Déplacement latéral gauche

* D : Déplacement latéral droit

* Flèches gauche/droite : Rotation de la caméra

* ESC : Quitter le jeu

## Fonctions clés

* Parsing et gestion des erreurs : check_map_file, map_file_parse, flood_fill_check

* Gestion des textures et couleurs : map_texture, path_texture, check_colors

* Gestion du joueur et déplacement : move_north, move_south, move_west, move_east

* Raycasting et rendu graphique : render_game, put_img, draw_column
