#include <renderer/Shader.h>
#define SHADER_COUNT_INITIAL 10

SHADER_DEFS

//renderer and camera singletons that are bound
//create single stacks for binding/unbinding shaders, cameras, textures, matrices
namespace
{
	static std::vector<Shader * > shaderStack;
}

void Shader::init()
{
	SHADER_INIT
}

void Shader::destroy()
{
	while (!shaderStack.empty()) shaderStack.pop_back();
}


void Shader::push(Shader * shader)
{
	DebugAssert(shader);
	//bind previos
	if (!shaderStack.empty())
		shaderStack.back()->unbind();
	shaderStack.push_back(shader);
	shaderStack.back()->bind();

}

Shader * Shader::current()
{
	Shader* i = shaderStack.empty()? 0 :  shaderStack.back();
	return i;
}
void Shader::pop()
{
	shaderStack.back()->unbind();
	shaderStack.pop_back();
	//bind previos
	if (!shaderStack.empty())
		shaderStack.back()->bind();

}
// - End statics 


Shader::Shader()
{
	_isValid = false;
}




void Shader::load(const std::string & filename)
{
	Debug("\nShader::Loading %s\n", filename.c_str());
//	DebugAssert(is_Valid); //already loaded
	_isValid = 1; //default true
	_shaderIds[SHADER_STAGE_VERTEX] = loadShader(filename + ".vs", GL_VERTEX_SHADER);
	_shaderIds[SHADER_STAGE_FRAGMENT] = loadShader(filename + ".fs", GL_FRAGMENT_SHADER);
	//TODO ADD GEOMETRY SHADER
	//_shaderIds[SHADER_GEOMETRY] = loadShader(filename + ".gs", GL_GEOMETRY_SHADER);
	//link programs
	_programId = glCreateProgram();
	for (int i = 0; i < SHADER_STAGE_COUNT; i++)
	{
		if(_shaderIds[i])
			glAttachShader(_programId, _shaderIds[i]);

	}
	Debug("Linking program ...\n");
	glLinkProgram(_programId);
	_isValid = checkError(_programId, GL_LINK_STATUS, true);
	glValidateProgram(_programId);
	Debug("Validating program ...\n");
	_isValid = checkError(_programId, GL_VALIDATE_STATUS, true);
	if (_isValid)
		Debug("Shader valid! ...\n");
}


Shader::~Shader()
{

	for (int i = 0; i < SHADER_STAGE_COUNT; i++)
		if (_shaderIds[i])
		{
			glDetachShader(_programId, _shaderIds[i]);
			glDeleteShader(_shaderIds[i]); // removes

		}
	if (_programId)
		glDeleteProgram(_programId);
}

GLuint  Shader::loadShader(std::string filename, GLuint  type)
{
	//Open and read file into string
	std::string text = "";
	std::ifstream fileIn(filename);
	if (fileIn.is_open())
	{
		std::string line = "";
		while (std::getline(fileIn, line))
			text += line + "\n";
		fileIn.close();
	}
	else
	{
		Warn("Could Not Load Shader %s ", filename.c_str());
		return 0;
	}
	//Compile
	int shader = glCreateShader(type);
	const char* source = (char*)(text.c_str());
	glShaderSource(shader, 1, &source, 0);
	glCompileShader(shader);
	if (!checkError(shader, GL_COMPILE_STATUS))
	{
		_isValid = false;
		(shader = 0);
	}
	return shader;
}

int Shader::getAttribLocation(const std::string & id) const
{
	glUseProgram(_programId);
	int location = glGetAttribLocation(_programId, id.c_str());
	//if (location < 0)
	//	Warn("Shader: Could not get attrib: %s", id.c_str());
	return location;
}

int  Shader::getUniformLocation(const std::string & id)const
{
	glUseProgram(_programId);
	int location = glGetUniformLocation(_programId, id.c_str());
	//if (location < 0)
	//	Warn("Shader: Could not get uniform: %s", id.c_str());
	return location;
}
void Shader::setUniformFloat(const std::string & id, float value)const
{
	int location = getUniformLocation(id);
	glUniform1f(location, value);

}
void Shader::setUniformInt(const std::string & id, int value)const
{
	int location = getUniformLocation(id);
	glUniform1i(location, value);

}
void Shader::setUniformArray(const std::string & id, const float* array, GLuint  count)const
{
	int location = getUniformLocation(id);
	//set the vector as you would an array since in SL vectors are "essentially" arrays
	glUniform1fv(location, count, array);
}
void Shader::setUniformVec3(const std::string & id, const Vec3& vector)const
{
	int location = getUniformLocation(id);
	//set the vector as you would an array since in SL vectors are "essentially" arrays
	glUniform3fv(location, 1, glm::value_ptr(vector));
}


void Shader::setUniformVec4(const std::string & id, const Vec4& vector)	const
{
	int location = getUniformLocation(id);
	//set the vector as you would an array since in SL vectors are "essentially" arrays
	glUniform4fv(location, 1, glm::value_ptr(vector));
}

void Shader::setUniformMat4(const std::string & id, const Mat4& matrix)const
{
	int  location = getUniformLocation(id);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}


bool Shader::checkError(GLuint  shader, GLuint  flag, bool isProgram)
{
	int status = 0;
	isProgram ?
		glGetProgramiv(shader, flag, &status)
		: glGetShaderiv(shader, flag, &status);
	if (status == GL_FALSE)
	{
		int errorLen = 0;
		isProgram ?
			glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &errorLen)
			: glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorLen);
		char* errorMsg = new char[errorLen];
		isProgram ?
			glGetProgramInfoLog(shader, errorLen, &errorLen, errorMsg)
			: glGetShaderInfoLog(shader, errorLen, &errorLen, errorMsg);
		Error("Shader Log: % s\n", errorMsg);
		delete errorMsg;
		return false;
	}
	return true;
}

