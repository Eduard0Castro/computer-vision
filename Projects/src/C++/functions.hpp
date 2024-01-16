#include <iostream>
#include "ImagesProcessing.hpp"
#include <opencv2/opencv.hpp>

using namespace std;

cv::Moments Hu(cv::Mat src){
    cv::Mat hu;
    cv::Moments moments_;
    moments_ = cv::moments(src, true);

    cv::HuMoments(moments_, hu);

    cout << hu << endl;
    cout << endl;

    return moments_;

}

/*================================================================================================*/
/*======================================Funções main.cpp==========================================*/


void vertices (){

    cv::Mat square = cv::imread("../Projects/Images/Extração/square.jpeg", 0);
    cv::Mat triangle = cv::imread("../Projects/Images/Extração/triangle.jpeg", 0);
    cv::Mat image;
    vector<vector<cv::Point>> contours;
    vector <cv::Point> vertices;
    int tot_vertices;
    double perimetro = 0;

    image = triangle;
    
    cv::threshold(image, image, 127, 255, cv::THRESH_BINARY);
    cv::findContours(image, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    perimetro = cv::arcLength(contours[0], true);

    // O epsilon indica a precisão da aproiximação da curva original a um polígono
    cv::approxPolyDP(contours[0], vertices, 0.1*perimetro, true);

    //O total de vértice é contabilizado através do tamanho do vetor gerado pela approxPoly
    tot_vertices = vertices.size();

    cout << tot_vertices << endl;
    cv::imshow("Square", image);
    
    cv::waitKey();
}

void drawForms(){

    cv::Mat puzzle = cv::imread("../Projects/Images/Extração/puzzle.bmp");
    cv::Mat gray, binary, copy = puzzle.clone(), copy_ellipse = puzzle.clone();
    vector<vector<cv::Point>> contours;
    cv::Rect retan;
    cv::Point2f center;
    float radius;
    cv::RotatedRect ellipse;

    cv::cvtColor(puzzle, gray, cv::COLOR_BGR2GRAY);
    cv::threshold(gray, binary, 127, 255, cv::THRESH_BINARY);


    //Retângulo envolvente:
    cv::findContours(binary, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    retan = cv::boundingRect(contours[0]);
    cv::rectangle(puzzle, retan, cv::Scalar(0,255,0), 1);
    cv::imshow("Puzzle Rect", puzzle);


    //Círculo envolvente:
    cv::minEnclosingCircle(contours[0], center, radius );
    cv::circle(copy, center, radius, cv::Scalar(0,255,0), 1);
    cv::imshow("Puzzle circle", copy);


    //Elipse envolvente:
    ellipse = cv::fitEllipse(contours[0]);
    cv::ellipse(copy_ellipse, ellipse, cv::Scalar(0, 255, 0), 1);
    cv::imshow("Puzzle ellipse", copy_ellipse);

    cv::waitKey();
}
void formats(){

    cv::Mat square = cv::imread("../Projects/Images/Extração/square.jpeg");
    cv::Mat triangle = cv::imread("../Projects/Images/Extração/triangle.jpeg");
    cv::Mat circle = cv::imread("../Projects/Images/Extração/circle.jpeg");
    cv::Mat canny, binary_t, gray, image;
    vector<vector<cv::Point>> contours;
    double area = 0, perimetro = 0;

    image = circle;

    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    cv::threshold(gray, binary_t, 127, 255, cv::THRESH_BINARY);

    /*Os melhores valores para canny, foram com as imagens em binário, porém
    para o caso do triângulo, os contornos não se fecharam, o que prejudicou o calculo 
    do perímetro e da área da primeira forma. Isso se resolveria colocando como input a 
    imagem em escala de cinza, porém os valores das outras formas erram por grandes margens.*/
    cv::Canny(binary_t, canny, 200, 250);

    //Primeira forma para encontrar área e perímetro:
    cv::findContours(canny, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    area = cv::contourArea(contours[0]);
    perimetro = cv::arcLength(contours[0], true);

    cout << "Área: " << area << endl;
    cout << "Perímetro: " << perimetro << endl;


    //Segunda forma para encontrar área e perímetro:
    area = 0;
    perimetro = 0;
    for (int x = 0; x < image.cols; x++){
        for(int y = 0; y < image.rows; y++){
            if(binary_t.at<uchar>(x, y) == 255)
                area += 1;

            if (canny.at<uchar>(x,y) == 255)
                perimetro += 1;
        }
    }

    cout << "\nContagem área: " << area << endl;
    cout << "Contagem perímetro: " << perimetro << endl;
}

void chips_segmentation(){

    cv::Mat chip1 = cv::imread("../Projects/Images/Segmentação/cap_ficha1.jpeg");
    cv::Mat chip2 = cv::imread("../Projects/Images/Segmentação/cap_ficha2.jpeg");
    cv::Mat sub, mask, end;

    cv::Vec3b min (0,120,120);
    cv::Vec3b max (180,255,255);

    /*Segmentação por movimento (subtract) e depois por cor para identificar a última
    posição da ficha, que é a única que aparece em vermelho pela operação da subtração.
    A função "inRange" pega os valores máximos e mínimos de espaço HSV da imagem subtraí-
    da e transforma em máscara só com os pixels que estão entre os valores apontados */
    cv::subtract(chip2, chip1, sub);
    cv::imshow("Sub", sub);
    cv::cvtColor(sub, sub, cv::COLOR_BGR2HSV);
    cv::inRange(sub, min, max, mask);
    cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, 
                     cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(10,10)));

    cv::imshow("Mask", mask);

    cv::waitKey();

}

void canny_coffee_segmentation(){

    //Segmentação por bordas:
    cv::Mat coffee = cv::imread("../Projects/Images/Segmentação/coffee.jpeg");
    cv::Mat gray, binary, canny;

    cv::Mat elementoEstruturante = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3));

    /*Passos: 1- Passar para escala de cinza
              2- Operação de fechamento para corrigir falhas internas da binarização
              3- Aplicar Canny para segmentar a imagem binária pelas bordas*/
    cv::cvtColor(coffee, gray, cv::COLOR_BGR2GRAY);
    cv::threshold(gray, binary, 135, 255, cv::THRESH_BINARY_INV);
    cv::morphologyEx(binary, binary, cv::MORPH_CLOSE, elementoEstruturante);
    cv::Canny(binary, canny, 100, 200);
    
    cv::imshow("Coffee", coffee);
    cv::imshow("Binary", binary);
    cv::imshow("Canny", canny);

    cv::waitKey();
}

