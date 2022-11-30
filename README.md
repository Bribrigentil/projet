# projet

#Bonjour je suis un readme.


Projet oiseaux,
On peut faire une classe éléments, puis héritage sur oiseaux et obstacles (arbres, poteaux)


1ere étape:
initialiser aléatoirement les positions et vitesses initiales des oiseaux. Pour ça:
  -créer la classe oiseau, variables et méthodes les plus générales
  -fonction main:
    -renvoie le tableau des positions et vitesses initiales
 
 
2éme étape: transcrire le tableau sur une carte ou les oiseaux sont représentés par des triangles
  -fonction main:
    -générer l'interface SFML sur laquelle les oiseaux vont se déplacer
    -les oiseaux sont représenter par des triangles isocèles orientés selon leur vecteur vitesse
    
3ème étape: reprendre l'interface SFML et l'animer dans le temps pour que les oiseau se déplacent selon leur vitesse initiale.

4ème étape: ajouter la condition de périodicité aux bords de l'interface SFML.

5ème étape: implémenter les règles de mouvement que doivent respecter oiseaux.
  -vitesse à t+dt= composante vitesse à t + composante dirigé vers le barycentre du groupe + composante pour alignere la vitesse avec la vitsse du groupe

6ème étape: définir un rayon R de visibilité pour que les oiseaux n'intéragissent qu'avec ceux situés proches d'eux

7ème étape: définir l'angle pour que les angles ne voient pas à 360° autour d'eux

8ème étape: ajouter la condition de non interpénétrabilité des oiseaux

Après je sais pas encore


