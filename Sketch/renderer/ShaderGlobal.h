//TODO load from a config file
//Global shared Shader Variable Names
//default vertex attribute names


#define SHADER_TYPES						\
enum ShaderType								\
{											\
	ShaderType_Invalid = 0,					\
	ShaderType_Point = 1,					\
	ShaderType_Flat,						\
	ShaderType_PhongColor,					\
	ShaderType_FlatTexture2d,				\
	ShaderType_Custom,						\
	ShaderType_Count						\
};											\


#define SHADER_DECLS						\
static const char *	Attrib_Position;		\
static const char *	Attrib_Normal;			\
static const char *	Attrib_UV;				\
static const char *	Attrib_Color;			\
											\
static const char *	Uniform_Color;			\
											\
static const char *	Uniform_Eye;			\
static const char *	Uniform_Model;			\
static const char *	Uniform_View;			\
static const char *	Uniform_Projection;		\
											\
static const char *	Uniform_Sampler[SAMPLER_COUNT];			\
											\
static Shader PointShader;					\
static Shader FlatShader;					\
static Shader PhongColorShader;				\
static Shader Texture2dShader;				\

#define SAMPLER_COUNT	4
#define SAMPLER_ID(i)	"sampler" #i
#define SHADER_DEFS												\
const char *	Shader::Attrib_Position		= "vs_pos"		;	\
const char *	Shader::Attrib_Normal		= "vs_normal"	;	\
const char *	Shader::Attrib_UV			= "vs_uv"		;	\
const char *	Shader::Attrib_Color		= "vs_color"	;	\
																\
const char *	Shader::Uniform_Eye			= "eye"			;	\
const char *	Shader::Uniform_Color		= "color"		;	\
const char *	Shader::Uniform_Model		= "model"		;	\
const char *	Shader::Uniform_View		= "view"		;	\
const char *	Shader::Uniform_Projection	= "projection"	;	\
																\
const char *	Shader::Uniform_Sampler[SAMPLER_COUNT] ={		\
			SAMPLER_ID(0),SAMPLER_ID(1),SAMPLER_ID(2),			\
			SAMPLER_ID(3)										\
}	;															\
																\
Shader Shader::PointShader;										\
Shader Shader::FlatShader;										\
Shader Shader::PhongColorShader;								\
Shader Shader::Texture2dShader;									\

#define SHADER_INIT												\
PointShader		.load(GLSL_PREFIX("point"			));			\
FlatShader		.load(GLSL_PREFIX("flat"			));			\
PhongColorShader.load(GLSL_PREFIX("phongColor"		));			\
Texture2dShader	.load(GLSL_PREFIX("flatTexture2d"	));			\
																\
																\














