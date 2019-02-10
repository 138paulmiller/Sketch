#include <renderer/RenderShapes.h>



//RenderShapes
//Triangles
FlatTriangle::FlatTriangle(const Color4 & color)
{
	/*
	2
	/ \
	/___\
	0     1
	*/
	//front face CCW
	_vertices.resize(3);

	_vertices[0] = NormalVertex({ { -1.0f, -1.0f, 0.1f },{ -1.0f, -1.0f, -0.1f } });
	_vertices[1] = NormalVertex({ { 1.0f, -1.0f, 0.1f },{ -1.0f, -1.0f, -0.1f } });
	_vertices[2] = NormalVertex({ { 0.0f,  1.0f, 0.1f },{ -1.0f, -1.0f, -0.1f } });

	_indices.resize(3);
	_indices[0] = 0;
	_indices[1] = 1;
	_indices[2] = 2;
	_color = color;
	Mesh::load();
}

PhongColorTriangle::PhongColorTriangle(const Color4 colors[3])
{
	/*
	2
	/ \
	/___\
	0     1
	*/
	//front face CCW

	_vertices.resize(3);
	_vertices[0] = ColorVertex({ { -1.0f, -1.0f, 0.1f },{ -1.0f, -1.0f, -0.1f }, colors[0] });
	_vertices[1] = ColorVertex({ { 1.0f, -1.0f, 0.1f },{ -1.0f, -1.0f, -0.1f }, colors[1] });
	_vertices[2] = ColorVertex({ { 0.0f,  1.0f, 0.1f },{ -1.0f, -1.0f, -0.1f }, colors[2] });

	_indices.resize(3);
	_indices[0] = 0;
	_indices[1] = 1;
	_indices[2] = 2;

	Mesh::load();
}


TextureTriangle::TextureTriangle(Texture * texture)
{
	_texture = texture;
	/*
	2
	/ \
	/___\
	0     1
	*/
	//front face CCW
	_vertices.resize(3);
	_vertices[0] = Texture2dVertex({ { -1.0f, -1.0f, 0.1f },{ -1.0f, -1.0f, -0.1f },{ 1.0f, 0.0f } });
	_vertices[1] = Texture2dVertex({ { 1.0f, -1.0f, 0.1f },{ -1.0f, -1.0f, -0.1f },{ 0.0f, 1.0f } });
	_vertices[2] = Texture2dVertex({ { 0.0f,  1.0f, 0.1f },{ -1.0f, -1.0f, -0.1f },{ 0.0f, 0.0f } });

	_indices.resize(3);
	_indices[0] = 0;
	_indices[1] = 1;
	_indices[2] = 2;

	Mesh::load();
}


//Grid
FlatGrid::FlatGrid(float width, float height, float tessalation, const Color4 &color)
{
	/*
	Use triangle fan
	0 ___1 ___2 ___3
	|	 |	  |    |
	4|__ 5|__6 |__7 |
	....
	m-4|m-3 |m-2 |m-1 |
	n-4 n-3  n-2  n-1
	mxn where  m=floor(height*tess)
	n=floor(width*tess)
	tessalation determined how many rows/cols are created
	*/
	Mesh::setDrawMode(GL_TRIANGLE_STRIP);
	float incW = tessalation*width;
	float incH = tessalation*height;
	bool notfloor = false;
	int a, b, c, d;
	int w = 0;
	int h = 0;

	for (float y = 0; y <= height; y += incH)
	{
		h++;
		for (float x = 0; x <= width; x += incW)
		{
			if (y == 0)w++;
			_vertices.push_back(NormalVertex({ x,y,0 }, { 0,0,-1 }));
		}
	}
	_color = color;
	/*
	B 
	A 

	*/
	//h++;
	//w++;
	for (int y = 1; y < h; y++)
		for (int x = 0; x < w; x++)
		{
			a = (y - 1)*w + x;
			b = (y)*w + x;

			_indices.push_back(a);
			_indices.push_back(b);
		}
	Mesh::load();
}