void stream_segmentation(){

    cv::VideoCapture cap(0);
    cv::Mat cam, img_hsv, mask;
    int mat_min = 87, mat_max = 146, 
        sat_min = 147, sat_max = 255, 
        brilho_min = 95, brilho_max = 255;

    cv::namedWindow("Barra de seleção", cv::WINDOW_AUTOSIZE);

    cv::createTrackbar("Mat min", "Barra de seleção", &mat_min, 255);
    cv::createTrackbar("Mat  max", "Barra de seleção", &mat_max, 255);

    cv::createTrackbar("Sat min", "Barra de seleção", &sat_min, 255);
    cv::createTrackbar("Sat max", "Barra de seleção", &sat_max, 255);

    cv::createTrackbar("Brilho min", "Barra de seleção", &brilho_min, 255);
    cv::createTrackbar("Brilho max", "Barra de seleção", &brilho_max, 255);

    while(true){

        cap.read(cam);
        
        cv::flip(cam, cam, 1);
        cv::cvtColor(cam, img_hsv, cv::COLOR_BGR2HSV);

        cv::Scalar min (mat_min, sat_min, brilho_min);
        cv::Scalar max (mat_max, sat_max, brilho_max);  

        cv::inRange(img_hsv, min, max, mask);
        cv::morphologyEx(mask, mask, cv::MORPH_CLOSE,
                         cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5,5)));

        cv::imshow("Cam", cam);
        cv::imshow("Mascara", mask);

        if (cv::waitKey(1) >= 0) break;

    }
    exit(0);
}

