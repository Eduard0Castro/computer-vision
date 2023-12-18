#include<iostream>
#include <opencv2/opencv.hpp>

using namespace std;

cv::Mat negative(cv::Mat);
cv::Mat resize(cv::Mat);

int main(){


    cv::String path = "../Projects/Images/eneas.jpg";
    cv::Mat eneas = cv::imread(path), neg, resized;

    if (eneas.empty()){
        cerr << "Erro ao carregar imagem\n";
        return -1;
    }

    cv::imshow("Nosso nome é Enéas", eneas);

    neg = negative(eneas);    
    resized = resize(eneas);
 
    //cv::bitwise_not(eneas, neg); função para negativar toda a imagem direto
    cv::imwrite("../Projects/Images/eneas_resized.jpg", resized );
    cv::imshow("Nosso nome é Enéas negativo", neg);
    cv::imshow("Redimensionada: ", resized);

    cv::waitKey();

    return 0;

}

cv:: Mat negative(cv::Mat img){
    
    cv::Mat neg;
    int coordenada[4] = {};
    int rows = img.rows;
    int cols = img.cols;

    neg = img.clone(); //Cria uma cópia independente

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
            neg.at<cv::Vec3b>(i, j)[0] = 255 - img.at<cv::Vec3b>(i, j)[0];
            neg.at<cv::Vec3b>(i, j)[1] = 255 - img.at<cv::Vec3b>(i, j)[1];
            neg.at<cv::Vec3b>(i, j)[2] = 255 - img.at<cv::Vec3b>(i, j)[2];
        }
    }

    return neg;
}

cv::Mat resize(cv::Mat img){
    cv::Mat resized;
    int width, height;
    int rows = img.rows, cols = img.cols;

    resized = img.clone();
    cout << rows << " x " << cols << endl;


    do{
    cout << "Digite um valor para a nova altura: ";
    cin >> height;
    }
    while(height <= 0 || height > 3*rows);
    
    do{
    cout << "Digite um valor para a nova largura: ";
    cin >> width;
    }
    while(width <= 0 || width > 3*cols);

    cv::resize(img,resized, cv::Size(width, height));

    return resized;
}