#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/nonfree/features2d.hpp> // for Lab.2: SIFT Detector

using namespace cv;

//***** Global variables for Lab.1
Mat src, src_gray; //����, gray image
int thresh = 80, max_thresh = 255; //threshold
String source_window = "Source image - �賭��";
String corners_window = "Corners detected - �賭��";

/// Function header
void cornerHarris_demo(int, void*);

int main(void)
{
	//***** ***** Lab.1 Simple Canny Edge Detector ***** *****//
	/// Load source image, resize 1/2 of size and convert it to gray
	src = imread("../image/Rhone_River.jpg");
	//resize(src, src, Size(src.size().width/2, src.size().height / 2));
	cvtColor(src, src_gray, CV_BGR2GRAY);

	/// Create a window and a trackbar
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	createTrackbar("Threshold: ", source_window, &thresh, max_thresh, cornerHarris_demo);

	/// Show image and keep running
	imshow(source_window, src);
	cornerHarris_demo(0, 0);

	//***** ***** Lab.2 SIFT(blob) detector ***** *****//

	/// SIFT feature detector: SIFT ��ü ����
	SiftFeatureDetector detector;

	/// Feature detection: Keypoints ��ü ����
	vector<KeyPoint> keypoints;

	/// using detect func: image���� keypoints�� ����ϰ� ����, 
	/// �Ϻκ��� keypoints ������ ���ؼ��� mask ���ڸ� �����ϸ� ��.
	detector.detect(src, keypoints);

	/// draw Keypoints: image�� keypoints�� ��ġ�� ������ ǥ��
	/// Scalar::all(-1)�� ���� �������� ǥ���ϸ�, DRAW_RICH_KEYPOINTS�� �����ϸ� ũ��� ���⼺�� �Բ� ǥ��
	drawKeypoints(src, keypoints, src, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	/// Show detected (drawn) keypoints
	imshow("SIFT Dectector/ Keypoints - �賭��", src);
	imwrite("../result_image/6_corner_blob_SIFT_Dectector_Keypoints.jpg", src);

	waitKey(0);
	return(0);
}

/** @function cornerHarris_demo */
void cornerHarris_demo(int, void*)
{
	/// ��� image, normalize�� image, scaling�� image ����
	Mat dst, dst_norm, dst_norm_scaled;
	dst = Mat::zeros(src.size(), CV_32FC1); // ��� image�� 0���� ä��, float�� ����

	/// Detector parameters
	int blockSize = 2;
	int apertureSize = 3;
	double k = 0.04; //k�� 0.04~0.06

	/// Detecting corners
	cornerHarris(src_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT);

	/// Normalizing: �ڽ��� ���ϴ� data range�� �ٲ�, scale�� �ٲ�
	normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	// cornerHarris �Լ����� float������ �ٲ� ���� �ٽ� �ٲ�
	// float�� imshow ���� ���ϱ� ����
	convertScaleAbs(dst_norm, dst_norm_scaled);

	/// Drawing a circle around corners: ������ ǥ��
	for (int j = 0; j < dst_norm.rows; j++) //height ��ŭ
	{
		for (int i = 0; i < dst_norm.cols; i++) //width ��ŭ
		{
			if ((int)dst_norm.at<float>(j, i) > thresh)
			{
				//@input, point center(�� �߽�), radius(����), ����:0, 
				//����:2, 8-connected line(�ε巴��), �̵���:0
				circle(dst_norm_scaled, Point(i, j), 5, Scalar(0), 2, 8, 0);
			}
		}
	}

	/// Showing the result
	namedWindow(corners_window, CV_WINDOW_AUTOSIZE);
	imshow(corners_window, dst_norm_scaled);
	imwrite("../result_image/6_corner_blob_Corners_detected.jpg", dst_norm_scaled);
}