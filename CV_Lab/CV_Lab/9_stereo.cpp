//11���� //0521 //stereo
#include <stdio.h>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/calib3d/calib3d.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	//load stereo images -> ���� 2��
	Mat L = imread("../image/scene1.row3.col1.ppm"); // left  ����
	Mat R = imread("../image/scene1.row3.col2.ppm"); // right ����
	imshow("Left Image", L);
	imshow("Right Image", R);
	imwrite("../result_image/9_stereo_Left.jpg", L);
	imwrite("../result_image/9_stereo_Right.jpg", R);


	// set block matching parameters // �Ķ���� ����
	CvStereoBMState *BMState = cvCreateStereoBMState(); // Ŭ������ �̿��� ��ü ���� -> �Լ��� �ּ� return�� ���� ����
	BMState->preFilterSize = 5;  // brightness correction, 5x5 ~ 21x21 // ��ü�� ., pointer�� �� �ּҷ� ���� ȭ��ǥ�� ��
	BMState->preFilterCap = 5;	// removed region after prefilter
	BMState->SADWindowSize = 11; // SAD: sum of absolute difference, window size (5x5.... 21x21) // ������ ������ 11(surport ����) �� ũ����
	//���� 11->5 ��ȣ���� Ŀ���� ������ �� �ȳ��� // 25�� �η繶��������(���е� ������) matching�� �� ����
	BMState->minDisparity = 1;   // minimum disparity [pixel] // ã�����ϴ� minimum ��
	BMState->numberOfDisparities = 32; // maximum disparity [pixel] // 1~32���� pixel ��
	BMState->textureThreshold = 10;  // minimum allowed
	BMState->uniquenessRatio = 5;    // uniqueness  (removing false matching) 

	// convert color space
	Mat Left, Right;
	cvtColor(L, Left, CV_RGB2GRAY); // gray�� ��ȯ
	cvtColor(R, Right, CV_RGB2GRAY);

	// type conversion: mat to IplImage
	IplImage *left, *right;
	left = &IplImage(Left);
	right = &IplImage(Right);

	CvMat* disparity = cvCreateMat(Left.rows, Left.cols, CV_16SC1);
	CvMat* disparity_img = cvCreateMat(Left.rows, Left.cols, CV_8UC1); // 1~32 -> 0~255 ��⸦ ������ �� �� �ְ� �ٲ���

	// run algorithm
	cvFindStereoCorrespondenceBM(left, right, disparity, BMState);
	cvNormalize(disparity, disparity_img, 0, 255, CV_MINMAX);  //normalize to display

	// show results // stereo matching show
	cvShowImage("Disparity", disparity_img);
	imwrite("../result_image/9_stereo_disparity.jpg", (Mat)disparity_img);

	waitKey(0);
	return 0;
}