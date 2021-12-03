#include "Shader.h"
#include <fstream>

namespace OpenGL {
	static std::string ReadFileAsString(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize((size_t)in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			LOG_ERROR("Could not open file '{0}'", filepath);
		}

		return result;
	}

	static GLuint CompileShader(GLenum type, const std::string& src)
	{
		GLuint shader = glCreateShader(type);

		const GLchar* sourceCStr = src.c_str();
		glShaderSource(shader, 1, &sourceCStr, 0);

		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(shader);

			LOG_ERROR("{0}", infoLog.data());
		}

		return shader;
	}

	Shader::Shader(const std::string& vert, const std::string& frag)
	{
		std::string vert_src = ReadFileAsString(vert);
		std::string frag_src = ReadFileAsString(frag);
		
		GLuint vertex_shader = CompileShader(GL_VERTEX_SHADER, vert_src);
		GLuint fragment_shader = CompileShader(GL_FRAGMENT_SHADER, frag_src);

		m_id = glCreateProgram();
		glAttachShader(m_id, vertex_shader);
		glAttachShader(m_id, fragment_shader);

		glLinkProgram(m_id);

		GLint success = 0;
		glGetProgramiv(m_id, GL_LINK_STATUS, (int*)&success);
		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_id, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(m_id);

			glDeleteShader(vertex_shader);
			glDeleteShader(fragment_shader);

			LOG_ERROR("{0}", infoLog.data());
		}

		glDetachShader(m_id, vertex_shader);
		glDetachShader(m_id, fragment_shader);
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_id);
	}

	void Shader::Bind()
	{
		glUseProgram(m_id);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}

	void Shader::SetFloat(const std::string& name, float v)
	{
		glUniform1f(GetLocation(name), v);
	}
	
	void Shader::SetVector2(const std::string& name, glm::vec2 v)
	{
		glUniform2f(GetLocation(name), v.x, v.y);
	}
	
	void Shader::SetVector3(const std::string& name, glm::vec3 v)
	{
		glUniform3f(GetLocation(name), v.x, v.y, v.z);
	}
	
	void Shader::SetVector4(const std::string& name, glm::vec4 v)
	{
		glUniform4f(GetLocation(name), v.x, v.y, v.z, v.w);
	}
	
	void Shader::SetInt(const std::string& name, int v)
	{
		glUniform1i(GetLocation(name), v);
	}
	
	void Shader::SetIVector2(const std::string& name, glm::ivec2 v)
	{
		glUniform2i(GetLocation(name), v.x, v.y);
	}
	
	void Shader::SetIVector3(const std::string& name, glm::ivec3 v)
	{
		glUniform3i(GetLocation(name), v.x, v.y, v.z);
	}
	
	void Shader::SetIVector4(const std::string& name, glm::ivec4 v)
	{
		glUniform4i(GetLocation(name), v.x, v.y, v.z, v.w);
	}
	
	void Shader::SetMatrix3(const std::string& name, glm::mat3 v)
	{
		glUniformMatrix3fv(GetLocation(name), 3 * 3, false, glm::value_ptr(v));
	}
	
	void Shader::SetMatrix4(const std::string& name, glm::mat4 v)
	{
		glUniformMatrix4fv(GetLocation(name), 4 * 4, false, glm::value_ptr(v));
	}
	
	GLint Shader::GetLocation(const std::string& name)
	{
		if (m_location_cache.find(name) != m_location_cache.end()) {
			return m_location_cache[name];
		}
		GLint loc = glGetUniformLocation(m_id, name.c_str());
		m_location_cache[name] = loc;
		return loc;
	}
}