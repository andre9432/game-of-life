#version 460 core

out vec4 FragColor;

in vec2 fragCoord;

layout(binding = 1, std430) buffer ssbo1 {
    vec4 ssboColor1[10000];
};

layout(binding = 2, std430) buffer ssbo2 {
    vec4 ssboColor2[10000];
};

void main()
{
    //ssboColor1[int(floor(fragCoord.x * 100.f)) + int(floor(fragCoord.y * 100.f)) * 100] = ssboColor2[int(floor(fragCoord.x * 100.f)) + int(floor(fragCoord.y * 100.f)) * 100];

    //if (ssboColor2[int(floor(fragCoord.x * 100.f)) + (int(floor(fragCoord.y * 100.f)) + 1) * 100].r > 0.5f && ssboColor2[int(floor(fragCoord.x * 100.f)) + int(floor(fragCoord.y * 100.f)) * 100].r < 0.5f)
    //{
    //    ssboColor1[int(floor(fragCoord.x * 100.f)) + int(floor(fragCoord.y * 100.f)) * 100] = ssboColor2[int(floor(fragCoord.x * 100.f)) + (int(floor(fragCoord.y * 100.f)) + 1) * 100];
    //}
    //else if (ssboColor2[int(floor(fragCoord.x * 100.f)) + (int(floor(fragCoord.y * 100.f)) - 1) * 100].r < 0.5f && ssboColor2[int(floor(fragCoord.x * 100.f)) + int(floor(fragCoord.y * 100.f)) * 100].r > 0.5f && int(floor(fragCoord.y * 100.f)) != 0)
    //{
    //    ssboColor1[int(floor(fragCoord.x * 100.f)) + int(floor(fragCoord.y * 100.f)) * 100].r = 0.f;
    //}

    float neighbours = ssboColor2[int(floor(fragCoord.x * 100.f)) + (int(floor(fragCoord.y * 100.f)) - 1) * 100].r + ssboColor2[int(floor(fragCoord.x * 100.f)) + (int(floor(fragCoord.y * 100.f)) + 1) * 100].r + ssboColor2[int(floor(fragCoord.x * 100.f)) + 1 + (int(floor(fragCoord.y * 100.f))) * 100].r + ssboColor2[int(floor(fragCoord.x * 100.f)) - 1 + (int(floor(fragCoord.y * 100.f))) * 100].r + ssboColor2[int(floor(fragCoord.x * 100.f)) - 1 + (int(floor(fragCoord.y * 100.f)) - 1) * 100].r + ssboColor2[int(floor(fragCoord.x * 100.f)) + 1 + (int(floor(fragCoord.y * 100.f)) - 1) * 100].r + ssboColor2[int(floor(fragCoord.x * 100.f)) - 1 + (int(floor(fragCoord.y * 100.f)) + 1) * 100].r + ssboColor2[int(floor(fragCoord.x * 100.f)) + 1 + (int(floor(fragCoord.y * 100.f)) + 1) * 100].r;

    if (ssboColor2[int(floor(fragCoord.x * 100.f)) + (int(floor(fragCoord.y * 100.f))) * 100].r > 0.5f && neighbours < 1.5f)
        ssboColor1[int(floor(fragCoord.x * 100.f)) + int(floor(fragCoord.y * 100.f)) * 100].r = 0.f;
    else if (ssboColor2[int(floor(fragCoord.x * 100.f)) + (int(floor(fragCoord.y * 100.f))) * 100].r > 0.5f && neighbours > 1.5f && neighbours < 3.5f)
        ssboColor1[int(floor(fragCoord.x * 100.f)) + int(floor(fragCoord.y * 100.f)) * 100].r = ssboColor2[int(floor(fragCoord.x * 100.f)) + int(floor(fragCoord.y * 100.f)) * 100].r;
    else if (ssboColor2[int(floor(fragCoord.x * 100.f)) + (int(floor(fragCoord.y * 100.f))) * 100].r > 0.5f && neighbours > 3.5f)
        ssboColor1[int(floor(fragCoord.x * 100.f)) + int(floor(fragCoord.y * 100.f)) * 100].r = 0.f;
    else if (ssboColor2[int(floor(fragCoord.x * 100.f)) + (int(floor(fragCoord.y * 100.f))) * 100].r < 0.5f && neighbours > 2.5f && neighbours < 3.5f)
        ssboColor1[int(floor(fragCoord.x * 100.f)) + int(floor(fragCoord.y * 100.f)) * 100].r = 1.f;

    FragColor = vec4(ssboColor2[int(floor(fragCoord.x * 100.f)) + int(floor(fragCoord.y * 100.f)) * 100].r * vec3(fragCoord.x, 0.f, 0.5), 1.0);
}