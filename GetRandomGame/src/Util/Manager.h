/*
 * Manager.h
 *
 *  Created on: 2012-02-13
 *      Author: Emile
 */

#ifndef MANAGER_H_
#define MANAGER_H_

#include "Singleton.h"
#include <iostream>
#include <map>

template<typename T>
class Manager: public Singleton<Manager<T> > {
	friend class Singleton<Manager<T> > ;
public:

	T * loadRessource(std::string filename) {
		if (!isLoaded(filename)) {
			T * newRessource = new T();
			newRessource->load(filename);
			registerRessource(newRessource);
			return newRessource;
		}
		return _ressourceMap[filename];
	}

	void deleteAllRessource();

	void reloadAllRessource() {

	}

//	std::map<std::string, T *> * getMap(){
//		return &_ressourceMap;
//	}

	bool isLoaded(std::string filename) {
		if (_ressourceMap.find(filename) != _ressourceMap.end()) {
			return true;
		}
		return false;
	}

	void registerRessource(T * ressource) {
		if (!isLoaded(ressource->getFilename())) {
			_ressourceMap[ressource->getFilename()] = ressource;
		}
	}
	/// Removes a texture from management
	void unRegisterRessource(T * ressource) {
		if (isLoaded(ressource->getFilename())) {
			_ressourceMap.erase(ressource->getFilename());
		}
	}
private:
	Manager() {
	}
	virtual ~Manager() {
	}

	std::map<std::string, T *> _ressourceMap;
};

#endif /* MANAGER_H_ */
