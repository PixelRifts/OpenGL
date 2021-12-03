#include "Texture.h"
#include <stb_image/stb_image.h>

namespace OpenGL {
	// Conversion maps from presets
	bool IsDepthFormat(TextureFormat format)
	{
		switch (format) {
		case TextureFormat::NONE: return false;
		case TextureFormat::RGB: return false;
		case TextureFormat::RGBA: return false;
		case TextureFormat::RED_INT: return false;
		case TextureFormat::RED_UINT: return false;
		case TextureFormat::DEPTH: return true;
		case TextureFormat::DEPTH_STENCIL: return true;
		}
		return false;
	}

	GLenum GetGLInternalFormat(TextureFormat format)
	{
		switch (format) {
		case TextureFormat::NONE: return GL_NONE;
		case TextureFormat::RGB: return GL_RGB8;
		case TextureFormat::RGBA: return GL_RGBA8;
		case TextureFormat::RED_INT: return GL_R32I;
		case TextureFormat::RED_UINT: return GL_R32UI;
		case TextureFormat::DEPTH: return GL_DEPTH24_STENCIL8;
		case TextureFormat::DEPTH_STENCIL: return GL_DEPTH24_STENCIL8;
		}
		return GL_INVALID_ENUM;
	}

	GLenum GetGLFormat(TextureFormat format)
	{
		switch (format) {
		case TextureFormat::NONE: return GL_NONE;
		case TextureFormat::RGB: return GL_RGB;
		case TextureFormat::RGBA: return GL_RGBA;
		case TextureFormat::RED_INT: return GL_RED_INTEGER;
		case TextureFormat::RED_UINT: return GL_RED_INTEGER;
		case TextureFormat::DEPTH: return GL_DEPTH_STENCIL_ATTACHMENT;
		case TextureFormat::DEPTH_STENCIL: return GL_DEPTH_STENCIL_ATTACHMENT;
		}
		return GL_INVALID_ENUM;
	}

	GLenum GetGLDatatype(TextureFormat format)
	{
		switch (format) {
		case TextureFormat::NONE: return GL_UNSIGNED_BYTE;
		case TextureFormat::RGB: return GL_UNSIGNED_BYTE;
		case TextureFormat::RGBA: return GL_UNSIGNED_BYTE;
		case TextureFormat::RED_INT: return GL_UNSIGNED_BYTE;
		case TextureFormat::RED_UINT: return GL_UNSIGNED_BYTE;
		case TextureFormat::DEPTH: return GL_UNSIGNED_BYTE;
		case TextureFormat::DEPTH_STENCIL: return GL_UNSIGNED_BYTE;
		}
		return GL_INVALID_ENUM;
	}

	bool IsMagFilterFilter(TextureResizeFilterType format)
	{
		switch (format) {
		case TextureResizeFilterType::LINEAR: return true;
		case TextureResizeFilterType::NEAREST: return true;
		case TextureResizeFilterType::LINEAR_MIPMAP_LINEAR: return false;
		case TextureResizeFilterType::LINEAR_MIPMAP_NEAREST: return false;
		case TextureResizeFilterType::NEAREST_MIPMAP_LINEAR: return false;
		case TextureResizeFilterType::NEAREST_MIPMAP_NEAREST: return false;
		}
		return false;
	}

	GLenum GetGLDatatype(TextureResizeFilterType format)
	{
		switch (format) {
		case TextureResizeFilterType::LINEAR: return GL_LINEAR;
		case TextureResizeFilterType::NEAREST: return GL_NEAREST;
		case TextureResizeFilterType::LINEAR_MIPMAP_LINEAR: return GL_LINEAR_MIPMAP_LINEAR;
		case TextureResizeFilterType::LINEAR_MIPMAP_NEAREST: return GL_LINEAR_MIPMAP_NEAREST;
		case TextureResizeFilterType::NEAREST_MIPMAP_LINEAR: return GL_NEAREST_MIPMAP_LINEAR;
		case TextureResizeFilterType::NEAREST_MIPMAP_NEAREST: return GL_NEAREST_MIPMAP_NEAREST;
		}
		return GL_INVALID_ENUM;
	}

	GLenum GetGLDatatype(TextureWrapFilterType format)
	{
		switch (format) {
		case TextureWrapFilterType::CLAMP_TO_EDGE: return GL_CLAMP_TO_EDGE;
		case TextureWrapFilterType::MIRROR_CLAMP_TO_EDGE: return GL_MIRROR_CLAMP_TO_EDGE;
		case TextureWrapFilterType::CLAMP_TO_BORDER: return GL_CLAMP_TO_BORDER;
		case TextureWrapFilterType::REPEAT: return GL_REPEAT;
		case TextureWrapFilterType::MIRRORED_REPEAT: return GL_MIRRORED_REPEAT;
		}
		return GL_INVALID_ENUM;
	}


	Texture2D::Texture2D(GLuint id)
	{
		m_id = id;
		m_width = 0;
		m_height = 0;
	}

	Texture2D::Texture2D(uint32_t width, uint32_t height, TextureSpec spec)
	{
		glGenTextures(1, &m_id);
		m_width = width;
		m_height = height;
		m_spec = spec;
		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GetGLDatatype(spec.RFilter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GetGLDatatype(spec.SFilter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GetGLDatatype(spec.TFilter));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetGLDatatype(spec.MinFilter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GetGLDatatype(spec.MagFilter));

		// nullptr data so it just allocates the memory and doesn't set
		glTexImage2D(GL_TEXTURE_2D, 0, GetGLInternalFormat(spec.Format), width, height, 0, GetGLFormat(spec.Format), GetGLDatatype(spec.Format), nullptr);
	}

	Texture2D::Texture2D(const std::string& path)
	{
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		int width = 0;
		int height = 0;
		int channels = 0;
		
		stbi_set_flip_vertically_on_load(true);
		void* image = stbi_load(path.c_str(), &width, &height, &channels, 0);

		m_width = width;
		m_height = height;
		m_spec.MinFilter = TextureResizeFilterType::NEAREST;
		m_spec.MagFilter = TextureResizeFilterType::NEAREST;
		m_spec.RFilter = TextureWrapFilterType::REPEAT;
		m_spec.SFilter = TextureWrapFilterType::REPEAT;
		m_spec.TFilter = TextureWrapFilterType::REPEAT;
		if (image != nullptr) {
			switch (channels) {
			case 3:
				m_spec.Format = TextureFormat::RGB;
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
				break;
			case 4:
				m_spec.Format = TextureFormat::RGBA;
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
				break;
			default:
				LOG_ERROR("Texture Loader doesn't support {0} channels\n", channels);
			}
		} else {
			LOG_ERROR("Cannot Find Filepath {0}\n", path);
		}

		stbi_image_free(image);
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_id);
	}

	void Texture2D::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void Texture2D::Bind(int slot)
	{
		// Set's active texture slot to 'slot'
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void Texture2D::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture2D::Resize(uint32_t width, uint32_t height)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	}

	void Texture2D::SetData(const void* data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}

	void Texture2D::SetData(uint32_t xoff, uint32_t yoff, uint32_t xsize, uint32_t ysize, const void* data)
	{
		glTexSubImage2D(GL_TEXTURE_2D, 0, xoff, yoff, xsize, ysize, GetGLFormat(m_spec.Format), GetGLDatatype(m_spec.Format), data);
	}
}