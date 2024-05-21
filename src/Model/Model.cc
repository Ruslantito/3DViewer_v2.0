#include "Model.h"

namespace s21 {

bool Model::Parse(const std::string &filename) {
  orig_vert_.clear();
  moved_vert_.clear();
  poly_.clear();
  std::ifstream fs(filename);
  if (!ParsingObj(fs)) {
    orig_vert_.clear();
    poly_.clear();
    return false;
  } else {
    RefreshVert();
    Normalization();
    return true;
  }
}

bool Model::BothAreSpaces(char lhs, char rhs) {
  return (lhs == rhs) && (lhs == ' ');
}

bool Model::ParsingObj(std::ifstream &f) {
  std::string line;
  std::string temp;
  while (std::getline(f, line)) {
    std::string::iterator new_end =
        std::unique(line.begin(), line.end(), BothAreSpaces);
    line.erase(new_end, line.end());

    if (line.back() == '\n' || line.back() == '\r') {
      line.pop_back();
    }

    if (line[0] == 'v' && line[1] == ' ') {
      line.erase(0, 2);
      std::istringstream ss(line);
      double number;

      for (size_t i = 0; i < 3; ++i) {
        std::getline(ss, temp, ' ');
        try {
          number = std::stod(temp);
        } catch (std::invalid_argument &e) {
          return false;
        }
        orig_vert_.push_back(number);
      }
    }

    if (line[0] == 'f' && line[1] == ' ') {
      line.erase(0, 2);
      std::istringstream ss(line);
      unsigned int first = 0;
      unsigned int number = 0;

      std::getline(ss, temp, ' ');
      temp = temp.substr(0, temp.find("/"));
      try {
        number = std::stoi(temp) - 1;
      } catch (std::invalid_argument &e) {
        return false;
      }
      first = number;
      poly_.push_back(number);

      while (std::getline(ss, temp, ' ')) {
        temp = temp.substr(0, temp.find("/"));
        try {
          number = std::stoi(temp) - 1;
        } catch (std::invalid_argument &e) {
          return false;
        }
        poly_.push_back(number);
        poly_.push_back(number);
      }
      poly_.push_back(first);
    }
  }

  return true;
}

void Model::Normalization() {
  auto minmax = std::minmax_element(moved_vert_.begin(), moved_vert_.end());
  camera_o_ = std::max(std::abs(*minmax.first), std::abs(*minmax.second));
}

void s21::Model::ActionFacede(CoordXYZ rotate_coor, CoordXYZ move_coor,
                              double scale_value) {
  action_place.ActionStart(rotate_coor, move_coor, scale_value, &moved_vert_);
}

}  // namespace s21
