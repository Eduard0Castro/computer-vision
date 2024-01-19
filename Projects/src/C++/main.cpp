#include "ImagesProcessing.hpp"
#include "functions.hpp"


int main(){

    cv::String path = "../Projects/Vídeos/formas-geometricas-480.mov";
    cv::VideoCapture video (path);
    cv::Mat frame, gray, binary;
    vector<int> medidos;
    int index = 0;
    int media = 0;
    int vertices = 0, anteriores = 0, perimetro = 0;
    vector<vector<cv::Point>> contours;
    vector <cv::Point> poligono;

    for (int i = 0; i < 7; i++){
        medidos.push_back(0);
        cout << medidos[i] << " ";

    }

    cout << endl;

    while (true){

        video.read(frame);
        if (frame.empty()) break;
        
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::threshold(gray, binary, 127, 255, cv::THRESH_BINARY);

        media = int(cv::mean(binary)[0]);

        if (media != 0){
            if(media == int(cv::mean(medidos)[0])){
                cv::findContours(binary, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
                perimetro = cv::arcLength(contours[0], true);
                cv::approxPolyDP(contours[0], poligono, 0.03*perimetro, true);

                vertices = poligono.size();

                if (vertices != anteriores){

                    anteriores = vertices;
                    switch (vertices)
                    {
                    case 3:
                        cout << "Triângulo" << endl; 
                        break;
                    case 4:
                        cout << "Quadrilátero" << endl;
                        break;
                    default:

                        if (vertices > 7){
                            cout << "Círculo" << endl;

                        }

                        else    
                            break;
                    }
                }
            }

        medidos[index] = media;

        if (index == 6)
            index = -1;

        index ++;

        }

        cv::imshow("Video", binary);

        if (cv::waitKey(10) >= 0) break;
        
    }

    return 0;

}