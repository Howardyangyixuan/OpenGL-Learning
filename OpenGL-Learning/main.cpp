//#define GLEW_STATIC
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//
//
//#include <iostream>
//using namespace std;
//
//int main()
//{
//    //glewInit();
//
//    //glewIsSupported("GL_VERSION_2_0");
//
//
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    GLFWwindow* window = glfwCreateWindow(200, 200, "m30", nullptr, nullptr);
//    if (window == nullptr)
//    {
//        cout << "Failed to create GLFW window" << endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//
//    int width, height;
//    glfwGetFramebufferSize(window, &width, &height);
//
//
//    glewInit();
//    glViewport(0, 0, width, height);
//    //glViewport(0, 0, width, height);
//    GLuint buffer[1];
//    glGenBuffers(1, buffer);
//
//    glGetString(0);
//
//
//
//    while (!glfwWindowShouldClose(window))
//    {
//        //cout << "m30" << endl;
//        glfwPollEvents();
//        glfwSwapBuffers(window);
//    }
//    glfwTerminate();
//    return 0;
//}

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
//const char *vertexShaderSource = "#version 330 core\n"
//    "layout (location = 0) in vec3 aPos;\n"
//    "void main()\n"
//    "{\n"
//    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//    "}\0";
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
//    "out vec4 vertexColor;"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos,1.0);\n"
//    "   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
    "}\0";
//const char *fragmentShaderSource = "#version 330 core\n"
//    "out vec4 FragColor;\n"
//    "void main()\n"
//    "{\n"
//    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//    "}\n\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
//"in vec4 vertexColor;\n"
"uniform vec4 ourColor;\n"
    "void main()\n"
    "{\n"
//"FragColor = vertexColor;\n"
"FragColor = ourColor;\n"
    "}\n\0";
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
    unsigned int vertexShader;
    vertexShader = glad_glCreateShader(GL_VERTEX_SHADER);
    glad_glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glad_glCompileShader(vertexShader);
    //成功与否
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    //创建并编译片段着色器
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    //着色器程序，链接两个着色器
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    //激活程序
    glUseProgram(shaderProgram);
    //删除着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    //三角形
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    float vertices[]={
    //        -0.5f, -0.5f, 0.0f,
    //        0.5f, -0.5f, 0.0f,
    //        0.0f,  0.5f, 0.0f,
    //      //有冗余
    //      // 第一个三角形
    //       0.5f, 0.5f, 0.0f,   // 右上角
    //       0.5f, -0.5f, 0.0f,  // 右下角
    //       -0.5f, 0.5f, 0.0f,  // 左上角
    //       // 第二个三角形
    //       0.5f, -0.5f, 0.0f,  // 右下角
    //       -0.5f, -0.5f, 0.0f, // 左下角
    //       -0.5f, 0.5f, 0.0f   // 左上角
            //使用索引，不输入重复的点
        0.5f, 0.5f, 0.0f,   // 右上角
        0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f, // 左下角
        -0.5f, 0.5f, 0.0f   // 左上角
    };
    unsigned int indices[] = { // 注意索引从0开始!
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //创建EBO
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //
    int n =0;
    while(!glfwWindowShouldClose(window)){
        processInput(window);
        //绘制三角形
        
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUseProgram(shaderProgram);
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        //
//        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//        glDrawArrays(GL_TRIANGLES, 3, 6);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //切换：填充/线性
//        n++;
//        if(n%100>50)glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
    glDeleteProgram(shaderProgram);
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
