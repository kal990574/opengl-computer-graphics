#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include "j3a.hpp"
#include "toys.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace glm;
using namespace std;

Program program;

void render(GLFWwindow* window);
void init();

GLuint vertexBuffer = 0;
GLuint normalBuffer = 0;
GLuint texCoordBuffer = 0;
GLuint indexBuffer = 0;
GLuint vertexArray = 0;
GLuint diffTex = 0;
GLuint bumpTex = 0;

float theta = 0;
float phi = 0;
double lastX = 0, lastY = 0;
float cameraDistance = 7;
float fovy = 0.8;
vec3 lightPosition = vec3(3,10,4);

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
void scrollCB(GLFWwindow* window, double xoffset, double yoffset){
    // cameraDistance *= cameraDistance * pow(1.01,yoffset);
    fovy *= pow(1.1,yoffset);
}
int main(){
    if(!glfwInit()) return 0;
    
#ifdef __APPLE__
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
#endif
    glfwWindowHint(GLFW_SAMPLES, 8);
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", 0, 0);
    glfwSetCursorPosCallback(window, cursorCB);
    glfwSetMouseButtonCallback(window, mouseBtnCB);
    glfwSetScrollCallback(window, scrollCB);
    glfwMakeContextCurrent(window);
    init();
    while(!glfwWindowShouldClose(window)){
        render(window);
        glfwPollEvents();
    }
    //glfwDestroyWindow(window);
    //glfwTerminate();
    return 0;
}

GLuint loadTexture(const std::string& filename){
    int w, h, n;
    GLuint tex = 0;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* buf = stbi_load(filename.c_str(), &w, &h, &n, 4);
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8_ALPHA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, buf);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(buf);
    return tex;
}

void init(){
    loadJ3A( "Trex.j3a" );
    program.loadShaders("shader.vert", "shader.frag");
    diffTex = loadTexture(diffuseMap[0]);
    bumpTex = loadTexture(bumpMap[0]);


    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, nVertices[0]*sizeof(glm::vec3), vertices[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, nVertices[0]*sizeof(glm::vec3), normals[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &texCoordBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, nVertices[0]*sizeof(glm::vec2), texCoords[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, nTriangles[0]*sizeof(glm::u32vec3), triangles[0], GL_STATIC_DRAW);
    
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, 0, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, 0, 0, 0);
}

void render( GLFWwindow* window){
    int w,h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0,0,w,h);
    vec3 cameraPosition = vec3(0, 0, cameraDistance);
    cameraPosition = vec3(rotate(theta, vec3(0,1,0)) * rotate(phi, vec3(1,0,0)) * vec4(cameraPosition,1));
    
    mat4 projMat = perspective(fovy, w/float(h), 0.1f, 100.f);
    mat4 viewMat = lookAt(cameraPosition, vec3(0), vec3(0,1,0));
    mat4 modelMat = mat4(1);
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0,0,0.7,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(program.programID);
    GLuint loc = glGetUniformLocation(program.programID, "modelMat");
    glUniformMatrix4fv(loc, 1, false, value_ptr(modelMat));
    loc = glGetUniformLocation(program.programID, "viewMat");
    glUniformMatrix4fv(loc, 1, false, value_ptr(viewMat));
    loc = glGetUniformLocation(program.programID, "projMat");
    glUniformMatrix4fv(loc, 1, false, value_ptr(projMat));
    loc = glGetUniformLocation(program.programID, "lightPosition");
    glUniform3fv(loc, 1, value_ptr(lightPosition));
    loc = glGetUniformLocation(program.programID, "cameraPosition");
    glUniform3fv(loc, 1, value_ptr(cameraPosition));
    loc = glGetUniformLocation(program.programID, "diffColor");
    glUniform3fv(loc, 1, value_ptr(diffuseColor[0]));
    loc = glGetUniformLocation(program.programID, "specColor");
    glUniform3fv(loc, 1, value_ptr(specularColor[0]));
    loc = glGetUniformLocation(program.programID, "shininess");
    glUniform1f(loc, shininess[0]);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffTex);
    loc = glGetUniformLocation(program.programID, "diffTex");
    glUniform1i(loc, 0);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, bumpTex);
    loc = glGetUniformLocation(program.programID, "bumpTex");
    glUniform1i(loc, 1);
    
    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(GL_TRIANGLES, nTriangles[0]*3, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);
}
