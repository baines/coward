#ifndef _GL_FN
	#define _GL_FN(type, name, args) \
		typedef type (APIENTRY * name##_p) args;
	#define UNDEF_GL_FN
#endif
_GL_FN(void, FrontFace, (GLenum  mode))
_GL_FN(void, GenTextures, (GLsizei n, GLuint *textures))
_GL_FN(void, BindTexture, (GLenum target, GLuint texture))
_GL_FN(void, TexParameteri, (GLenum target, GLenum pname, GLint param))
_GL_FN(void, TexImage2D, (GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels))
_GL_FN(void, Clear, (GLbitfield mask))
_GL_FN(void, MatrixMode, (GLenum mode))
_GL_FN(void, Viewport, (GLint x, GLint y, GLsizei width, GLsizei height))
_GL_FN(void, LoadIdentity, (void))
_GL_FN(void, Enable, (GLenum cap))
_GL_FN(void, Ortho, (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near_val, GLdouble far_val))
_GL_FN(void, BlendFunc, (GLenum sfactor, GLenum dfactor))
_GL_FN(void, DrawElements, (GLenum mode, GLsizei  count,  GLenum  type,  const GLvoid *  indices))
_GL_FN(void, Scalef, (GLfloat x, GLfloat y, GLfloat z))
_GL_FN(void, VertexPointer, (GLint  size,  GLenum  type,  GLsizei  stride,  const GLvoid *  pointer))
_GL_FN(void, TexCoordPointer, (GLint  size,  GLenum  type,  GLsizei  stride,  const GLvoid *  pointer))
_GL_FN(void, EnableClientState, (GLenum  cap))
#ifdef UNDEF_GL_FN
	#undef _GL_FN
	#undef UNDEF_GL_FN
#endif
