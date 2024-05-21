#ifndef CPP4_3DVIEWER_SRC_VIEW_VIEW_H_
#define CPP4_3DVIEWER_SRC_VIEW_VIEW_H_

#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QSettings>
#include <QTimer>
#include <QWidget>
#include <algorithm>
#include <charconv>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#include "../Controller/Controller.h"
#include "./Singleton.h"
#include "./ui_View.h"
#include "QtGifImage-master/src/gifimage/qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {

class View : public QOpenGLWidget {
  Q_OBJECT

 public:
  View(Controller *c, std::shared_ptr<Singleton> settings_,
       QWidget *parent = nullptr);
  ~View();

 private slots:
  void OpenFile();
  void BackColorSlider();
  void VertColorSlider();
  void LinesColorSlider();
  void Reset();
  void SaveImage();
  void StartDraw();
  void Init();
  void SaveGif();
  void OneGif();

 private:
  void DrawCube();
  void Rotate();
  void Scale();
  void Move();
  void SaveSettings();
  void LoadSettings();

  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  QPoint mouse_position_;
  double y_start_, x_start_, camera_;
  Controller *controller_;
  std::shared_ptr<Singleton> settings_;
  Ui::View *ui_;

  QString s_file_name_;
  int start_time_, tmp_time_;
  float time_print_;
  const int gif_fps_ = 10, gif_length_ = 5;
  const int gif_const_fps_ = 1000 / gif_fps_;
  QTimer *timer_;
  QGifImage *gif_;
};

}  // namespace s21

#endif  //  CPP4_3DVIEWER_SRC_VIEW_VIEW_H_
