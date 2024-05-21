#include "ActionFacede.h"

namespace s21 {

void RotateStrategy::Logic(CoordXYZ rotate,
                           std::vector<double>* moved_vert) const {
  RotateX(rotate.x, moved_vert);
  RotateY(rotate.y, moved_vert);
  RotateZ(rotate.z, moved_vert);
}

void RotateStrategy::RotateX(double rotate,
                             std::vector<double>* moved_vert) const {
  rotate = rotate * pi_divided_180_;
  for (unsigned i = 0; i < moved_vert->size(); i += 3) {
    double temp_y = (*moved_vert)[i + 1];
    double temp_z = (*moved_vert)[i + 2];
    (*moved_vert)[i + 1] =
        temp_y * std::cos(rotate) - temp_z * std::sin(rotate);
    (*moved_vert)[i + 2] =
        temp_y * std::sin(rotate) + temp_z * std::cos(rotate);
  }
}

void RotateStrategy::RotateY(double rotate,
                             std::vector<double>* moved_vert) const {
  rotate = rotate * pi_divided_180_;
  for (unsigned i = 0; i < moved_vert->size(); i += 3) {
    double temp_x = (*moved_vert)[i];
    double temp_z = (*moved_vert)[i + 2];
    (*moved_vert)[i] = temp_x * std::cos(rotate) + temp_z * std::sin(rotate);
    (*moved_vert)[i + 2] =
        temp_z * std::cos(rotate) - temp_x * std::sin(rotate);
  }
}

void RotateStrategy::RotateZ(double rotate,
                             std::vector<double>* moved_vert) const {
  rotate = rotate * pi_divided_180_;
  for (unsigned i = 0; i < moved_vert->size(); i += 3) {
    double temp_x = (*moved_vert)[i];
    double temp_y = (*moved_vert)[i + 1];
    (*moved_vert)[i] = temp_y * std::sin(rotate) + temp_x * std::cos(rotate);
    (*moved_vert)[i + 1] =
        temp_y * std::cos(rotate) - temp_x * std::sin(rotate);
  }
}

void RotateStrategy::Execute(CoordXYZ rotate,
                             std::vector<double>* moved_vert) const {
  Logic(rotate, moved_vert);
}

void MoveStrategy::Logic(CoordXYZ move, std::vector<double>* moved_vert) const {
  std::thread th1(&MoveStrategy::MoveLogic, this, move.x, 0, moved_vert);
  std::thread th2(&MoveStrategy::MoveLogic, this, move.y, 1, moved_vert);
  MoveLogic(move.z, 2, moved_vert);
  th1.join();
  th2.join();
}

void MoveStrategy::MoveLogic(int move, int start_from,
                             std::vector<double>* moved_vert) const {
  for (unsigned i = start_from; i < moved_vert->size(); i += 3) {
    (*moved_vert)[i] += move;
  }
}

void MoveStrategy::Execute(CoordXYZ move,
                           std::vector<double>* moved_vert) const {
  Logic(move, moved_vert);
}

void Scale::Logic(double scale_value, std::vector<double>* moved_vert) {
  std::thread th1(&Scale::ScaleLogic, this, scale_value, 0, moved_vert);
  std::thread th2(&Scale::ScaleLogic, this, scale_value, 1, moved_vert);
  std::thread th3(&Scale::ScaleLogic, this, scale_value, 2, moved_vert);
  ScaleLogic(scale_value, 3, moved_vert);
  th1.join();
  th2.join();
  th3.join();
}

void Scale::ScaleLogic(double scale_value, int thread,
                       std::vector<double>* moved_vert) {
  for (size_t i = thread; i < moved_vert->size();) {
    (*moved_vert)[i] *= scale_value;
    i += 4;
  }
}

void Scale::Execute(double scale_value, std::vector<double>* moved_vert) {
  Logic(scale_value, moved_vert);
}

void ActionPlace::ActionStart(CoordXYZ rotate_coor, CoordXYZ move_coor,
                              double scale_value,
                              std::vector<double>* moved_vert) {
  job_.SetStrategy(&r_s_);
  job_.Execute(rotate_coor, moved_vert);
  job_.SetStrategy(&m_s_);
  job_.Execute(move_coor, moved_vert);
  scale_.Execute(scale_value, moved_vert);
}

}  // namespace s21
