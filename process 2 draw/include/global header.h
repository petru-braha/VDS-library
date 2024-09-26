#pragma once

#include <glad/glad.h>
#include "error management/file exception.h"
#include "error management/index exception.h"
#include "error management/shader exception.h"
#include "error management/GLenum exception.h"

#include <initializer_list>
#include "point.h"

typedef std::initializer_list<float> lf;
typedef std::initializer_list<unsigned int> li;

unsigned int sizeof_GLenum(unsigned int type)
{
	switch (type)
	{
	case GL_BYTE:			return sizeof(char);
	case GL_UNSIGNED_BYTE:	return sizeof(unsigned char);
	case GL_SHORT:			return sizeof(short);
	case GL_UNSIGNED_SHORT:	return sizeof(unsigned short);
	case GL_INT:			return sizeof(int);
	case GL_UNSIGNED_INT:	return sizeof(unsigned int);
	case GL_FLAT:			return sizeof(float);
	default:				return 0;
	}
}
