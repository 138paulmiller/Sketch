#ifndef __DEFS_H__
#define __DEFS_H__

#define DEBUG_ON	 
#define DEBUG_ASSERTS 
#define DEBUG_PRINT





//Some standard defs used
// POD types are lower case
// All others are class defs

#ifdef DEBUG_ASSERTS
#include <cassert>
#	define	DebugAssert(x)			assert(x)
#	define	DebugStaticAssert(x)	static_assert(x)
#endif

#ifdef DEBUG_PRINT
#include <cstdio>
#	define	Debug(msg, ...) {printf(msg, __VA_ARGS__);}
#endif

#define	Warn(msg, ...) {	printf("\n\rWARNING:");printf(msg, __VA_ARGS__);}

#define	Error(msg, ...) {	printf("\n\r[ERROR at %s : %d]\n", __FILE__, __LINE__); \
							printf(msg, __VA_ARGS__);		\
							_writeLog( msg, __VA_ARGS__);	\
							getchar();}						\

#define LogIn(file) _openLog(file)

#define Log(msg, ...) _writeLog(msg)


#define LogOut() _closeLog()

//FILE * _logfile();
void _openLog(const char * file);
void _writeLog(const char * msg, const char * format);
void _closeLog(const char * msg);

//Lina Agl lib, replace later
#include <glm/glm.hpp>
//include after <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <algorithm>
#include <vector>

// all linear algebra types must be stored in contiguos mem and override operator[] 
// the following must be defined

typedef glm::vec2  Vec2;
typedef glm::vec3  Vec3;
typedef glm::vec4  Vec4;
typedef glm::mat4  Mat4;				/*Mat4(1) must be identity*/

typedef glm::vec3  Color3;
typedef glm::vec4  Color4;
typedef glm::uvec3 Color3u;
typedef glm::uvec4 Color4u;



 float      	dot			(const Vec2 & a,	const Vec2 & b);
 float      	dot			(const Vec3 & a,	const Vec3 & b);
 float      	dot			(const Vec4 & a,	const Vec4 & b);
//Vec2 cross		(const Vec2 & a,	const Vec2 & b);
 Vec3 	cross		(const Vec3 & a,	const Vec3 & b);
//Vec4 cross		(const Vec4 & a,	const Vec4 & b);
Mat4 	lookAt		(const Vec3 & eye,	const Vec3 & center, const Vec3 &up);
Mat4 	scale		(const Mat4 & mat,	const Vec3 & scalars);
Mat4 	rotate		(const Mat4 & mat,	const Vec3 & axis, float angle);
Mat4 	translate	(const Mat4 & mat,	const Vec3 & deltas);

#define max(x,y) std::max(x,y)
#define min(x,y) std::min(x,y)

///Replace later
//
//Contiguos array!Vector must overload .size() &v[0] must be base 
#define Array std::vector
#define List std::list

#define PI 3.14157f
#define PI_2 PI * 2



#define GLSL_PREFIX(s) std::string("../Sketch/glsl/" s)


#endif