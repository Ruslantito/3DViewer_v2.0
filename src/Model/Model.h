#ifndef CPP4_3DVIEWER_SRC_MODEL_MODEL_H_
#define CPP4_3DVIEWER_SRC_MODEL_MODEL_H_

#include <algorithm>
#include <cmath>
#include <execution>
#include <fstream>
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <vector>

#include "./ActionFacede.h"

namespace s21 {

class Model {
 public:
  Model() = default;

  bool Parse(const std::string& filename);
  void RefreshVert() { moved_vert_ = orig_vert_; }
  void ActionFacede(CoordXYZ rotate_coor, CoordXYZ move_coor,
                    double scale_value);
  double* GetMovedVert() { return moved_vert_.data(); }
  unsigned int* GetPoly() { return poly_.data(); }
  size_t GetVertSize() { return moved_vert_.size() / 3; }
  size_t GetPolySize() { return poly_.size(); }
  double GetCamera() { return camera_o_; }

 private:
  bool ParsingObj(std::ifstream& f);
  static bool BothAreSpaces(char lhs, char rhs);
  void Normalization();

  ActionPlace action_place;
  std::vector<double> orig_vert_;
  std::vector<double> moved_vert_;
  std::vector<unsigned int> poly_;
  double camera_o_ = 0;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_SRC_MODEL_MODEL_H_
