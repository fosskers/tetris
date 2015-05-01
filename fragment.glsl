#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;
in vec3 vColour;

out vec4 colour;

void main() {
        vec3 lightColour = vec3(1.0,1.0,1.0);

        // Ambient Lighting
        float ambientStr = 0.1f;
        vec3 ambient = ambientStr * lightColour;

        // Diffuse Lighting
        vec3 norm     = normalize(Normal);
        vec3 lightDir = normalize(LightPos - FragPos);
        float diff    = max(dot(norm,lightDir),0.0);
        vec3 diffuse  = diff * lightColour;

        // Specular Lighting
        float specStr   = 0.5f;
        vec3 viewDir    = normalize(-FragPos);
        vec3 reflectDir = reflect(-lightDir,norm);
        float spec      = pow(max(dot(viewDir,reflectDir),0.0),32);
        vec3 specular   = specStr * spec * lightColour;

        vec3 result = (ambient + diffuse + specular) * vColour;

        colour = vec4(result, 1.0f);
}
