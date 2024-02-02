#include "ImagesProcessing.hpp"
#include "functions.hpp"


int main(){

    cv::String path = "../Projects/Vídeos/movimentacao.mov";
    cv::VideoCapture cap (path);
    cv::Mat frame, hsv, binary;
    vector<vector<cv::Point>> contours;
    vector<cv::Point> polygon;
    cv::Rect retan;
    cv::Scalar min (160,100,100), max (200, 255, 255);
    int perimetro = 0;

    while (cv::waitKey(10) < 0){
        cap.read(frame);

        if (frame.empty())
            break;

        cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

        cv::inRange(hsv, min, max, binary);
        cv::morphologyEx(binary, binary, cv::MORPH_CLOSE, 
                        cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size (9,9)),
                        cv::Point(-1,-1), 2);
        
        cv::findContours(binary, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

        if (contours.size() >= 1){
            perimetro = cv::arcLength(contours[0], true);
            cv::approxPolyDP(contours[0], polygon, 0.1*perimetro, true);
            retan = cv::boundingRect(polygon);
            cv::rectangle(frame, retan, cv::Scalar(0,255,0), 2);
       
            
        }
        cv::imshow("Original", frame);
        cv::imshow("Video", binary);


    }

    cap.release();
    cv::destroyAllWindows();

    return 0;

}