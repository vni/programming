// https://www.youtube.com/watch?v=7-nHdQjSRe0
// C++ Templates - Part 4 : Curiously Recurring Template Pattern

#include <iostream>
#include <vector>

struct Shape
{
    virtual Shape *Clone() = 0;
    virtual void Draw() { std::cout << "Shape::Draw(this: " << this << ");\n"; }
    virtual ~Shape() = default;
};

template<typename T>
struct ShapeCRTP : public Shape // Curiously Recurring Type Pattern
{
    virtual Shape* Clone() override { return new T(*static_cast<T*>(this)); }
};

struct Square : public ShapeCRTP<Square>
{
    virtual void Draw() override { std::cout << "Square::Draw(this: " << this << ");\n"; }

    int x = 1;
};

struct Rectangle : public ShapeCRTP<Rectangle>
{
    virtual void Draw() override { std::cout << "Rectangle::Draw(this: " << this << ");\n"; }

    int x = 1;
    int y = 2;
};

struct Triangle : public ShapeCRTP<Triangle>
{
    virtual void Draw() override { std::cout << "Triangle::Draw(this: " << this << ");\n"; }
};

int main()
{
    std::vector<Shape*> shapes;
    shapes.push_back(new Square);
    shapes.push_back(new Rectangle);
    shapes.push_back(new Rectangle);
    shapes.push_back(new Rectangle);
    shapes.push_back(new Square);
    shapes.push_back(new Triangle);
    //shapes.push_back(Shape()); // compilation failure: invalid new-expression of abstract class type ‘Shape’

    std::vector<Shape*> cloned;
    std::cout << "shapes:\n";
    for (auto v: shapes) {
        v->Draw();
        cloned.push_back(v->Clone());
    }

    std::cout << "\n\ncloned:\n";
    for (auto v: cloned) {
        v->Draw();
    }
}
