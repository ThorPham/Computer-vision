//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/core/core.hpp"
//#include "opencv2/calib3d/calib3d.hpp"
//#include "opencv2/opencv.hpp"
//
//using namespace cv;
//using namespace std;
//
////* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
////* * * * * * * * * * for lab2 - Render the disparity in 3D space (point cloud) * * * * * * * * * * poing cloud�� ����Ϸ��� ���⼭���� �ּ� ���� * * * * * * * * //
////* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//template <class T>
//static void fillOcclusionInv_(Mat& src, T invalidvalue)
//{
//	int bb = 1;
//	const int MAX_LENGTH = src.cols*0.8;
//#pragma omp parallel for // openMP�� �̿��� ���� ó��
//	for (int j = bb; j < src.rows - bb; j++)
//	{
//		T* s = src.ptr<T>(j);
//		const T st = s[0];
//		const T ed = s[src.cols - 1];
//		s[0] = 0;
//		s[src.cols - 1] = 0;
//		for (int i = 0; i < src.cols; i++)
//		{
//			if (s[i] == invalidvalue)
//			{
//				int t = i;
//				do
//				{
//					t++;
//					if (t > src.cols - 1)break;
//				} while (s[t] == invalidvalue);
//
//				const T dd = max(s[i - 1], s[t]);
//				if (t - i > MAX_LENGTH)
//				{
//					for (int n = 0; n < src.cols; n++)
//					{
//						s[n] = invalidvalue;
//					}
//				}
//				else
//				{
//					for (; i < t; i++)
//					{
//						s[i] = dd;
//					}
//				}
//			}
//		}
//	}
//}
//template <class T>
//static void fillOcclusion_(Mat& src, T invalidvalue)
//{
//	int bb = 1;
//	const int MAX_LENGTH = src.cols*0.5;
//#pragma omp parallel for // openMP�� �̿��� ���� ó��
//	for (int j = bb; j < src.rows - bb; j++)
//	{
//		T* s = src.ptr<T>(j);
//		const T st = s[0];
//		const T ed = s[src.cols - 1];
//		s[0] = 255;
//		s[src.cols - 1] = 255;
//		for (int i = 0; i < src.cols; i++)
//		{
//			if (s[i] <= invalidvalue)
//			{
//				int t = i;
//				do
//				{
//					t++;
//					if (t > src.cols - 1)break;
//				} while (s[t] <= invalidvalue);
//
//				const T dd = min(s[i - 1], s[t]);
//				if (t - i > MAX_LENGTH)
//				{
//					for (int n = 0; n < src.cols; n++)
//					{
//						s[n] = invalidvalue;
//					}
//				}
//				else
//				{
//					for (; i < t; i++)
//					{
//						s[i] = dd;
//					}
//				}
//			}
//		}
//	}
//}
//void fillOcclusion(Mat& src, int invalidvalue, bool isInv = false)
//{	// �ұ�Ģ�� ���� �����Ͽ� �ұ�Ģ�� ���� �ּ�ȭ�ϰ� �ٽ� ä��
//	if (isInv)
//	{
//		if (src.type() == CV_8U)
//		{
//			fillOcclusionInv_<uchar>(src, (uchar)invalidvalue);
//		}
//		else if (src.type() == CV_16S)
//		{
//			fillOcclusionInv_<short>(src, (short)invalidvalue);
//		}
//		else if (src.type() == CV_16U)
//		{
//			fillOcclusionInv_<unsigned short>(src, (unsigned short)invalidvalue);
//		}
//		else if (src.type() == CV_32F)
//		{
//			fillOcclusionInv_<float>(src, (float)invalidvalue);
//		}
//	}
//	else
//	{
//		if (src.type() == CV_8U)
//		{
//			fillOcclusion_<uchar>(src, (uchar)invalidvalue);
//		}
//		else if (src.type() == CV_16S)
//		{
//			fillOcclusion_<short>(src, (short)invalidvalue);
//		}
//		else if (src.type() == CV_16U)
//		{
//			fillOcclusion_<unsigned short>(src, (unsigned short)invalidvalue);
//		}
//		else if (src.type() == CV_32F)
//		{
//			fillOcclusion_<float>(src, (float)invalidvalue);
//		}
//	}
//}
//void eular2rot(double yaw, double pitch, double roll, Mat& dest)
//{
//	double theta = yaw / 180.0*CV_PI;
//	double pusai = pitch / 180.0*CV_PI;
//	double phi = roll / 180.0*CV_PI;
//
//	double datax[3][3] = { {1.0,0.0,0.0},
//	{0.0,cos(theta),-sin(theta)},
//	{0.0,sin(theta),cos(theta)} };
//	double datay[3][3] = { {cos(pusai),0.0,sin(pusai)},
//	{0.0,1.0,0.0},
//	{-sin(pusai),0.0,cos(pusai)} };
//	double dataz[3][3] = { {cos(phi),-sin(phi),0.0},
//	{sin(phi),cos(phi),0.0},
//	{0.0,0.0,1.0} };
//	Mat Rx(3, 3, CV_64F, datax);
//	Mat Ry(3, 3, CV_64F, datay);
//	Mat Rz(3, 3, CV_64F, dataz);
//	Mat rr = Rz * Rx*Ry;
//	rr.copyTo(dest);
//}
//
//void lookat(Point3d from, Point3d to, Mat& destR)
//{
//	double x = (to.x - from.x);
//	double y = (to.y - from.y);
//	double z = (to.z - from.z);
//
//	double pitch = asin(x / sqrt(x*x + z * z)) / CV_PI * 180.0;
//	double yaw = asin(-y / sqrt(y*y + z * z)) / CV_PI * 180.0;
//
//	eular2rot(yaw, pitch, 0, destR);
//}
//template <class T>
//static void projectImagefromXYZ_(Mat& image, Mat& destimage, Mat& disp, Mat& destdisp, Mat& xyz, Mat& R, Mat& t, Mat& K, Mat& dist, Mat& mask, bool isSub)
//{
//	if (destimage.empty())destimage = Mat::zeros(Size(image.size()), image.type());
//	if (destdisp.empty())destdisp = Mat::zeros(Size(image.size()), disp.type());
//
//	vector<Point2f> pt;
//	if (dist.empty()) dist = Mat::zeros(Size(5, 1), CV_32F);
//	cv::projectPoints(xyz, R, t, K, dist, pt);
//
//	destimage.setTo(0);
//	destdisp.setTo(0);
//
//#pragma omp parallel for
//	for (int j = 1; j < image.rows - 1; j++)
//	{
//		int count = j * image.cols;
//		uchar* img = image.ptr<uchar>(j);
//		uchar* m = mask.ptr<uchar>(j);
//		for (int i = 0; i < image.cols; i++, count++)
//		{
//			int x = (int)(pt[count].x + 0.5);
//			int y = (int)(pt[count].y + 0.5);
//			if (m[i] == 255)continue;
//			if (pt[count].x >= 1 && pt[count].x < image.cols - 1 && pt[count].y >= 1 && pt[count].y < image.rows - 1)
//			{
//				short v = destdisp.at<T>(y, x);
//				if (v < disp.at<T>(j, i))
//				{
//					destimage.at<uchar>(y, 3 * x + 0) = img[3 * i + 0];
//					destimage.at<uchar>(y, 3 * x + 1) = img[3 * i + 1];
//					destimage.at<uchar>(y, 3 * x + 2) = img[3 * i + 2];
//					destdisp.at<T>(y, x) = disp.at<T>(j, i);
//
//					if (isSub)
//					{
//						if ((int)pt[count + image.cols].y - y > 1 && (int)pt[count + 1].x - x > 1)
//						{
//							destimage.at<uchar>(y, 3 * x + 3) = img[3 * i + 0];
//							destimage.at<uchar>(y, 3 * x + 4) = img[3 * i + 1];
//							destimage.at<uchar>(y, 3 * x + 5) = img[3 * i + 2];
//
//							destimage.at<uchar>(y + 1, 3 * x + 0) = img[3 * i + 0];
//							destimage.at<uchar>(y + 1, 3 * x + 1) = img[3 * i + 1];
//							destimage.at<uchar>(y + 1, 3 * x + 2) = img[3 * i + 2];
//
//							destimage.at<uchar>(y + 1, 3 * x + 3) = img[3 * i + 0];
//							destimage.at<uchar>(y + 1, 3 * x + 4) = img[3 * i + 1];
//							destimage.at<uchar>(y + 1, 3 * x + 5) = img[3 * i + 2];
//
//							destdisp.at<T>(y, x + 1) = disp.at<T>(j, i);
//							destdisp.at<T>(y + 1, x) = disp.at<T>(j, i);
//							destdisp.at<T>(y + 1, x + 1) = disp.at<T>(j, i);
//						}
//						else if ((int)pt[count - image.cols].y - y < -1 && (int)pt[count - 1].x - x < -1)
//						{
//							destimage.at<uchar>(y, 3 * x - 3) = img[3 * i + 0];
//							destimage.at<uchar>(y, 3 * x - 2) = img[3 * i + 1];
//							destimage.at<uchar>(y, 3 * x - 1) = img[3 * i + 2];
//
//							destimage.at<uchar>(y - 1, 3 * x + 0) = img[3 * i + 0];
//							destimage.at<uchar>(y - 1, 3 * x + 1) = img[3 * i + 1];
//							destimage.at<uchar>(y - 1, 3 * x + 2) = img[3 * i + 2];
//
//							destimage.at<uchar>(y - 1, 3 * x - 3) = img[3 * i + 0];
//							destimage.at<uchar>(y - 1, 3 * x - 2) = img[3 * i + 1];
//							destimage.at<uchar>(y - 1, 3 * x - 1) = img[3 * i + 2];
//
//							destdisp.at<T>(y, x - 1) = disp.at<T>(j, i);
//							destdisp.at<T>(y - 1, x) = disp.at<T>(j, i);
//							destdisp.at<T>(y - 1, x - 1) = disp.at<T>(j, i);
//						}
//						else if ((int)pt[count + 1].x - x > 1)
//						{
//							destimage.at<uchar>(y, 3 * x + 3) = img[3 * i + 0];
//							destimage.at<uchar>(y, 3 * x + 4) = img[3 * i + 1];
//							destimage.at<uchar>(y, 3 * x + 5) = img[3 * i + 2];
//
//							destdisp.at<T>(y, x + 1) = disp.at<T>(j, i);
//						}
//						else if ((int)pt[count - 1].x - x < -1)
//						{
//							destimage.at<uchar>(y, 3 * x - 3) = img[3 * i + 0];
//							destimage.at<uchar>(y, 3 * x - 2) = img[3 * i + 1];
//							destimage.at<uchar>(y, 3 * x - 1) = img[3 * i + 2];
//
//							destdisp.at<T>(y, x - 1) = disp.at<T>(j, i);
//						}
//						else if ((int)pt[count + image.cols].y - y > 1)
//						{
//							destimage.at<uchar>(y + 1, 3 * x + 0) = img[3 * i + 0];
//							destimage.at<uchar>(y + 1, 3 * x + 1) = img[3 * i + 1];
//							destimage.at<uchar>(y + 1, 3 * x + 2) = img[3 * i + 2];
//
//							destdisp.at<T>(y + 1, x) = disp.at<T>(j, i);
//						}
//						else if ((int)pt[count - image.cols].y - y < -1)
//						{
//							destimage.at<uchar>(y - 1, 3 * x + 0) = img[3 * i + 0];
//							destimage.at<uchar>(y - 1, 3 * x + 1) = img[3 * i + 1];
//							destimage.at<uchar>(y - 1, 3 * x + 2) = img[3 * i + 2];
//
//							destdisp.at<T>(y - 1, x) = disp.at<T>(j, i);
//						}
//					}
//				}
//			}
//		}
//	}
//
//	if (isSub)
//	{
//		Mat image2;
//		Mat disp2;
//		destimage.copyTo(image2);
//		destdisp.copyTo(disp2);
//		const int BS = 1;
//#pragma omp parallel for
//		for (int j = BS; j < image.rows - BS; j++)
//		{
//			uchar* img = destimage.ptr<uchar>(j);
//			T* m = disp2.ptr<T>(j);
//			T* dp = destdisp.ptr<T>(j);
//			for (int i = BS; i < image.cols - BS; i++)
//			{
//				if (m[i] == 0)
//				{
//					int count = 0;
//					int d = 0;
//					int r = 0;
//					int g = 0;
//					int b = 0;
//					for (int l = -BS; l <= BS; l++)
//					{
//						T* dp2 = disp2.ptr<T>(j + l);
//						uchar* img2 = image2.ptr<uchar>(j + l);
//						for (int k = -BS; k <= BS; k++)
//						{
//							if (dp2[i + k] != 0)
//							{
//								count++;
//								d += dp2[i + k];
//								r += img2[3 * (i + k) + 0];
//								g += img2[3 * (i + k) + 1];
//								b += img2[3 * (i + k) + 2];
//							}
//						}
//					}
//					if (count != 0)
//					{
//						double div = 1.0 / count;
//						dp[i] = d * div;
//						img[3 * i + 0] = r * div;
//						img[3 * i + 1] = g * div;
//						img[3 * i + 2] = b * div;
//					}
//				}
//			}
//		}
//	}
//}
//void projectImagefromXYZ(Mat& image, Mat& destimage, Mat& disp, Mat& destdisp, Mat& xyz, Mat& R, Mat& t, Mat& K, Mat& dist, bool isSub = true, Mat& mask = Mat())
//{
//	if (mask.empty())mask = Mat::zeros(image.size(), CV_8U);
//	if (disp.type() == CV_8U)
//	{
//		projectImagefromXYZ_<unsigned char>(image, destimage, disp, destdisp, xyz, R, t, K, dist, mask, isSub);
//	}
//	else if (disp.type() == CV_16S)
//	{
//		projectImagefromXYZ_<short>(image, destimage, disp, destdisp, xyz, R, t, K, dist, mask, isSub);
//	}
//	else if (disp.type() == CV_16U)
//	{
//		projectImagefromXYZ_<unsigned short>(image, destimage, disp, destdisp, xyz, R, t, K, dist, mask, isSub);
//	}
//	else if (disp.type() == CV_32F)
//	{
//		projectImagefromXYZ_<float>(image, destimage, disp, destdisp, xyz, R, t, K, dist, mask, isSub);
//	}
//	else if (disp.type() == CV_64F)
//	{
//		projectImagefromXYZ_<double>(image, destimage, disp, destdisp, xyz, R, t, K, dist, mask, isSub);
//	}
//}
//Mat makeQMatrix(Point2d image_center, double focal_length, double baseline)
//{
//	Mat Q = Mat::eye(4, 4, CV_64F);
//	Q.at<double>(0, 3) = -image_center.x;
//	Q.at<double>(1, 3) = -image_center.y;
//	Q.at<double>(2, 3) = focal_length;
//	Q.at<double>(3, 3) = 0.0;
//	Q.at<double>(2, 2) = 0.0;
//	Q.at<double>(3, 2) = 1.0 / baseline;
//
//	return Q;
//}
//void stereoTest()
//{
//	//(1) Reading L&R images and estimating disparity map by semi-global block matching.
//	Mat image = imread("../image/l.png", 1); // ���׷��� �̹����� �о�帲
//	Mat imageR = imread("../image/r.png", 1);
//	Mat destimage;
//
//	/*int resize_k = 4; // ���� ũ�Ⱑ ũ�� ������ �ٲٱ�
//	resize(image, image, Size(image.size().width / resize_k, image.size().height / resize_k));
//	resize(imageR, imageR, Size(imageR.size().width / resize_k, imageR.size().height / resize_k));*/
//
//	StereoSGBM sgbm(1, 16 * 2, 3, 200, 255, 1, 0, 0, 0, 0, true); //SGBM���� ���� ȭ���� �����
//	Mat disp;
//	Mat destdisp;
//	Mat dispshow;
//	sgbm(image, imageR, disp); // ��� ����� ������ �ּ� ���� -16�� ���� �ұ�Ģ���� �Ҵ��
//	fillOcclusion(disp, 16); // �ұ�Ģ ���� �׷����� ������ ���Ҵ��ϴ� �Լ�
//
//	//(2)make Q matrix and reproject pixels into 3D space // ��Ʈ������ ����� ���� �̹����� 3���� ������ ����
//	const double focal_length = 598.57;
//	const double baseline = 14.0;
//	// 3���� ������ �����ϱ� ���� Q ����� ��� // ���׷��� ī�޶� �����Ͽ� Q ����� ��� ���� CV::streoRevtify���� ������
//	Mat Q = makeQMatrix(Point2d((image.cols - 1.0) / 2.0, (image.rows - 1.0) / 2.0), focal_length, baseline * 16);
//
//	Mat depth;
//	cv::reprojectImageTo3D(disp, depth, Q); // ������ 3���� ������ ������ 
//	Mat xyz = depth.reshape(3, depth.size().area()); // 3ä���� float �迭�� �����
//
//	//(3) camera setting // ī�޶� ���� // ��� ����
//	Mat K = Mat::eye(3, 3, CV_64F);
//	K.at<double>(0, 0) = focal_length;
//	K.at<double>(1, 1) = focal_length;
//	K.at<double>(0, 2) = (image.cols - 1.0) / 2.0;
//	K.at<double>(1, 2) = (image.rows - 1.0) / 2.0;
//
//	Mat dist = Mat::zeros(5, 1, CV_64F);
//	Mat R = Mat::eye(3, 3, CV_64F);
//	Mat t = Mat::zeros(3, 1, CV_64F);
//
//	Point3d viewpoint(0.0, 0.0, baseline * 10); // ����
//	Point3d lookatpoint(0.0, 0.0, -baseline * 10.0); // �ֽ���
//	const double step = baseline;
//	int key = 0;
//	bool isSub = true;
//	//(4) rendering loop // 3���� ��ǥ���� ���ο� ������ �̹����� ������ ����
//	while (key != 27)
//	{
//		lookat(viewpoint, lookatpoint, R); // ���� ī�޶��� ������ ������Ʈ��
//		t.at<double>(0, 0) = viewpoint.x;
//		t.at<double>(1, 0) = viewpoint.y;
//		t.at<double>(2, 0) = viewpoint.z;
//
//		cout << t << endl;  // ��ǥ ���
//		t = R * t;
//
//		//(5) projecting 3D point cloud to image.
//		projectImagefromXYZ(image, destimage, disp, destdisp, xyz, R, t, K, dist, isSub);
//
//		destdisp.convertTo(dispshow, CV_8U, 0.5);
//		imshow("depth - �賭��", dispshow);
//		imshow("image - �賭��", destimage);
//
//		// ��ġ ���� ��Ʈ��
//		if (key == 'f') // ����ȭ ���� ������ �� ���� ��ȯ
//		{				// default ���� ON
//			isSub = isSub ? false : true;
//		}
//		if (key == 'a') // �Ʒ���
//		{
//			viewpoint.y += step;
//		}
//		if (key == 's') // ����
//		{
//			viewpoint.y -= step;
//		}
//		if (key == 'z') //���������� 
//		{
//			viewpoint.x += step;
//		}
//		if (key == 'x') //��������
//		{
//			viewpoint.x -= step;
//		}
//		if (key == 'q') // �ָ�
//		{
//			viewpoint.z += step;
//		}
//		if (key == 'w') // ������ 
//		{
//			viewpoint.z -= step;
//		}
//		key = waitKey(1); // �ǽð����� key ���� ����ϱ� ���� 1�� ��
//						  // 0�� �ٲ� ������ Ű���� ����ϵ��� ��
//	}
//}
////* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
////* * * * * * * * * * for lab2 - Render the disparity in 3D space (point cloud) * * * * * * * * * * poing cloud�� ����Ϸ��� ������� �ּ� �� * * * * * * * * * * //
////* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//* * * * * * * * * * for lab2 - Texture mapping on the 3D shape * * * * * * * * * * Texture mapping�� ����Ϸ��� ���⼭���� �ּ����� * * * * * * * * * * * * * * //
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

