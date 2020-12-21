#include "OpenGLWidget.h"

#include <QMouseEvent>

#include <cmath>

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    // Set view matrix
}

OpenGLWidget::~OpenGLWidget()
{
    // Make OpenGL context current and call cleanupGL()
    makeCurrent();
    cleanupGL();
    doneCurrent();
}

void OpenGLWidget::mousePressEvent(QMouseEvent * /*event*/)
{
    // Clear input samples and redraw
    m_curView.m_sketchline.clear();
    repaint();
    // update();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    // Add input sample and redraw
    QPoint p = event->pos();
    m_curView.m_sketchline.push_back(GLVertex(p.x(), p.y()));
    m_curView.update_vbo(true);
    repaint();
    // update();
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent * /*event*/)
{
    // Nothing to do
    ToyView *view = new ToyView(m_curView.m_sketchline, m_toyViews.size());
    view->set_mvp(m_mvp);
    m_toyViews.push_back(view);
    repaint();
    // update();
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_MULTISAMPLE);
    // Set clear color
    glClearColor(1, 1, 1, 1);

    // GLVertex p0(300, 0);
    // GLVertex p1(300, 600);
    // GLVertex p2(100, 100);
    // GLVertex p3(100, 200);

    // SketchLine line0 = {p0, p1};
    // SketchLine line1 = {p2, p3};

    // ToyView *view0 = new ToyView(line0, m_toyViews.size());
    // view0->set_mvp(m_mvp);
    // m_toyViews.push_back(view0);

    // ToyView *view1 = new ToyView(line1, m_toyViews.size());
    // view1->set_mvp(m_mvp);
    // m_toyViews.push_back(view1);
    // qDebug() << __FILE__ << " " << __LINE__;
}

void OpenGLWidget::resizeGL(int w, int h)
{
    // Set projection matrix
    const float left = 0.0f;
    const float right = w;
    const float bottom = h;
    const float top = 0.0f;
    const float near = -1.0f;
    const float far = 1.0f;
    m_mvp.setToIdentity();
    m_mvp.ortho(left, right, bottom, top, near, far);

    m_curView.set_mvp(m_mvp);

    for (ToyView *view : m_toyViews)
    {
        view->set_mvp(m_mvp);
    }
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_curView.draw_line();
    for (int i = 0; i < m_toyViews.size(); i++)
    {
        m_toyViews[i]->draw_line();
        //        m_toyViews[i]->draw_mesh();
    }
}

void OpenGLWidget::cleanupGL()
{
    for (ToyView *view : m_toyViews)
    {
        delete view;
        view = 0;
    }
}