void otsu(){

    /*O algoritmo de Nobuyuki Otsu calcula o threshold de acordo com a imagem 
    carregada (baseado no histograma da imagem). Dessa forma, pode-se binarizar
    a imagem de uma forma um tanto quanto mais precisa do que simplesmente 
    testar o valores com a binarização comum.*/

    cv::Mat coffee = cv::imread("../Projects/Images/Segmentação/coffee.jpeg");
    cv::Mat gray, binary, binary_otsu;
    double otsu; 

    cv::cvtColor(coffee, gray, cv::COLOR_BGR2GRAY);
    cv::threshold(gray, binary, 135, 255, cv::THRESH_BINARY_INV);
    otsu = cv::threshold(gray, binary_otsu, 0, 255, (cv::THRESH_BINARY_INV + cv::THRESH_OTSU));

    cv::imshow("Coffee", coffee);
    cv::imshow("Binary", binary);
    cv::imshow("Otsu Binary", binary_otsu);

    cout << "Threshold by Otsu algorithm: " << otsu << endl;

    cv::waitKey();

}

void adaptativa(){

    /*Quando a iluminação na imagem não é uniforme, pode-se utilizar a chamada
    binarização adaptativa para oferecer um processo de binarização sem perdas
    significativas para a imagem. 
    O problema desse processo é que nem sempre ele representa o preenchimento da
    imagem da forma correta, sendo mais útil para imagens com números e letras
    como o exemplo do sudoku: */

    cv::Mat pills = cv::imread("../Projects/Images/Segmentação/pills.jpeg");
    cv::Mat sudoku = cv::imread("../Projects/Images/Segmentação/sudoku.jpeg");
    cv::Mat median, binary, sudoku_perspective, binary_sudoku, gray_sudoku;
    ImagesProcessing pers(sudoku);


    //Binary pills

    cv::imshow("Pills", pills);

    //Binarização global:
    cv::threshold(pills, binary, 70, 255, cv::THRESH_BINARY);
    cv::morphologyEx(binary, binary, cv::MORPH_ELLIPSE, 
                     cv::getStructuringElement(cv::MORPH_OPEN, cv::Size(3,3)));
    cv::imshow("Global Binary Pills", binary);

    //Binarização adaptativa:
    cv::cvtColor(pills, pills, cv::COLOR_BGR2GRAY);
    cv::medianBlur(pills, median, 7);
    cv::adaptiveThreshold(median, binary, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, 
                          cv::THRESH_BINARY_INV, 11, 5);
    cv::imshow("Binary", binary);


    //Binary sudoku:

    sudoku_perspective = pers.warp(55, 99, 337, 99, 55, 395, 337, 392, 282, 292);

    cv::imshow("Sudoku perspective", sudoku_perspective);


    //Binarização global:
    cv::threshold(sudoku_perspective, binary_sudoku, 125, 255, cv::THRESH_BINARY_INV);
    cv::imshow("Global Binary Sudoku", binary_sudoku);

    //Binarização adaptiva:
    cv::cvtColor(sudoku_perspective, gray_sudoku, cv::COLOR_BGR2GRAY);
    cv::adaptiveThreshold(gray_sudoku, binary_sudoku, 255,
                          cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY_INV, 11, 10);
    cv::imshow("Adaptative binary", binary_sudoku);


    cv::waitKey();

}

