#include "View.h"

namespace s21 {

View::View(Controller* c, std::shared_ptr<Singleton> s, QWidget* parent)
    : QOpenGLWidget(parent), controller_(c), settings_(s), ui_(new Ui::View) {
  setFixedSize(1200, 1200);
  ui_->setupUi(this);

  connect(ui_->OpenFile, SIGNAL(clicked()), this, SLOT(OpenFile()));
  connect(ui_->ResetButton, SIGNAL(clicked()), this, SLOT(Reset()));
  connect(ui_->save_image, SIGNAL(clicked()), this, SLOT(SaveImage()));
  connect(ui_->save_gif, SIGNAL(clicked()), this, SLOT(SaveGif()));

  connect(ui_->horizontalSlider, SIGNAL(valueChanged(int)), this,
          SLOT(BackColorSlider()));
  connect(ui_->horizontalSlider_2, SIGNAL(valueChanged(int)), this,
          SLOT(BackColorSlider()));
  connect(ui_->horizontalSlider_3, SIGNAL(valueChanged(int)), this,
          SLOT(BackColorSlider()));
  connect(ui_->horizontalSlider_4, SIGNAL(valueChanged(int)), this,
          SLOT(VertColorSlider()));
  connect(ui_->horizontalSlider_5, SIGNAL(valueChanged(int)), this,
          SLOT(VertColorSlider()));
  connect(ui_->horizontalSlider_6, SIGNAL(valueChanged(int)), this,
          SLOT(VertColorSlider()));
  connect(ui_->horizontalSlider_7, SIGNAL(valueChanged(int)), this,
          SLOT(LinesColorSlider()));
  connect(ui_->horizontalSlider_8, SIGNAL(valueChanged(int)), this,
          SLOT(LinesColorSlider()));
  connect(ui_->horizontalSlider_9, SIGNAL(valueChanged(int)), this,
          SLOT(LinesColorSlider()));
  connect(ui_->horizontalSlider_10, SIGNAL(valueChanged(int)), this,
          SLOT(StartDraw()));
  connect(ui_->horizontalSlider_11, SIGNAL(valueChanged(int)), this,
          SLOT(StartDraw()));
  connect(ui_->horizontalSlider_12, SIGNAL(valueChanged(int)), this,
          SLOT(StartDraw()));
  connect(ui_->horizontalSlider_13, SIGNAL(valueChanged(int)), this,
          SLOT(StartDraw()));
  connect(ui_->horizontalSlider_14, SIGNAL(valueChanged(int)), this,
          SLOT(StartDraw()));
  connect(ui_->horizontalSlider_15, SIGNAL(valueChanged(int)), this,
          SLOT(StartDraw()));

  connect(ui_->spinBox_4, SIGNAL(valueChanged(int)), this, SLOT(StartDraw()));
  connect(ui_->spinBox_5, SIGNAL(valueChanged(int)), this, SLOT(StartDraw()));
  connect(ui_->spinBox_6, SIGNAL(valueChanged(int)), this, SLOT(StartDraw()));

  connect(ui_->lines_style, SIGNAL(currentIndexChanged(int)), this,
          SLOT(StartDraw()));
  connect(ui_->vert_style, SIGNAL(currentIndexChanged(int)), this,
          SLOT(StartDraw()));
  connect(ui_->proj_type, SIGNAL(currentIndexChanged(int)), this,
          SLOT(StartDraw()));
  LoadSettings();
  Init();
}

View::~View() {
  SaveSettings();
  delete ui_;
}

void View::initializeGL() { glEnable(GL_DEPTH_TEST); }

void View::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

void View::paintGL() {
  glClearColor(ui_->horizontalSlider->value() / 100.0,
               ui_->horizontalSlider_2->value() / 100.0,
               ui_->horizontalSlider_3->value() / 100.0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  if (ui_->proj_type->currentIndex() == 0) {
    glOrtho(-camera_ * 2, camera_ * 2, -camera_ * 2, camera_ * 2,
            -camera_ * 100, camera_ * 100);
  } else {
    gluPerspective(90.0, 1.0, 0.1, 1000000);
    glTranslated(0, 0, -camera_ * 2);
  }

  CoordXYZ rotate{ui_->horizontalSlider_13->value(),
                  ui_->horizontalSlider_14->value(),
                  ui_->horizontalSlider_15->value()};
  CoordXYZ move{ui_->horizontalSlider_10->value(),
                ui_->horizontalSlider_11->value(),
                ui_->horizontalSlider_12->value()};
  controller_->ActionFacede(rotate, move, ui_->spinBox_6->value() / 100.0);

  DrawCube();
  controller_->RefreshVert();
}

void View::StartDraw() { update(); }

void View::Init() {
  ui_->color_r->setText(
      QString::number(ui_->horizontalSlider->value() / 100.0));
  ui_->color_g->setText(
      QString::number(ui_->horizontalSlider_2->value() / 100.0));
  ui_->color_b->setText(
      QString::number(ui_->horizontalSlider_3->value() / 100.0));
  ui_->color_r_3->setText(
      QString::number(ui_->horizontalSlider_7->value() / 100.0));
  ui_->color_g_3->setText(
      QString::number(ui_->horizontalSlider_8->value() / 100.0));
  ui_->color_b_3->setText(
      QString::number(ui_->horizontalSlider_9->value() / 100.0));
  ui_->color_r_2->setText(
      QString::number(ui_->horizontalSlider_4->value() / 100.0));
  ui_->color_g_2->setText(
      QString::number(ui_->horizontalSlider_5->value() / 100.0));
  ui_->color_b_2->setText(
      QString::number(ui_->horizontalSlider_6->value() / 100.0));
}

void View::DrawCube() {
  glVertexPointer(3, GL_DOUBLE, 0, controller_->GetMovedVert());
  glEnableClientState(GL_VERTEX_ARRAY);
  glColor3d(ui_->horizontalSlider_4->value() / 100.0,
            ui_->horizontalSlider_5->value() / 100.0,
            ui_->horizontalSlider_6->value() / 100.0);
  glPointSize(ui_->spinBox_5->value());
  if (ui_->vert_style->currentIndex() == 0) {
    ui_->label_9->show();
    ui_->spinBox_5->show();
    glDrawArrays(GL_POINTS, 0, controller_->GetVertSize());
  } else if (ui_->vert_style->currentIndex() == 1) {
    ui_->label_9->show();
    ui_->spinBox_5->show();
    glEnable(GL_POINT_SMOOTH);
    glDrawArrays(GL_POINTS, 0, controller_->GetVertSize());
    glDisable(GL_POINT_SMOOTH);
  } else {
    ui_->label_9->hide();
    ui_->spinBox_5->hide();
  }
  glColor3d(ui_->horizontalSlider_7->value() / 100.0,
            ui_->horizontalSlider_8->value() / 100.0,
            ui_->horizontalSlider_9->value() / 100.0);
  glLineWidth(ui_->spinBox_4->value());
  if (ui_->lines_style->currentIndex() == 1) {
    glLineStipple(1, 0x00FF);
    glEnable(GL_LINE_STIPPLE);
    glDrawElements(GL_LINES, controller_->GetPolySize(), GL_UNSIGNED_INT,
                   controller_->GetPoly());
    glDisable(GL_LINE_STIPPLE);
  } else {
    glDrawElements(GL_LINES, controller_->GetPolySize(), GL_UNSIGNED_INT,
                   controller_->GetPoly());
  }
  glDisableClientState(GL_VERTEX_ARRAY);
}

void View::OpenFile() {
  QString filter = " OBJ Files (*.obj)";
  QString file_name = QFileDialog::getOpenFileName(this, "Open OBJ file",
                                                   QDir::homePath(), filter);
  if (!file_name.isEmpty() && !file_name.isNull()) {
    QString name = file_name.mid(file_name.lastIndexOf('/') + 1);
    if (controller_->Parse(file_name.toStdString())) {
      camera_ = controller_->GetCamera();
      ui_->name->setText(name);
      ui_->vertices->setText(QString::number(controller_->GetVertSize()));
      ui_->edges->setText(QString::number(controller_->GetPolySize() / 2));
      ui_->path->setText(file_name);
    } else {
      ui_->name->setText("");
      ui_->vertices->setText("");
      ui_->edges->setText("");
      ui_->path->setText("");
      QMessageBox messageBox;
      messageBox.critical(0, "Error", "Error with obj file!");
      messageBox.setFixedSize(500, 200);
    }
  }
}

void View::mousePressEvent(QMouseEvent* mo) {
  mouse_position_ = mo->pos();
  x_start_ = ui_->horizontalSlider_13->value();
  y_start_ = ui_->horizontalSlider_14->value();
}

void View::mouseMoveEvent(QMouseEvent* mo) {
  ui_->horizontalSlider_13->setValue(
      x_start_ + 0.2 * (mo->pos().y() - mouse_position_.y()));
  ui_->horizontalSlider_14->setValue(
      y_start_ + 0.2 * (mo->pos().x() - mouse_position_.x()));
  update();
}

void View::Reset() {
  ui_->horizontalSlider_10->setValue(0);
  ui_->horizontalSlider_11->setValue(0);
  ui_->horizontalSlider_12->setValue(0);
  ui_->horizontalSlider_13->setValue(0);
  ui_->horizontalSlider_14->setValue(0);
  ui_->horizontalSlider_15->setValue(0);
  ui_->spinBox_6->setValue(100);
  ui_->horizontalSlider->setValue(0);
  ui_->horizontalSlider_2->setValue(0);
  ui_->horizontalSlider_3->setValue(0);
  ui_->lines_style->setCurrentIndex(0);
  ui_->spinBox_4->setValue(1);
  ui_->horizontalSlider_7->setValue(100);
  ui_->horizontalSlider_8->setValue(0);
  ui_->horizontalSlider_9->setValue(0);
  ui_->vert_style->setCurrentIndex(0);
  ui_->spinBox_5->setValue(2);
  ui_->horizontalSlider_4->setValue(0);
  ui_->horizontalSlider_5->setValue(0);
  ui_->horizontalSlider_6->setValue(100);
  update();
}

void View::BackColorSlider() {
  ui_->color_r->setText(
      QString::number(ui_->horizontalSlider->value() / 100.0));
  ui_->color_g->setText(
      QString::number(ui_->horizontalSlider_2->value() / 100.0));
  ui_->color_b->setText(
      QString::number(ui_->horizontalSlider_3->value() / 100.0));
  update();
}

void View::VertColorSlider() {
  ui_->color_r_2->setText(
      QString::number(ui_->horizontalSlider_4->value() / 100.0));
  ui_->color_g_2->setText(
      QString::number(ui_->horizontalSlider_5->value() / 100.0));
  ui_->color_b_2->setText(
      QString::number(ui_->horizontalSlider_6->value() / 100.0));
  update();
}

void View::LinesColorSlider() {
  ui_->color_r_3->setText(
      QString::number(ui_->horizontalSlider_7->value() / 100.0));
  ui_->color_g_3->setText(
      QString::number(ui_->horizontalSlider_8->value() / 100.0));
  ui_->color_b_3->setText(
      QString::number(ui_->horizontalSlider_9->value() / 100.0));
  update();
}

void View::SaveImage() {
  QString str = QFileDialog::getSaveFileName(this, NULL, NULL,
                                             "BMP (*.bmp) ;; JPEG (*.jpeg)");
  if (!str.isEmpty()) {
    this->grabFramebuffer().save(str);
  }
}

void View::SaveGif() {
  s_file_name_ = QFileDialog::getSaveFileName(this, NULL, NULL,
                                              "GIF (*.gif) ;; GIF (*.gif)");
  if (s_file_name_.isNull()) return;

  gif_ = new QGifImage;
  gif_->setDefaultDelay(gif_const_fps_);
  start_time_ = 0, tmp_time_ = gif_const_fps_;
  this->ui_->save_gif->setDisabled(true);
  timer_ = new QTimer(this);
  connect(timer_, SIGNAL(timeout()), this, SLOT(OneGif()));
  timer_->start(gif_const_fps_);
}

void View::OneGif() {
  if (start_time_ >= tmp_time_) {
    QPixmap screenGIF(this->size());
    this->render(&screenGIF);
    QImage image = grabFramebuffer();
    gif_->addFrame(image, gif_const_fps_);
    time_print_ = (float)start_time_ / 1e3;
    ui_->Counter->setNum((int)(time_print_ + 1));
    tmp_time_ += gif_const_fps_;
  }
  if (start_time_ == 1000 * gif_length_) {
    gif_->save(s_file_name_);
    timer_->stop();
    ui_->Counter->setText("Done");

    disconnect(timer_, SIGNAL(timeout()), this, SLOT(OneGif()));

    delete gif_;
    delete timer_;
    this->ui_->save_gif->setDisabled(false);
  }
  start_time_ += gif_const_fps_;
}

void View::SaveSettings() {
  settings_->SetScale(ui_->spinBox_6->value());
  settings_->SetRotX(ui_->horizontalSlider_13->value());
  settings_->SetRotY(ui_->horizontalSlider_14->value());
  settings_->SetRotZ(ui_->horizontalSlider_15->value());
  settings_->SetMoveX(ui_->horizontalSlider_10->value());
  settings_->SetMoveY(ui_->horizontalSlider_11->value());
  settings_->SetMoveZ(ui_->horizontalSlider_12->value());
  settings_->SetBackR(ui_->horizontalSlider->value());
  settings_->SetBackG(ui_->horizontalSlider_2->value());
  settings_->SetBackB(ui_->horizontalSlider_3->value());
  settings_->SetLineSt(ui_->lines_style->currentIndex());
  settings_->SetLineTh(ui_->spinBox_4->value());
  settings_->SetLinesR(ui_->horizontalSlider_7->value());
  settings_->SetLinesG(ui_->horizontalSlider_8->value());
  settings_->SetLinesB(ui_->horizontalSlider_9->value());
  settings_->SetVertSt(ui_->vert_style->currentIndex());
  settings_->SetVertSize(ui_->spinBox_5->value());
  settings_->SetVertR(ui_->horizontalSlider_4->value());
  settings_->SetVertG(ui_->horizontalSlider_5->value());
  settings_->SetVertB(ui_->horizontalSlider_6->value());
}

void View::LoadSettings() {
  ui_->spinBox_6->setValue(settings_->GetScale());
  ui_->horizontalSlider_13->setValue(settings_->GetRotX());
  ui_->horizontalSlider_14->setValue(settings_->GetRotY());
  ui_->horizontalSlider_15->setValue(settings_->GetRotZ());
  ui_->horizontalSlider_10->setValue(settings_->GetMoveX());
  ui_->horizontalSlider_11->setValue(settings_->GetMoveY());
  ui_->horizontalSlider_12->setValue(settings_->GetMoveZ());
  ui_->horizontalSlider->setValue(settings_->GetBackR());
  ui_->horizontalSlider_2->setValue(settings_->GetBackG());
  ui_->horizontalSlider_3->setValue(settings_->GetBackB());
  ui_->lines_style->setCurrentIndex(settings_->GetLineSt());
  ui_->spinBox_4->setValue(settings_->GetLineTh());
  ui_->horizontalSlider_7->setValue(settings_->GetLinesR());
  ui_->horizontalSlider_8->setValue(settings_->GetLinesG());
  ui_->horizontalSlider_9->setValue(settings_->GetLinesB());
  ui_->vert_style->setCurrentIndex(settings_->GetVertSt());
  ui_->spinBox_5->setValue(settings_->GetVertSize());
  ui_->horizontalSlider_4->setValue(settings_->GetVertR());
  ui_->horizontalSlider_5->setValue(settings_->GetVertG());
  ui_->horizontalSlider_6->setValue(settings_->GetVertB());
}

}  // namespace s21
