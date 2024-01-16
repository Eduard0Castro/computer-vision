#include "ImagesProcessing.hpp"
#include "functions.hpp"

int main(){


    cv::Mat hole_1 = cv::imread("../Projects/Images/Extração/hole_1.bmp", 0);
    cv::Mat hole_2 = cv::imread("../Projects/Images/Extração/hole_2.bmp", 0);
    cv::Mat hole_3 = cv::imread("../Projects/Images/Extração/hole_3.bmp", 0);
    vector<vector<cv::Point>> contours;
    int num_holes = 0;
    cv::Mat image = hole_3;

    cv::threshold(image, image, 127, 255, cv::THRESH_BINARY);
    cv::findContours(image, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    //Subtrai-se 1 para desconsiderar o contorno do objeto em si
    num_holes = contours.size() - 1;

    cout << "Furos: " << num_holes << endl;

    cv::imshow("Holes", image);

    cv::waitKey();

    return 0;

}