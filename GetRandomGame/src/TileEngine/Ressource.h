/*
 * Ressource.h
 *
 *  Created on: 2012-02-13
 *      Author: Emile
 */

#ifndef RESSOURCE_H_
#define RESSOURCE_H_


class Ressource {
public:

	Ressource() {
		_filename = "";
		_isLoaded = false;
		//this->load(filename);
	}
	virtual ~Ressource() {
	}
	virtual void load(std::string filename) = 0;

	std::string getFilename() const {
		return _filename;
	}

	bool isLoaded() const{
		return _isLoaded;
	}

protected:
	std::string _filename;
	bool _isLoaded;
private:

};

#endif /* RESSOURCE_H_ */
