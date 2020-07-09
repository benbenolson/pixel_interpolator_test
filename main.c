#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

/* Temporary easy image parser */
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "gl_wrapper.h"

typedef struct object {
  GLuint vao,
         ebo,
         shader_program;
} object;

const GLchar const *vertex_shader_source = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0";
  
const GLchar const *fragment_shader_source = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  "}\n";

int shader_compile_failed(GLuint shader) {
  GLint success;
  GLchar log[512];
  
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(shader, 512, NULL, log);
    fprintf(stderr, "Shader failed to compile:\n");
    fprintf(stderr, "%s\n", log);
    return 1;
  }
  
  return 0;
}

int program_compile_failed(GLuint program) {
  GLint success;
  GLchar log[512];
  
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if(!success) {
    glGetProgramInfoLog(program, 512, NULL, log);
    fprintf(stderr, "Program failed to compile:\n");
    fprintf(stderr, "%s\n", log);
    return 1;
  }
  
  return 0;
}

void deinit_rectangle(object *rectangle) {
  if(!rectangle) {
    return;
  }
  
  glDeleteProgram(rectangle->shader_program);
  free(rectangle);
}

object *init_rectangle() {
  object *retval;
  GLuint ebo,
         vbo,
         vao,
         vertex_shader,
         fragment_shader,
         shader_program;
         
  /* For reading in image data */
  int width, height, num_channels;
  unsigned char *image_data;
  
  /* Vertices */
  GLfloat vertices[] = {
    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
  };
  GLuint indices[] = {
    0, 1, 3,
    1, 2, 3
  };
  
  glGenBuffers(1, &ebo);
  
  /* Create and bind the VAO */
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  
  /* Create and fill the VBO */
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  /* Create and fill the EBO */
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  
  /* Compile the vertex shader */
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
  glCompileShader(vertex_shader);
  if(shader_compile_failed(vertex_shader)) {
    goto cleanup_rectangle;
  }
  
  /* Compile the fragment shader */
  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
  glCompileShader(fragment_shader);
  if(shader_compile_failed(fragment_shader)) {
    goto cleanup_rectangle;
  }
  
  /* Link the vertex and fragment shaders */
  shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);
  if(program_compile_failed(shader_program)) {
    goto cleanup_rectangle;
  }
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
  glEnableVertexAttribArray(0);
  
  retval = malloc(sizeof(object));
  retval->vao = vao;
  retval->shader_program = shader_program;
  retval->ebo = ebo;
  
cleanup_rectangle:
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
  return retval;
}

int main(int argc, char **argv) {
  GLFWwindow *window;
  object *rectangle;
  
  /* Initialize GLFW */
  if(!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW.\n");
    return 1;
  }
  
  init_opengl_funcs();
  
  /* Set parameters for GLFW */
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);
  if(window == NULL) {
    fprintf(stderr, "Failed to open GLFW window.\n");
    goto cleanup_main;
  }
  glfwMakeContextCurrent(window);
  
  /* Initialize our object */
  rectangle = init_rectangle();
  
  /* Rendering loop */
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  do {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(rectangle->shader_program);
    glBindVertexArray(rectangle->vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
  
  glfwWindowShouldClose(window) == 0);
  
cleanup_main:
  if(window) {
    glfwDestroyWindow(window);
  }
  if(rectangle) {
    deinit_rectangle(rectangle);
  }
  glfwTerminate();
}
