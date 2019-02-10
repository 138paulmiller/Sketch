
template <typename VertexType, ShaderType shaderType>
Mesh<VertexType, shaderType>::Mesh(GLuint drawMode ) 
		: _transform(1), _drawMode(drawMode) { }


template <typename VertexType, ShaderType shaderType>
 Mesh<VertexType, shaderType>::~Mesh() {	 }



template <typename VertexType, ShaderType shaderType>
void Mesh<VertexType, shaderType>::load() 
{
	bind();
	_vertexArray.load(Shader::current(), &_vertices[0], _vertices.size(), &_indices[0], _indices.size());
	unbind();
}

template <typename VertexType, ShaderType shaderType>
void Mesh<VertexType, shaderType>::update(float delta)
{
	bind();
	_vertexArray.update(Shader::current(), &_vertices[0], _vertices.size(), &_indices[0], _indices.size());
	Renderable::update(delta);
	unbind();
}

template <typename VertexType, ShaderType shaderType>
 void Mesh<VertexType, shaderType>::preRender()
{
	DebugAssert(_vertices.size() && _indices.size()); // > 0 size
	bind();
	onPreRender();
	Shader::current()->setUniformMat4(Shader::Uniform_Model, _transform);
}
template <typename VertexType, ShaderType shaderType>
void Mesh<VertexType, shaderType>::render()
{

	Shader::current()->setUniformMat4(Shader::Uniform_Model, _transform);
	if (_isWireframe)
	{
		//normal
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		_vertexArray.render(_drawMode);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	}
	else
	{
		_vertexArray.render(_drawMode);
	}
	Renderable::render();
	onRender();
	unbind();
}



template <typename VertexType, ShaderType shaderType>
void Mesh<VertexType, shaderType>::bind() 
{
	switch (shaderType)
	{
	case ShaderType_Point:			Shader::push(&Shader::PointShader);			break;
	case ShaderType_Flat:			Shader::push(&Shader::FlatShader);			break;
	case ShaderType_PhongColor:		Shader::push(&Shader::PhongColorShader);	break;
	case ShaderType_FlatTexture2d:	Shader::push(&Shader::Texture2dShader);		break;
	case ShaderType_Custom:			/*Custom shaders must be pushed popped by user*/break;
	}
	onBind();
}


template <typename VertexType, ShaderType shaderType>
void Mesh<VertexType, shaderType>::unbind() 
{
	/*Custom shaders must be pushed popped by user*/
	if(shaderType !=  ShaderType_Custom)
		Shader::pop();
	onUnbind();
}


