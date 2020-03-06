#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

// Global variables of Lab.2
Mat src, src_gray; //���� �̹���, gray ��ȯ �̹���
Mat dst, detected_edges; //��� �̹���, edge �̹���
//int edgeThresh = 1; //�ʿ���� ����
int lowThreshold; //���� slicing ��ġ 
int const max_lowThreshold = 100; //slicing ����(����: 0~100)
int ratio = 3; //*lowThreshold = highThreshold
int kernel_size = 3; //aperture
char window_name[] = "(Lab 2) Interactive Canny Detector - �賭��";

void CannyThreshold(int, void*)
{
	// @function CannyThreshold // @brief Trackbar callback - Canny thresholds input with a ratio 1:3

	// Reduce noise with a kernel 3x3 @input, output, kernel size
	blur(src_gray, detected_edges, Size(3, 3));

	// Canny detector @input, output, �ּ� threshold1, �ִ� threshold2, aperture
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);

	// Using Canny's output as a mask, we display our result
	dst = Scalar::all(0); //fill zero matrix //������ ���
	src.copyTo(dst, detected_edges); // mask: detected_edges //��� ���� edge ����

	//show result about colorful edge detect
	imshow(window_name, dst);
}
int main()
{
	//***** ***** Lab.1 Simple Canny Edge Detector ***** *****//

	// Load an image
	src = imread("../image/colorful stock.jpg");
	resize(src, src, Size(640, 480));
	//namedWindow("Original image", CV_WINDOW_AUTOSIZE); 
	imshow("(Lab 1) Original image - �賭��", src); //show original image
	//imwrite("../result_image/5_sobel_Original.jpg", src);

	Mat gray, edge, draw; //gray �̹���, edge ��� �̹���, edge ����� gray�� �ٲ� �̹���
	cvtColor(src, gray, CV_BGR2GRAY); //���� �̹����� gray �̹����� �ٲ�
	Canny(gray, edge, 100, 200, 3); //@input, output, low threshold(linking), high threshold, aperture
	edge.convertTo(draw, CV_8U); //to convert gray scale 1ä�� unsigned char
	//namedWindow("image", CV_WINDOW_AUTOSIZE);
	imshow("(Lab 1) image Using canny edge detector - �賭��", draw);
	//imwrite("../result_image/5_sobel_canny edge.jpg", draw);



	//***** ***** Lab.2 Interactive Canny Detector ***** *****//

	// Create a matrix of the same type and size as src (for dst)
	dst.create(src.size(), src.type());

	// Convert the image to grayscale @input, output, BGR to GRAY
	cvtColor(src, src_gray, CV_BGR2GRAY);

	// Create a window
	namedWindow(window_name, CV_WINDOW_AUTOSIZE);
	// Create a Trackbar for user to enter threshold 
	// @Trackbar�̸�, Window�̸�, ���� slicing ��ġ, slicing ����, ������ �Լ�
	createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);

	// Show the image //thread
	CannyThreshold(0, 0);

	//***** ***** Lab.3 Sobel Edge ***** *****//

	// Sobel Filter @input, output, depth(����̹��� ��������,8��Ʈ:��������ü, dx, dy
	Mat sobelMag, sobelDir, sobelX, sobelY;

	Sobel(gray, sobelX, CV_8U, 1, 0); //x direction
	imshow("(Lab 3) Ix using sobel mask - �賭��", sobelX);
	imwrite("../result_image/5_sobel_Ix_using_sobel_mask.jpg", sobelX);

	Sobel(gray, sobelY, CV_8U, 0, 1); //y direction
	imshow("(Lab 3) Iy using sobel mask - �賭��", sobelY);
	imwrite("../result_image/5_sobel_Iy_using_sobel_mask.jpg", sobelY);

	//magnitude(sobelX, sobelY, sobelMag);
	sobelMag = abs(sobelX) + abs(sobelY); //magnitude
	imshow("(Lab 3) Magnitude - �賭��", sobelMag);
	imwrite("../result_image/5_sobel_Magnitude.jpg", sobelMag);

	sobelX.convertTo(sobelX, CV_32F); //phase ����� ���� float����ȯ
	sobelY.convertTo(sobelY, CV_32F);
	sobelMag.convertTo(sobelMag, CV_32F);

	//cartToPolar(sobelX, sobelY, sobelMag, sobelDir);
	phase(sobelX, sobelY, sobelDir); //@input x, input y, output angle
	imshow("(Lab 3) Direction - �賭��", sobelDir); //direction

	normalize(sobelDir, sobelDir, 0, 255, NORM_MINMAX);
	imwrite("../result_image/5_sobel_Direction.jpg", sobelDir);

	// Wait until user exit program by pressing a key
	waitKey(0);
	return 0;
}

