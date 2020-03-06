//21611591 �賭��
#include <opencv2/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <stdlib.h> // srand �Լ� ����� ���ؼ�
#include <time.h> // time �Լ� ����� ���ؼ�
#include <string.h>

using namespace cv;
using namespace std;

void salt_pepper(cv::Mat image, int n) // �ұ�-���� ���� ÷�� �Լ�
{
	int i, j;
	srand((int)time(NULL));

	for (int k = 0; k < n; k++)

	{
		i = rand() % image.cols; // �̹����� ��ũ�� ������ ���� �� ����, x ��ǥ��
		j = rand() % image.rows; // �̹����� ��ũ�� ������ ���� �� ����, y ��ǥ��

		//cout << "at (" << j << ", " << i << "), add salt or pepper!" << endl; // �����ϰ� ������ �ȼ� ��ġ ���, (x, y)

		int salt_or_pepper = (rand() % 2) * 255; // �����ϰ� 0 �Ǵ� 255, 0�̸� ����, 255�� �ұ�

		if (image.type() == CV_8UC1) // �׷��̷��� �����̶��
		{
			image.at<uchar>(j, i) = salt_or_pepper; // �����ϰ� ���õ� �ȼ��� 0 �Ǵ� 255�� ���� 
		}
		else if (image.type() == CV_8UC3) // 3ä�� �÷� �����̶��
		{
			// �����ϰ� ���õ� �ȼ��� 0 �Ǵ� 255�� ����, ��� �Ǵ� �������� ����� ���� �� �÷� ä�ο� ������ ���� ��. (0, 0, 0) �Ǵ� (255, 255, 255)
			image.at<cv::Vec3b>(j, i)[0] = salt_or_pepper; // B ä��
			image.at<cv::Vec3b>(j, i)[1] = salt_or_pepper; // G ä��
			image.at<cv::Vec3b>(j, i)[2] = salt_or_pepper; // R ä��
		}
	}
}
Mat gaussian(cv::Mat Origin, cv::Mat dst, float sigma = 30.0) //��α׿��� 30.0�� �־���� defalut�� ������
{
	//---������ image ����---//
	Mat noise(Origin.size(), CV_32FC3); //����� ÷���� �̹��� ���� //3ä�� double
	float average = 0.0; //����� 0�̰�
	float std = sigma; //ǥ�� ������ sigma�̵��� ����

	//��� average, ǥ������ std�� ���Ժ����� ������ ���� ���� matrix ��ȯ
	randn(noise, Scalar::all(average), Scalar::all(std));
	imshow("(Lab3) Gaussian noise Image - �賭��", noise);
	//imwrite("../result_image/4_filtering_Gaussian_noise.jpg", noise);

	Mat3b imageF_8UC3;
	noise.convertTo(imageF_8UC3, CV_8UC3, 255);
	imwrite("../result_image/4_filtering_Gaussian_noise.jpg", imageF_8UC3);

	Origin.convertTo(dst, CV_32FC3); //������������ dst image�� ����ȯ ���� //copyTo�� ���� ���� ����.
	addWeighted(dst, 1.0, noise, 1.0, .0, dst); //dst(������ ����) = dst * 1.0 + noise * 1.0 + .0 
	dst.convertTo(dst, Origin.type()); //�ռ� �Ŀ� dst �ڷ����� �ٽ� ���� ������ ���� ����

	return dst; //��� image return
}
int main(int argc, char** argv)
{
	/********** 1. OpenCV-Blur **********/

	//Load an image from file
	Mat src = imread("../image/Lena.jpg");

	//show the loaded image
	imshow("(Lab1) Original Image - �賭��", src);

	//����� ������ Mat ��ü ����
	Mat dst;
	char zBuffer[35];

	for (int i = 1; i < 31; i = i + 2)
	{
		//copy the text to the "zBuffer"
		_snprintf_s(zBuffer, 35, "Kernel Size : %d x %d", i, i);

		//smooth the image in the "src" and save it to "dst"
		blur(src, dst, Size(i, i), cv::Point(-1, -1), BORDER_REPLICATE); //Point(-1,-1): kernel center

		//put the text in the "zBuffer" to the "dst" image
		//������ �Բ� ���ڸ� ����, �� ������ �°� ��ġ�� ������ ��������
		putText(dst, zBuffer, Point(src.cols / 4, src.rows / 8), CV_FONT_HERSHEY_COMPLEX, 0.9, Scalar(255, 255, 255)
		);

		//show the blurred image with the text
		imshow("(Lab1) Smoothed Image - �賭��", dst);
		imwrite("../result_image/4_filtering_smoothed_" + to_string(i) + ".jpg", dst);

		//wait for 2 seconds
		int c = waitKey(20);

		//if the "esc" key is pressed during the wait, return
		if (c == 27)
		{
			return 0;
		}
	}
	//make the "dst" image, black
	dst = Mat::zeros(src.size(), src.type());

	//copy the text to the "zBuffer"
	_snprintf_s(zBuffer, 35, "Press Any Key to Exit");

	//������ ��ġ�� ����Ű�� ���� �����ص� �ȴٴ� ���ڸ� ����
	//put the text in the "zBuffer" to the "dst" image
	putText(dst, zBuffer, Point(src.cols / 6, src.rows / 2), CV_FONT_HERSHEY_COMPLEX, 0.9, Scalar(255, 255, 255));

	//show the black image with the text
	imshow("(Lab1) Smoothed Image - �賭��", dst);

	//wait for a key press infinitely
	//waitKey(0);

	/********** 2. Median Filter **********/

	//Mat src = imread("myimg.jpg");	//Load an image from file	
	imshow("(Lab2) Original Image - �賭��", src);	//Show the Original image

	//---Noise ÷��---//	
	Mat spn_img;		//salt and pepper noise�� ���� Mat �̹��� ��ü ������	
	src.copyTo(spn_img);		//���� �̹����� ������ ������ ������ �� ���� noise�� ����� ����

	salt_pepper(spn_img, 5000);		//���� image�� 5000���� �ұ� �Ǵ� ���߸� �Ѹ�
	imshow("(Lab2) (salt and pepper) Noise Added Image - �賭��", spn_img);  //Show salt and pepper noise image
	imwrite("../result_image/4_filtering_salt&pepper_Noise_Added.jpg", spn_img);

	//---Filtering---//
	Mat MedianF_img; //noise ���󿡼� median filter�� ������ ����� ������ ��ü ����
	Mat GaussianF_img; //noise ���󿡼� gaussian filter�� ������ ����� ������ ��ü ����

	//char zBuffer[35]; //image�� ���ڸ� ��� buffer ����

	for (int i = 1; i <= 9; i += 2) //kernel size ��ȭ //kernel size�� Ȧ���� �� �� ����
	{
		medianBlur(spn_img, MedianF_img, i); //median filter�� ����, kernel size
		GaussianBlur(spn_img, GaussianF_img, Size(i, i), 0); //gaussian filter�� ����, kernel size, sigma 0�̸� kernel size�� ���� �ڵ� ���

		_snprintf_s(zBuffer, 35, "Kernel Size : %d x %d", i, i); // kernel size�� ���� �ٸ��� ���ڸ� ǥ����
		//������ �Բ� ���ڸ� ����, �� ������ �°� ��ġ�� ������ ��������
		putText(MedianF_img, zBuffer, Point(src.cols / 4, src.rows / 8), CV_FONT_HERSHEY_COMPLEX, 0.9, Scalar(255, 255, 255));
		putText(GaussianF_img, zBuffer, Point(src.cols / 4, src.rows / 8), CV_FONT_HERSHEY_COMPLEX, 0.9, Scalar(255, 255, 255));

		imshow("(Lab2) Median filtered Image - �賭��", MedianF_img); //median filter�� ���� �̹����� ������
		imshow("(Lab2) Gaussian filtered Image - �賭��", GaussianF_img); //gaussian filter�� ���� �̹����� ������
		imwrite("../result_image/4_filtering_salt&pepperNoise_Median_filtered_kernel_size_" + to_string(i) + ".jpg", MedianF_img);
		imwrite("../result_image/4_filtering_salt&pepperNoise_Gaussian_filtered_kernel_size_" + to_string(i) + ".jpg", GaussianF_img);

		//wait for 2 seconds
		int c = waitKey(20);
	}
	for (int i = 1; i <= 5; i += 2) //sigma ��ȭ //sigma�� Ȧ���� ����
	{
		GaussianBlur(spn_img, GaussianF_img, Size(5, 5), i, i); //gaussian filter�� ����, kernel size, sigma

		_snprintf_s(zBuffer, 35, "Sigma : %d", i); // Sigma�� ���� �ٸ��� ���ڸ� ǥ����
		//������ �Բ� ���ڸ� ����, �� ������ �°� ��ġ�� ������ ��������
		putText(GaussianF_img, zBuffer, Point(src.cols / 4, src.rows / 8), CV_FONT_HERSHEY_COMPLEX, 0.9, Scalar(255, 255, 255));

		imshow("(Lab2) Gaussian filtered Image - �賭��", GaussianF_img); //gaussian filter�� ���� �̹����� ������
		imwrite("../result_image/4_filtering_salt&pepperNoise_Gaussian_filtered_sigma_" + to_string(i) + ".jpg", GaussianF_img);

		//wait for 2 seconds
		int c = waitKey(20);
	}

	/********** 3. Gaussian Filter **********/
	//Mat src = imread("myimg.jpg");	//Load an image from file	
	imshow("(Lab3) Original Image - �賭��", src);	//Show the Original image

	//---Noise ÷��---//	
	Mat gn_img;		//gaussian noise�� ���� Mat �̹��� ��ü ������	

	gn_img = gaussian(src, gn_img, 20); //����þ� ������ ÷�� //sigma = 20
	imshow("(Lab3) (gaussian) Noise Added Image - �賭��", gn_img);  //Show salt and pepper noise image
	imwrite("../result_image/4_filtering_gaussian_Noise_Added.jpg", gn_img);

	//---Filtering---//
	//Mat MedianF_img; //noise ���󿡼� median filter�� ������ ����� ������ ��ü ����
	//Mat GaussianF_img; //noise ���󿡼� gaussian filter�� ������ ����� ������ ��ü ����

	//char zBuffer[35]; //image�� ���ڸ� ��� buffer ����

	for (int i = 1; i <= 9; i += 2) //kernel size ��ȭ //kernel size�� Ȧ���� �� �� ����
	{
		medianBlur(gn_img, MedianF_img, i); //median filter�� ����, kernel size
		GaussianBlur(gn_img, GaussianF_img, Size(i, i), 0); //gaussian filter�� ����, kernel size, sigma 0�̸� kernel size�� ���� �ڵ� ���

		_snprintf_s(zBuffer, 35, "Kernel Size : %d x %d", i, i); // kernel size�� ���� �ٸ��� ���ڸ� ǥ����
		//������ �Բ� ���ڸ� ����, �� ������ �°� ��ġ�� ������ ��������
		putText(MedianF_img, zBuffer, Point(src.cols / 4, src.rows / 8), CV_FONT_HERSHEY_COMPLEX, 0.9, Scalar(255, 255, 255));
		putText(GaussianF_img, zBuffer, Point(src.cols / 4, src.rows / 8), CV_FONT_HERSHEY_COMPLEX, 0.9, Scalar(255, 255, 255));

		imshow("(Lab3) Median filtered Image - �賭��", MedianF_img); //median filter�� ���� �̹����� ������
		imshow("(Lab3) Gaussian filtered Image - �賭��", GaussianF_img); //gaussian filter�� ���� �̹����� ������
		imwrite("../result_image/4_filtering_gaussianNoise_Median_filtered_kernel_size_" + to_string(i) + ".jpg", MedianF_img);
		imwrite("../result_image/4_filtering_gaussianNoise_Gaussian_filtered_kernel_size_" + to_string(i) + ".jpg", GaussianF_img);

		//wait for 2 seconds
		int c = waitKey(20);
	}
	for (int i = 1; i <= 5; i += 2) //sigma ��ȭ //sigma�� Ȧ���� ����
	{
		GaussianBlur(gn_img, GaussianF_img, Size(5, 5), i, i); //gaussian filter�� ����, kernel size, sigma

		_snprintf_s(zBuffer, 35, "Sigma : %d", i); // Sigma�� ���� �ٸ��� ���ڸ� ǥ����
		//������ �Բ� ���ڸ� ����, �� ������ �°� ��ġ�� ������ ��������
		putText(GaussianF_img, zBuffer, Point(src.cols / 4, src.rows / 8), CV_FONT_HERSHEY_COMPLEX, 0.9, Scalar(255, 255, 255));

		imshow("(Lab3) Gaussian filtered Image - �賭��", GaussianF_img); //gaussian filter�� ���� �̹����� ������
		imwrite("../result_image/4_filtering_gaussianNoise_Gaussian_filtered_sigma_" + to_string(i) + ".jpg", GaussianF_img);

		//wait for 2 seconds
		int c = waitKey(20);
	}

	//�����δ� kernel size�� 5x5�̰� sigma�� kernel size�� 1/6�� ������ �ϴµ�, ������ �����Ƿ� 100�� ũ���Ͽ� ������
	Mat kernelX = getGaussianKernel(600, 100); //kernel size, sigma, kernel type�� �־��� --> ����þ� coefficient�� ����
	Mat kernelY = getGaussianKernel(600, 100);
	Mat GaussianK = kernelX * kernelY.t(); //x��� y���� ���ļ� �ϳ��� ������ kernel�� ������� //���ļ��� ���� ���ϱ�

	normalize(GaussianK, GaussianK, 0, 0.8, NORM_MINMAX); //src, dst, alpha, beta, nomalize //  nomalize ���ָ� ����þ� ������ �������� ��
	imshow("(Lab3) Gaussian Kernel Image - �賭��", GaussianK); //����þ� Ŀ���� imshow��

	normalize(GaussianK, GaussianK, 0, 255, NORM_MINMAX);
	/*
	`�� normalize �ؼ� write ���ִ°�?`
	normalize�� ������ ���� ��� ������ ȭ������ imwrite ��.

	<imwrite documentation>
	https://docs.opencv.org/2.4/modules/highgui/doc/reading_and_writing_images_and_video.html?highlight=imwrite#imwrite
	The function imwrite saves the image to the specified file. 
	The image format is chosen based on the filename extension (see imread() for the list of extensions). 
	Only 8-bit (or 16-bit unsigned (CV_16U) in case of PNG, JPEG 2000, and TIFF)
	single-channel or 3-channel (with ��BGR�� channel order) images can be saved using this function. 
	If the format, depth or channel order is different, 
	use Mat::convertTo() , and cvtColor() to convert it before saving.
	
	`imshow�� �� �Ǵ°�?`
	<imshow>
	If the image is 8-bit unsigned, it is displayed as is.
	If the image is 16-bit unsigned or 32-bit integer, the pixels are divided by 256. That is, the value range [0,255*256] is mapped to [0,255].
	If the image is 32-bit floating-point, the pixel values are multiplied by 255. That is, the value range [0,1] is mapped to [0,255].
	*/
	imwrite("../result_image/4_filtering_Gaussian_Kernel_example.jpg", GaussianK);

	waitKey(0);

	return 0;
}