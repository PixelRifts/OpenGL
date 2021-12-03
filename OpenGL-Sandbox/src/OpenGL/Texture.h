#pragma once

#include "Commons.h"

namespace OpenGL {
	// Corresponds to the format in which the texture is stored in memory
	// This list is definitely not complete
	enum class TextureFormat {
		NONE = -1, // Invalid State
		RGB,
		RGBA,
		RED_INT,
		RED_UINT,
		DEPTH,
		DEPTH_STENCIL
	};

	bool IsDepthFormat(TextureFormat format);
	GLenum GetGLInternalFormat(TextureFormat format);
	GLenum GetGLFormat(TextureFormat format);
	GLenum GetGLDatatype(TextureFormat format);

	// Corresponds to how a Texture get's resized if being mapped to a bigger or smaller part of the screen
	enum class TextureResizeFilterType {
		LINEAR,
		NEAREST,
		LINEAR_MIPMAP_LINEAR,
		LINEAR_MIPMAP_NEAREST,
		NEAREST_MIPMAP_LINEAR,
		NEAREST_MIPMAP_NEAREST,
	};

	bool IsMagFilterFilter(TextureResizeFilterType format);
	GLenum GetGLDatatype(TextureResizeFilterType format);

	// Dictates how the Texture get's sampled if the UVs are not between 0-1
	enum class TextureWrapFilterType {
		CLAMP_TO_EDGE,
		MIRROR_CLAMP_TO_EDGE,
		CLAMP_TO_BORDER,
		REPEAT,
		MIRRORED_REPEAT
	};

	GLenum GetGLDatatype(TextureWrapFilterType format);


	// This is the blueprint of a texture
	// This holds all the parameters to be used
	struct TextureSpec {
		TextureFormat Format = TextureFormat::RGBA;
		// Describes how the texture get's sampled when minified
		TextureResizeFilterType MinFilter = TextureResizeFilterType::NEAREST;
		// Describes how the texture get's sampled when magnified
		TextureResizeFilterType MagFilter = TextureResizeFilterType::NEAREST;

		// Describes how the texture get's sampled when sampling >1 or <0 is done in x dir
		TextureWrapFilterType RFilter = TextureWrapFilterType::REPEAT;
		// Describes how the texture get's sampled when sampling >1 or <0 is done in y dir
		TextureWrapFilterType SFilter = TextureWrapFilterType::REPEAT;
		// Describes how the texture get's sampled when sampling >1 or <0 is done in z dir
		TextureWrapFilterType TFilter = TextureWrapFilterType::REPEAT;
	};

	class Texture2D {
	public:
		// Wraps a id in a Texture instance
		Texture2D(GLuint id);
		// Creates a Texture with the specified size. with the provided spec. Also allocates the required data
		Texture2D(uint32_t width, uint32_t height, TextureSpec spec);
		// Loads a Texture from the filesystem.
		Texture2D(const std::string& path);
		~Texture2D();

		void Bind();
		void Bind(int slot);
		void Unbind();

		// Reallocates the data with the new size
		void Resize(uint32_t width, uint32_t height);
		// Sets the full texture
		void SetData(const void* data);
		// Sets a portion of the full texture
		void SetData(uint32_t xoff, uint32_t yoff, uint32_t xsize, uint32_t ysize, const void* data);
	private:
		GLuint m_id;
		uint32_t m_width;
		uint32_t m_height;
		TextureSpec m_spec;
	};
}