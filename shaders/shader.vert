#version 330 core

// in variables

layout (location = 0) in vec3 aVertex; // Attrib position 0
layout (location = 1) in vec3 aColor;  // Attrib position 1
layout (location = 2) in vec3 aNormal; // Attrib position 2

// out variables

out vec3 vColorVector;
out vec3 vNormalVector;
out vec3 vLightVector; // Vector from vertex to light in view space
out vec3 vEyeVector;   // Vector from vertex to eye in view space

// uniform variables

uniform mat3 uNormalMatrix;
uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

// Light and eye positions
const vec3 LIGHT_WC = vec3(0.0f, 10.0f, 10.0f); 
const vec3 EYE_EC   = vec3(0.0f, 0.0f, 0.0f );

void main()
{
    // Transform model coordinates -> world coordinates -> eye coordinates
    vec4 vertexWC = uModelMatrix * vec4(aVertex, 1.0f);
    vec4 vertexEC = uViewMatrix * vertexWC;

    // Set final vertex position
    gl_Position = uProjectionMatrix * vertexEC;

    // Pass color vector to rasterizer/fragment shader
    vColorVector = aColor;

    // Pass transformed vector to rasterizer/fragment shader
    vNormalVector = normalize(uNormalMatrix * aNormal);

    // Apply view matrix to light position and get vector from vertex to light
    vec4 lightEC = uViewMatrix * vec4(LIGHT_WC, 1.0f);
    vLightVector = normalize(lightEC.xyz - vertexEC.xyz);

    // Calculate vector from vertex to eye
    vEyeVector = normalize(EYE_EC - vertexEC.xyz);
}
