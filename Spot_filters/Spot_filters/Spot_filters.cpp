#include <iostream>
#include "Metric.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	if (argc != 3) {
		cout << "Not enough command line arguments" << endl;
		return -1;
	}
	
	//Metric
	Mat A, B, C; //Loading images
	A = imread(argv[1]);
	B = imread(argv[2]);
	if ((!A.data) || (!B.data)) {
		cout << "No image data" << endl;
		return -1;
	}

	resize(B, C, A.size()); //Resize picture B to size A
	try {
		float metric = ssim(A, C); //SSIM calculation
		cout << "SSIM = " << metric;
	}
	catch (const char* message) {
		cout << message;
	}


	/////////////////////////////////////////////////////////////
	char* filename = new char;
	cin >> filename;
	Mat image = imread(filename, IMREAD_COLOR);

	Mat resimg_gray1 = image.clone();
	resimg_gray1 = gray_scale(image);
	imshow("Display Window1", resimg_gray1);

	Mat resimg_gray2 = image.clone();
	cvtColor(resimg_gray2, resimg_gray2, COLOR_RGB2GRAY);
	imshow("Display Window2", resimg_gray2);
	delete filename;

	/////////////////////////////////////////////////////////////
	Mat resimg_br1 = image.clone();
	resimg_br1 = brightness_rgb(image);
	imshow("Display Window1", resimg_br1);

	Mat resimg_br2 = image.clone();
	resimg_br2 = brightness_hsv(image);
	imshow("Display Window2", resimg_br2);
	
	
	/////////////////////////////////////////////////////////////
	
	
	waitKey(0);
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
