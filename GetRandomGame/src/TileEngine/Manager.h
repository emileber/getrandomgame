/*
 * Manager.h
 *
 *  Created on: 2012-02-13
 *      Author: Emile
 */

#ifndef MANAGER_H_
#define MANAGER_H_

#include "Ressource.h"
#include "Singleton.h"
#include <map>

template<typename T>
class Manager: public Singleton<Manager<T> > {
public:

	Manager() {
	}
	virtual ~Manager() {
	}

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

	void reloadAllRessource(){

	}

	bool isLoaded(std::string filename) {
		if (_ressourceMap.find(filename) == _ressourceMap.end()) {
			return false;
		}
		return true;
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
protected:

	std::map<std::string, T *> _ressourceMap;
private:

};

#endif /* MANAGER_H_ */
