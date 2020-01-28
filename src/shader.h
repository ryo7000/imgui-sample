#ifndef SRC_SHADER_H
#define SRC_SHADER_H

#include "glad/glad.h"

#include "mvp_window.h"

class shader {
public:
  shader();
  virtual ~shader() = default;

  void render(const mvp& mvp);

private:
  GLuint m_program_id;
  GLuint m_pos_loc;
  GLuint m_matrix_loc;
  GLuint m_color_loc;
  GLuint m_vbo;
};

#endif // SRC_SHADER_H
