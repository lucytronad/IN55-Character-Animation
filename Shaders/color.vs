#version 140

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

in vec3 position;
in vec3 color;

out vec3 fColor;


void main()
{
  gl_Position = MVP * vec4( position, 1.0f );

  fColor = color;
}
