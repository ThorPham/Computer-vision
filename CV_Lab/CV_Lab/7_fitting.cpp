#include <stdio.h> //��Ī ���� MAX, MIN �Ÿ��� ����
#include <iostream> //vector ����ϱ� ����
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <opencv2/nonfree/features2d.hpp> // for 2.4.13
#include "opencv2/calib3d/calib3d.hpp"

using namespace cv;
using namespace std;

//ransac method
int main(int argc, char** argv)
{
	Mat img_object = imread("../image/LEMONA0.jpg", IMREAD_GRAYSCALE); //����� Ư¡�� ���� �ȹٷ� �� �� �̹���
	Mat img_scene = imread("../image/LEMONA2.jpg", IMREAD_GRAYSCALE); //�ƹ������� ����� ������ �� ��ü �̹���

	//�̹����� �������� ���δ�.
	resize(img_object, img_object, Size(img_object.size().width / 2, img_object.size().height / 2));
	resize(img_scene, img_scene, Size(img_scene.size().width / 2, img_scene.size().height / 2));

	if (!img_object.data || !img_scene.data) //�̹��� READ�� �����ϸ� �ߴ� ���� üũ
	{
		std::cout << " --(!) Error reading images " << std::endl; return -1;
	}

	//-- Step 1: Detect the keypoints using SURF Detector
	int minHessian = 400;
	SurfFeatureDetector detector(minHessian);
	vector<KeyPoint> keypoints_object, keypoints_scene;
	detector.detect(img_object, keypoints_object); //�� ����
	detector.detect(img_scene, keypoints_scene);

	//-- Step 2: Calculate descriptors (feature vectors)
	SurfDescriptorExtractor extractor;
	Mat descriptors_object, descriptors_scene;
	extractor.compute(img_object, keypoints_object, descriptors_object); //key point ��ġ�� ���� descriptors ���
	extractor.compute(img_scene, keypoints_scene, descriptors_scene);

	//-- Step 3: Matching descriptor vectors using FLANN matcher
	FlannBasedMatcher matcher;
	vector< DMatch > matches; //��Ī�� ��
	matcher.match(descriptors_object, descriptors_scene, matches); //��Ī �Լ� 
	double max_dist = 0; double min_dist = 100;
	//-- Quick calculation of max and min distances between keypoints
	for (int i = 0; i < descriptors_object.rows; i++)
	{
		double dist = matches[i].distance; //�Ÿ� max, min ã��, ������ ����
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}

	printf("-- Max dist : %f \n", max_dist);
	printf("-- Min dist : %f \n", min_dist);
	printf("21611591 �賭�� \n");

	//-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
	vector< DMatch > good_matches; //�Ÿ� ���� ������ �͸� �̾Ƴ� �� ����
	for (int i = 0; i < descriptors_object.rows; i++)
	{
		if (matches[i].distance < 5 * min_dist) //lab2���� 3 --> 5�� ����
		{
			good_matches.push_back(matches[i]);
		}
	}

	Mat img_matches;
	drawMatches(img_object, keypoints_object, img_scene, keypoints_scene,
		good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
		vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	//-- Localize the object
	vector<Point2f> obj;
	vector<Point2f> scene;

	for (int i = 0; i < good_matches.size(); i++)
	{
		//-- Get the keypoints from the good matches
		obj.push_back(keypoints_object[good_matches[i].queryIdx].pt);
		scene.push_back(keypoints_scene[good_matches[i].trainIdx].pt);
	}
	vector<uchar> inliers(obj.size(), 0);
	//fine a perspective transformation between two planes
	//Mat H = findHomography(obj, scene, inliers, RANSAC);//RANSAC based homography estimation for lab 1
	Mat H = findHomography(obj, scene, inliers, LMEDS); //Other Method for lab2 : 0 or LMEDS

	// Draw the inlier points
	vector<Point2f>::const_iterator itPts = obj.begin(); //object �̹����� ���� �׸��� ����
	vector<uchar>::const_iterator itIn = inliers.begin();
	while (itPts != obj.end()) {
		// draw a circle at each inlier location
		if (*itIn)
			circle(img_object, *itPts, 3, Scalar(0, 255, 0), 2); //������ ���� �� ���̵��� ������
		++itPts;
		++itIn;
	}
	itPts = scene.begin(); //scene �̹����� ���� �׸��� ����
	itIn = inliers.begin();
	while (itPts != scene.end()) {
		// draw a circle at each inlier location
		if (*itIn)
			circle(img_scene, *itPts, 3, Scalar(0, 255, 0), 2);
		++itPts;
		++itIn;
	}
	imshow("Matching:object-�賭��", img_object);
	imshow("Matching:scene-�賭��", img_scene);
	imwrite("../result_image/7_fitting_Matching_object.jpg", img_object);
	imwrite("../result_image/7_fitting_Matching_scene.jpg", img_scene);

	//-- Get the corners from the image_1 ( the object to be "detected" )
	vector<Point2f> obj_corners(4);
	obj_corners[0] = cvPoint(0, 0); obj_corners[1] = cvPoint(img_object.cols, 0);
	obj_corners[2] = cvPoint(img_object.cols, img_object.rows); obj_corners[3] = cvPoint(0, img_object.rows);
	vector<Point2f> scene_corners(4);

	perspectiveTransform(obj_corners, scene_corners, H);

	//-- Draw lines between the corners (the mapped object in the scene - image_2 ) 
	line(img_matches, scene_corners[0] + Point2f(img_object.cols, 0), scene_corners[1] + Point2f(img_object.cols, 0), Scalar(0, 255, 0), 4);
	line(img_matches, scene_corners[1] + Point2f(img_object.cols, 0), scene_corners[2] + Point2f(img_object.cols, 0), Scalar(0, 255, 0), 4);
	line(img_matches, scene_corners[2] + Point2f(img_object.cols, 0), scene_corners[3] + Point2f(img_object.cols, 0), Scalar(0, 255, 0), 4);
	line(img_matches, scene_corners[3] + Point2f(img_object.cols, 0), scene_corners[0] + Point2f(img_object.cols, 0), Scalar(0, 255, 0), 4);

	//-- Show detected matches
	imshow("Good Matches & Object detection-�賭��", img_matches);
	imwrite("../result_image/7_fitting_Good_Matches&Object_detection.jpg", img_matches);


	waitKey(0);
	return 0;
}