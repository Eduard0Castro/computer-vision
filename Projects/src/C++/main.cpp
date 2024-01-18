#include "ImagesProcessing.hpp"
#include "functions.hpp"

int main(){

    cv::Mat selecao = cv::imread("../Projects/Images/HaarCascade/selecao.jpg");
    cv::CascadeClassifier face_cascade;
    string haarcascade = "../Projects/XML/haarcascade_frontalface_default.xml";
    cv::Mat gray;
    vector<cv::Rect> detects;

    cv::cvtColor(selecao, gray, cv::COLOR_BGR2GRAY);

    face_cascade.load(haarcascade);
    face_cascade.detectMultiScale(gray, detects, 1.3, 5, 0, cv::Size(30,30));

    for (int i = 0; i < detects.size(); i++){
        cv::rectangle(selecao, detects[i], cv::Scalar(0,255,0), 2);
    }

    cout << "Número de faces: " << detects.size() << endl;
    cv::imshow("Seleção", selecao);
    cv::waitKey();
   

    return 0;

}