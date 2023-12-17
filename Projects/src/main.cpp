#include<iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;

int main(){


    cv::String path = "/home/eduardocastro/Computer_Vision/Projects/Images/eneas.jpg";
    cv::Mat eneas = cv::imread(path), neg;
    cv::Mat cam;
    int coordenada[4] = {};

    if (eneas.empty()){
        cerr << "Erro ao carregar imagem\n";
        return -1;
    }

    neg = eneas.clone(); //cria uma cópia idependente

    cv::imshow("Nosso nome é Enéas", eneas);


    int rows = eneas.rows;
    int cols = eneas.cols;

    cout << rows <<  " x " << cols << endl;
    cout << endl;
        
    do{
        cout << "Digite o x da primeira coordenada da imagem: ";
        cin >> coordenada[0];
    }
    while (coordenada [0] < 0 || coordenada[0] > rows);

    do{
        cout << "Digite o y da primeira coordenada da imagem: ";
        cin >> coordenada[1];
    }
    while (coordenada[1] < 0 || coordenada[1] > cols);

    do{
        cout << "Digite o x da segunda coordenada da imagem: ";
        cin >> coordenada[2];
    }
    while(coordenada[2] < 0 || coordenada[2] > rows);

    do{
        cout << "Digite o y da segunda coordenada da imagem: ";
        cin >> coordenada[3];
    }
    while (coordenada[3] < 0 || coordenada [3] > cols);

    //Para o óculos Dr. Eneas: 131 x 80 ; 198 x 258


    for (int i = coordenada[0]; i < coordenada[2]; i++){
        for (int j = coordenada[1]; j < coordenada[3]; j++){
            neg.at<cv::Vec3b>(i, j)[0] = 255 - eneas.at<cv::Vec3b>(i, j)[0];
            neg.at<cv::Vec3b>(i, j)[1] = 255 - eneas.at<cv::Vec3b>(i, j)[1];
            neg.at<cv::Vec3b>(i, j)[2] = 255 - eneas.at<cv::Vec3b>(i, j)[2];
        }
    }
    
 
    //cv::bitwise_not(eneas, neg); função para negativar toda a imagem direto
    //cv::imwrite("../Projects/Images/eneas_negativo.jpg", neg );
    cv::imshow("Nosso nome é Enéas negativo", neg);


    cv::waitKey();

    return 0;

}
