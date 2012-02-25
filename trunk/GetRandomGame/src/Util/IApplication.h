/*
 * ApplicationInterface.h
 *
 *  Created on: 2012-02-24
 *      Author: Emile
 */

#ifndef APPLICATIONINTERFACE_H_
#define APPLICATIONINTERFACE_H_

/*
 *
 */
class IApplication {
public:
	virtual ~IApplication() {}

	virtual void Update() = 0; // generic function, redefine by the subclass
	virtual void Draw() = 0; // generic function, redefine by the subclass
	virtual void Close() = 0; // generic function, redefine by the subclass
};

#endif /* APPLICATIONINTERFACE_H_ */
