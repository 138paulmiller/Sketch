#ifndef	SHADER_H
#define	SHADER_H


/*
	Class used to compile shaders. 
	ON Shader Instantiation, it is automatically registered on creation
	Call shaders using getShader
*/
#include <GL/glew.h>
#include <renderer/Defs.h>
#include <renderer/Stackable.h>
#include <string>
#include <fstream>

//Segment global names
#include <renderer/ShaderGlobal.h>

SHADER_TYPES

class Shader
{
public:

	SHADER_DECLS
	//Non owning pointers
	static Shader*	current	()					;
	static void		push	( Shader* shader)	;
	static void		pop		()					;
	static void		destroy	()					;
	static void		init	()					;


	//Expects filename, and parses filename.vs and filename.fs
	Shader();
	~Shader();

			void load(const std::string & filename);
	inline	void bind()		{ glUseProgram(_programId); }  //if shader is valid
	inline	void unbind()	{ glUseProgram(0); } //if shader is valid


	int getAttribLocation(const std::string & id) const;
	int getUniformLocation(const std::string & id) const;

	void setUniformInt	(const std::string & id, int value						)const;
	void setUniformFloat(const std::string & id, float value					)const;
	void setUniformArray(const std::string & id, const float* data, GLuint count)const;
	void setUniformVec3	(const std::string & id, const Vec3& vector				)const;
	void setUniformVec4	(const std::string & id, const Vec4& vector				)const;
	void setUniformMat4	(const std::string & id, const Mat4& matrix				)const;

	inline bool isValid() { return 	 _isValid; } //if shader is valid
	

protected:
	static	bool	checkError(GLuint shader, GLuint flag, bool isProgram = false);
			GLuint	loadShader(std::string filename, GLuint type);

private:
	//Enums for each shader stage in program
	enum ShaderStage { SHADER_STAGE_VERTEX = 0, SHADER_STAGE_GEOMETRY, SHADER_STAGE_FRAGMENT, SHADER_STAGE_COUNT };
	//Shader stages
	GLuint _shaderIds[SHADER_STAGE_COUNT];
	//Shader program
	GLuint _programId;
	bool _isValid; //if shader is valid
};

#include <memory>
//Shader Manager, instatiates and frees shaders
//




//class ShaderManager
//{
//public:
//	ShaderManager();
//	~ShaderManager();
//	static ShaderManager & instance();
//
//	void bind(int id); 
//	void create(int id, const char* filename);
//
//private:
//	using ShaderMap = std::vector<std::unique_ptr<Shader> >;
//	//todo use different struture possibly O(1) with runtime additional shaders customizable 
//	ShaderMap m_shaderMap;
//
//};

#endif