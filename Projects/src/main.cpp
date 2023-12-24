#include "ImagesProcessing.hpp"

int main(){


    cv::String path = "../Projects/Images/fruits.jpg";
    vector<cv::Mat> channels;
    cv::Mat img = cv::imread(path), blue, green, red, vorta;

    cv::resize(img, img, cv::Size(400, 300));

    //segmentar canais bgr:
    cv::split(img, channels);

    blue = channels[0];
    green = channels[1];
    red = channels[2];

    //combinar canais bgr novamente:
    cv::merge(channels, vorta);
    cv::imshow("Original", img);
    cv::imshow("Blue", blue);
    cv::imshow("Green", green);
    cv::imshow("Red", red);
    cv::imshow("Vorta", vorta);

    cv::waitKey(0);

    return 0;

}


int teste_class(){
    cv::String path = "../Projects/Images/eneas.jpg";
    cv::String build = "../Projects/Images/building.jpg";
    cv::Mat eneas = cv::imread(path), neg, resized, swapped, faces, warped, contours;

    if (eneas.empty()){
        cerr << "Erro ao carregar imagem\n";
        return -1;
    }

    ImagesProcessing teste(eneas);

    neg = teste.negative();
    resized = teste.resize();
    swapped = teste.swap();
    faces = teste.faceDetection();
    contours = teste.drawContours();

    teste.cut();

    //cv::bitwise_not(eneas, neg); função para negativar toda a imagem direto
    cv::imwrite("../Projects/Images/eneas_resized.jpg", resized );
    
    cv::imshow("Nosso nome é Enéas negativo", neg);
    cv::imshow("Redimensionada: ", resized);
    cv::imshow("Swapped", swapped);
    cv::imshow("Faces detectadas", faces);
    cv::imshow("Contours", contours);
    cv::imshow("Nosso nome é Enéas", eneas);

    cv::waitKey();

    return 0;


}