void coffee_segmentation(){

    cv::Mat coffee = cv::imread("../Projects/Images/Segmentação/coffee.jpeg");
    cv::Mat c_gray = cv::imread("../Projects/Images/Segmentação/gray_coffee.bmp");
    cv::Mat gray, binary, elementoEstruturante;

    cv::cvtColor(coffee, gray, cv::COLOR_BGR2GRAY);

    elementoEstruturante = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3));

    cv::threshold(gray, binary, 135, 255, cv::THRESH_BINARY_INV);
    cv::imshow("First Binary", binary);
    cv::morphologyEx(binary, binary, cv::MORPH_CLOSE, 
                     elementoEstruturante, cv::Point(-1,-1), 1);
    cv::erode(binary, binary, elementoEstruturante, cv::Point(-1,-1), 1);

    cv::imshow("Coffee", coffee);
    cv::imshow("Binary coffee", binary);

    cv::waitKey(0);
}

void andromeda(){

    cv::Mat andromeda = cv::imread("../Projects/Images/Morfologia/andromeda.bmp");
    cv::Mat elementoEstruturante, top_hat;

    //Top Hat aplicada a elementos estruturantes menores pode suprimir grande regiões
    elementoEstruturante = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5,5));
    cv::morphologyEx(andromeda, top_hat, cv::MORPH_TOPHAT, elementoEstruturante);

    cv::imshow("Andromeda", andromeda);
    cv::imshow("Sem andromeda", top_hat);

    cv::waitKey(0);

}

void rice(){

    /*As operações de abertura e fechamento em imagens em tons de cinza são
    utilizadas para uniformizar a iluminação na imagem. 
    Abertura: tende a suprimir pequenas regiões brilhantes
    Fechamento: tende a suprimir pequenas regiões escuras */
    cv::Mat arroz = cv::imread("../Projects/Images/Morfologia/arroz.bmp");
    cv::Mat open, subt, added, top_hat, added_th;


    cv::morphologyEx(arroz, open, cv::MORPH_OPEN, 
                     cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(100,100)));
    cv::subtract(arroz, open, subt);
    cv::add(subt, subt, added);

    /*A operação Top Hat executa a abertura e a subtração de uma vez: */
    cv::morphologyEx(arroz, top_hat, cv::MORPH_TOPHAT,
                     cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(100,100)));
    cv::add(top_hat, top_hat, added_th);

    cv::imshow("Arroz", arroz);
    cv::imshow("Abertura", open);
    cv::imshow("Subtraída", subt);
    cv::imshow("Adicionada", added);
    cv::imshow("Top Hat", top_hat);
    cv::imshow("Adicionada Top Hat", added_th);

    cv::waitKey(0);

}

void bearing_morphology(){

    /*Elemento estruturante é a matriz que é formada sendo seu pixel central 
    sobreposto em todos os pixels para determinar se ele vai ou não para a imagem
    final dependendo da operação realizada.
    
    Erosão: todos os pixels da vizinhança do pixel-alvo devem coincidir 
            com o os do elemento estruturante para que aquele esteja na imagem
            final.
    Dilatação: ao menos um pixel da vinhança do pixel-alvo ou ele mesmo deve coindir
               com um pixel do elemento estruturante para estar na imagem final*/

    cv::Mat rolamento = cv::imread("../Projects/Images/Morfologia/rolamento.bmp");
    cv::Mat rolamento_ruido = cv::imread("../Projects/Images/Morfologia/rolamento_ruido.bmp");
    cv::Mat ruido_interno = cv::imread("../Projects/Images/Morfologia/ruido_interno.bmp");
    cv::Mat eroded, dilated, abertura, fechamento, gradient;

    cv::erode(rolamento, eroded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5,5)), 
              cv::Point(-1, -1), 2);
    cv::dilate(rolamento, dilated, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5,5)), 
              cv::Point(-1, -1), 2); 

    /*
      Abertura: erosão -> dilatação: tratar ruídos

      Fechamento: dilatação -> erosão: corrigir danos da binarização

      Gradiente: diferença entre erosão e dilatação; representa os
      contornos do objeto de interesse
    */
    cv::morphologyEx(rolamento_ruido, abertura, cv::MORPH_OPEN, 
                     cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3,3)));
    cv::morphologyEx(ruido_interno, fechamento, cv::MORPH_CLOSE, 
                     cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5,5)));
    cv::morphologyEx(rolamento, gradient, cv::MORPH_GRADIENT,
                     cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3,3)));



    cv::imshow("Original", rolamento);
    cv::imshow("Eroded", eroded);
    cv::imshow("Dilated", dilated);
    cv::imshow("Rolamento Ruido", rolamento_ruido);
    cv::imshow("Rolamento abertura", abertura);
    cv::imshow("Ruido interno", ruido_interno);
    cv::imshow("Fechamento", fechamento);
    cv::imshow("Gradient", gradient);

    cv::waitKey(0);

}

