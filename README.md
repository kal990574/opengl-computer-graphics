## 기능 구현

### 1. Viewing 기능을 위한 Model, View, Projection Matrix 행렬 설계 및 계산
그래픽스 렌더링 파이프라인에서 `Model`, `View`, `Projection` 행렬을 설계하고 계산하여 3D 객체의 위치와 시점을 조정합니다. 이를 통해 월드 좌표계에서 객체를 올바르게 배치하고, 화면에 투영할 수 있습니다.

```cpp
Matrix4x4 modelMatrix = Matrix4x4.TRS(position, rotation, scale);
Matrix4x4 viewMatrix = Camera.main.worldToCameraMatrix;
Matrix4x4 projectionMatrix = Camera.main.projectionMatrix;

Matrix4x4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
```

### 2. 사실적인 조명과 Shading 효과를 위한 Phong Lighting Model 구현
사실적인 조명 효과를 위해 `Phong Lighting Model`을 구현합니다. 이 모델은 `Ambient`, `Diffuse`, `Specular` 조명을 계산하여 3D 객체에 현실감 있는 조명을 적용합니다.

```cpp
Vector3 ambient = ambientLightColor * materialAmbient;
Vector3 diffuse = max(Vector3.Dot(normal, lightDir), 0.0f) * lightColor * materialDiffuse;
Vector3 viewDir = normalize(viewPos - fragPos);
Vector3 reflectDir = reflect(-lightDir, normal);
float spec = pow(max(dot(viewDir, reflectDir), 0.0f), shininess);
Vector3 specular = lightColor * (spec * materialSpecular);

Vector3 phong = ambient + diffuse + specular;
```

### 3. GLSL을 활용한 Shader 구현
`GLSL`(OpenGL Shading Language)을 사용하여 셰이더를 구현합니다. 이를 통해 그래픽스 파이프라인에서 조명과 색상, 텍스처 등을 조정하여 실시간으로 렌더링되는 객체의 외형을 제어합니다.

```glsl
#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

out vec4 FragColor;

void main()
{
    // Ambient
    vec3 ambient = 0.1 * lightColor;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}
```
