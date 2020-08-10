#version 330 core
out vec4 FragColor;

in vec2 ourTextureCoord;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float mixPercent;
void main()
{
    FragColor = mix(texture(ourTexture1,ourTextureCoord),texture(ourTexture2,vec2(ourTextureCoord.x,ourTextureCoord.y)),mixPercent);
}
