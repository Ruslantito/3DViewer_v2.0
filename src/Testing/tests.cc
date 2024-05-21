#include <gtest/gtest.h>

#include "../Model/Model.h"

namespace {

s21::Model test;

TEST(parser, 01) {
  test.Parse("./obj/cube_test.obj");

  ASSERT_EQ(test.GetMovedVert()[0], -1);
  ASSERT_EQ(test.GetMovedVert()[1], -1);
  ASSERT_EQ(test.GetMovedVert()[2], -1);
  ASSERT_EQ(test.GetMovedVert()[3], -1);
  ASSERT_EQ(test.GetMovedVert()[4], -1);
  ASSERT_EQ(test.GetMovedVert()[5], 1);
  ASSERT_EQ(test.GetMovedVert()[6], -1);
  ASSERT_EQ(test.GetMovedVert()[7], 1);
  ASSERT_EQ(test.GetMovedVert()[8], -1);
  ASSERT_EQ(test.GetMovedVert()[9], -1);
  ASSERT_EQ(test.GetMovedVert()[10], 1);
  ASSERT_EQ(test.GetMovedVert()[11], 1);
  ASSERT_EQ(test.GetMovedVert()[12], 1);
  ASSERT_EQ(test.GetMovedVert()[13], -1);
  ASSERT_EQ(test.GetMovedVert()[14], -1);
  ASSERT_EQ(test.GetMovedVert()[15], 1);
  ASSERT_EQ(test.GetMovedVert()[16], -1);
  ASSERT_EQ(test.GetMovedVert()[17], 1);
  ASSERT_EQ(test.GetMovedVert()[18], 1);
  ASSERT_EQ(test.GetMovedVert()[19], 1);
  ASSERT_EQ(test.GetMovedVert()[20], -1);
  ASSERT_EQ(test.GetMovedVert()[21], 1);
  ASSERT_EQ(test.GetMovedVert()[22], 1);
  ASSERT_EQ(test.GetMovedVert()[23], 1);
}

TEST(parser, 02) {
  auto res = test.Parse("./obj/wrong_file_v.obj");

  ASSERT_EQ(res, false);
}

TEST(parser, 03) {
  auto res = test.Parse("./obj/wrong_file_f1.obj");

  ASSERT_EQ(res, false);
}

TEST(parser, 04) {
  auto res = test.Parse("./obj/wrong_file_f2.obj");

  ASSERT_EQ(res, false);
}

TEST(scale, 01) {
  test.Parse("./obj/cube_test.obj");
  s21::CoordXYZ rotate_coor = {0, 0, 0};
  s21::CoordXYZ move_coor = {0, 0, 0};
  double scale = 1.3;
  test.ActionFacede(rotate_coor, move_coor, scale);

  ASSERT_EQ(test.GetMovedVert()[0], -1.3);
  ASSERT_EQ(test.GetMovedVert()[1], -1.3);
  ASSERT_EQ(test.GetMovedVert()[2], -1.3);
  ASSERT_EQ(test.GetMovedVert()[3], -1.3);
  ASSERT_EQ(test.GetMovedVert()[4], -1.3);
  ASSERT_EQ(test.GetMovedVert()[5], 1.3);
  ASSERT_EQ(test.GetMovedVert()[6], -1.3);
  ASSERT_EQ(test.GetMovedVert()[7], 1.3);
  ASSERT_EQ(test.GetMovedVert()[8], -1.3);
  ASSERT_EQ(test.GetMovedVert()[9], -1.3);
  ASSERT_EQ(test.GetMovedVert()[10], 1.3);
  ASSERT_EQ(test.GetMovedVert()[11], 1.3);
  ASSERT_EQ(test.GetMovedVert()[12], 1.3);
  ASSERT_EQ(test.GetMovedVert()[13], -1.3);
  ASSERT_EQ(test.GetMovedVert()[14], -1.3);
  ASSERT_EQ(test.GetMovedVert()[15], 1.3);
  ASSERT_EQ(test.GetMovedVert()[16], -1.3);
  ASSERT_EQ(test.GetMovedVert()[17], 1.3);
  ASSERT_EQ(test.GetMovedVert()[18], 1.3);
  ASSERT_EQ(test.GetMovedVert()[19], 1.3);
  ASSERT_EQ(test.GetMovedVert()[20], -1.3);
  ASSERT_EQ(test.GetMovedVert()[21], 1.3);
  ASSERT_EQ(test.GetMovedVert()[22], 1.3);
  ASSERT_EQ(test.GetMovedVert()[23], 1.3);
}

TEST(move, 01) {
  test.Parse("./obj/cube_test.obj");
  s21::CoordXYZ rotate_coor = {0, 0, 0};
  s21::CoordXYZ move_coor = {5, 5, 5};
  test.ActionFacede(rotate_coor, move_coor, 1);
  ASSERT_EQ(test.GetMovedVert()[0], 4);
  ASSERT_EQ(test.GetMovedVert()[1], 4);
  ASSERT_EQ(test.GetMovedVert()[2], 4);
  ASSERT_EQ(test.GetMovedVert()[3], 4);
  ASSERT_EQ(test.GetMovedVert()[4], 4);
  ASSERT_EQ(test.GetMovedVert()[5], 6);
  ASSERT_EQ(test.GetMovedVert()[6], 4);
  ASSERT_EQ(test.GetMovedVert()[7], 6);
  ASSERT_EQ(test.GetMovedVert()[8], 4);
  ASSERT_EQ(test.GetMovedVert()[9], 4);
  ASSERT_EQ(test.GetMovedVert()[10], 6);
  ASSERT_EQ(test.GetMovedVert()[11], 6);
  ASSERT_EQ(test.GetMovedVert()[12], 6);
  ASSERT_EQ(test.GetMovedVert()[13], 4);
  ASSERT_EQ(test.GetMovedVert()[14], 4);
  ASSERT_EQ(test.GetMovedVert()[15], 6);
  ASSERT_EQ(test.GetMovedVert()[16], 4);
  ASSERT_EQ(test.GetMovedVert()[17], 6);
  ASSERT_EQ(test.GetMovedVert()[18], 6);
  ASSERT_EQ(test.GetMovedVert()[19], 6);
  ASSERT_EQ(test.GetMovedVert()[20], 4);
  ASSERT_EQ(test.GetMovedVert()[21], 6);
  ASSERT_EQ(test.GetMovedVert()[22], 6);
  ASSERT_EQ(test.GetMovedVert()[23], 6);
}

TEST(rotate, 01) {
  test.Parse("./obj/cube_test.obj");
  s21::CoordXYZ rotate_coor = {30, 0, 0};
  s21::CoordXYZ move_coor = {0, 0, 0};
  test.ActionFacede(rotate_coor, move_coor, 1);
  EXPECT_NEAR(test.GetMovedVert()[0], -1, 1e-7);
  EXPECT_NEAR(test.GetMovedVert()[1], -0.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[2], -1.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[3], -1, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[4], -1.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[5], 0.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[6], -1, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[7], 1.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[8], -0.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[9], -1, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[10], 0.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[11], 1.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[12], 1, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[13], -0.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[14], -1.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[15], 1, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[16], -1.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[17], 0.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[18], 1, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[19], 1.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[20], -0.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[21], 1, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[22], 0.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[23], 1.366025, 1e-6);
}

TEST(rotate, 02) {
  test.Parse("./obj/cube_test.obj");
  s21::CoordXYZ rotate_coor = {0, 30, 0};
  s21::CoordXYZ move_coor = {0, 0, 0};
  test.ActionFacede(rotate_coor, move_coor, 1);
  EXPECT_NEAR(test.GetMovedVert()[0], -1.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[1], -1, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[2], -0.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[3], -0.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[4], -1, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[5], 1.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[6], -1.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[7], 1, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[8], -0.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[9], -0.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[10], 1, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[11], 1.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[12], 0.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[13], -1, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[14], -1.366025, 1e-6);

  EXPECT_NEAR(test.GetMovedVert()[15], 1.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[16], -1, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[17], 0.366025, 1e-6);

  EXPECT_NEAR(test.GetMovedVert()[18], 0.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[19], 1, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[20], -1.366025, 1e-6);

  EXPECT_NEAR(test.GetMovedVert()[21], 1.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[22], 1, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[23], 0.366025, 1e-6);
}

TEST(rotate, 03) {
  test.Parse("./obj/cube_test.obj");
  s21::CoordXYZ rotate_coor = {0, 0, 30};
  s21::CoordXYZ move_coor = {0, 0, 0};
  test.ActionFacede(rotate_coor, move_coor, 1);
  EXPECT_NEAR(test.GetMovedVert()[0], -1.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[1], -0.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[2], -1, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[3], -1.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[4], -0.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[5], 1, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[6], -0.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[7], 1.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[8], -1, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[9], -0.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[10], 1.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[11], 1, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[12], 0.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[13], -1.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[14], -1, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[15], 0.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[16], -1.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[17], 1, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[18], 1.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[19], 0.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[20], -1, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[21], 1.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[22], 0.366025, 1e-6);
  EXPECT_NEAR(test.GetMovedVert()[23], 1, 1e-6);
}

TEST(normal, 01) {
  test.Parse("./obj/Amogus.obj");
  EXPECT_NEAR(test.GetCamera(), 197.665, 1e-3);
}

}  // namespace