void binary_plate(){
    
    /*Para binarizar um imagem com OpenCV, utilizar-se-á o método "threshold"
    que necessita de uma imagem em escala de cinza e seus parâmetros envolvem
    a imagem base, o destino, o threshold (limiar que separa o será preto e o que 
    será branco dependendo do tipo de thresholding do último parâmetro), valor máximo 
    de representação (branco - 255), THRESH_BINARY: os pixels abaixo do valor apontado 
    serão representados em preto (0) e os acima ou iguais, seguindo o maxValue. 
    O INV é o inverso*/
    cv::Mat plate = cv::imread("../Projects/Images/Morfologia/plate.bmp");
    cv::Mat gray_plate, binary_plate;

    cv::cvtColor(plate, gray_plate, cv::COLOR_BGR2GRAY);
    cv::threshold(gray_plate, binary_plate, 60, 255, cv::THRESH_BINARY_INV);

    cv::imshow("Gray Plate", gray_plate);
    cv::imshow("Binary plate", binary_plate);

    cv::waitKey(0);


}

void bone(){

    cv::Mat bone = cv::imread("../Projects/Images/Filtros/bone.bmp");
    cv::Mat gaussian, detalhada, Final;

    /*O procedimento é usar um filtro passa-baixa para gerar um imagem suavizada
    para depois subtraí-la da imagem original afim de gerar uma imagem só com
    as altas frequência para então somar esta com a original para aguçar as in-
    formações de alta frequência*/

    cv::GaussianBlur(bone, gaussian, cv::Size(13,13), 3);
    cv::subtract(bone, gaussian, detalhada);
    detalhada = 3*detalhada;
    cv::add(bone, detalhada, Final);

    cv::imshow("Bone", bone);
    cv::imshow("Gaussiana", gaussian);
    cv::imshow("Bordas", detalhada);
    cv::imshow("Final", Final);

    cv::waitKey(0);
}

void agucar_bordas(){

    /*Aqui é feita a subtração da imagem original com a imagem gerada pela
    função laplacian. A função 'subtract' consegue realizar essa operação
    tratando automaticamente os pixels que ficam com valores negativos.
    Essa operação é realizada para aguçar as bordas de uma imagem*/

    cv::Mat moon = cv::imread("../Projects/Images/Filtros/moon.bmp");
    cv::Mat laplacian, subtracted;

    cv::Laplacian(moon, laplacian, CV_8U);
    cv::subtract(moon, laplacian, subtracted);

    cv::imshow("Moon original", moon);
    cv::imshow("Laplacian Moon", laplacian);
    cv::imshow("Subtracted", subtracted);

    cv::waitKey(0);

}

