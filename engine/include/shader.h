#ifndef ENGINE_SHADER_H
#define ENGINE_SHADER_H

#include <glad/glad.h>

#include <string>

/** Shader class */
class Shader
{
public:
	Shader() = default;

	/**
	 * [Constructor] Reads and builds the shader
	 * @param [in] vertex_code Absolute path to the vertex shader file
	 * @param [in] fragment_code Absolute path to the fragment shader file
	 */
	Shader(const std::string& vertex_code, const std::string& fragment_code, const std::string& geometry_code = "");

	/**
	 * Use/activate the shader program
	 * @return
	 */
	void Use();

	///@{
	/**
	 * Queries a uniform location and sets its value
	 * @param [in] name Name of the uniform
	 * @param [in] value Value of the uniform
	 */
	void SetBool	(const GLchar* name, GLboolean value) const;
	void SetInteger	(const GLchar* name, GLint 	   value) const;
	void SetFloat	(const GLchar* name, GLfloat   value) const;
//	void SetVector2f(const GLchar* name, GLfloat   value) const;
//	void SetVector3f(const GLchar* name, GLfloat   value) const;
//	void SetVector4f(const GLchar* name, GLfloat   value) const;
//	void SetMatrix4	(const GLchar* name, GLfloat   value) const;
	///@}
//
//	///@{
//	/**
//	 * Queries a uniform location and sets its value
//	 * @param [in] name Name of the uniform
//	 * @param [in] x
//	 */
//	void SetVector2f(const std::string& name, float value,) const;
//	void SetVector3f(const std::string& name, float value,) const;
//	void SetVector4f(const std::string& name, float value,) const;
//	///@}


private:
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
	GLuint LinkShaders(GLuint vertex, GLuint fragment, GLuint geometry = 0) const;

	/**
	 * Utility function for checking shader compilation/linking errors.
	 * @param [in] shader Unsigned reference to the shader
	 * @param [in] shader_type Type of the shader as a std::string (valid values: "VERTEX", "FRAGMENT", "PROGRAM")
	 */
	void CheckCompileOrLinkErrors(GLuint shader, const std::string &type) const;

public:
	/**
	 * The id of the shader program
	 */
	GLuint id;
};

#endif // ENGINE_SHADER_H

