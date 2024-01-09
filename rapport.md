### Rapport projet abeille VS frelon

## Compilation et Utilisation

Pour compiler le projet il suffit de rentrer la commande make dans le terminal la ou se trouve le makefile.

Pour uttiliser le programme lancer la commande ```./AVSF fichiersauv```.

Vous pouver donner le nom que vous voulez au fichier de sauvegarde

si vous ne donner pas de fichier de sauvgarde le programme ne se lancera pas et si vous donner des argument en trop seul le premier sera pris en compte.

## Amélioration

Au lieu de récupérer les ressource et de faire les combat a la fin du tour nous avons pensez que il serait plus ammusant et strategique de tout faire en tant réel.

## Difficulté

Nous avons eu pas mal de difficulté a gerer les deplacement la plus part des bug que nous avons eu vienne de la fonction déplacement car il existe beacoup de cas différent qu'il fallais géré.

## Précision sur les choix du code

Ici nous allons parler des fonction un peut compliquer comme la fonction deplacement citer plus tôt.

Dans la fonction deplacement se qui a poser le plus de probleme c'est quand on rajoute une uniter qui viens d'être crée ou quand on charge une sauvegarde et quelle n'a aucune case ou elle etais au debut cela pausais des probleme pour les rechainages sur la 3eme liste chainer nous vérifions donc si il existe une case actuelle ou non.

Dans la fonction TourAbeille et TourFrelon nous parcouron les liste en faisant attention a garder en memoire la ruche de la colonie que nous traverson afin d'éviter des déplacemnt inutile dans la liste et pour chaque unite nous faisons un switch case afin de savaoir quelle unite somme nous entrain de jouer et d'afficher le menue de la bonne uniter menue qui nous renvoie le choix de l'utilisateur afin de faire les fonction voulue.
