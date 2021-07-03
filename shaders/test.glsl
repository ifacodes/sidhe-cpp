#ifdef VERTEX
//layout (location = 0) in vec2 pos;
uniform mat4 transform;

void main() {

  /*const vec2 v[4] = {
    vec2(pos.x-0.5, pos.y-0.5),
    vec2(pos.x+0.5, pos.y-0.5),
    vec2(pos.x-0.5, pos.y+0.5),
    vec2(pos.x+0.5, pos.y+0.5),
  };*/

  const vec2 v[4] = {
    vec2(0.0-0.5, 0.0-0.5),
    vec2(0.0+0.5, 0.0-0.5),
    vec2(0.0-0.5, 0.0+0.5),
    vec2(0.0+0.5, 0.0+0.5),
  };

  gl_Position = transform * vec4(v[gl_VertexID], 0.0, 1.0);
}
#endif

#ifdef FRAGMENT
out vec4 FragColor;

void main() {
  FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
#endif