#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Shader.hpp"
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
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello OpenGL", NULL, NULL);
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
    //三角形
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    float vertices[]={
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
           -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
    };
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    //创建EBO
    unsigned int EBO;
    glGenBuffers(1, &EBO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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
        glDrawArrays(GL_TRIANGLES, 0, 3);
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
