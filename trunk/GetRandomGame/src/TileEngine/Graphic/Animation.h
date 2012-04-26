/*
 * Animation.h
 *
 *  Created on: 2012-02-24
 *      Author: Emile
 *
 *      Contains a Texture that serve as a
 *      sprite sheet, a vector of pair of Rect and
 *      frame time (AnimationFrameList) and it loop
 *      through it.
 */

// TODO finish animation class

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <string>
#include <vector>
#include "Ressource.h"
#include "GraphicType.h"

namespace TileEngine {

// holds frame data
struct AnimationFrame {
	SectionRect coords;
	uint32_t delay;
};

// typedef for readibilty
typedef std::vector<AnimationFrame> AnimationFrameList;

/*
 *
 */
class Animation: public Ressource {
public:
	Animation();
	virtual ~Animation();

	virtual void Load(std::string filename);

};

} /* namespace TileEngine */
#endif /* ANIMATION_H_ */
