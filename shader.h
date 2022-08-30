#include "MathUtils.h"

class IShader
{
    virtual void vert(vec3 inPos, vec4& outClipPos) {}
    virtual void frag(vec4 inClipPos, vec4& outColor) {}
};