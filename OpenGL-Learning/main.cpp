#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Shader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
int main()
{
//    glfw实例化
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    cout<<"完成glfw实例化"<<endl;
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello OpenGL", NULL, NULL);
    if(window==NULL){
//        cout<<window<<endl;
        cout<<"创建glfw窗口失败"<<endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    cout<<"完成窗口对象创建"<<endl;
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout<<"初始化GLAD失败"<<endl;
        return -1;
    }
    cout<<"初始化GLAD"<<endl;
    //这一句会影响三角形的初始位置，不知道为什么！！！
//    glViewport(0,0,800,600);
    cout<<"初始化视口"<<endl;
    glfwSetFramebufferSizeCallback(window,  framebuffer_size_callback);
    cout<<"设置回调"<<endl;
    //创建并编译顶点着色器
    Shader ourShader("../3.3.shader.vs", "../3.3.shader.fs");
    //在更改uniform之前，一定要使用一次
    ourShader.use();
    float offset = 0.5f;
    ourShader.setFloat("offset", offset);
    //三角形
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    float vertices[] = {
    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };
    unsigned int indices[] = { // 注意索引从0开始!
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };
    //创建纹理
    unsigned int texture;
    glad_glGenTextures(1,&texture);
    glad_glBindTexture(GL_TEXTURE_2D,texture);
    //设置环绕和过滤
    glad_glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glad_glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glad_glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glad_glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    //加载纹理
    int width, height, nrChannels;
      unsigned char *data = stbi_load("../wall.jpg", &width, &height, &nrChannels, 0);
    if(data){
        glad_glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        glad_glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        std::cout<<"加载纹理失败"<<std::endl;
    }
    stbi_image_free(data);
    
    
    //创建顶点缓冲对象
    unsigned int VBO;
    glGenBuffers(1,&VBO);
    //创建VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    // 1. 绑定VAO
    glBindVertexArray(VAO);
    // 2. 把顶点数组复制到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(2*3*sizeof(float)));
    glEnableVertexAttribArray(2);
    
    //创建EBO
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //
    while(!glfwWindowShouldClose(window)){
        processInput(window);
        //绘制三角形
        
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //
        //
        ourShader.use();
        glBindVertexArray(VAO);
        glad_glBindTexture(GL_TEXTURE_2D,texture);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
        glad_glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        //解绑
        glBindVertexArray(0);
        //绘制颜色
//        glad_glClearColor(0.2f,0.3f,0.3f,1.0f);
//        glad_glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    cout<<"循环渲染"<<endl;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
//    getchar();
    return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
