#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
	cv::Mat image;	// ����һ����ͼ��

	image = cv::imread("./img/kawaii.jpg");	// ��ȡͼ���ļ�

	// ����ȡ�Ƿ�ɹ�
	if (image.empty())
	{
		std::cout << "ERROR : Read image Failed!\n";
		return -1;
	}

	cv::namedWindow("Image");	// ����ͼƬ��ʾ����,�ɲ�д
	cv::imshow("Image", image);	// �ڴ�����ʾͼƬ

	cv::imwrite("./img/1.png", image);	// ��ͼ�񱣴�Ϊpng��ʽ

	cv::waitKey(0);

	return 0;
}