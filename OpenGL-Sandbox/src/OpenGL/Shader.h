#pragma once

#include "Commons.h"
#include <glm/glm.hpp>

namespace OpenGL {
	class Shader {
	public:
		// Loads two files. One for vertex shader, one for fragment shader
		Shader(const std::string& vert, const std::string& frag);
		~Shader();

		void Bind();
		void Unbind();

		// Setting Uniforms
		void SetFloat(const std::string& name, float v);
		void SetVector2(const std::string& name, glm::vec2 v);
		void SetVector3(const std::string& name, glm::vec3 v);
		void SetVector4(const std::string& name, glm::vec4 v);
		void SetInt(const std::string& name, int v);
		void SetIVector2(const std::string& name, glm::ivec2 v);
		void SetIVector3(const std::string& name, glm::ivec3 v);
		void SetIVector4(const std::string& name, glm::ivec4 v);
		void SetMatrix3(const std::string& name, glm::mat3 v);
		void SetMatrix4(const std::string& name, glm::mat4 v);

	private:
		GLint GetLocation(const std::string& name);

		GLuint m_id;
		// A cache of all uniform locations. Getting uniform locations is apparently best minimal
		std::unordered_map<std::string, GLint> m_location_cache;
	};
}