void operators(){

    /*Os operadores de Sobel e Laplaciano são usados para realçar bordas e contornos,
    sendo que o Laplaciano consegue um desempenho superior ao de Sobel, mas ainda é muito
    sensível a ruídos. Para melhorar essa questão, utiliza-se um filtro gaussiano 
    antes de aplicar o operador*/

    cv::Mat parking = cv::imread("../Projects/Images/Filtros/parking1.bmp");
    cv::Mat bilateral, SobelX, SobelY, laplacian, laplacian_r;


    /*O filtro bileteral é um filtro não linear, mas que comporta-se como um gaussiano,
    suavizando a imagem, mas preservando os contornos*/
    cv::bilateralFilter(parking, bilateral, 10, 75, 75);
    cv::Sobel(parking, SobelX, CV_8U, 1, 0, 3);
    cv::Sobel(parking, SobelY, CV_8U, 0, 1, 3);

    cv::Laplacian(parking, laplacian_r, CV_8U);
    cv::Laplacian(bilateral, laplacian, CV_8U);

    cv::imshow("Parking original", parking);
    cv::imshow("Parking bilateral", bilateral);
    cv::imshow("Sobel X", SobelX);
    cv::imshow("Sobel Y", SobelY);
    cv::imshow("Laplacian com ruido", laplacian_r);
    cv::imshow("Laplacian", laplacian);

    cv::waitKey(0);
}

void filters(){

    cv::Mat img = cv::imread("../Projects/Images/Filtros/fifty_cut.bmp");
    cv::Mat radio = cv::imread("../Projects/Images/Filtros/radiotividade.bmp");
    cv::Mat woman = cv::imread("../Projects/Images/Filtros/woman.bmp");
    cv::Mat SaltPepper = cv::imread("../Projects/Images/Filtros/SaltPepper.bmp");
    cv::Mat parking = cv::imread("../Projects/Images/Filtros/parking1.bmp");
    cv::Mat average, gaussian, median_blur, bilateral;


    cv::imshow("Fifty", img);

    //Filtro de média: passa-baixa; para suavizar a imagem
    cv::blur(img, average, cv::Size(5,5));
    cv::imshow("Average", average);


    //Filtro gaussiano: passa-baixa, suavizar, mas com um parâmetro a mais, o sigma
    cv::GaussianBlur(img, gaussian,  cv::Size(5,5), 0);//sigma é o grau de suavização desejado
    cv::imshow("Gaussian", gaussian);

    cv::imshow("Original", radio);
    

    //Testando filtro gaussiano com diferentes valores de tamanho e sigma:

    //É recomendado que a mascara seja uma matriz quadrada 
    //com numero impar de linhas e colunas
    cv::GaussianBlur(radio, gaussian, cv::Size(21,21), 4);
    cv::imshow("Gaussian 1", gaussian);

    cv::GaussianBlur(radio, gaussian, cv::Size(41, 41), 8);
    cv::imshow("Gaussian 2", gaussian);


    cv::imshow("Woman Original", woman);
    cv::GaussianBlur(woman, gaussian, cv::Size(3,3), 5);
    cv::imshow("Gaussian Woman", gaussian);


    /*Filtro de Mediana: passa-alta, não linear, útil no tratamento de ruídos do 
    tipo sal e pimenta e preserva bordas e contornos
    Quando executado com valor de intensidade (último parâmetro de 'medianBlur')
    muito alto, pode deformar os contornos*/
    cv::imshow("SaltPepper Original", SaltPepper);
    cv::medianBlur(SaltPepper, median_blur, 5);
    cv::imshow("Filtro de Mediana", median_blur);


    /*Filtro bilateral: passa-alta, não linear, comporta-se como um gaussiano,
    mas preservando as bordas e os contornos. É o mais utilizado para tanto
    Parâmetros inteiros: 10 é o tamanho do filtro (não recomendado ser maior
    que 5 em imagens captadas em tempo real)*/ 
    cv::imshow("Parking original", parking);
    cv::bilateralFilter(parking, bilateral, 10, 75, 75);
    cv::imshow("Bilateral Filter", bilateral);

    cv::waitKey(0);
}

void add_sub_mix(){

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

    //Aplicando as matrizes na imagem original e gerando as imagens:
    cv::warpAffine(img, rotated, m_rotacao, cv::Size(img.cols, img.cols));
    cv::warpAffine(img, translated, m_translacao, cv::Size(img.cols, img.cols));

    cv::resize(img, img, cv::Size(0,0), 0.5, 0.5, cv::INTER_CUBIC);
    
    cv::imshow("Original resized", img);
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
