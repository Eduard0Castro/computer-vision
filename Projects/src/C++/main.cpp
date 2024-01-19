#include "ImagesProcessing.hpp"
#include "functions.hpp"


int main(){

    cv::String path = "../Projects/Vídeos/objetos-coloridos-480.mov";
    cv::VideoCapture video(path);
    cv::Mat frame;
    int contr = 0, contb = 0, contv = 0;
    cv::Scalar media;
    double maiord = 0;
    int index = 0, lastscreen = 0;


    while (true){
        
        index ++;
        video.read(frame);
        if (frame.empty()) break;

        media = cv::mean(frame);
        maiord = max(media[0], media[1]);
        maiord = max(maiord, media[2]);

        if (index == 30){
            if (int(media[0]) == int(media[2])){
                lastscreen = 0;
            }

            else{

                if (lastscreen == 0){
                    if (media[1] == maiord){
                        cout << "Tampa Verde!" << endl;
                        contv ++;
                    }
                    else if (media[2] ==  maiord){
                        cout << "Tampa Vermelha!" << endl;
                        contr++;
                    }

                    else{
                        cout << "Tampa Azul!" << endl;
                        contb++;
                    }

                    lastscreen = 1;
                }
            
            }
        index = 0;
        }

        cv::imshow("Frame", frame);

        if (cv::waitKey(10) >= 0) break;


    }

    cout << "Tampas azuis: " << contb << endl;
    cout << "Tampas verdes: " << contv << endl;
    cout << "Tampaz vermelhas: " << contr << endl;

    return 0;

}