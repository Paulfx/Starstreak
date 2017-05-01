—————————————————————————————————————————————————————————————————————————————————————
I. Manuel.
—————————————————————————————————————————————————————————————————————————————————————
- Cross OS : OSX, LINUX

- Plein écran, adaptatif à la résolution 

- Compilation: Depuis le terminal: "make clean" puis "make" dans la racine du projet

- Exécution: ./StarStreak depuis bin 
	Attention ./bin/startreak ne marche pas. « smart_path(« ») » non implémenté

- Mode Jouer : 
	Vous devez sélectionné le mode « jouer » sur le premier menu , sélectionner une 	chanson et une difficulté. La partie se lance.
	Les notes descendent et vous devez les jouer lorsqu’elle arrivent sur la barre de 	validation. Le score final est affiché en fin de partie.
	Vous ne pouvez jouer une chansons que si la partition existe (de base, on vous en 	donne) 
- Mode Créer :
	Vous devez sélectionné le mode « créer » sur le premier menu, sélectionner une 		chanson et une difficulté. Attention la création effacera les partitions de la 		même chanson et de la même difficulté. Le partie se lance. 
	Vous placez des notes en appuyant sur les touches du clavier correspondantes. Un 	carré de couleur apparait pour vous dire que vous avez bien placé une note. 
- Utilisation:
	Les commandes sont :
	— Echap = Retour (dans le menu)
	- Q= Quitter
	- A= Note verte
	- Z= Note rouge
	- E= Note jaune
	- R= Note bleue
	- T= Note orange
	- Entrée= Continuer—————————————————————————————————————————————————————————————————————————————————————
II. Format de fichiers.
—————————————————————————————————————————————————————————————————————————————————————
Pour l’audio, nous avons choisi le .wav qui est lisible par beaucoup d’OS, contrairement au .ogg (par exemple)

Les partitions se trouvent dans le dossier data/songs/ . Chaque musique a son propre dossier avec 0 ou plusieurs partitions (3 max). 
Une partition est un fichier texte qui nous permet de fixer les notes dans le temps. 
La première ligne du fichier correspond au nombre de ligne. 
Chaque ligne suivante correspond au notes jouées (00000) aucune note, (11111) toute les notes et a la durée écouler depuis le début de la musique. 

L’index correspond a chaque musique disponible avec les emplacements : 
	- des fichiers sons
	- des images
	- des fichiers partitions
Mais aussi de la durée totale du morceaux. 

—————————————————————————————————————————————————————————————————————————————————————
III. Organisation de l’archive.
—————————————————————————————————————————————————————————————————————————————————————

Les fichiers sources se trouvent dans le répertoire "src" de l’archive, séparé en /Core et /sdl2. Les tests de redressions (mains) sont dans le dossier src
Le répertoire data contient toute les données nécessaires au bon fonctionnement du jeux. 
Dans cette archives vous n’aurez que 2 chansons jouables (+1 menu)
Une troisième est disponible sur le lien de téléchargement au pied du ReadMe. (.wav à insérer dans data/wav)
Vous trouverez dans data/songs/ les partitions disponibles (nom/nom+difficulté).
L’éxecutable est dans le dossier bin. 
La documentation se trouve dans le répertoire doc et comprend: le diagramme des modules, le diagramme de Gantt prévisionnel, ainsi que la documentation du code.
Le Makefile 
—————————————————————————————————————————————————————————————————————————————————————
IV. Auteurs.
—————————————————————————————————————————————————————————————————————————————————————
Paul Lafoix
Maxime Langlade
Antoine Police
Théo Rabut
