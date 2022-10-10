#include "Shader.h"
#include <LoadShader.h>

Shader::Shader(const char* _vertex_file_path, const char* _fragment_file_path)
{
	programID = LoadShaders(_vertex_file_path, _fragment_file_path);
}

void Shader::activate()
{
	glUseProgram(programID);
}

void Shader::deactivate()
{
	glDeleteProgram(programID);
}
