/*
 * Manager.h
 *
 *  Created on: 2012-02-13
 *      Author: Emile
 *
 *      Generic Template to manage Ressource sub-class.
 *      It protects you from loading a file twice.
 *
 *      Note: NO NEED TO CREATE, IT'S A SINGLETON
 *      (view the design pattern singleton for more info)
 *
 *      To have access to it:
 *      Manager<YourRessourceSubClass>::getInstance();
 *
 *      To get a ressource:
 *      Manager<YourRessourceSubClass>::getInstance()->LoadRessource("yourFilePath");
 *
 *      The file path serves as a key, if you use LoadRessource with
 *      a file that has already been loaded, you'll get the pointer to
 *      that Ressource.
 *
 *
 */

#ifndef MANAGER_H_
#define MANAGER_H_

#include "Singleton.h"
#include <iostream>
#include <map>
#include "Ressource.h"

template<typename T>
class Manager: public Singleton<Manager<T> >{
	friend class Singleton<Manager<T> > ;
public:

	/**
	 * Load the ressource only if not already register
	 *  string filename is the key
	 *  T * is a pointer to the ressource itself
	 */
	T * LoadRessource(std::string filename) {
		if (!IsLoaded(filename)) {
			T * newRessource = new T();
			newRessource->Load(filename);
			RegisterRessource(newRessource);
			return newRessource;
		}
		return mRessourceMap[filename];
	}

	/**
	 * Clear the map
	 */
	void DeleteAllRessource() {
		typename std::map<std::string, T*>::iterator pos =
				mRessourceMap.begin();
		while (pos != mRessourceMap.end()) {
			delete (*pos).second;
			pos++;
		}
		mRessourceMap.clear();
	}

	/**
	 * Reload all the ressource in the map
	 */
	void ReloadAllRessource() {
		typename std::map<std::string, T*>::iterator pos =
				mRessourceMap.begin();
		while (pos != mRessourceMap.end()) {
			(*pos).second->Reload();
			pos++;
		}
	}

	/**
	 * Return true if filename is already loaded
	 */
	bool IsLoaded(std::string filename) {
		if (mRessourceMap.find(filename) != mRessourceMap.end()) {
			return true;
		}
		return false;
	}

	/// Add a ressource to manage
	void RegisterRessource(T * ressource) {
		if (!IsLoaded(ressource->GetFilename())) {
			mRessourceMap[ressource->GetFilename()] = ressource;
		}
	}
	/// Removes a texture from management
	void UnRegisterRessource(T * ressource) {
		if (IsLoaded(ressource->GetFilename())) {
			mRessourceMap.erase(ressource->GetFilename());
		}
	}

	void ListAllRessourceKey() {
		typename std::map<std::string, T*>::iterator pos =
				mRessourceMap.begin();
		std::cout << "Ressource Map contain:" << std::endl;
		while (pos != mRessourceMap.end()) {
			std::cout << (*pos).first << std::endl;
			pos++;
		}
		std::cout << "_ressourceMap::END" << std::endl;
	}

protected:
	Manager() {
	}
	virtual ~Manager() {
		DeleteAllRessource();
	}
private:
	std::map<std::string, T *> mRessourceMap;
};

#endif /* MANAGER_H_ */
