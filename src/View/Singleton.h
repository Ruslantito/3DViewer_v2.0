#ifndef CPP4_3DVIEWER_SRC_VIEW_SINGLETON_H_
#define CPP4_3DVIEWER_SRC_VIEW_SINGLETON_H_

#include <QSettings>

namespace s21 {

class Singleton {
 public:
  ~Singleton() {
    try {
      set_->sync();
    } catch (...) {
      std::cout << "Error with settings!" << std::endl;
    }
  }

  static std::shared_ptr<Singleton> Instance() {
    static std::shared_ptr<Singleton> instance(new Singleton);
    return instance;
  }

  void SetScale(int scale) { set_->setValue("scale", scale); }
  void SetRotX(int rot_x) { set_->setValue("rotate_x", rot_x); }
  void SetRotY(int rot_y) { set_->setValue("rotate_y", rot_y); }
  void SetRotZ(int rot_z) { set_->setValue("rotate_z", rot_z); }
  void SetMoveX(int m_x) { set_->setValue("move_x", m_x); }
  void SetMoveY(int m_y) { set_->setValue("move_y", m_y); }
  void SetMoveZ(int m_z) { set_->setValue("move_z", m_z); }
  void SetBackR(int back_r) { set_->setValue("background_r", back_r); }
  void SetBackG(int back_g) { set_->setValue("background_g", back_g); }
  void SetBackB(int back_b) { set_->setValue("background_b", back_b); }
  void SetLineSt(int line_st) { set_->setValue("lines_style", line_st); }
  void SetLineTh(int line_th) { set_->setValue("lines_thick", line_th); }
  void SetLinesR(int lines_r) { set_->setValue("lines_r", lines_r); }
  void SetLinesG(int lines_g) { set_->setValue("lines_g", lines_g); }
  void SetLinesB(int lines_b) { set_->setValue("lines_b", lines_b); }
  void SetVertSt(int vert_st) { set_->setValue("vertices_style", vert_st); }
  void SetVertSize(int vert_size) {
    set_->setValue("vertices_size", vert_size);
  }
  void SetVertR(int vert_r) { set_->setValue("vertices_r", vert_r); }
  void SetVertG(int vert_g) { set_->setValue("vertices_g", vert_g); }
  void SetVertB(int vert_b) { set_->setValue("vertices_b", vert_b); }

  int GetScale() { return set_->value("scale", "100").toInt(); }
  int GetRotX() { return set_->value("rotate_x", "0").toInt(); }
  int GetRotY() { return set_->value("rotate_y", "0").toInt(); }
  int GetRotZ() { return set_->value("rotate_z", "0").toInt(); }
  int GetMoveX() { return set_->value("move_x", "0").toInt(); }
  int GetMoveY() { return set_->value("move_y", "0").toInt(); }
  int GetMoveZ() { return set_->value("move_z", "0").toInt(); }
  int GetBackR() { return set_->value("background_r", "0").toInt(); }
  int GetBackG() { return set_->value("background_g", "0").toInt(); }
  int GetBackB() { return set_->value("background_b", "0").toInt(); }
  int GetLineSt() { return set_->value("lines_style", "0").toInt(); }
  int GetLineTh() { return set_->value("lines_thick", "1").toInt(); }
  int GetLinesR() { return set_->value("lines_r", "100").toInt(); }
  int GetLinesG() { return set_->value("lines_g", "0").toInt(); }
  int GetLinesB() { return set_->value("lines_b", "0").toInt(); }
  int GetVertSt() { return set_->value("vertices_style", "0").toInt(); }
  int GetVertSize() { return set_->value("vertices_size", "2").toInt(); }
  int GetVertR() { return set_->value("vertices_r", "0").toInt(); }
  int GetVertG() { return set_->value("vertices_g", "0").toInt(); }
  int GetVertB() { return set_->value("vertices_b", "100").toInt(); }

 private:
  Singleton() { set_ = new QSettings("./settings.ini", QSettings::IniFormat); };
  Singleton(const Singleton &old) = delete;
  const Singleton &operator=(const Singleton &old) = delete;
  QSettings *set_ = nullptr;
};

}  // namespace s21

#endif  //  CPP4_3DVIEWER_SRC_VIEW_SINGLETON_H_
