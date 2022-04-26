#include "../include/LowLevelGraphics/shaderProgram.hpp"

using namespace aml;

ShaderProgram::ShaderProgram(aml::ShaderResource &fragmentShader, aml::ShaderResource &vertexShader)
{
    // create the gl shader program
    programId = glCreateProgram();

    // bind both vertex and fragment shaders to the program
    glAttachShader(programId, vertexShader.shader);
    glAttachShader(programId, fragmentShader.shader);

    // link the program
    glLinkProgram(programId);

    // check for any runtime errors
    aml::checkForGLErrors(__FILE__, __LINE__);
    // set linkage flag to true
    compiled = true;
}
ShaderProgram::ShaderProgram()
{
    programId = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
    // delete the program
    glDeleteProgram(programId);
}
void ShaderProgram::run()
{
    // run all the shaders
    glUseProgram(programId);
}

GLuint ShaderProgram::getID()
{
    return programId;
};


void ShaderProgram::addShader(aml::ShaderResource &shader){
    if(compiled){
        throw std::runtime_error("cannot add shader to program that has allready been compiled");
    }
    glAttachShader(programId, shader.shader);
};


void ShaderProgram::compile(){
    if(compiled){
        throw std::runtime_error("cannot compile shader program that has allready been compiled");
    }
    glLinkProgram(programId);
    compiled = true;
};

Uniform &ShaderProgram::operator[](const std::string uniformName)
{
    // insert a new uniform if there is no uniform with uniformName in uniformMap
    if (uniformMap.count(uniformName) == 0)
    {
        uniformMap[uniformName] = aml::Uniform(this, uniformName);
    }
    // return the value within the map
    return uniformMap[uniformName];
}