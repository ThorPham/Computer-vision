#include "opencv2/core/core.hpp" //������� c++
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	//6���� //0416 //edge
	Mat src = imread("../image/Lena.jpg");

	imshow("Input", src);

	Mat gray;
	cvtColor(src, gray, CV_BGR2GRAY);

	Mat edge;
	Canny(gray, edge, 50, 200, 3); //50 ��ŷ//150 ������ ���� //3 ������
	//edge.convertTo(edge, CV_8U); //�׷��� ������

	imshow("Canny Result", edge);
	imwrite("../result_image/5_edge_canny.jpg", edge);
	waitKey(0); //�ȸ����� cin.ignore(); 
				//����ڰ� Ű����ġ�� �Է��� 1���� �� ����: ignore(1)->����Ű(�ٸ� key�� ��) ��ٸ�, �ܼ�â ����
	return 0;
}