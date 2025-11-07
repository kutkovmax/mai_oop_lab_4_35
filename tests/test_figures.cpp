#include <gtest/gtest.h>
#include <sstream>
#include <memory>
#include "rectangle.h"
#include "trapezoid.h"
#include "rhombus.h"
#include "figure_array.h"

TEST(RectangleTest, AreaAndCenter) {
    Rectangle<double> r;
    std::stringstream ss("0 0  4 0  4 3  0 3");
    ss >> r;
    EXPECT_NEAR(double(r), 12.0, 1e-6);
    auto c = r.center();
    EXPECT_NEAR(c.x, 2.0, 1e-6);
    EXPECT_NEAR(c.y, 1.5, 1e-6);
}

TEST(RhombusTest, AreaAndCenter) {
    Rhombus<double> rh;
    // diagonals 6 and 8 -> area = 24
    std::stringstream ss("3 0  0 4  3 8  6 4");
    ss >> rh;
    EXPECT_NEAR(double(rh), 24.0, 1e-6);
    auto c = rh.center();
    EXPECT_NEAR(c.x, 3.0, 1e-6);
    EXPECT_NEAR(c.y, 4.0, 1e-6);
}

TEST(TrapezoidTest, Area) {
    Trapezoid<double> t;
    std::stringstream ss("0 0  5 0  4 3  1 3");
    ss >> t;
    EXPECT_NEAR(double(t), 12.0, 1e-6);
}

TEST(ArrayTest, PushEraseTotal) {
    Array<std::shared_ptr<Figure<double>>> arr;
    {
        auto r = std::make_shared<Rectangle<double>>();
        std::stringstream ss("0 0  2 0  2 2  0 2");
        ss >> *r;
        arr.push_back(r);
    }
    {
        auto rh = std::make_shared<Rhombus<double>>();
        std::stringstream ss("2 1  1 2  2 3  3 2");
        ss >> *rh;
        arr.push_back(rh);
    }
    EXPECT_EQ(arr.size(), 2);
    double total = arr.totalArea();
    EXPECT_NEAR(total, 4.0 + 2.0, 1e-6);
    arr.erase(0);
    EXPECT_EQ(arr.size(), 1);
}
