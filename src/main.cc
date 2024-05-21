#include <QApplication>

#include "View/View.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  s21::Model model;
  std::shared_ptr<s21::Singleton> singleton = s21::Singleton::Instance();
  s21::Controller controller(&model);
  s21::View view(&controller, singleton);
  view.show();
  return a.exec();
}