//Unit Cube
PhongColorCube::PhongColorCube(const Color4 color[8])
{
	/*   
	   7 ______6
	    /|   / |
	 3 /_|__/2 |
	  |  |  |  |
	  | 4|__|__| 5
	  | /   | /
	  |/____|/
	  0      1
	*/
	//front face CCW
	int i = 0;
	static const float x = 0.5;

	_vertices.resize(8);
	//								pos					norm				
	_vertices[i++] = ColorVertex({ -x, -x, x },		{ -x, -x,  x },		color[0]);
	_vertices[i++] = ColorVertex({ x, -x,  x },		{ x, -x,  x },		color[1]);
	_vertices[i++] = ColorVertex({ x,  x,  x },		{ x,  x,  x },		color[2]);
	_vertices[i++] = ColorVertex({ -x, x,  x },		{ x, -x,  x },		color[3]);
	//back face CCW 												 
	_vertices[i++] = ColorVertex({ -x, -x, -x },	{ -x, -x, -x },		color[4]);
	_vertices[i++] = ColorVertex({ x, -x, -x },		{ x, -x, -x },		color[5]);
	_vertices[i++] = ColorVertex({ x,  x, -x },		{ x,  x, -x },		color[6]);
	_vertices[i++] = ColorVertex({ -x, x, -x },		{ x, -x, -x },		color[7]);

	_indices.resize(36);
	//faces a,b,c CCW Orientation
	i = 0;
	//front 
	_indices[i++] = 0;	_indices[i++] = 1;	_indices[i++] = 2;
	_indices[i++] = 0;	_indices[i++] = 2;	_indices[i++] = 3;
	//right
	_indices[i++] = 1;	_indices[i++] = 5;	_indices[i++] = 6;
	_indices[i++] = 1;	_indices[i++] = 6;	_indices[i++] = 2;
	//back
	_indices[i++] = 4;	_indices[i++] = 6;	_indices[i++] = 5;
	_indices[i++] = 4;	_indices[i++] = 7;	_indices[i++] = 6;
	//left
	_indices[i++] = 4;	_indices[i++] = 0;	_indices[i++] = 3;
	_indices[i++] = 4;	_indices[i++] = 3;	_indices[i++] = 7;

	//bottom
	_indices[i++] = 0;	_indices[i++] = 4;	_indices[i++] = 5;
	_indices[i++] = 0;	_indices[i++] = 5;	_indices[i++] = 1;
	//top
	_indices[i++] = 3;	_indices[i++] = 7;	_indices[i++] = 6;
	_indices[i++] = 3;	_indices[i++] = 6; 	_indices[i++] = 2;

	this->load();
}

PointSphere::PointSphere(float tessalation, const Color4 & color)
{
	DebugAssert(tessalation > 0 && tessalation < 0.5);
	this->setDrawMode(GL_POINTS);
	_color = color;
	//increment by PI/2*tessalation from 0 to PI/2 for tau, 
	/*
	|	rho sin(phi)cos(t)
	|	rho sin(phi)sin(t)
	|	rho cos(phi)

	*/
	const float rho = 1;

	const float inc = tessalation * PI_2;
	float phi, theta;

	for (phi = 0; phi <= PI_2; phi += inc)
	{
		for (theta = 0; theta <= PI_2; theta += inc)
		{
			_vertices.push_back(PointVertex(
			{
				rho * sin(phi) * cos(theta),
				rho * sin(phi) * sin(theta),
				rho * cos(phi),
			}
			));
			_indices.push_back(_vertices.size() - 1);
		}
	}
	load();
}

#define SPHERE_POINT(_rho,_phi,_theta)	\
								{	\
_rho * sin(_phi) * cos(_theta),	\
_rho * sin(_phi) * sin(_theta),	\
_rho * cos(_phi)				}	\



PhongColorSphere::PhongColorSphere(float tessalation, const Color4 & color)
	:	Mesh<ColorVertex, ShaderType_PhongColor>(GL_TRIANGLE_STRIP)
{
	DebugAssert(tessalation > 0 && tessalation < 0.5);
	_color = color;
	//increment by PI/2*tessalation from 0 to PI/2 for tau, 
	/*
		|	rho sin(phi)cos(t)
		|	rho sin(phi)sin(t)
		|	rho cos(phi)

	*/
	const float rho = 1;
	Vec3 pos, norm;
	Color4 col;
	ColorVertex vert;
	
	const float inc = tessalation * PI_2 *2;
	const float inc2 = inc * 2;
	float phi, theta, nextPhi, nextTheta;
	
	int count = (int)(PI_2 / inc);

	_indices.resize(count*(count)*2);
	int i =0;
	for (phi = 0; phi <= PI_2 ; phi += inc)
	{

		for (theta = 0; theta <= PI_2; theta += inc2)
		{


			/*  b___d
				|\  |
				| \ |
				|__\|
				a   c
			*/
			nextPhi = phi + inc;
			nextTheta = theta + inc;
			//a
			pos = SPHERE_POINT(rho,phi, theta);
			norm = pos;
			col = Color4(pos[0], pos[1], pos[2],1);
			vert = ColorVertex(pos, norm, color);
			_indices[i++] = _vertices.size();
			_vertices.emplace_back(vert);

			//b
			pos = SPHERE_POINT(rho, nextPhi, theta);
			norm = pos;
			col = Color4(pos[0], pos[1], pos[2], 1);
			vert = ColorVertex(pos, norm, color);
			_indices[i++] = _vertices.size();
			_vertices.emplace_back(vert);

			////c
			//pos = SPHERE_POINT(rho, phi, nextTheta);
			//norm = pos;
			//col = Color4(pos[0], pos[1], pos[2], 1);
			//vert = ColorVertex(pos, norm, color);
			//_indices[i++] = _vertices.size();
			//_vertices.emplace_back(vert);

			////d
			//pos = SPHERE_POINT(rho, nextPhi, nextTheta);
			//norm = pos;
			//col = Color4(pos[0], pos[1], pos[2], 1);
			//vert = ColorVertex(pos, norm, color);
			//_indices[i++] = _vertices.size();
			//_vertices.emplace_back(vert);


		}
	}


	load();
}
