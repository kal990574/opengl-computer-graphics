#include "GL/glew.h"
#define GLEW_STATIC
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "toys.h"
using namespace glm;
using namespace std;

Program program;

void render(GLFWwindow* window);
void init();

GLuint vertexBuffer = 0;
GLuint indexBuffer = 0;
GLuint vertexArray = 0;
int main(){
    if(!glfwInit()) return 0;
    
#ifdef __APPLE__
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
#endif
    
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", 0, 0);
    glfwMakeContextCurrent(window);
    glewInit();
    init();
    while(!glfwWindowShouldClose(window)){
        render(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
void init(){
    program.loadShaders("shader.vert", "shader.frag");
    vector<vec3> p = {{0.5,-0.5,0}, {0,0.5,0}, {-0.5,-0.5,0}, {0,-0.5,0}, {-0.3,0,0}, {0.3,0,0}};
    vector<uvec3> triangles = {{0,3,5}, {2,4,3}, {1,4,5}};
    
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, p.size()*sizeof(vec3), p.data(), GL_STATIC_DRAW);
    
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size()*sizeof(uvec3), triangles.data(), GL_STATIC_DRAW);
    
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexArray);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, nullptr);
}

void render( GLFWwindow* window){
    int w,h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0,0,w,h);
    glClearColor(0,0,0.7,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program.programID);
    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    // 몇번째 점까지
    glDrawElements(GL_TRIANGLES, 3*3, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);
}
