
template <typename VertexCallback>
//Unit Cube
Cube<VertexCallback>::Cube()
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
	//								pos					norm			 uv	
	_vertices[i++] =	VertexCallback({ -x, -x, x },  { -x, -x,  x }	, {0,0});
	_vertices[i++] =	VertexCallback({ x, -x,  x },  { x, -x,  x }	, {1,0});
	_vertices[i++] =	VertexCallback({ x,  x,  x },  { x,  x,  x }	, {1,1});
	_vertices[i++] =	VertexCallback({ -x, x,  x },  { x, -x,  x }	, {0,1});
	//back face CCW														  
	_vertices[i++] =	VertexCallback({ -x, -x, -x }, { -x, -x, -x }	, {0,0});
	_vertices[i++] =	VertexCallback({ x, -x, -x },  { x, -x, -x }	, {1,0});
	_vertices[i++] =	VertexCallback({ x,  x, -x },  { x,  x, -x }	, {1,1});
	_vertices[i++] =	VertexCallback({ -x, x, -x },  { x, -x, -x }	, {0,1});

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
