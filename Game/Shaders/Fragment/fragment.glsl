#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
in mat3 TBN;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_normal;
uniform vec3 diffuse;
uniform vec3 view_pos;

vec3 BlinnPhong(vec3 normal, vec3 fragPos, vec3 lightPos, vec3 lightColor)
{
    // diffuse
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    // specular
    vec3 viewDir = normalize((TBN * view_pos) - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;
    // simple attenuation
    float max_distance = 1.5;
    float distance = length(lightPos - fragPos);
    float attenuation = 1.0 / distance;

    diffuse *= attenuation;
    specular *= attenuation;
    return diffuse + specular;
}

void main()
{
    vec3 color = texture(texture_diffuse, TexCoords).rgb;
    vec3 lighting = vec3(0.0);
    
    lighting += BlinnPhong(normalize(Normal), FragPos, vec3(-300,800,1990), vec3(2000,2000,2000));
    lighting += BlinnPhong(normalize(Normal), FragPos, vec3(200,1000,-1990), vec3(40,20,200));
    lighting += BlinnPhong(normalize(Normal), FragPos, vec3(-400,1790,-1990), vec3(40,20,200));
    
    color *= lighting;
    
    color = pow(color, vec3(1.0/2.2));
    FragColor = vec4(color, 1.0);
}

