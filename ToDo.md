# THE To Do list #


Table Of Content:


---

# <font color='red'>IMPORTANT avant de commencer</font> #
  1. Consultez les membres de l'équipe
  1. Consultez la documentation sur le wiki et dans le dossier docs du projet
  1. Regardez et comprenez le [Diagramme de Classe](http://code.google.com/p/getrandomgame/source/browse/trunk/GetRandomGame/docs/getArandomGame.uml) (nécessite [StarUML](http://staruml.sourceforge.net/en/download.php))
  1. Vous ne trouvez pas de page dans le wiki sur le module que vous désirez? créez-la et expliquez votre module.
  1. puis inscrivez votre nom devant l'élément de la liste que vous allez travailler.
  1. Ajuster vos [Duties](http://code.google.com/p/getrandomgame/people/list)


---

# Les étapes #

## Étape 1: design ##
### Le Game Doc ###
Pas fait totalement, mais le wiki en couvre une grande partie.

### Les technologies ###
C++, SDL, OpenGL, muilti-platform...

c'est pas mal fait!

## Étape 2: conception ##
Donc maintenant que tout est diponible pour starter, il ne vous reste plus qu'à prendre le module suivant qui vous intéresse:

### Le moteur ###
  * <font color='blue' size='3'>Paufiner le Tile Engine (Emile)</font>
    * <font color='green'>Ajout d'openGL (done)</font>
    * <font color='green'>Gestion de l'affichage (done)</font>
    * <font color='green'>Light Engine (almost done)</font>
    * Les menu/interface (inventaire, stats, hotbar, healt/xp/mana bar, etc) EN COURS
      * ça implique faire des classes générique genre Button et Labels et Menu, voir Class Diagram et Maquette
    * <font color='green'>Gestion des contrôles (done)</font>
    * Peut-être Aspect Réseau
    * <font color='green'>Game State<br>
<ul><li>Menu principal (done)</font>
</li><li>Login au serveur et loading screen (si réseau)</li></ul>

### Le Jeu ###
  * <font color='blue' size='3'>Le Monde <a href='World.md'>(voir la page)</a>
<ul><li>tile map (Emile)<br>
</li><li>RANDOM de la map (Alexandre DT)</font>
</li></ul>  * <font size='3'>Les Tokens</font>
    * Ainsi que des états comme (en feu, gelé, électrifiant, etc, voir [features](Features.md))
  * <font size='3'>Le système de génération d'item</font>
    * Donc faire les classes Item et Inventaire
    * puis importer le système de génération aléatoire avec préfixe et suffixe
    * Le système de crafting
  * <font color='blue' size='3'>Les Characters (FreD)</font>
    * Player (FreD)
    * NPC
    * Monsters
  * <font color='blue' size='3'>Le système d'interaction (bebleu)</font>
    * Mouvement dans les tuiles
    * interaction de combat autant qu'avec des objets (classe générique Interaction)
    * Les interactions Magiques (spells)
    * Interactions sociales
  * <font size='3'>Le pathfinding</font>
    * Pour notre personnage lors de mouvement avec clique
    * Pour les NPC (A`*` probablement)
  * <font size='3'>L’intelligence Artificiel</font>
    * Passive/agressive directe ou indirect etc


## Étape 3: Contenu et paufinement ##
Donc, si tu es rendu ici, c'est que le jeu, est un jeu, et qu'il est jouable.

Il reste donc les étapes suivantes:
### Définir les règles ###
Il faut définir les règles exactes et balancer le tout. La balance du jeu sera encore paufiné dans les Beta tests.

### un éditeur ###
pour ajouter du contenu facilement
  * des animations
  * Des parties de map
    * comme des donjons
    * des batiments
  * des objets
  * des types d'objets
  * autre contenu

## Étape 4: Beta test ##

Privé ou publique?

## Étape 5: Release ##

Steam serait une plateforme intéressante.

Merci et bon développement!

Voilà, s'il manque quelque chose, n'hésitez pas à modifier les pages.