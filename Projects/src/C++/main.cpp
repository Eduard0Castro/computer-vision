#include "ImagesProcessing.hpp"
#include "functions.hpp"

int main(){

    cv::Mat rodela1 = cv::imread("../Projects/Images/Extração/rodela1.jpeg", 0);
    cv::Mat rodela2 = cv::imread("../Projects/Images/Extração/rodela2.jpeg", 0);
    cv::Mat rodela3 = cv::imread("../Projects/Images/Extração/rodela3.jpeg", 0);

    Hu(rodela1);
    Hu(rodela2);
    Hu(rodela3);

    return 0;

}