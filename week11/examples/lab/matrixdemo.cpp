#include <iostream>
#include <memory>

class Matrix
{
  private:
    size_t rows;
    size_t cols;
    std::shared_ptr<float[]> data;
  public:
    Matrix(size_t r, size_t c)
    {
        if ( r * c == 0)
        {
            rows = 0;
            cols = 0;
            data = nullptr;
        }
        else{
            rows = r;
            cols = c;
            data = std::shared_ptr<float[]>(new float[r * c]);
        }
    }
    Matrix(const Matrix & m): rows(m.rows), cols(m.cols), data(m.data){}

    friend std::ostream & operator<<(std::ostream & os, const Matrix & m)
    {
        os << "size (" << m.rows << "x" << m.cols << ")" << std::endl;
        os << "[" << std::endl;
        for (size_t r = 0; r < m.rows; r++)
        {
            for(size_t c = 0; c < m.cols; c++)
                os << m.data[r * m.rows + c] << ", ";
            os << std::endl;
        }
        os << "]";
        return os;
    }
};

int main()
{
    Matrix m1(3,8);
    Matrix m2(4,8);

    m2 = m1;
    m1.setElement(1,2, 4.5f);
    std::cout << m2.getElement(1,2) << std::endl;

    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;

    return 0;
}