///openGL ����
#include <windows.h>
#include <glut.h>

///openCV ����
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <strstream>
#include <functional>
#include <stdio.h>

using namespace cv;

GLuint TextureIdx[1]; //the array for our TextureIdx
Mat mSource_Bgr;	  //texture mapping�� image
GLfloat angle = 45.0; //original source�� cube ����

/// keyboard�� 3d ť�� �����̱�
// (1) ť�� ��ġ
float cubeX = 0.0;
float cubeY = 0.0;
float cubeZ = -4.0;
// (2) ȸ��
float pitch = 0.0;
float yaw = 0.0;
float roll = 0.0;


int UploadTexture(Mat image, GLuint &TextureIdx) ///The my Image to OpenGl TextureIdx function
{
	if (image.empty())
		return -1;
	glGenTextures(1, &TextureIdx);
	glBindTexture(GL_TEXTURE_2D, TextureIdx); //bind the TextureIdx to it's array
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.cols, image.rows, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, image.data);
	return 0;
}
void FreeTexture(GLuint TextureIdx) ///texture mapping �� �����Ҵ� ������ ����
{
	glDeleteTextures(1, &TextureIdx);
}
void special(int key, int x, int y) // ����Ű�� ���� ȸ���� �Է�
{
	if (key == GLUT_KEY_UP)
	{
		pitch += 1.0;
	}
	else if (key == GLUT_KEY_DOWN)
	{
		pitch -= 1.0;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		yaw += 1.0;
	}
	else if (key == GLUT_KEY_LEFT)
	{
		yaw -= 1.0;
	}
}
void keyboard(unsigned char key, int x, int y) // ���� �¿� �����Ըָ� �Է� //* ������ ��: �빮�� ������ �ȵ�
{
	//cout << "���� Ű�� ���������ϴ�. \"" << key << "\" ASCII: " << (int)key << endl;

	//ESC Ű�� �������ٸ� ���α׷� ����
	if (key == 27)
	{
		exit(0);
	}
	else if (key == 43) // ����Ű +Ű
	{
		roll += 1.0;
	}
	else if (key == 45) // ����Ű -Ű
	{
		roll -= 1.0;
	}
	else if (key == 'q') // q key - ũ��, ������
	{
		cubeZ += 0.1;
	}
	else if (key == 'w') // w key - �۰� ,�ָ�
	{
		cubeZ -= 0.1;
	}
	else if (key == 'a') // a key - ����
	{
		cubeY += 0.1;
	}
	else if (key == 's') // s key - �Ʒ���
	{
		cubeY -= 0.1;
	}
	else if (key == 'z') // z key - ����������
	{
		cubeX += 0.1;
	}
	else if (key == 'x') // x key - ��������
	{
		cubeX -= 0.1;
	}
}
void plane(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
	glLoadIdentity();                                   // Reset The View

	//�Ʒ� �� ���� original source, ȸ�� �Ұ� //angle�� ���� ��ȭ�� ���� ����
	//glTranslatef(0.0f, .0f, -5.0f);
	//glRotatef(angle, 1.0f, 1.0f, 0.0f);

	// �̵��� ȸ���� ����
	glTranslatef(cubeX, cubeY, cubeZ);
	glRotatef(pitch, 1.0, 0.0, 0.0);  //x�࿡ ���� ȸ��
	glRotatef(yaw, 0.0, 1.0, 0.0);    //y�࿡ ���� ȸ��
	glRotatef(roll, 0.0, 0.0, 1.0);   //z�࿡ ���� ȸ��

	glBindTexture(GL_TEXTURE_2D, TextureIdx[0]); //unbind the TextureIdx

	glBegin(GL_QUADS);
	// Front Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	// Back Face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	// Top Face
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	// Bottom Face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	// Right face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	// Left Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();


	glBindTexture(GL_TEXTURE_2D, 0); //unbind the TextureIdx
}
void display(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //ȭ���� �����. (�÷����ۿ� ���̹���)
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	plane(); //ť�긦 �׸�
	glutSwapBuffers();
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); //������ ũ��� ������Ʈ ����
	glMatrixMode(GL_PROJECTION);			  //���� ������ Projection Matrix�� ������ ��. ī�޶�� ���̴� ��� ����
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);  //Field of view angle(���� degrees), �������� aspect ratio, Near�� Far Plane ����
	glMatrixMode(GL_MODELVIEW);								  //���� ������ ModelView Matirx�� ������ ��. ��ü ����
}
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//* * * * * * * * * * for lab2 - Texture mapping on the 3D shape * * * * * * * * * * // Texture mapping�� ����Ϸ��� ������� �ּ� �� * * * * * * * * * * //
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


