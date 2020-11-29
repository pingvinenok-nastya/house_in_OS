/*
 * Texture.h
 *
 *  Created on: 5 дек. 2019 г.
 *      Author: nito
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GL/gl.h>
#include <GL/glu.h>

class Texture
{
protected:
	GLuint _id;
public:
	explicit Texture(const char * filename);
	Texture(const Texture&) = delete;
	~Texture();

	void bind();
};



#endif /* TEXTURE_H_ */
