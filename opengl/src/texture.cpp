#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "../inc/texture.hpp"

Texture::Texture(const char *path)
	: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr),
	  m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(true);

	m_LocalBuffer = stbi_load(path, &m_Width, &m_Height, &m_BPP, 0);

	if (!m_LocalBuffer)
		sys_error("stbi_load error");

	GLCALL( glGenTextures(1, &m_RendererID) );
	GLCALL( glBindTexture(GL_TEXTURE_2D, m_RendererID) );

	SetTexParameters();

	GLCALL( glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0,
						 GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer) );

	if(m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}

Texture::~Texture()
{
	GLCALL( glDeleteTextures(1, &m_RendererID) );
}

void
Texture::Bind(uint32 slot) const
{
	GLCALL( glActiveTexture(GL_TEXTURE0 + slot) );
	GLCALL( glBindTexture(GL_TEXTURE_2D, m_RendererID) );
}

void
Texture::Unbind() const
{
	GLCALL( glBindTexture(GL_TEXTURE_2D, 0) );
}

void 
Texture::SetTexParameters()
{
	GLCALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR) );
	GLCALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );
	GLCALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE) );
	GLCALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE) );

//	GLCALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT) );
//	GLCALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT) );
}
