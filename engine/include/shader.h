#ifndef ENGINE_SHADER_H
#define ENGINE_SHADER_H

#include <glad/glad.h>

#include <string>
#include <ostream>

class Shader
{
public:
	Shader() = default;

	/**
	 * [Constructor] Reads and builds the shader
	 * @param [in] vertex_path Path to the source code of vertex shader
	 * @param [in] fragment_path Path to the source code of fragment shader
	 */
	Shader(const GLchar* vertex_path, const GLchar* fragment_path);

	/**
	 * Use/activate the shader program
	 */
	void Use();

	/**
	 * Queries a uniform location and sets its value as a bool
	 * @param [in] name Name of the uniform as std::string
	 * @param [in] value Value of the uniform as bool
	 */
	void SetBool(const std::string& name, bool value) const;

	/**
	 * Queries a uniform location and sets its value as an int
	 * @param [in] name Name of the uniform as std::string
	 * @param [in] value Value of the uniform as int
	 */
	void SetInt(const std::string& name, int value) const;

	/**
	 * Queries a uniform location and sets its value as an float
	 * @param [in] name Name of the uniform as std::string
	 * @param [in] value Value of the uniform as float
	 */
	void SetFloat(const std::string& name, float value) const;

private:

	/**
	 * Reads the shader file
	 * @param [in] shader_path Path to GLSL shader file
	 * @return Shader code as a std::string
	 * @exception Prints an error message if there was any error in reading the file
	 */
	std::string ReadShaderFile(const GLchar *shader_path) const;

	/**
	 * Creates and compile a shader of input shader_type and
	 * @param shader_type Type of the shader to be created and compiled
	 * @param shader_code Shader's code as C++ string
	 * @return An unsigned reference to the created shader
	 * @exception Prints an error message if the shader compilation failed
	 */
	GLuint CreateAndCompileShader(GLenum shader_type, const std::string &shader_code) const;

	/**
	 * Creates a shader program and links the input shaders to it
	 * @param vertex Unsigned reference to the vertex shader
	 * @param fragment Unsigned reference to the fragment shader
	 */
	GLuint LinkShaders(GLuint vertex, GLuint fragment);

	/**
	 * Utility function for checking shader compilation/linking errors.
	 * @param [in] shader Unsigned reference to the shader
	 * @param [in] shader_type Type of the shader as a std::string (valid values: "VERTEX", "FRAGMENT", "PROGRAM")
	 */
	void CheckCompileOrLinkErrors(GLuint shader, const std::string &type) const;

public:
	/**
	 * Get a reference to the shader program
	 * @return An unsigned int reference to the shader program
	 */
	GLuint GetShaderProgram() const { return shader_program; }

private:
	/**
	 * The id of the shader program
	 */
	GLuint shader_program;
};

#endif //ENGINE_SHADER_H
