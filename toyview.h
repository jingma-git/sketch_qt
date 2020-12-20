#ifndef TOYVIEW_H
#define TOYVIEW_H

#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include <QOpenGLFunctions>


struct GLVertex {
    float x, y;
    GLVertex(float x, float y) : x(x), y(y) {}
};

typedef std::vector<GLVertex> SketchLine;

struct ToyView
{
    ToyView();
    ToyView(SketchLine sketchline, int id=-1);

    ~ToyView();

    void init();
    void draw_mesh();
    void bind_line();
    void draw_line();
    void set_mvp(const QMatrix4x4& mvp_){ mvp = mvp_;}

    SketchLine m_sketchline;

private:
    float line_color[4];

    // sketchline
    QOpenGLVertexArrayObject line_vao;
    QOpenGLBuffer line_vbo;
    QOpenGLShaderProgram line_shaderProgram;

    QMatrix4x4 mvp;
    GLuint mvp_loc;
    GLuint vertex_loc;
    QOpenGLFunctions* f;

    int id;
    bool isInit; //is vao, vbo created
    bool isFilled; // is vbo filled
};

#endif // TOYVIEW_H
