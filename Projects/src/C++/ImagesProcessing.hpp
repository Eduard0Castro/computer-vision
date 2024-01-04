#ifndef IMAGESPROCESSING_HPP
#define IMAGESPROCESSING_HPP
#include <iostream>
#include <opencv2/opencv.hpp>
 
using namespace std;

class ImagesProcessing{
    protected:

        cv::Mat copy;
        int rows, cols;

    public:

        ImagesProcessing(cv::Mat img){
            
            copy = img;
            rows = copy.rows;
            cols = copy.cols;

        }

        ~ImagesProcessing(){

        }

        cv::Mat negative();
        cv::Mat resize();
        cv::Mat swap();
        cv::Mat faceDetection();
        void cut();
        cv::Mat warp(float, float, float, float, float, float, float, float, float, float);
        cv::Mat drawContours();
};

cv::Mat ImagesProcessing::negative(){
    
    cv::Mat neg = copy.clone();
    int coordenadas[4] = {};

    cout << endl;

    do{
        cout << "Digite o x da coordenada de início: ";
        cin >> coordenadas[0];
    }
    while(coordenadas[0] < 0 || coordenadas[0] > cols);

    do{
        cout << "Digite o y da coordenada de início: ";
        cin >> coordenadas[1];
    }
    while(coordenadas[1] < 0 || coordenadas[1] > rows);

    do{
        cout << "Digite o x da coordenada final: ";
        cin >> coordenadas[2];
    }
    while(coordenadas[2] < 0 || coordenadas[2] > cols);

    do{
        cout << "Digite o y da coordenada final: ";
        cin >> coordenadas[3];
    }
    while (coordenadas[3] < 0 || coordenadas[3] > rows);

    for (int i = coordenadas[0]; i <= coordenadas[2]; i++){
        for (int j = coordenadas[1]; j < coordenadas[3]; j++){
            neg.at<cv::Vec3b>(j,i)[0] = 255 - copy.at<cv::Vec3b>(j,i)[0];
            neg.at<cv::Vec3b>(j,i)[1] = 255 - copy.at<cv::Vec3b>(j,i)[1];
            neg.at<cv::Vec3b>(j,i)[2] = 255 - copy.at<cv::Vec3b>(j,i)[2];
        }
    }

    return neg;
}

cv::Mat ImagesProcessing::resize(){

    cv::Mat resized;
    int width, height;

    cout << endl;

    do{
        cout << "Digite o novo valor para a altura: ";
        cin >> height;
    }
    while(height <=0 || height > 3*copy.size().height);

    do{
        cout << "Digite o novo valor para a largura: ";
        cin >> width;
    }
    while(width <= 0 || width > 3*copy.size().width);

    cv::resize(copy, resized, cv::Size(width, height));

    return resized;
}

cv::Mat ImagesProcessing::swap(){
    
    cv::Mat3b swapped(rows, cols, cv::Vec3b(0,0,0));

    cv::Rect rois[4] = {
        cv::Rect(0, 0, cols/2, rows/2), 
        cv::Rect(cols/2, 0, cols/2, rows/2),
        cv::Rect(0, rows/2, cols/2, rows/2), 
        cv::Rect(cols/2, rows/2, cols/2, rows/2) 
    };

    int sequence [4] = {3,1,2,0};

    for (int i = 0; i < 4; i++){
        cv::Mat region(copy, rois[i]);
        region.copyTo(swapped(rois[sequence[i]]));
    }

    return swapped;

}

cv::Mat ImagesProcessing::faceDetection(){
   
    cv::Mat detections = copy.clone();
    cv::String haar_cascade = "../Projects/XML/haarcascade_frontalface_default.xml";
    cv::CascadeClassifier detect;
    vector<cv::Rect> detects;
    

    detect.load(haar_cascade);
    if (detect.empty()){
        cerr << "Não foi possível carregar o XML" << endl;
    }

    detect.detectMultiScale(copy, detects);

    for (int i = 0; i < detects.size(); i++){
        cv::rectangle(detections, detects[i].tl(), detects[i].br(), cv::Scalar(0, 255, 0), 2);
    }

    return detections;

}

void ImagesProcessing::cut(){

    cv::Mat cortes;
    int n_cortes = 5;

    for (int i = 0; i < n_cortes; i++){
        cortes = copy(cv::Rect(0, rows*i/n_cortes, 
                      copy.size().width, copy.size().height/n_cortes));

        cv::imwrite(cv::format("../Projects/Images/Eneas/eneas%d.jpg", i+1), cortes);
    }
}

cv::Mat ImagesProcessing::warp(float x1 = 457, float y1 = 179, 
                               float x2 = 745, float y2 = 57, 
                               float x3 = 47, float y3 = 476, 
                               float x4 = 664, float y4 = 284, 
                               float width = 400, float height = 450){
                               //dados para a imagem "building.jpg"
    
    cv::Mat warped, mat_perspective;


    cv::Point2f src[4] = {{x1, y1}, {x2, y2}, 
                         {x3, y3}, {x4, y4}}; 

    cv::Point2f destiny[4] = {{0,0}, {width, 0}, 
                             {0, height}, {width, height}};
                             
    //Matriz de ajuste de perspectiva:
    mat_perspective = cv::getPerspectiveTransform(src, destiny);

    cv::warpPerspective(copy, warped, mat_perspective, cv::Size(width, height));

    return warped;
}

cv::Mat ImagesProcessing::drawContours(){
    
    cv::Mat contours = copy.clone(), bin, dilated, kernel;
    cv::String name;
    vector<vector<cv::Point>> contornos, lados;
    vector <cv::Vec4i> hierarquia;
    vector<cv::Rect> retangulo;
    float perimetro;
    int cont = 0;
    

    //kernel é uma matriz retangular (shape = 1) de tamanho 3x3
    kernel = cv::getStructuringElement(1, cv::Size(3,3));

    //threshold 1 e 2 são as intensidades de gradiente aceitas
    cv::Canny(copy, bin, 0, 200); 

    cv::dilate(bin, dilated, kernel);

    cv::findContours(dilated, contornos, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    lados = contornos;

    retangulo.resize(contornos.size());

    for(int i = 0; i < contornos.size(); i++){

        perimetro = cv::arcLength(contornos[i], true);
        cv::approxPolyDP(contornos[i], lados[i], 0.01*perimetro, true); 
        retangulo[i] = cv::boundingRect(lados[i]);

        if (lados.size() == 4){
            name = "Retangulo";

            if (perimetro >= 100){
                cv::drawContours(contours, lados, i, cv::Scalar(0,0,255), 2);
                cv::putText(contours, name, cv::Point(retangulo[i].x, retangulo[i].y), 
                            cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0,255,0), 1, 2);
            }

            cont++;  
        }

        else{
            cv::putText(contours, cv:: String("No contours!"), cv::Point(5,20),
                        cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,0,255), 1.5);
        }

    }

    cout << endl << cont << endl;
    return contours;

}

#endif