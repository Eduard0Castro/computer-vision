#include "ImagesProcessing.hpp"

int main(){

    cv::Mat andromeda = cv::imread("../Projects/Images/Morfologia/andromeda.bmp");
    cv::Mat elementoEstruturante, top_hat;

    //Top Hat aplicada a elementos estruturantes menores pode suprimir grande regiões
    elementoEstruturante = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5,5));
    cv::morphologyEx(andromeda, top_hat, cv::MORPH_TOPHAT, elementoEstruturante);

    cv::imshow("Andromeda", andromeda);
    cv::imshow("Sem andromeda", top_hat);

    cv::waitKey(0);

    return 0;

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

    //Aplicando a matriz na imagem original e gerando a imagem rotacionada:
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