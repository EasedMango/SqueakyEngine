//#include <glad/glad.h>
//#define GLFW_INCLUDE_NONE
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <glm/ext.hpp>
//#include "linmath.h"
//#include <string>
//#include <stdlib.h>
//#include <stdio.h>
//#include <fstream>
//#include <sstream>
//#include <iostream>
//static void error_callback(int error, const char* description)
//{
//    fprintf(stderr, "Error: %s\n", description);
//}
//
//static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, GLFW_TRUE);
//}
//
//class Window {
//public:
//    static GLFWwindow* window;
//    void OnCreate() {
//        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
//        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//
//        window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
//        if (!window)
//        {
//            glfwTerminate();
//            exit(EXIT_FAILURE);
//        }
//        glfwSetKeyCallback(window, key_callback);
//
//        glfwMakeContextCurrent(window);
//        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
//        glfwSwapInterval(1);
//    }
//};
//
//class Shader {
//public:
//    static GLuint vertex_shader;
//    static GLuint fragment_shader;
//    static GLuint program;
//    std::string ReadFile(const char* filename) {
//        // 1. retrieve the vertex/fragment source code from filePath
//        std::string shaderCode;
//
//        std::ifstream ShaderFile;
//
//        // ensure ifstream objects can throw exceptions:
//        ShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//        try
//        {
//            // open files
//            ShaderFile.open(filename);
//
//            std::stringstream ShaderStream;
//            // read file's buffer contents into streams
//            ShaderStream << ShaderFile.rdbuf();
//
//            // close file handlers
//            ShaderFile.close();
//
//            // convert stream into string
//            shaderCode = ShaderStream.str();
//        }
//        catch (std::ifstream::failure e)
//        {
//            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
//        }
//
//        return shaderCode;
//    }
//
//    void OnCreate() {
//        std::string vert = ReadFile("src/Shader/defualtVert.glsl");
//        const char* vertex_shader_text = vert.c_str();
//        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
//        glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
//        glCompileShader(vertex_shader);
//
//        std::string frag = ReadFile("src/Shader/defualtFrag.glsl");
//        const char* fragment_shader_text = frag.c_str();
//        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
//        glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
//        glCompileShader(fragment_shader);
//
//        program = glCreateProgram();
//        glAttachShader(program, vertex_shader);
//        glAttachShader(program, fragment_shader);
//        glLinkProgram(program);
//    }
//};
//
//class Triangle {
//public:
//    GLuint vertex_buffer;
//    GLint mvp_location, vpos_location, vcol_location;
//    float vertices[3][5] =
//    {
//       { -0.6f, -0.4f, 1.f, 0.f, 0.f },
//       {  0.6f, -0.4f, 0.f, 1.f, 0.f },
//       {   0.f,  0.6f, 0.f, 0.f, 1.f }
//    };
//
//    void OnCreate() {
//        glGenBuffers(1, &vertex_buffer);
//        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    }
//    void SendToShader(GLuint shader_) {
//        mvp_location = glGetUniformLocation(shader_, "MVP");
//        vpos_location = glGetAttribLocation(shader_, "vPos");
//        vcol_location = glGetAttribLocation(shader_, "vCol");
//
//        glEnableVertexAttribArray(vpos_location);
//        glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
//            sizeof(vertices[0]), (void*)0);
//        glEnableVertexAttribArray(vcol_location);
//        glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
//            sizeof(vertices[0]), (void*)(sizeof(float) * 2));
//    }
//};
//
//void main() {
//    Shader* shader;
//    Window* window;
//    Triangle* triangle;
//    shader->OnCreate();
//    window->OnCreate();
//    triangle->OnCreate();
//
//    while (!glfwWindowShouldClose(window->window))
//    {
//        float ratio;
//        int width, height;
//        //mat4x4 m, p, mvp;
//        glm::mat4 m, p, mvp;
//
//        glfwGetFramebufferSize(Window::window, &width, &height);
//        ratio = width / (float)height;
//
//        glViewport(0, 0, width, height);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        m = glm::mat4(1);
//        glm::rotate(m, (float)glfwGetTime(), glm::vec3(0, 0, 1));
//        // mat4x4_rotate_Z(m, m, (float)glfwGetTime());
//        p = glm::ortho(-ratio, ratio, -1.0f, 1.0f);
//        //mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
//        mvp = p * m;
//        //mat4x4_mul(mvp, p, m);
//
//        glUseProgram(shader->program);
//        glUniformMatrix4fv(triangle->mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//
//        glfwSwapBuffers(window->window);
//        glfwPollEvents();
//    }
//    glfwDestroyWindow(window->window);
//
//    glfwTerminate();
//    exit(EXIT_SUCCESS);
//}