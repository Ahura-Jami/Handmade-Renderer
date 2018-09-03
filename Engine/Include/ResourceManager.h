#ifndef ENGINE_RESOURCE_MANAGER_H
#define ENGINE_RESOURCE_MANAGER_H

#include <map>
#include <string>

#include "Shader.h"
#include "Texture.h"

/**
 * A static singleton ResourceManager class that hosts severalfunctions to load textures and shaders.
 * Each loaded texture and/or shader is also stored for future reference by string handles.
 * All functions and resources are static and no public constructor is defined.
 */
class ResourceManager
{
	/** Private constructor */
	ResourceManager() = default;

	/** Resource Storage */
	static std::map<std::string, Shader>& GetShaderRegistry();
	static std::map<std::string, Texture2D>& GetTextureRegistry();

public:
	/**
	 * Disallows copying or moving this singleton class
	 */
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	/**
	 * Loads and genrates a shader program from file
	 * These are vertex, fragment, or geometry shader's source code.
	 * @param name
	 * @param vertex_shader_path
	 * @param fragment_shader_path
	 * @param geometry_shader_path
	 * @return
	 */
	static Shader LoadShader(const std::string& name,
	 						 const std::string& vertex_shader_path,
	 						 const std::string& fragment_shader_path,
	 						 const std::string& geometry_shader_path = "");

	/**
	 * Retrieves a stored shader
	 * @param name
	 * @return
	 */
	static Shader GetShader(const std::string& name);

	/**
	 * Loads (and generates) a texture from file
	 * @param file
	 * @param alpha
	 * @param name
	 * @return
	 */
	static Texture2D LoadTexture(const std::string& name, const std::string& file/*, GLboolean alpha*/);

	/**
	 * Retrieves a stored texture
	 * @param name
	 * @return
	 */
	static Texture2D GetTexture(const std::string& name);

	/**
	 * Properly de-allocates all loaded resources
	 */
	static void Clear();

private:
	/**
	 * Reads the shader file
	 * @param [in] shader_path Path to a GLSL shader file
	 * @return Shader code as a std::string
	 * @exception Prints an error message if there was any error in reading the file
	 */
	static std::string ReadShaderFile(const GLchar* shader_path);

	/**
	 * Loads the texture file
	 * @param [in] file Absolute path to the texture file
	 * @param [out] width A pointer to an integer variable that will hold the width of the loaded texture
	 * @param [out] height A pointer to an integer variable that will hold the height of the loaded texture
	 * @param [out] num_channels A pointer to an integer variable that will hold the number of color channels
	 * 							 of the loaded image
	 * @return GLubyte* (aka unsigned char*) Pointer to loaded image data
 	 * @exception Prints an error message if there was any error in reading the texture file
	 */
	static GLubyte* ReadTextureFile(const std::string& file, int* width, int* height, int* num_channels);
};

#endif //ENGINE_RESOURCE_MANAGER_H
