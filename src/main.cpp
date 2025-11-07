#include <iostream>
#include <memory>
#include <sstream>
#include "figure.h"
#include "rectangle.h"
#include "trapezoid.h"
#include "rhombus.h"
#include "figure_array.h"

using T = double;

int main() {
    std::cout << "Figures program (Variant 35: Rectangle, Trapezoid, Rhombus)\n";
    std::cout << "Input format:\n";
    std::cout << "N\n";
    std::cout << "<type> <8 numbers...>\n";
    std::cout << "type: 1=Rectangle 2=Trapezoid 3=Rhombus\n";
    std::cout << "Each figure: 8 numbers: x1 y1 x2 y2 x3 y3 x4 y4\n\n";

    int n;
    if (!(std::cin >> n)) {
        std::cerr << "Bad input\n";
        return 1;
    }

    Array<std::shared_ptr<Figure<T>>> arr;

    for (int i = 0; i < n; ++i) {
        int type;
        std::cin >> type;
        if (!std::cin) {
            std::cerr << "Bad input\n";
            return 1;
        }

        if (type == 1) {
            auto r = std::make_shared<Rectangle<T>>();
            std::cin >> *r;
            arr.push_back(r);
        } else if (type == 2) {
            auto t = std::make_shared<Trapezoid<T>>();
            std::cin >> *t;
            arr.push_back(t);
        } else if (type == 3) {
            auto rh = std::make_shared<Rhombus<T>>();
            std::cin >> *rh;
            arr.push_back(rh);
        } else {
            std::cerr << "Unknown type " << type << "\n";
            --i;
            continue;
        }
    }

    std::cout << "\nAll figures:\n";
    arr.printAll();

    std::cout << "\nCenters:\n";
    arr.printCenters();

    std::cout << "\nTotal area: " << arr.totalArea() << "\n";

    // demonstrate erasing 0 if exists
    if (arr.size() > 0) {
        arr.erase(0);
        std::cout << "\nAfter erase index 0:\n";
        arr.printAll();
    }

    return 0;
}
