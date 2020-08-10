//
//  Shader.cpp
//  OpenGL-Learning
//
//  Created by 杨义轩 on 2020/8/3.
//  Copyright © 2020 杨义轩. All rights reserved.
//

#include "Shader.hpp"
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit|std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit|std::ifstream::badbit);
    try{
        // 打开文件
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // 读取文件的缓冲内容到数据流中
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        //关闭文件
        vShaderFile.close();
        fShaderFile.close();
        //转换数据流到string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }catch(std::ifstream::failure e){
        std::cout<<"ERROR::SHADER::文件未能成功读取" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    //2.编译着色器
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    //顶点着色器
    vertex =  glad_glCreateShader(GL_VERTEX_SHADER);
    glad_glShaderSource(vertex,1,&vShaderCode,NULL);
    glad_glCompileShader(vertex);
    glad_glGetShaderiv(vertex,GL_COMPILE_STATUS,&success);
    if(!success){
        glad_glGetShaderInfoLog(vertex,512,NULL,infoLog);
        std::cout<<"ERROR::SHADER::顶点着色器编译失败\n"<<infoLog<<std::endl;
    };
    fragment =  glad_glCreateShader(GL_FRAGMENT_SHADER);
    glad_glShaderSource(fragment,1,&fShaderCode,NULL);
    glad_glCompileShader(fragment);
    glad_glGetShaderiv(fragment,GL_COMPILE_STATUS,&success);
    if(!success){
        glad_glGetShaderInfoLog(fragment,512,NULL,infoLog);
        std::cout<<"ERROR::SHADER::片段着色器编译失败\n"<<infoLog<<std::endl;
    };
    ID = glad_glCreateProgram();
    glad_glAttachShader(ID,vertex);
    glad_glAttachShader(ID,fragment);
    glad_glLinkProgram(ID);
    glad_glGetProgramiv(ID,GL_LINK_STATUS,&success);
    if(!success){
        glad_glGetProgramInfoLog(ID,512,NULL,infoLog);
        std::cout<<"ERROR::SHADER::着色器链接失败\n"<<infoLog<<std::endl;
    };
    glad_glDeleteShader(vertex);
    glad_glDeleteShader(fragment);
}
void Shader::use(){
    glad_glUseProgram(ID);
}
void Shader::setBool(const std::string &name, bool value)const{
    glad_glUniform1i(glad_glGetUniformLocation(ID,name.c_str()),(int)value);
}
void Shader::setInt(const std::string &name, int value)const{
      glad_glUniform1i(glad_glGetUniformLocation(ID,name.c_str()),value);
}
void Shader::setFloat(const std::string &name, float value)const{
    glad_glUniform1f(glad_glGetUniformLocation(ID,name.c_str()),value);
}
void Shader::setMat4(const std::string &name, glm::mat4 value)const{
    int location = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
