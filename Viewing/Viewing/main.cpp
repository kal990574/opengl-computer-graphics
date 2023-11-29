#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include "j3a.hpp"
#include "toys.h"
using namespace glm;
using namespace std;

Program program;

void render(GLFWwindow* window);
void init();

GLuint vertexBuffer = 0;
GLuint indexBuffer = 0;
GLuint vertexArray = 0;
float theta = 0;
float phi = 0;
double lastX = 0, lastY = 0;

void cursorCB(GLFWwindow* w, double xPos, double yPos){
    if(glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_1)){
        theta -= (xPos - lastX)/300;
        phi -= (yPos - lastY)/300;
        lastX = xPos;
        lastY = yPos;
    }
}
void mouseBtnCB(GLFWwindow* w, int button, int action, int mods){
    if( button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS){
        glfwGetCursorPos(w, &lastX, &lastY);
    }
}
int main(){
    if(!glfwInit()) return 0;
    
#ifdef __APPLE__
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
#endif
    
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", 0, 0);
    glfwSetCursorPosCallback(window, cursorCB);
    glfwSetMouseButtonCallback(window, mouseBtnCB);
    glfwMakeContextCurrent(window);
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
    loadJ3A( "elephant.j3a" );
    program.loadShaders("shader.vert", "shader.frag");
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, nVertices[0]*sizeof(glm::vec3), vertices[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, nTriangles[0]*sizeof(glm::u32vec3), triangles[0], GL_STATIC_DRAW);
    
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
    vec3 cameraPosition = vec3(0,0,7);
    cameraPosition = vec3(rotate(theta, vec3(0,1,0)) * rotate(phi, vec3(1,0,0)) * vec4(cameraPosition,1));
    
    mat4 projMat = perspective(radians(45.f), w/float(h), 0.1f, 100.f);
    mat4 viewMat = lookAt(cameraPosition, vec3(0), vec3(0,1,0));
    mat4 modelMat = mat4(1);
    
    glClearColor(0,0,0.7,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program.programID);
    GLuint loc = glGetUniformLocation(program.programID, "modelMat");
    glUniformMatrix4fv(loc, 1, false, value_ptr(modelMat));
    loc = glGetUniformLocation(program.programID, "viewMat");
    glUniformMatrix4fv(loc, 1, false, value_ptr(viewMat));
    loc = glGetUniformLocation(program.programID, "projMat");
    glUniformMatrix4fv(loc, 1, false, value_ptr(projMat));
    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(GL_TRIANGLES, nTriangles[0]*3, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);
}
