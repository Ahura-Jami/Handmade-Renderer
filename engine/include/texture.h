#ifndef ENGINE_TEXTURE_H
#define ENGINE_TEXTURE_H

#include <glad/glad.h>
#include <string>

/** Texture data and configuration */
struct TextureData
{
	TextureData() = default;

	/** Format of texture object */
	GLuint internal_format;

	/** Format of loaded image */
	GLuint image_format;

	/** Height of the loaded image */
	int width;

	/** Height of the loaded image */
	int height;

	/** Number of color channels of the loaded image */
	int num_channels;

	/** Wrapping mode on S axis*/
	GLuint wrap_s;

	/** GWrapping mode on T axis*/
	GLuint wrap_t;

	/** Filtering mode if texture pixels < screen pixels */
	GLuint filter_min;

	/** filtering mode if texture pixels > screen pixels */
	GLuint filter_mag;
};

/**
 * Texture2D is able to store and configure a texture in OpenGL.
 * It also hosts utility functions for easy management.
 */
class Texture2D
{
public:
	/**
	 * (Constructor) Creates a texture object from input texture file
	 * @param [in] texture_path Absolute path to the texture file
	 */
	Texture2D(const std::string& texture_path);

	/**
	 * Binds this texture to be used and rendered
	 */
	void Bind() const;

private:
	/**
	 * Loads the texture file
	 * @param [in] texture_path Absolute path to the texture file
	 * @param [out] texture_info A pointer to TextureInfo struct that will contain the loaded texture information
	 */
	GLubyte* LoadTextureFile(const std::string& texture_path);

	/**
	 * Generates and binds a 2D texture object from the loaded texture
	 * @param [in] texture_info Loaded texture information
	 * @return A reference to the generated 2D texture
	 */
	GLuint GenerateTexture2D(const GLubyte* image_data);

public:
	/**
	 * A reference to the texture object that was created by GenerateTexture function
	 * All texture operations should refer to this object
	 */
	GLuint id;

private:
	/** Texture data */
	TextureData data;
};

#endif //ENGINE_TEXTURE_H
