/*
 * globals.h
 *
 *  Created on: 28 ���. 2019 �.
 *      Author: prepod
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <SDL2/SDL.h>
#include <stdexcept>
#include <string>

static inline void SDL_DIE(const char * where)
{
	throw std::runtime_error(
			std::string(where) +
			std::string(": ") +
			std::string(SDL_GetError()));
}



#endif /* GLOBALS_H_ */
