#version 400 core

in vec2 pass_textureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector; 
in vec3 toCameraVector;
in float visibility;

out vec4 out_Color;

uniform float shineDamper;
uniform float reflectivity;

uniform sampler2D textureSampler;

uniform vec3 lightColor;
uniform vec3 skyColor;

void main(void) {
    vec4 textureColor = texture(textureSampler, pass_textureCoords);
    if (textureColor.a < 0.5)
        discard;

    vec3 unitNormal = normalize(surfaceNormal);
    vec3 unitLightVector = normalize(toLightVector);

    float nDot1 = dot(unitNormal, unitLightVector);
    float brightness = max(nDot1, 0.2);
    vec3 diffuse = brightness * lightColor;

    vec3 unitToCameraVector = normalize(toCameraVector);
    vec3 lightDirection = -unitLightVector;
    vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

    float specularFactor = dot(unitToCameraVector, reflectedLightDirection);
    specularFactor = max(specularFactor, 0.0);
    float dampedFactor = pow(specularFactor, shineDamper);

    vec3 finalSpecular = dampedFactor * reflectivity * lightColor;

    out_Color = vec4(diffuse, 1.0) * textureColor + vec4(finalSpecular, 1.0);
    out_Color = mix(vec4(skyColor, 1.0), out_Color, visibility);
}