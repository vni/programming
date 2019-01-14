// https://www.youtube.com/watch?v=7-nHdQjSRe0
// C++ Templates - Part 4 : Curiously Recurring Template Pattern

#include <iostream>
#include <vector>

struct Shape
{
    virtual Shape* Clone() = 0;
    virtual void Draw() { std::cout << "Shape::Draw(this: " << this << ");\n"; }
    virtual ~Shape() = default;
};

struct Square : public Shape
{
    virtual Square *Clone() override { std::cout << "Square::Clone(...);\n"; return new Square(*this); }
    virtual void Draw() override { std::cout << "Square::Draw(this: " << this << ");\n"; }

    int x = 1;
};

struct Rectangle : public Shape
{
    virtual Rectangle *Clone() override { std::cout << "Rectangle::Clone(...);\n"; return new Rectangle(*this); }
    virtual void Draw() override { std::cout << "Rectangle::Draw(this: " << this << ");\n"; }

    int x = 1;
    int y = 2;
};

int main()
{
    std::vector<Shape*> shapes;
    shapes.push_back(new Square);
    shapes.push_back(new Rectangle);
    shapes.push_back(new Rectangle);
    shapes.push_back(new Rectangle);
    shapes.push_back(new Square);
    //shapes.push_back(new Shape); // compilation failure: invalid new-expression of abstract class type ‘Shape’

    std::vector<Shape*> cloned;
    std::cout << "shapes:\n";
    for (auto &v: shapes) {
        v->Draw();
        cloned.push_back(v->Clone());
    }

    std::cout << "\n\ncloned:\n";
    for (auto &v: cloned) {
        v->Draw();
    }
}
