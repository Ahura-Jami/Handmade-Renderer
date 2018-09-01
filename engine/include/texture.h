#ifndef ENGINE_TEXTURE_H
#define ENGINE_TEXTURE_H

#include <glad/glad.h>
#include <string>

struct TextureInfo
{
	TextureInfo() = default;
	~TextureInfo();

	GLubyte* data;
	int height;
	int width;
	int num_channels;
};

class Texture
{
public:
	/**
	 * (Constructor) Creates a texture object from input texture file
	 * @param [in] texture_path Absolute path to the texture file
	 */
	Texture(const std::string& texture_path);

private:
	/**
	 * Loads the texture file
	 * @param [in] texture_path Absolute path to the texture file
	 * @param [out] texture_info A pointer to TextureInfo struct that will contain the loaded texture information
	 */
	void LoadTextureFile(const std::string& texture_path, TextureInfo* texture_info) const;

	/**
	 * Generates and binds a 2D texture object from the loaded texture
	 * @param [in] texture_info Loaded texture information
	 * @return A reference to the generated 2D texture
	 */
	GLuint GenerateTexture2D(const TextureInfo& texture_info);

public:
	/**
	 * @return The texture object
	 */
	GLuint GetTextureReference() const { return texture; }

private:
	/**
	 * A reference to the texture object that was created by GenerateTexture function
	 */
	GLuint texture;
};

#endif //ENGINE_TEXTURE_H
