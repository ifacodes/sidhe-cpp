#ifdef VERTEX
layout (location = 0) in vec2 pos;
uniform mat4 model;
uniform mat4 ortho;
uniform vec2 uv_offset;

void main() {

  gl_Position = ortho * model * vec4(pos, 0.0, 1.0);
  out.uv = uv + uv * uv_offset;
}
#endif

#ifdef FRAGMENT
out vec4 FragColor;

void main() {
  FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
#endif
