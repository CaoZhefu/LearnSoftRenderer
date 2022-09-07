#include "shader.h"

void Shader_Phong::vert(vec3 inPos, vec4& outClipPos) {
    vec4 p(inPos.x, inPos.y, inPos.z, 1.0);
    mat4 mvp = persp * view * model;
    vec4 ret = mvp * p;
    outClipPos = ret;
}

void Shader_Phong::frag(vec4 inClipPos, vec4& outColor) {
    outColor = vec4(1.0, 1.0, 1.0, 1.0);
}