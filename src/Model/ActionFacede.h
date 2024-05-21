#ifndef CPP4_3DVIEWER_SRC_MODEL_ACTIONFACEDE_H_
#define CPP4_3DVIEWER_SRC_MODEL_ACTIONFACEDE_H_

#include <cmath>
#include <iostream>
#include <thread>
#include <vector>

namespace s21 {

struct CoordXYZ {
  int x;
  int y;
  int z;
};

class StrategyInterface {
 public:
  virtual void Execute(CoordXYZ action,
                       std::vector<double>* moved_vert) const = 0;
};

class RotateStrategy : public StrategyInterface {
 public:
  void Execute(CoordXYZ rotate, std::vector<double>* moved_vert) const override;

 private:
  double pi_divided_180_ = M_PI / 180;
  void Logic(CoordXYZ rotate, std::vector<double>* moved_vert) const;
  void RotateX(double rotate, std::vector<double>* moved_vert) const;
  void RotateY(double rotate, std::vector<double>* moved_vert) const;
  void RotateZ(double rotate, std::vector<double>* moved_vert) const;
};

class MoveStrategy : public StrategyInterface {
 public:
  void Execute(CoordXYZ move, std::vector<double>* moved_vert) const override;

 private:
  void Logic(CoordXYZ move, std::vector<double>* moved_vert) const;
  void MoveLogic(int move, int start_from,
                 std::vector<double>* moved_vert) const;
};

class Context {
 public:
  Context() { strategy_ = nullptr; }
  explicit Context(StrategyInterface* strategy) : strategy_(strategy) {}
  void SetStrategy(StrategyInterface* strategy) { strategy_ = strategy; }
  void Execute(CoordXYZ action, std::vector<double>* moved_vert) const {
    strategy_->Execute(action, moved_vert);
  }

 private:
  StrategyInterface* strategy_;
};

class Scale {
 public:
  void Execute(double scale_value, std::vector<double>* moved_vert);

 private:
  void Logic(double scale_value, std::vector<double>* moved_vert);
  void ScaleLogic(double scale_value, int thread,
                  std::vector<double>* moved_vert);
};

class ActionPlace {
 public:
  void ActionStart(CoordXYZ rotate_coor, CoordXYZ move_coor, double scale_value,
                   std::vector<double>* moved_vert);

 private:
  RotateStrategy r_s_;
  MoveStrategy m_s_;
  Context job_;
  Scale scale_;
};

}  // namespace s21

#endif  //  CPP4_3DVIEWER_SRC_MODEL_ACTIONFACEDE_H_
