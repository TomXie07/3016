#ifndef PUBLIC_H
#define PUBLIC_H

// std
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <vector>

// glew
#define GLEW_STATIC
#include <glew/glew.h>

// glut
#include <GL/freeglut.h>

// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>
#include <glm/gtx/normal.hpp>
#include <glm/gtx/rotate_vector.hpp>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#if defined(_M_AMD64) || defined(_M_X64)
    #pragma comment(lib, "x64/glew32s.lib")
    #pragma comment(lib, "x64/SOIL2.lib")
#else
    #pragma comment(lib, "x86/glew32s.lib")
    #pragma comment(lib, "x86/SOIL2.lib")
#endif

#define offset_element(obj,element) ((void*)(offsetof(obj, element)))

#ifndef __stringify
//#define __stringify_1(s) #s
//#define __stringify(...) __stringify_1(__VA_ARGS__)
#define __stringify_1(x) #x
#define __stringify(x)  __stringify_1(x)
#endif

#ifndef M_RD
#define M_RD (M_PI / 180.0f)
#define M_INV_RD (1.0 / M_RD)
#endif

//
// color
//

namespace colors
{
    const glm::vec4 black  (0.0f, 0.0f, 0.0f, 1.0f);    // #000000
    const glm::vec4 gray   (0.5f, 0.5f, 0.5f, 1.0f);    // #808080
    const glm::vec4 red    (1.0f, 0.0f, 0.0f, 1.0f);    // #FF0000
    const glm::vec4 yellow (1.0f, 1.0f, 0.0f, 1.0f);    // #FFFF00
    const glm::vec4 lime   (0.0f, 1.0f, 0.0f, 1.0f);    // #00FF00
    const glm::vec4 cyan   (0.0f, 1.0f, 1.0f, 1.0f);    // #00FFFF
    const glm::vec4 blue   (0.0f, 0.0f, 1.0f, 1.0f);    // #00FFFF
    const glm::vec4 magenta(1.0f, 0.0f, 1.0f, 1.0f);    // #FF00FF
    const glm::vec4 maroon (0.5f, 0.0f, 0.0f, 1.0f);    // #800000
    const glm::vec4 olive  (0.5f, 0.5f, 0.0f, 1.0f);    // #808000
    const glm::vec4 green  (0.0f, 0.5f, 0.0f, 1.0f);    // #008000
    const glm::vec4 teal   (0.0f, 0.5f, 0.5f, 1.0f);    // #008080
    const glm::vec4 navy   (0.0f, 0.0f, 0.5f, 1.0f);    // #000080
    const glm::vec4 purple (0.5f, 0.0f, 0.5f, 1.0f);    // #800080
    const glm::vec4 silver (0.75f, 0.75f, 0.75f, 1.0f); // #C0C0C0
    const glm::vec4 white  (1.0f, 1.0f, 1.0f, 1.0f);    // #FFFFFF
}

//
// random()
//

#if !defined(__BORLANDC__)
inline void randomize()
{
    srand(static_cast<unsigned int>(time(nullptr)));
}

inline int random(int n)
{
    return rand() % n;
}
#endif

inline int random(int a, int b)
{
    return a + random(b - a);
}

inline float random_real()
{
    return rand() / float(RAND_MAX);
}

inline float random_real(float n)
{
    return random_real() * n;
}

inline float random_real(float a, float b)
{
    return a + random_real(b - a);
}

#endif // PUBLIC_H
