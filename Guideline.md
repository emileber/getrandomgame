# Guidelines for the Project #


Table Of Content:


---

# Project related rules #

## #include Rules ##
### Forward Declaration ###
Voir cette [question sur Stack Overflow](http://stackoverflow.com/a/553869/1218980)

Exemple de forward declaration

```
// GetRandomGame.h

// Specific and absolutely necessary includes
#include "Environment.h"
#include "World/WorldCoord.h"
#include "Graphic/Texture.h"

// necessary STL stuff
#include <vector>

// forward declaration
class WorldMap;
class Tile;
// forward declare a template
template<typename T>
class Manager;
// forward declare classes inside a namespace
namespace TileEngine {
class Engine;
class LightEngine;
class Camera;
class GuiContainer;
class Sprite;
class GLabel;
class FPoint;
}
```

```
// GetRandomGame.cpp

#include "Engine.h"

// the app state
#include "GetRandomGame.h"

// world map related
#include "WorldMap.h"
#include "MapGenerator.h"
#include "DungeonGenerator.h"
#include "World/Tile.h"

// Generic graphic classes
#include "Graphic/LightEngine.h"
#include "Graphic/Texture.h"
#include "Graphic/Camera.h"
#include "Graphic/Animation.h"
#include "Graphic/Font.h"
#include "Graphic/Behavior/GraphicTranslation.h"

// GUI related
#include "GUI/GLabel.h"
#include "GUI/GTextArea.h"
#include "GameUI/GameUI.h"

// Generic Template and functions
#include "Manager.h"
#include "Util.h"

// STL stuff
#include <ctime>
#include <math.h>

// the unique namespace we're using. The other must be specified like OtherNamespace::theFunction();
using namespace TileEngine;
```

### Chose importante à se souvenir ###
  * NEVER put "using namespace Anamspace;" in a header file. You may put it once in a CPP file.
  * Always include files from the more specific ones to the more general ones. Like that:
    * #include "ParentClass.h"
    * #include "SomeClassYouCreated.h"
    * #include "AgenericTemplateClass.h"
    * #include `<`AnyStlClass`>`
    * #include `<`likeString`>`
  * put the whole path to your file, don't include the directory inside the project config file.

## Const use ##
Les Font (et Texture) en particulier ne devraient jamais être modifiés puisqu'ils sont partagés par plusieurs objets. Donc chaque variable Font utilisé dans un objet devrait idéalement être comme ça:

```
// Reçoit un pointeur non-constant vers une variable "font" constante (read-only)
void SetFont(const Font * font){
    mFont = font;
}

// return un pointeur non constant vers une variable de Type Font constante
// a noté le const après la function, cela promet de ne pas modifier l'objet
// à qui appartient la function "GetFont()"
const Font * GetFont() const {
    return mFont;
}

/* ... */

protected:
    const Font * mFont; // le pointeur peut changer, mais pas la valeur pointée

```


# Useful Functions (#include "Util/Util.h") #

## The Util namespace ##

Can be found in the Util directory right now.

```
/**
 * Utility functions
 */
namespace Util {

std::vector<std::string> & split(const std::string & s, char delim,
		std::vector<std::string> & elems);
std::vector<std::string> split(const std::string & s, char delim);
std::string formatTime(long int total);

/**
 * Template functions
 */

/**
 * NumToStr cast any number T to a string. Use that one for outputting numbers.
 * @param number anything in fact that can be outputed to a string
 * @return an std::string with the passed argument
 */
template<typename T>
std::string numToStr(T number) {
	std::stringstream ss; //create a stringstream
	ss << number; //add number to the stream
	return ss.str(); //return a string with the contents of the stream
}

/**
 * cast any string to a specify T number. Use that one for inputs.
 * @param Text that you whant to cast to a number
 * @return a T number or Zero if not castable
 */
template<typename T>
T strToNbr(const std::string &Text) {
	std::istringstream ss(Text);
	T result;
	return ss >> result ? result : 0; // return zero if not castable
}
```

## Split a String with a Custom delimiter (in the Util namespace) ##

[Source](http://stackoverflow.com/a/236803/1218980)

```

#include <string>
#include <sstream>
#include <vector>

// Split a string and store it in the "elems" vector that you've provided
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

// Alternative: Sprit string and create a vector with the result
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    return split(s, delim, elems);
}

```