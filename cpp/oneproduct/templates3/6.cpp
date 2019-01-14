#include <iostream>

int main()
{
    int x = 42;
    int &xr = x;
    int const &cxr = x;
    int const cy = 99;
    int const &cyr = cy;


    std::cout << "x: " << x << ", xr: " << xr << ", cxr: " << cxr << ", "
              << "cy: " << cy << ", cyr: " << cyr << "\n";

    std::cout << "\nTry to modify x: 28\n";
    x = 28;
    std::cout << "x: " << x << ", xr: " << xr << ", cxr: " << cxr << ", "
              << "cy: " << cy << ", cyr: " << cyr << "\n";

    std::cout << "\nTry to modify xr: 22\n";
    xr = 22;
    std::cout << "x: " << x << ", xr: " << xr << ", cxr: " << cxr << ", "
              << "cy: " << cy << ", cyr: " << cyr << "\n";

    std::cout << "\nTry to modify cy: 13\n";
    std::cout << "\033[31;1merror:\033[0m assignment of read-only variable ‘cy’\n";
    /*
     *cy = 13;
     *std::cout << "x: " << x << ", xr: " << xr << ", cxr: " << cxr << ", "
     *          << "cy: " << cy << ", cyr: " << cyr << "\n";
     */

    std::cout << "\nTry to modify cyr: 88\n";
    std::cout << "\033[31;1merror:\033[0m assignment of read-only reference ‘cyr’\n";
    /*
     *cyr = 88;
     *std::cout << "x: " << x << ", xr: " << xr << ", cxr: " << cxr << ", "
     *          << "cy: " << cy << ", cyr: " << cyr << "\n";
     */

    std::cout << "\n";
    auto x1 = x;    // int, copy of x
    auto x2 = xr;   // int, copy of xr
    auto x3 = cxr;  // int, copy of cxr
    auto x4 = cy;   // int, copy of cy
    auto x5 = cyr;  // int, copy of cyr
    std::cout << "x1: " << x1 << ", x2: " << x2 << ", x3: " << x3 << ", x4: " << x4 << ", x5: " << x5 << "\n";
    std::cout << "modify x1..5 as they are ints, so they are the copies of the original values\n";
    x1 = 1, x2 = 2, x3 =3, x4 = 4, x5 = 5;
    std::cout << "x1: " << x1 << ", x2: " << x2 << ", x3: " << x3 << ", x4: " << x4 << ", x5: " << x5 << "\n";
    std::cout << "x: " << x << ", xr: " << xr << ", cxr: " << cxr << ", "
              << "cy: " << cy << ", cyr: " << cyr << "\n";

    std::cout << "\n";
    auto &y1 = x;   // int ref to x
    auto &y2 = xr;  // int ref to x
    auto &y3 = cxr; // const int ref to x
    auto &y4 = cy;  // const int ref to cy
    auto &y5 = cyr; // const int ref to cyr
    std::cout << "y1: " << y1 << ", y2: " << y2 << ", y3: " << y3 << ", y4: " << y4 << ", y5: " << y5 << "\n";
    std::cout << "try to modify y1..5 as they are all refs, and some of them are const refs\n";
    y1 = 10, y2 = 20; // y3 = 30, y4 = 40, y5 = 50;
    std::cout << "y1: " << y1 << ", y2: " << y2 << ", y3: " << y3 << ", y4: " << y4 << ", y5: " << y5 << "\n";
    std::cout << "x: " << x << ", xr: " << xr << ", cxr: " << cxr << ", "
              << "cy: " << cy << ", cyr: " << cyr << "\n";


    std::cout << "\n";
    auto const &z1 = x;   // const int ref to x
    auto const &z2 = xr;  // const int ref to x
    auto const &z3 = cxr; // const int ref to x
    auto const &z4 = cy;  // const int ref to y
    auto const &z5 = cyr; // const int ref to y
    std::cout << "z1: " << z1 << ", z2: " << z2 << ", z3: " << z3 << ", z4: " << z4 << ", z5: " << z5 << "\n";
    std::cout << "Failed to modify z const refs, cause all of them are const\n";
    //z1 = 100, z2 = 200; z3 = 300, z4 = 400, z5 = 500;
    std::cout << "z1: " << z1 << ", z2: " << z2 << ", z3: " << z3 << ", z4: " << z4 << ", z5: " << z5 << "\n";
    std::cout << "x: " << x << ", xr: " << xr << ", cxr: " << cxr << ", "
              << "cy: " << cy << ", cyr: " << cyr << "\n";
}
