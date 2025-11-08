// src/main.cpp
#include <iostream>
#include <memory>
#include "figure_array.h"
#include "rectangle.h"
#include "rhombus.h"
#include "trapezoid.h"

int main() {
    using D = double;
    Array<std::shared_ptr<Figure<D>>> figures;

    int choice;
    while (true) {
        std::cout << "\n1. add rect\n";
        std::cout << "2. add rhombus\n";
        std::cout << "3. add trapezoid\n";
        std::cout << "4. print all\n";
        std::cout << "5. print centers\n";
        std::cout << "6. total area\n";
        std::cout << "7. erase by index\n";
        std::cout << "0. exit\n> ";
        std::cin >> choice;

        if (!std::cin || choice == 0) break;

        if (choice == 1) {
            auto r = std::make_shared<Rectangle<D>>();
            std::cout << "enter 4 points (x y x y x y x y): ";
            std::cin >> *r;
            figures.push_back(r);
        } else if (choice == 2) {
            auto rh = std::make_shared<Rhombus<D>>();
            std::cout << "enter 4 points (x y x y x y x y): ";
            std::cin >> *rh;
            figures.push_back(rh);
        } else if (choice == 3) {
            auto t = std::make_shared<Trapezoid<D>>();
            std::cout << "enter 4 points (x y x y x y x y): ";
            std::cin >> *t;
            figures.push_back(t);
        } else if (choice == 4) {
            figures.printAll();
        } else if (choice == 5) {
            figures.printCenters();
        } else if (choice == 6) {
            std::cout << "total area = " << figures.totalArea() << "\n";
        } else if (choice == 7) {
            size_t idx;
            std::cout << "index to erase: ";
            std::cin >> idx;
            try {
                figures.erase(idx);
            } catch (const std::exception& e) {
                std::cerr << e.what() << "\n";
            }
        }
    }

    std::cout << "bye\n";
    return 0;
}
