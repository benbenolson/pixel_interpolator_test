#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <GL/glxext.h>

/* Function pointers to common OpenGL functions */
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLDELETESHADERPROC glDeleteShader;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLDELETEPROGRAMPROC glDeleteProgram;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;

/* Currently just sets the function pointers to the appropriate implementation-specific functions. */
void init_opengl_funcs() {
  glGetShaderiv = (PFNGLGETSHADERIVPROC) glXGetProcAddress("glGetShaderiv");
  glGetProgramiv = (PFNGLGETPROGRAMIVPROC) glXGetProcAddress("glGetProgramiv");
  glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) glXGetProcAddress("glGetShaderInfoLog");
  glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) glXGetProcAddress("glGetProgramInfoLog");
  glLinkProgram = (PFNGLLINKPROGRAMPROC) glXGetProcAddress("glLinkProgram");
  glDeleteShader = (PFNGLDELETESHADERPROC) glXGetProcAddress("glDeleteShader");
  glUseProgram = (PFNGLUSEPROGRAMPROC) glXGetProcAddress("glUseProgram");
  glAttachShader = (PFNGLATTACHSHADERPROC) glXGetProcAddress("glAttachShader");
  glGenBuffers = (PFNGLGENBUFFERSPROC) glXGetProcAddress("glGenBuffers");
  glCreateProgram = (PFNGLCREATEPROGRAMPROC) glXGetProcAddress("glCreateProgram");
  glDeleteProgram = (PFNGLDELETEPROGRAMPROC) glXGetProcAddress("glDeleteProgram");
  glBindBuffer = (PFNGLBINDBUFFERPROC) glXGetProcAddress("glBindBuffer");
  glBufferData = (PFNGLBUFFERDATAPROC) glXGetProcAddress("glBufferData");
  glShaderSource = (PFNGLSHADERSOURCEPROC) glXGetProcAddress("glShaderSource");
  glCompileShader = (PFNGLCOMPILESHADERPROC) glXGetProcAddress("glCompileShader");
  glCreateShader = (PFNGLCREATESHADERPROC) glXGetProcAddress("glCreateShader");
  glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC) glXGetProcAddress("glGenVertexArrays");
  if(!glGenVertexArrays) {
    fprintf(stderr, "glGenVertexArrays is not supported by this implementation.\n");
    exit(1);
  }
  glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) glXGetProcAddress("glBindVertexArray");
  glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC) glXGetProcAddress("glVertexAttribPointer");
  glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC) glXGetProcAddress("glEnableVertexAttribArray");
}
