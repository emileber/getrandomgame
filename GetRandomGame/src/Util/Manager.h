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

	/**
	 * Load the ressource only if not already register
	 *  string filename is the key
	 *  T * is a pointer to the ressource itself
	 */
	T * loadRessource(std::string filename) {
		if (!isLoaded(filename)) {
			T * newRessource = new T();
			newRessource->load(filename);
			registerRessource(newRessource);
			return newRessource;
		}
		return _ressourceMap[filename];
	}

	/**
	 * Clear the map
	 */
	void deleteAllRessource() {
		typename std::map<std::string, T*>::iterator pos =
				_ressourceMap.begin();
		while (pos != _ressourceMap.end()) {
			delete (*pos).second;
			pos++;
		}
		_ressourceMap.clear();
	}

	/**
	 * Reload all the ressource in the map
	 */
	void reloadAllRessource() {
		typename std::map<std::string, T*>::iterator pos =
				_ressourceMap.begin();
		while (pos != _ressourceMap.end()) {
			(*pos).second->reload();
			pos++;
		}
	}

	/**
	 * Return true if filename is already loaded
	 */
	bool isLoaded(std::string filename) {
		if (_ressourceMap.find(filename) != _ressourceMap.end()) {
			return true;
		}
		return false;
	}

	/// Add a ressource to manage
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

	void listAllRessourceKey() {
		typename std::map<std::string, T*>::iterator pos =
				_ressourceMap.begin();
		std::cout << "Ressource Map contain:" << std::endl;
		while (pos != _ressourceMap.end()) {
			std::cout << (*pos).first << std::endl;
			pos++;
		}
		std::cout << "_ressourceMap::END" << std::endl;
	}
private:
	Manager() {
	}
	virtual ~Manager() {
		deleteAllRessource();
	}

	std::map<std::string, T *> _ressourceMap;
};

#endif /* MANAGER_H_ */
