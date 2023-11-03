#define GLEW_STATIC
#include <GL/glew.h>
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
    
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", 0, 0);
    glewInit();
    init();
    while(!glfwWindowShouldClose(window)){
        render(window);
        glfwPollEvents();
    }
    return 0;
}
void init(){
    program.loadShaders("shader.vert", "shader.frag");
    vector<vec3> p = {{-0.7,-0.7,0}, {-0.7,0.7,0}, {0.7,-0.7,0}, {0.7,0.7,0}};
    vector<ivec3> triangles = {{0,1,2}};
    
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, p.size()*sizeof(vec3), p.data(), GL_STATIC_DRAW);
    
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size()*sizeof(ivec3), triangles.data(), GL_STATIC_DRAW);
    
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
    glDrawElements(GL_TRIANGLES, 1*3, GL_INT, 0);
    glfwSwapBuffers(window);
}
