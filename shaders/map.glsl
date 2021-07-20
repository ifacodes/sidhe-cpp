#ifdef VERTEX
layout (location = 0) in vec2 pos;
uniform mat4 model;
uniform mat4 ortho;

void main() {

  gl_Position = ortho * model * vec4(pos, 0.0, 1.0);

}
#endif

#ifdef FRAGMENT
out vec4 FragColor;

void main() {
  FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
#endif
