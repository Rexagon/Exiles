#include "Shader.h"

#include "FileSystem.h"
#include "Log.h"

std::map<std::string, std::unique_ptr<ShaderPart>> ShaderAsset::m_shaderParts;

// ShaderPart //
////////////////

class ShaderPart
{
public:
	ShaderPart(const GLenum& type)
	{
		switch (type) {
		case GL_VERTEX_SHADER:
			m_typeString = "vertex";
			break;
		case GL_FRAGMENT_SHADER:
			m_typeString = "fragment";
			break;
		case GL_GEOMETRY_SHADER:
			m_typeString = "geometry";
			break;
		case GL_COMPUTE_SHADER:
			m_typeString = "compute";
			break;
		default:
			m_typeString = "unknown";
			break;
		}
		m_id = glCreateShader(type);

#ifdef DEBUG
		Log::Write("[DEBUG]", m_typeString, "shader part created");
#endif // DEBUG
	}

	~ShaderPart()
	{
		glDeleteShader(m_id);

#ifdef DEBUG
		Log::Write("[DEBUG]", m_typeString, "shader part deleted");
#endif // DEBUG
	}

	void LoadFromFile(const std::string& path)
	{
		std::string data = FileSystem::GetFileData(path);
		LoadFromString(data);
	}

	void LoadFromString(const std::string& source)
	{
		const char* sourceChars = source.c_str();
		glShaderSource(m_id, 1, &sourceChars, NULL);
	}

	bool Compile()
	{
		glCompileShader(m_id);

		GLint compilationStatus;
		glGetShaderiv(m_id, GL_COMPILE_STATUS, &compilationStatus);
		if (compilationStatus == GL_FALSE)
		{
			GLint infoLogLength;
			glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			glGetShaderInfoLog(m_id, infoLogLength, NULL, strInfoLog);

			Log::Write("[ERROR]", m_typeString, "shader part compilation failed:", strInfoLog);
			delete[] strInfoLog;

			return false;
		}

		return true;
	}

	GLuint GetId() const { return m_id; }
private:
	GLuint m_id;
	std::string m_typeString;
};


// Shader //
////////////

Shader::Shader() : m_shaderCount(0)
{
	m_id = glCreateProgram();

#ifdef DEBUG
	Log::Write("[DEBUG] shader created");
#endif // DEBUG

}

Shader::~Shader()
{
	glDeleteProgram(m_id);

#ifdef DEBUG
	Log::Write("[DEBUG] shader deleted");
#endif // DEBUG
}

void Shader::AttachPart(ShaderPart* part)
{
	glAttachShader(m_id, part->GetId());
	m_shaderCount++;
}

bool Shader::LinkProgram()
{
	if (m_shaderCount > 1) {
		glLinkProgram(m_id);

		GLint linkStatus;
		glGetProgramiv(m_id, GL_LINK_STATUS, &linkStatus);
		if (linkStatus == GL_FALSE) {
			GLint infoLogLength;
			glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			glGetProgramInfoLog(m_id, infoLogLength, NULL, strInfoLog);

			Log::Write("shader program linking failed:", strInfoLog);
			delete[] strInfoLog;
		}
		else {
			return true;
		}
	}
	else {
		throw std::runtime_error("Shader program must have at least 2 shaders");
	}

	return false;
}

void Shader::Bind()
{
	glUseProgram(m_id);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

void Shader::SetAttribute(const std::string &name, unsigned int index)
{
	glBindAttribLocation(m_id, index, name.c_str());
}

void Shader::AddUniform(const std::string &name)
{
	GLint uniformLocation = glGetUniformLocation(m_id, name.c_str());
	if (uniformLocation == -1) {
		Log::Write("[ERROR] unable to add uniform with name:", name);
	}
	else {
		m_uniformLocations[name] = uniformLocation;
	}
}

GLuint Shader::GetUniformLocation(const std::string & name)
{
	auto it = m_uniformLocations.find(name);
	if (it == m_uniformLocations.end()) {
		GLuint location = glGetUniformLocation(m_id, name.c_str());
		m_uniformLocations[name] = location;
		return location;
	}
	else {
		return it->second;
	}
}

void Shader::SetUniform(const std::string & name, int u)
{
	glUniform1i(GetUniformLocation(name), u);
}

void Shader::SetUniform(const std::string & name, float u)
{
	glUniform1f(GetUniformLocation(name), u);
}

void Shader::SetUniform(const std::string & name, const vec2 & u)
{
	glUniform2f(GetUniformLocation(name), u.x, u.y);
}

void Shader::SetUniform(const std::string & name, const ivec2 & u)
{
	glUniform2i(GetUniformLocation(name), u.x, u.y);
}

void Shader::SetUniform(const std::string & name, const vec3 & u)
{
	glUniform3f(GetUniformLocation(name), u.x, u.y, u.z);
}

void Shader::SetUniform(const std::string & name, const ivec3 & u)
{
	glUniform3i(GetUniformLocation(name), u.x, u.y, u.z);
}

void Shader::SetUniformArray(const std::string & name, int* arr, int size)
{
	glUniform1iv(GetUniformLocation(name), size, arr);
}

void Shader::SetUniformArray(const std::string & name, float* arr, int size)
{
	glUniform1fv(GetUniformLocation(name), size, arr);
}

void Shader::SetUniformArray(const std::string & name, vec2* arr, int size)
{
	glUniform2fv(GetUniformLocation(name), size, &arr[0][0]);
}

void Shader::SetUniformArray(const std::string & name, ivec2* arr, int size)
{
	glUniform2iv(GetUniformLocation(name), size, &arr[0][0]);
}

void Shader::SetUniformArray(const std::string & name, vec3* arr, int size)
{
	glUniform3fv(GetUniformLocation(name), size, &arr[0][0]);
}

void Shader::SetUniformArray(const std::string & name, ivec3* arr, int size)
{
	glUniform3iv(GetUniformLocation(name), size, &arr[0][0]);
}


// TextureAsset //
//////////////////

ShaderAsset::ShaderAsset(const std::string & vertexPart, const std::string & fragmentPart) :
	m_vertexPart(vertexPart), m_fragmentPart(fragmentPart)
{
}

ShaderAsset::ShaderAsset(const std::string & vertexPart, const std::string & geometryPart, const std::string & fragmentPart) :
	m_vertexPart(vertexPart), m_geometryPart(geometryPart), m_fragmentPart(fragmentPart)
{
}

asset_ptr ShaderAsset::Load()
{
	if (!m_shader) {
		m_shader = std::make_shared<Shader>();
		if (m_vertexPart != "") {
			m_shader->AttachPart(GetShaderPart(m_vertexPart, GL_VERTEX_SHADER));
		}

		if (m_geometryPart != "") {
			m_shader->AttachPart(GetShaderPart(m_geometryPart, GL_GEOMETRY_SHADER));
		}

		if (m_fragmentPart != "") {
			m_shader->AttachPart(GetShaderPart(m_fragmentPart, GL_FRAGMENT_SHADER));
		}

		m_shader->LinkProgram();
	}

	return m_shader;
}

ShaderPart * ShaderAsset::GetShaderPart(const std::string & name, GLenum type)
{
	auto it = m_shaderParts.find(name);
	if (it == m_shaderParts.end()) {
		std::unique_ptr<ShaderPart> shaderPart = std::make_unique<ShaderPart>(type);
		shaderPart->LoadFromFile(name);
		auto result = shaderPart.get();
		m_shaderParts[name] = std::move(shaderPart);
		return result;
	}
	else {
		return it->second.get();
	}
}
