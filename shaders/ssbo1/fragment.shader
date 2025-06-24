#version 460 core

out vec4 FragColor;

in vec2 fragCoord;

layout(binding = 1, std430) buffer ssbo1 {
    vec4 ssboColor1[10000];
};

layout(binding = 2, std430) buffer ssbo2 {
    vec4 ssboColor2[10000];
};

int twoDtoarr(ivec2 pos)
{
    return pos.x + pos.y * 100;
}

void main()
{
    //ivec2 arr2dpos = ivec2(int(floor(fragCoord.x * 100.f)), int(floor(fragCoord.y * 100.f)));
    ssboColor2[int(floor(fragCoord.x * 100.f)) + int(floor(fragCoord.y * 100.f)) * 100] = ssboColor1[int(floor(fragCoord.x * 100.f)) + int(floor(fragCoord.y * 100.f)) * 100];

    float grid = step(0.9f, fract(fragCoord.x * 100.f)) + step(0.9f, fract(fragCoord.y * 100.f));

    FragColor = vec4(ssboColor1[int(fragCoord.x * 100.f) + int(fragCoord.y * 100.f) * 100].r * vec3(fragCoord.x, 0.f, 0.5) + vec3(grid) * 0.3f, 1.0);

    
}