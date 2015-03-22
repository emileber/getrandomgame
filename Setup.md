# Configure Eclipse CDT with MinGW, SDL and OpengGL on Windows #


Table Of Content:


---


Get started!

# Requirements #
All You need:
  1. MinGW
  1. [Eclipse CDT](http://www.eclipse.org/downloads/packages/eclipse-ide-cc-developers-includes-incubating-components/indigosr2)
    * [Subversion pluggin](http://subclipse.tigris.org/servlets/ProjectProcess;jsessionid=BBB7E188C6378470662EDE0875D5CAAA?pageID=p4wYuA)
Voir la [Download List](http://code.google.com/p/getrandomgame/downloads/list) pour trouver certains fichier facilement.


---

# MinGW #

see the [Download list](http://code.google.com/p/getrandomgame/downloads/list)

Installe TOUTES les choix pour être sur.

F\*ck, all you need is to click next!

<font color='red'>Ajouter C:\MinGW\bin à la variable système PATH et restart pc</font>


---

# Eclipse #
[clicking here is all you need to know](http://www.eclipse.org/downloads/packages/eclipse-ide-cc-developers-includes-incubating-components/indigosr2)

<font color='red'>Pour chacun des paths suivant, COCHEZ "Add to all configurations"</font>

C/C++ General > Paths and Symbols > Languages GNU C++ > onglet Includes:
  * "C:\MinGW\lib\gcc\mingw32\4.6.1\include\c++"
  * "C:\MinGW\lib"
  * "C:\MinGW\lib\gcc\mingw32\4.6.1\include\c++\backward"
  * "C:\MinGW\lib\gcc\mingw32\4.6.1\include"
  * "C:\MinGW\lib\gcc\mingw32\4.6.1\include\c++\mingw32"
  * "C:\MinGW\lib\gcc\mingw32\4.6.1\include-fixed"
  * "C:\MinGW\include"

Avant de continuer, essaye de créer un projet Hello World en c++ **en choisissant le compilateur MinGW**

## Subclipse ##

  1. dans Help > Install New Software, coller l'url "http://subclipse.tigris.org/update_1.8.x"
  1. Cocher Subversion (et aussi SVNkit mais je suis pas sur, anyway, prend pas de risque)
  1. click next... next... etc. installe ça comme d'habitude.




---

# Project's Specific Settings #

## Creer le projet ##

  1. Clique droit dans le _Project Explorer_ puis cliquer Import
  1. Choisir _SVN > Checkout project from SVN_
  1. Use/create the svn url of the trunk, use HTTPS
  1. Sélectionner le dossier de projet dans le trunk (soit GetRandomGame)
  1. Checkout as a project configured using the New Project Wizard
  1. Empty c++ Project
  1. Nommer le projet par le nom du projet que vous allez utiliser (soit _GetRandomGame_ présentement)
  1. Choisir pour project type: _Executable > Empty Project_ avec la **Toolchain > MinGW GCC, (IMPORTANT)**

## Configurer le projet ##

**Il est possible de COPIER/COLLER tous les path et flags suivant dans les boites respectives.**

<font color='red'>IMPORTANTE 1ere étape: Clique droit sur le dossier <i>lib</i> et choisir <i>Ressource Configurations > Exclude from Build</i> et choisir DEBUG et RELEASE.</font>

### Dans les Project > Properties ###

C/C++ General > Paths and Symbols > Languages GNU C++ > onglet Source Location:
  * Ajouter le dossier: _src_ (en utilisant le bouton Add Folder à droite et le bouton Workspace)

C/C++ Build > settings > GCC C++ Compiler:

Preprocessor > Defined symbols (-D)
  * main=SDL\_main

**Pour les paths suivants, il est possible d'utiliser le bouton workspace**

Includes > Include paths (-I)
```
"${workspace_loc:/${ProjName}/lib/SDL/include}"
"${workspace_loc:/${ProjName}/lib/include}"
"${workspace_loc:/${ProjName}/lib/SDL_image/include}"
"${workspace_loc:/${ProjName}/lib/FreeType/include}"
"${workspace_loc:/${ProjName}/lib/FTGL/src}"
"${workspace_loc:/${ProjName}/src/GetRandomGame}"
"${workspace_loc:/${ProjName}/src/TileEngine}"
"${workspace_loc:/${ProjName}/src/Util}"
```

MinGW C++ Linker > Libraries
add the folowing libraries (Libraries -l)

```
mingw32
SDL_image
SDLmain
SDL
opengl32
glu32
freetype
ftgl
```

and add the folowing library Search Path (Libraries -L) juste en dessous
```
"${workspace_loc:/${ProjName}/lib/SDL/lib}"
"${workspace_loc:/${ProjName}/lib/SDL_image/lib}"
"${workspace_loc:/${ProjName}/lib/FreeType/lib}"
"${workspace_loc:/${ProjName}/lib/FTGL/lib}"
"${workspace_loc:/${ProjName}/lib/GLEW/lib}"
```

<font color='red'><b>the linker flag below is optionnal and shouldn't be used unless it won't compile</b></font>

<font color='gray'>MinGW C++ Linker > Miscellaneous<br>
Linker flags: -mwindows</font>

_Note: Pas besoin d'ajouter le dossier de jeu comme include puisqu'il est considéré par défaut comme le dossier de développement._

## Build le projet ##

  1. Click on the debug button (little hammer) which means: Build "DEBUG" for the project "GetRandomGame"
    * If there's an error, see the FAQ or open an Issue. Thanks.
  1. Now, all that's left is to add the dll files beside the Binary that we have just created.

## Ajouter les DLL ##

Take the following DLL which are in the BIN or LIB folder and place them beside GetRandomGame.exe in the DEBUG folder.

  * freetype6.dll
  * ftgl.dll
  * SDL.dll
  * SDL\_image.dll

### For a release Build ###

Add those: (that can all be found in a MinGW sub-folder)
  * libgcc\_s\_dw2-1.dll
  * libpng12-0.dll
  * libstdc++-6.dll
  * zlib1.dll

## Linker flags ##

**NOTHING TO DO HERE**

You should have something like that:
```
-lmingw32 -lSDL_image -lSDLmain -lSDL -lopengl32 -lglu32 -lfreetype -lftgl
```

The names may change but <font color='red'><b>the order shouldn't be changed</b></font>!


---

# Possible Errors and Debugging tips #

## unrecognised emulation mode:windows ##

Remove the -mwindows linker flag.

if it doesn't work, [Stack Overflow might help](http://stackoverflow.com/q/663811)

## Pure virtual stuff? ##

```
The type 'FTTextureFont' must implement the inherited pure virtual method 'FTFont::MakeGlyph'
```

Une fonction de la classe parent est affectée la valeur zéro de cette façon:
  * void someFunction() = 0;

Il est primordial de la redéfinir dans la sous-classe.

## Application Crashes on start up? ##

L'application plante au démarrage? While debugging, you see something like that?

```
gdb: unknown target exception 0xc0000135 at 0x7724f52f
```

Avec ce genre d'erreur lors du debug, il est facile d'avoir un message plus clair en utilisant le gdb (débugger) en ligne de commande.

You should try using the gdb in the windows command line (DOS emulator).

```
C:\Users\Emile\workspace\GetRandomGame\Debug>gdb GetRandomGame
GNU gdb (GDB) 7.3.1
Copyright (C) 2011 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "mingw32".
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>...
Reading symbols from c:\users\emile\workspace\getrandomgame\debug\GetRandomGame.
exe...done.


(gdb) run
Starting program: c:\users\emile\workspace\getrandomgame\debug\GetRandomGame.exe

[New Thread 2748.0x1e24]
gdb: unknown target exception 0xc0000135 at 0x7724f52f
During startup program exited with code 0xc0000135.
(gdb)
```

Une fenêtre d'erreur devrait apparaître et indiquer un nom de fichier manquant.


---

# Information sur les lib, mais rien a faire #
## SDL Extension Libraries ##

Chaque bibliothèque SDL possède trois parties essentielles :

  * Les fichiers d'entête (**.h)
  * Le fichier lib
  * Le(s) fichier(s) dll**

### SDL ###

Téléchargez la version de SDL spécialement compilé pour Mingw. (Voir onglet Download)
(SDL-devel-1.2.14-mingw32.tar.gz)

  1. Comme pour toute installation de SDL, copiez bin\SDL.dll vers C:\WINDOWS ou le dossier de l'éxecutable (DEBUG ou RELEASE)
  1. Copiez le contenu de SDL-version\lib (libSDL.dll.a, libSDL.la, libSDLmain.a) vers C:\MinGW\lib ou ajoutez simplement le dossier lib aux Library Path.
  1. Copiez le contenu de SDL-version\include (copiez le dossier SDL) vers C:\MinGW\include\ ou ajoutez simplement le dossier include aux Include du projet.

##### [SDL image](http://getrandomgame.googlecode.com/files/SDL_image-devel-1.2.10-VC.zip) #####

#include "SDL/SDL\_image.h" (not needed)

![http://loka.developpez.com/tutoriel/sdl/bibliotheques/bib_codeblocks/images/SDL_image_CodeBlocks.png](http://loka.developpez.com/tutoriel/sdl/bibliotheques/bib_codeblocks/images/SDL_image_CodeBlocks.png)

## OpenGL ##
ça c'est déjà inclu dans Global, mais au cas ou, les voici:
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

MinGW C++ Linker > Libraries
  * opengl32
  * glu32

### Free Type 2 ###

  1. Unzip wherever you want <font color='red'>(not in the project workspace)</font>
  1. Follow its Download page instructions.
  1. Add the linker flag: "libfreetype" (or the name of the lib you've got)

### FTGL ###

**It needs a working copy of FreeType2, so you need to have FreeType2 first**

  1. Unzip wherever you want (not in the project workspace)
  1. Compile the lib with MinGW (you can import the MS visual C++ or visual studio project in code::block, link the right directories and it does it all for you)
  1. Make the project link to the include and lib folder.
  1. add ftgl.dll to the debug/release folder beside the Executable file.
  1. Add the linker flag: "libftgl" (or the name of the lib you've got)

[FTGL pitfalls](http://devcry.heiho.net/2012/01/opengl-font-rendering-with-ftgl.html)