#include "shader.h"
#include <vector>
#include <array>

const char *glsl_v = R"#(
attribute vec3 pos;
uniform mat4 mvpMatrix;

void main(void) {
    gl_Position = mvpMatrix * vec4(pos, 1.0);
}
)#";

const char *glsl_f = R"#(
uniform vec3 color;

void main(void) {
    gl_FragColor = vec4(color, 1.0);
}
)#";

shader::shader() {
  auto v_shader_id = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(v_shader_id, 1, &glsl_v, nullptr);
  glCompileShader(v_shader_id);

  auto f_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(f_shader_id, 1, &glsl_f, nullptr);
  glCompileShader(f_shader_id);

  m_program_id = glCreateProgram();
  glAttachShader(m_program_id, v_shader_id);
  glAttachShader(m_program_id, f_shader_id);
  glLinkProgram(m_program_id);

  m_pos_loc = glGetAttribLocation(m_program_id, "pos");
  m_matrix_loc = glGetUniformLocation(m_program_id, "mvpMatrix");
  m_color_loc = glGetUniformLocation(m_program_id, "color");

  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  std::vector<float> v = {
    0.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    0.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 0.0, 0.0,
    0.0, 0.0, 1.0
  };
  glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(float), &v[0], GL_STATIC_DRAW);
}

void shader::render(const mvp& mvp) {
  glUseProgram(m_program_id);

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glEnableVertexAttribArray(m_pos_loc);
  glVertexAttribPointer(m_pos_loc, 3, GL_FLOAT, GL_FALSE, 0, 0);

  auto matrix = mvp.create();
  glUniformMatrix4fv(m_matrix_loc, 1, GL_FALSE, &matrix[0][0]);

  std::array<std::array<float, 3>, 3> colors = {{
      { 1.0f, 0.0f, 0.0f },
      { 0.0f, 1.0f, 0.0f },
      { 0.0f, 0.0f, 1.0f }
  }};

  for (int i = 0; i < 3; i++) {
      glUniform3f(m_color_loc, colors[i][0], colors[i][1], colors[i][2]);
      glDrawArrays(GL_LINES, i * 2, 2);
  }
}
