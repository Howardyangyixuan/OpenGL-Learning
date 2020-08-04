//
//  Shader.hpp
//  OpenGL-Learning
//
//  Created by 杨义轩 on 2020/8/3.
//  Copyright © 2020 杨义轩. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <glad/glad.h>
#include <stdio.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader{
public:
    unsigned int ID;
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    void use();
    void setBool(const std::string &name,bool value)const;
    void setInt(const std::string &name, int value)const;
    void setFloat(const std::string &name, float value)const;
};
#endif /* Shader_hpp */
