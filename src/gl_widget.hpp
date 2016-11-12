#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTime>
#include "textured_rect.hpp"

#include <array>

class MainWindow;

QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)
QT_FORWARD_DECLARE_CLASS(QOpenGLShader)
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT
public:
  GLWidget(MainWindow * mw, QColor const & background);        // конструктор
  ~GLWidget();                                                 // деструктор

protected:
  void resizeGL(int w, int h) override;                        // переопределение изменения размера окна
  void paintGL() override;                                     // переопределение
  void initializeGL() override;                                // переопределение

  void Update(float elapsedSeconds);                           //
  void Render();                                               //

  void mousePressEvent(QMouseEvent * e) override;              // переопределение
  void mouseDoubleClickEvent(QMouseEvent * e) override;        // переопределение
  void mouseMoveEvent(QMouseEvent * e) override;               // переопределение
  void mouseReleaseEvent(QMouseEvent * e) override;            // переопределение
  void wheelEvent(QWheelEvent * e) override;                   // переопределение
  void keyPressEvent(QKeyEvent * e) override;                  // переопределение
  void keyReleaseEvent(QKeyEvent * e) override;                // переопределение

private:
  int L2D(int px) const { return px * devicePixelRatio(); }    //

  MainWindow * m_mainWindow;                                          // передается из конструктора

  unsigned int m_frames = 0;                                          //
  QTime m_time;                                                       //
  QColor m_background;                                                // передается из конструктора
  QSize m_screenSize;                                                 // размер окна

  QOpenGLTexture * m_texture = nullptr;                               // текстура объекта
  TexturedRect * m_texturedRect = nullptr;                            //

  QVector2D m_position = QVector2D(100, 100);                         // Позиция двигаемого alien
  std::array<bool, 4> m_directions = { false, false, false, false };  //
};
