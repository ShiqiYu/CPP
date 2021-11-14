#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main()
{
    float a[6]={1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f};
    float b[6]={1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
    cv::Mat A(2, 3, CV_32FC1, a);
    cv::Mat B(3, 2, CV_32FC1, b);

    cv::Mat C = A * B;

    cout << "Matrix C = " << endl 
        << C << endl;
    return 0;
}