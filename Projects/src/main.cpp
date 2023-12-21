#include "ImagesProcessing.hpp"

int main(){

    cv::String path = "../Projects/Images/eneas.jpg";
    cv::Mat eneas = cv::imread(path), neg, resized, swapped, faces;
    ImagesProcessing teste(eneas);
    if (eneas.empty()){
        cerr << "Erro ao carregar imagem\n";
        return -1;
    }

    neg = teste.negative();
    resized = teste.resize();
    swapped = teste.swap();
    faces = teste.faceDetection();
    teste.cut();

    // //cv::bitwise_not(eneas, neg); função para negativar toda a imagem direto
    cv::imwrite("../Projects/Images/eneas_resized.jpg", resized );
    cv::imshow("Nosso nome é Enéas negativo", neg);
    cv::imshow("Redimensionada: ", resized);
    cv::imshow("Swapped", swapped);
    cv::imshow("Faces detectadas", faces);
    cv::imshow("Nosso nome é Enéas", eneas);

    cv::waitKey();

    return 0;

}