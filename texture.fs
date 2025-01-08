#version 330 core

in vec2 fragTexCoord;
in vec3 fragWorldPos;

out vec4 outColor;

uniform sampler2D textureSampler;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float lightRadius;

void main() {
    float distance = length(fragWorldPos - lightPos);

    float intensity = max(1.0 - (distance / lightRadius), 0.0);

    vec4 baseColor = texture(textureSampler, fragTexCoord);

    outColor = vec4(baseColor.rgb * lightColor * intensity, baseColor.a);
}
