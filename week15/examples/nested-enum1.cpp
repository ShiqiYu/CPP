#include <iostream>

enum DataType
{
    TYPE8U,
    TYPE8S,
    TYPE32F,
    TYPE64F
};
class Mat
{
private:
    DataType type;
    void * data;
public:
    Mat(DataType type) : type(type), data(NULL){}

    DataType getType() const { return type;  }
};

int main()
{
    Mat image(TYPE8U);

    if (image.getType() == TYPE8U)
        std::cout << "This is an 8U matrix." << std::endl;
	else
        std::cout << "I am not an 8U matrix." << std::endl;

    return 0;
}
