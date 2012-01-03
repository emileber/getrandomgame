/*
 * Singleton.h
 *
 *  Created on: 2011-12-26
 *      Author: Emile
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

template<typename T>
class Singleton {
protected:
	// Constructeur/destructeur
	Singleton() {}
	virtual ~Singleton() {}

public:
	// Interface publique
	static T *getInstance() {
		if (0 == _singleton) {
			_singleton = new T;
		}

		return (static_cast<T*>(_singleton));
	}

	static void kill() {
		if (0 != _singleton) {
			delete _singleton;
			_singleton = 0;
		}
	}

private:
	// Unique instance
	static T *_singleton;
};

template<typename T>
T *Singleton<T>::_singleton = 0;

#endif /* SINGLETON_H_ */
