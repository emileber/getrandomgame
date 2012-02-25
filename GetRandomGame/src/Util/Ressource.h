/*
 * Ressource.h
 *
 *  Created on: 2012-02-13
 *      Author: Emile
 *
 *      Abstract class to be used by the
 *      generic Manager Template.
 *
 */

#ifndef RESSOURCE_H_
#define RESSOURCE_H_

#include <iostream>

class Ressource {
public:

	Ressource() {
		mFilename = "";
		mIsLoaded = false;
	}
	virtual ~Ressource() {
	}

	/**
	 * Pure virtual function
	 * MUST be implement in sub class
	 */
	virtual void Load(std::string filename) = 0;

	virtual void Reload() {
		//std::cout << "Ressource::reload " << _filename << std::endl;
		if (mFilename != "") {
			Load(mFilename);
		}
	}

	std::string GetFilename() const {
		return mFilename;
	}

	bool IsLoaded() const {
		return mIsLoaded;
	}

protected:
	std::string mFilename;
	bool mIsLoaded;
};

#endif /* RESSOURCE_H_ */
