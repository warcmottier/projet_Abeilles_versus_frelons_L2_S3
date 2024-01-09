### Rapport projet abeille VS frelon

## Compilation et Utilisation

Pour compiler le projet il suffit de rentrer la commande make dans le terminal au même endroit que le makefile.

Pour utiliser le programme lancer la commande ```./AVSF fichiersauv```.

Vous avez le choix du nom du fichier de sauvegarde.

Si vous ne donner pas de fichier de sauvgarde le programme ne se lancera pas.

Si vous donner des arguments en trop, seul le premier sera pris en compte.

## Amélioration

Au lieu de récupérer les ressources et de faire les combats à la fin du tour, nous nous sommes dit que ce serait plus ammusant et stratégique de tout faire en temps réel.

## Difficulté

Nous avons eu pas mal de difficulté à gérer les déplacements, la plus part des bug que nous avons eu viennent de la fonction déplacement car il existe beacoup de cas différents qu'il fallait gérer.

## Précision sur les choix du code

Ici nous allons parler des fonctions un peu compliquées comme la fonction déplacement citer précédemment.

Dans la fonction deplacementc ce qui a posé le plus de problèmes, il s'agit du rajout d'une unité qui vient d'être crée, ou quand on charge une sauvegarde et quelle n'a aucune case où elle était au debut, cela posait des problèmes pour les rechainages sur la 3eme liste chainée, nous vérifions donc si il existe une case actuelle ou non.

Dans la fonction TourAbeille et TourFrelon, nous parcourons les listes en faisant attention à garder en mémoire la ruche de la colonie que nous traversons, afin d'éviter des déplacements inutile dans la liste et pour chaque unité nous faisons un switch case afin de savoir quelle unite somme nous entrain de jouer et d'afficher le menu de la bonne unité, menu qui nous renvoie le choix de l'utilisateur afin de faire les fonctions voulue.
