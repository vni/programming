#include <iostream>

int main()
{
    int x = 42;
    int &xr = x;
    int const &cxr = x;
    int const cy = 24;
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
}
