#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_2_Core>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include <vector>
#include "toyview.h"

typedef QOpenGLFunctions_3_2_Core OpenGLFunctions;

class OpenGLWidget : public QOpenGLWidget, protected OpenGLFunctions
{
private:
    Q_OBJECT
    Q_DISABLE_COPY(OpenGLWidget)

public:
    OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void cleanupGL();

private:
    // Input mouse data
    ToyView m_curView;
    std::vector<ToyView *> m_toyViews;

    QMatrix4x4 m_mvp;
};

#endif // OPENGLWIDGET_H
