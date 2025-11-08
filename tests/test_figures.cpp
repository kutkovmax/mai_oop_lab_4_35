#include <gtest/gtest.h>
#include <memory>
#include <cmath>
#include "figure_array.h"
#include "rectangle.h"
#include "rhombus.h"
#include "trapezoid.h"

using D = double;

//
// ---------- RECTANGLE TESTS ----------
//
TEST(RectangleTest, BasicProperties) {
    Rectangle<D> r1(Point<D>{0,0}, Point<D>{2,0}, Point<D>{2,1}, Point<D>{0,1});
    Rectangle<D> r2 = r1; // copy

    EXPECT_TRUE(r1 == r2);
    EXPECT_NEAR(r1.area(), 2.0, 1e-9);

    auto c = r1.center();
    EXPECT_NEAR(c.x, 1.0, 1e-9);
    EXPECT_NEAR(c.y, 0.5, 1e-9);
}

TEST(RectangleTest, InequalityAfterChange) {
    Rectangle<D> r1(Point<D>{0,0}, Point<D>{2,0}, Point<D>{2,1}, Point<D>{0,1});
    Rectangle<D> r2(Point<D>{0,0}, Point<D>{1,0}, Point<D>{1,1}, Point<D>{0,1});
    EXPECT_FALSE(r1 == r2);
}

TEST(RectangleTest, CloneWorks) {
    Rectangle<D> r1(Point<D>{0,0}, Point<D>{2,0}, Point<D>{2,1}, Point<D>{0,1});
    std::unique_ptr<Figure<D>> clone(r1.clone());
    EXPECT_NEAR(static_cast<double>(*clone), r1.area(), 1e-9);
}

//
// ---------- RHOMBUS TESTS ----------
//
TEST(RhombusTest, BasicProperties) {
    Rhombus<D> rh(Point<D>{0,0}, Point<D>{1,1}, Point<D>{2,0}, Point<D>{1,-1});
    double a = rh.area();
    EXPECT_GT(a, 0.0);

    auto c = rh.center();
    EXPECT_NEAR(c.x, 1.0, 1e-9);
    EXPECT_NEAR(c.y, 0.0, 1e-9);
}

//
// ---------- TRAPEZOID TESTS ----------
//
TEST(TrapezoidTest, BasicProperties) {
    Trapezoid<D> t(Point<D>{0,0}, Point<D>{3,0}, Point<D>{2,1}, Point<D>{1,1});
    EXPECT_GT(t.area(), 0.0);

    auto c = t.center();
    EXPECT_GT(c.x, 0.0);
    EXPECT_GE(c.y, 0.0);
}

//
// ---------- ARRAY TESTS ----------
//
TEST(ArrayTest, SharedPtrFiguresOperations) {
    Array<std::shared_ptr<Figure<D>>> arr;
    auto r = std::make_shared<Rectangle<D>>(Point<D>{0,0}, Point<D>{1,0}, Point<D>{1,1}, Point<D>{0,1});
    auto t = std::make_shared<Trapezoid<D>>(Point<D>{0,0}, Point<D>{3,0}, Point<D>{2,1}, Point<D>{1,1});

    arr.push_back(r);
    arr.push_back(std::move(t));

    EXPECT_EQ(arr.size(), 2);
    double total = arr.totalArea();
    EXPECT_GT(total, 0.0);

    arr.erase(0);
    EXPECT_EQ(arr.size(), 1);

    Array<std::shared_ptr<Figure<D>>> arr2 = std::move(arr);
    EXPECT_EQ(arr.size(), 0);
    EXPECT_EQ(arr2.size(), 1);
}

TEST(ArrayTest, ConcreteRectangleType) {
    Array<Rectangle<D>> rects;
    Rectangle<D> R1(Point<D>{0,0}, Point<D>{2,0}, Point<D>{2,1}, Point<D>{0,1});
    Rectangle<D> R2(Point<D>{0,0}, Point<D>{1,0}, Point<D>{1,1}, Point<D>{0,1});

    rects.push_back(R1);
    rects.push_back(std::move(R2));

    EXPECT_EQ(rects.size(), 2);
    double total = rects.totalArea();
    EXPECT_GT(total, 0.0);

    rects.erase(1);
    EXPECT_EQ(rects.size(), 1);
}

TEST(ArrayTest, TotalAreaWithDifferentFigures) {
    Array<std::shared_ptr<Figure<D>>> arr;
    arr.push_back(std::make_shared<Rectangle<D>>(Point<D>{0,0}, Point<D>{1,0}, Point<D>{1,1}, Point<D>{0,1}));
    arr.push_back(std::make_shared<Rhombus<D>>(Point<D>{0,0}, Point<D>{1,1}, Point<D>{2,0}, Point<D>{1,-1}));
    arr.push_back(std::make_shared<Trapezoid<D>>(Point<D>{0,0}, Point<D>{3,0}, Point<D>{2,1}, Point<D>{1,1}));

    double total = arr.totalArea();
    EXPECT_GT(total, 0.0);
}

//
// ---------- MAIN ----------
//
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
