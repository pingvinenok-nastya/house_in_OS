/*
 * Texture.cc
 *
 *  Created on: 5 дек. 2019 г.
 *      Author: nito
 */

#include "Texture.h"
#include "globals.h"
#include <SDL2/SDL_image.h>
#include <memory>

Texture::Texture(const char * filename)
{
	auto orig_surf = std::shared_ptr<SDL_Surface>(
			IMG_Load(filename),
			SDL_FreeSurface);
	if (orig_surf == nullptr)
		SDL_DIE("Texture::Texture()");

	auto conv_surf = std::shared_ptr<SDL_Surface>(
			SDL_CreateRGBSurface(0, orig_surf->w, orig_surf->h, 32,
					0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000),
			SDL_FreeSurface);
	if (conv_surf == nullptr)
		SDL_DIE("Texture::Texture()");

	SDL_UpperBlit(orig_surf.get(), nullptr, conv_surf.get(), nullptr);

	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, conv_surf->w, conv_surf->h,
			GL_RGBA, GL_UNSIGNED_BYTE, conv_surf->pixels);
}

Texture::~Texture()
{
	glDeleteTextures(1, &_id);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, _id);
}