int main(int argc, char** argv)
{
	////* * * * * * * * * * lab 1. block matching based disparity * * * * * * * * * *//
	////load stereo images -> ���� 2��
	//Mat l = imread("../image/im2.ppm"); // left  ���� 
	//Mat r = imread("../image/im6.ppm"); // right ���� right_un.png

	////image resize because big size
	////resize(l, l, size(l.size().width / 4, l.size().height / 4));
	////resize(r, r, size(r.size().width / 4, r.size().height / 4));

	//imshow("Left image - �賭��", l);
	//imshow("Right image - �賭��", r);

	//// set block matching parameters // �Ķ���� ����
	//CvStereoBMState *BMState = cvCreateStereoBMState(); // Ŭ������ �̿��� ��ü ���� -> �Լ��� �ּ� return�� ���� ����
	//BMState->preFilterSize = 5;  // brightness correction, 5x5 ~ 21x21 // ��ü�� ., pointer�� �� �ּҷ� ���� ȭ��ǥ�� ��
	//BMState->preFilterCap = 5;	// removed region after prefilter
	//BMState->SADWindowSize = 17; // sad: sum of absolute difference, window size (5x5.... 21x21) // ������ ������ 11(support ����) �� ũ����
	////support ���� 11->5 ��ȣ���� Ŀ���� ������ �� �ȳ��� // 25�� �η繶��������(���е� ������) matching�� �� ����
	//BMState->minDisparity = 1;   // minimum disparity [pixel] // ã�����ϴ� minimum ��
	//BMState->numberOfDisparities = 32; // maximum disparity [pixel] // 1~32���� pixel ��
	//BMState->textureThreshold = 10;  // minimum allowed
	//BMState->uniquenessRatio = 5;    // uniqueness  (removing false matching) 

	//// convert color space
	//Mat Left, Right;
	//cvtColor(l, Left, CV_RGB2GRAY); // gray�� ��ȯ
	//cvtColor(r, Right, CV_RGB2GRAY);

	//// type conversion: mat to iplimage
	//IplImage *left, *right;
	//left = &IplImage(Left);
	//right = &IplImage(Right);

	//CvMat* disparity = cvCreateMat(Left.rows, Left.cols, CV_16SC1);
	//CvMat* disparity_img = cvCreateMat(Left.rows, Left.cols, CV_8UC1); // 1~32 -> 0~255 ��⸦ ������ �� �� �ְ� �ٲ���

	//// run algorithm
	//cvFindStereoCorrespondenceBM(left, right, disparity, BMState);
	//cvNormalize(disparity, disparity_img, 0, 255, CV_MINMAX);  //normalize to display

	//// show results // stereo matching show
	//cvShowImage("disparity - �賭��", disparity_img);

	//waitKey(0);

	//* * * * * * * * * * lab 2. 3d rendering * * * * * * * * * *//
	///* * * * * (1) render the disparity in 3d space (point cloud)
	// sample of stereo matching and 3d point cloud rendering
	//stereoTest();

	/////* * * * * (2) Texture mapping on the 3D shape with openGL
	glutInit(&argc, argv);						    // GLUT �ʱ�ȭ
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);   // ���� ���ۿ� ���� ���۸� ����ϵ��� ����, GLUT_RGB=0x00��
	glutInitWindowSize(700, 700);				    // �������� width�� height
	glutInitWindowPosition(100, 100);			    // �������� ��ġ (x,y)

	glutCreateWindow("Texture mapping on the 3D shape - OpenGL Window - �賭��"); // ������ ����
	glEnable(GL_TEXTURE_2D);                        // Enable Texture Mapping ( NEW )
	glShadeModel(GL_SMOOTH);                        // Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);           // Black Background
	glClearDepth(1.0f);                             // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);                        // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);                         // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Really Nice Perspective 

	glutDisplayFunc(display); // ���÷��� �ݹ� �Լ� ���
							  // display�Լ��� ������ ó�� ������ ���� ȭ�� �ٽ� �׸� �ʿ� ������ ȣ���
	glutIdleFunc(display);

	glutReshapeFunc(reshape); // reshape �ݹ� �Լ� ���
							  // reshape�Լ��� ������ ó�� ������ ���� ������ ũ�� ����� ȣ��ȴ�.

	mSource_Bgr = imread("../image/earth.png", 1);  //The load my image to opengl TextureIdx

	UploadTexture(mSource_Bgr, TextureIdx[0]); // ������ü�� �׷��� ������ load texture

	//Ű���� �ݹ� �Լ� ���, Ű���尡 �������� ȣ��ȴ�. 
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	// GLUT event processing loop�� ������
	// �� �Լ��� ���ϵ��� �ʱ� ������ �����ٿ� �ִ� �ڵ尡 ������� ���� 
	glutMainLoop();

	// ESC Key�� �������� // �����δ� ������� �ʴ� �Ʒ� 2�� //�����Ҵ� ������ ���� ����
	FreeTexture(TextureIdx[0]);           //Free our TextureIdx
	return 0;
}