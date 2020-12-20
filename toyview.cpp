#include "toyview.h"
#include <QVector4D>


ToyView::ToyView()
    :id(-1),
     isInit(false),
     isFilled(false)
{
}

ToyView::ToyView(SketchLine sketchline, int id_){
    id = id_;
    isInit = false;
    isFilled = false;

    m_sketchline = sketchline;
    mvp.setToIdentity();
}


ToyView::~ToyView(){
    line_vbo.destroy();
    line_vao.destroy();
}

void ToyView::init(){
    //------------------------------ Initialize shader program---------------------------------------
    line_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader_sketch.vert");
    line_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader_sketch.frag");
    if(!line_shaderProgram.link()){
        qDebug() << "Failed to link line shader program\n";
    }

    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    //------------------------------ Get shader location ---------------------------------------
    line_shaderProgram.bind();
    vertex_loc = line_shaderProgram.attributeLocation("vertex");
    mvp_loc = line_shaderProgram.uniformLocation("mvp");
    line_shaderProgram.release();

    //------------------------------ Create VBO and VAO ------------------------------------------
    line_vbo.create();
    line_vao.create();

    GLsizei stride = sizeof(GLVertex);
    line_vao.bind();
    //QOpenGLVertexArrayObject::Binder vaoBinder(&line_vao);
    line_vbo.bind();
    f->glEnableVertexAttribArray(vertex_loc);
    f->glVertexAttribPointer(vertex_loc,
                             2,
                             GL_FLOAT,
                             GL_FALSE,
                             stride,
                             NULL);
    line_vbo.release();
    line_vao.release();
    isInit = true;
}


void ToyView::draw_mesh(){
}


void ToyView::bind_line(){
    line_vbo.bind();
    line_vbo.allocate(m_sketchline.data(), m_sketchline.size() * sizeof(GLVertex));
    line_vbo.release();
    isFilled = true;
}

void ToyView::draw_line(){
    if(m_sketchline.size()<2) return;

    if(!isInit){
        init();
    }
    if(!isFilled){
        bind_line();
    }

    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();

    line_shaderProgram.bind();
    line_shaderProgram.setUniformValue(mvp_loc, mvp);

    line_vao.bind();
    f->glDrawArrays(GL_LINE_STRIP, 0, m_sketchline.size());
    line_vao.release();
    line_shaderProgram.release();
}
