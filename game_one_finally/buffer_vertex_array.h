#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
class buffer_vertex_array
{

	GLuint vao;
	GLuint vbo_;
	
public:

	
	void bind_buffer(GLuint size_byte, void* data)
	{
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo_);

		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_);
		glBufferData(GL_ARRAY_BUFFER, size_byte, data, GL_STATIC_DRAW);



		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(nullptr));
		glEnableVertexAttribArray(0);
		
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 *sizeof(GLfloat)));
		glEnableVertexAttribArray(1);


		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	void draw(const GLuint size_byte) const
	{
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, size_byte/5);
		glBindVertexArray(0);
	}
	void unbind(){
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo_);
	}


	buffer_vertex_array();
	~buffer_vertex_array();
};


