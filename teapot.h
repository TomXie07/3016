#pragma once

#include "public.h"

using namespace glm;

struct Vertex
{
    vec3 position;
    vec2 texcoord;
    vec3 normal;

    Vertex() {}
    Vertex(vec3 pos, vec2 st, vec3 norm) : position(pos), texcoord(st), normal(norm) {}
};

extern Vertex TEAPOT_LID[4680];
extern Vertex TEAPOT_BODY[14280];
