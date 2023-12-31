#include "ImagesProcessing.hpp"

int main(){

    cv::Mat red_chips = cv::imread("../Projects/Images/Fichas/ficha1.bmp");
    cv::Mat black_chips = cv::imread("../Projects/Images/Fichas/ficha2.bmp");
    cv::Mat one = cv::imread("../Projects/Images/Fichas/red1.bmp");
    cv::Mat Two = cv::imread("../Projects/Images/Fichas/red2.bmp");
    cv::Mat added, subtracted, mixed, three;

    cv::add(red_chips, black_chips, added);
    //cv::imshow("Adicionada 1", added);


    cv::subtract(added, 70, subtracted);
    //cv::imshow("Subtraída", subtracted);

    cv::addWeighted(red_chips, 1, black_chips, 0.2, 0, mixed);
    //cv::imshow("Mixed", mixed);

    cv::subtract(Two, one, three);
    cv::imshow("Sub", three);
    cv::cvtColor(three, three, cv::COLOR_BGR2GRAY);
    cv::threshold(three, three, 30, 150, cv::THRESH_BINARY);

    cv::imshow("Bin", three);
    cv::waitKey(0);


    return 0;

}

void cut_chips(){
    cv::Mat fichas_juntas = cv::imread("../Projects/Images/Fichas/fichas_juntas.bmp");
    cv::Mat fichas;
    int x = 0, y = 0;
    for (int i = 0; i < 3; i++){
        fichas = fichas_juntas(cv::Rect(x, y, 500, 500));
        cv::imwrite(cv::format("../Projects/Images/Fichas/ficha%d.bmp", i+1), fichas);
        x = x + 540;
        cout << "Imagem " << i << endl;
        cv::imshow("Fichas", fichas);
        cv::waitKey(0);
    }
}

void kafka_perspective(){

    cv::Mat franz = cv::imread("../Projects/Images/Perspective/franz.jpg");
    cv::resize(franz, franz, cv::Size(365,650));
    ImagesProcessing perspective(franz);
    cv::Mat kafka;
    kafka = perspective.warp(46, 347, 167, 295, 226, 476, 346, 370, 200, 350);
    
    cv::imshow("Book", kafka);
    cv::waitKey(0);
}

void geometry_operations(){
        cv::Mat img = cv::imread("../Projects/Images/Processadas/folha.bmp");
    cv::Mat rotated, translated;

    //Obtendo a matriz de rotação:
    cv::Mat m_rotacao = cv::getRotationMatrix2D(cv::Point2f(img.size().width/2,
                                                img.size().height/2), -90, 1);

    //Obtendo a matriz de translação:
    cv::Mat m_translacao = (cv::Mat_<float>(2,3) << 1, 0, 100, 0, 1, 100);

    //Aplicando a matriz na imagem original e gerando a imagem rotacionada:
    cv::warpAffine(img, rotated, m_rotacao, cv::Size(img.cols, img.cols));
    cv::warpAffine(img, translated, m_translacao, cv::Size(img.cols, img.cols));

    cv::resize(img, img, cv::Size(0,0), 0.5, 0.5, cv::INTER_CUBIC);
    
    cv::imshow("Original", img);
    cv::imshow("Rotated", rotated);
    cv::imshow("Translated", translated);

    cv::waitKey(0);
}

int channels_segmentation(){

    cv::String path = "../Projects/Images/Processadas/clock.bmp";
    vector<cv::Mat> channels, channelsbgr;
    cv::Mat img = cv::imread(path), hue, saturation, value, vorta;
    cv::Vec3b valorPixel;
    int pixelhue, pixelblue;
    
    if (img.empty()){
        cerr << "Não possível carregar a imagem\n";
        return -1;
    }
    cv::resize(img, img, cv::Size(400, 300));
    cv::cvtColor(img, vorta, cv::COLOR_BGR2HSV);

    valorPixel = img.at<cv::Vec3b>(cv::Point(150,150));

    //segmentar canais hsv e bgr:
    cv::split(vorta, channels);
    cv::split(img, channelsbgr);

    hue = channels[0];
    saturation = channels[1];
    value = channels[2];
    
    hue = 0.55*hue;

    pixelhue = hue.at<uchar>(150,150);
    pixelblue = channelsbgr[0].at<uchar>(cv::Point(150,150));

    //combinar canais hsv novamente:
    cv::merge(channels, vorta);
    cv::cvtColor(vorta, vorta, cv::COLOR_HSV2BGR);


    cv::imshow("Original", img);
    cv::imshow("Hue", hue);
    cv::imshow("Saturation", saturation);
    cv::imshow("Value", value);
    cv::imshow("Modificada ", vorta);
    
    cout << valorPixel << endl;
    cout << pixelblue << endl;
    cout << pixelhue << endl;

    cv::waitKey(0);

    return 0;
}


int teste_class(){
    cv::String path = "../Projects/Images/Eneas/eneas.jpg";
    cv::String build = "../Projects/Images/Perspective/building.jpg";
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
    cv::imwrite("../Projects/Images/Eneas/eneas_resized.jpg", resized );
    
    cv::imshow("Nosso nome é Enéas negativo", neg);
    cv::imshow("Redimensionada: ", resized);
    cv::imshow("Swapped", swapped);
    cv::imshow("Faces detectadas", faces);
    cv::imshow("Contours", contours);
    cv::imshow("Nosso nome é Enéas", eneas);

    cv::waitKey();

    return 0;


}