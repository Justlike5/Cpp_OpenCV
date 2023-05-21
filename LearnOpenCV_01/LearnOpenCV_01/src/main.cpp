#include <opencv2/opencv.hpp>
#include <iostream>

#define LOG(x) std::cout << x << '\n'

int main()
{
	cv::Mat image = cv::imread("./img/kawaii.jpg");

	if (image.empty())
	{
		LOG("Read Image file Failed!");
	}

	cv::imshow("Kawaii", image);

	LOG("ͼ��ĸ߶�Ϊ: " << image.rows);	// ���������
	LOG("ͼ��Ŀ��Ϊ: " << image.cols);	// ���������
	LOG("ͼ���ͨ����Ϊ: " << image.channels());	// ͼ��ɫ��ͨ����
	LOG("ͼ��ĳߴ�Ϊ: " << image.size);	// ���� * ����

	cv::Mat imageKeen(image, cv::Rect(0, 0, 270, 270));

	cv::imshow("Kawaii", imageKeen);

	cv::waitKey(0);

	return 0;
}