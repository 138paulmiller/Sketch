#include <renderer/Defs.h>
#include <fstream>
static FILE * logfile;
void _openLog(const char * file)
{
	fopen_s(&logfile, file, "w");
	if (logfile <=0)
		Warn("Could Not Open Log FILE!");
}
void _writeLog(const char * msg, const char * format)
{
	fprintf(logfile, msg, format);
}
void _closeLog(const char * msg)
{
	fclose(logfile);
}


 float    	dot			(const Vec2 & a,	const Vec2 & b)							{ return glm::dot(a, b);	 }
 float    	dot			(const Vec3 & a,	const Vec3 & b)							{ return glm::dot(a, b);	 }
 float    	dot			(const Vec4 & a,	const Vec4 & b)							{ return glm::dot(a, b);	 }
// const Vec2 &	cross		(const Vec2 & a,	const Vec2 & b)							{ return glm::cross(a, b);	 }
 Vec3	cross		(const Vec3 & a,	const Vec3 & b)							{ return glm::cross(a, b);	 }
// Vec4 &	cross		(const Vec4 & a,	const Vec4 & b)							{ return glm::cross(a, b);	 }
 Mat4	lookAt		(const Vec3 & eye,  const Vec3 & center, const Vec3 &up)	{ return glm::lookAt(eye, center, up);	}
 Mat4	scale		(const Mat4 & mat,  const Vec3 & scalars)					{ return glm::scale(mat, scalars);		}
 Mat4	rotate		(const Mat4 & mat,  const Vec3 & axis, float angle)			{ return glm::rotate(mat, angle, axis); }
 Mat4	translate	(const Mat4 & mat,  const Vec3 & deltas)					{ return glm::translate(mat, deltas);	}