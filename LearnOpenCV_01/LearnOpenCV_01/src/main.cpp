#include "../ref/OnMouse.h"
#include <iostream>

#include "../ref/Salt.h"

#define LOG(x) std::cout << x << '\n'

int main()
{
	cv::Mat image_in, image_target, image_gray_in, image_gray_target, image_hist_in, image_hist_target;
	image_in = cv::imread("./img/kawaii.jpg");
	image_target = cv::imread("./img/lockyStar.jpg");

	if (image_in.empty() || image_target.empty())
	{
		LOG("Load Image Error!");
		return -1;
	}

	// �Ҷ�ͼ : src
	cv::cvtColor(image_in, image_gray_in, cv::COLOR_BGR2GRAY);
	cv::imshow("image_gray_in", image_gray_in);

	// �Ҷ�ͼ : target
	cv::cvtColor(image_target, image_gray_target, cv::COLOR_BGR2GRAY);
	cv::imshow("image_gray_target", image_gray_target);

	// ֱ��ͼ���⻯ : src
	cv::Mat image_enhanced_in;
	cv::equalizeHist(image_gray_in, image_enhanced_in);
	cv::imshow("image_enhanced_in", image_enhanced_in);

	// ֱ��ͼ���⻯ : target
	cv::Mat  image_enhanced_target;
	cv::equalizeHist(image_gray_target, image_enhanced_target);
	cv::imshow("image_enhanced_target", image_enhanced_target);

	// ��ȡͼ��ֱ��ͼ

	int histsize = 256;
	float ranges[] = { 0,256 };
	const float* histRanges = { ranges };
	cv::calcHist(&image_gray_in, 1, 0, cv::Mat(), image_hist_in, 1, &histsize, &histRanges, true, false);
	cv::calcHist(&image_gray_target, 1, 0, cv::Mat(), image_hist_target, 1, &histsize, &histRanges, true, false);

	// �����������⻯ͼ��ֱ��ͼ���ۻ�����
	float hist_in_cdf[256] = { image_hist_in.at<float>(0) };
	float hist_target_cdf[256] = { image_hist_target.at<float>(0) };
	for (int i = 1; i < 256; i++)
	{
		hist_in_cdf[i] = (hist_in_cdf[i - 1] + image_hist_in.at<float>(i));
		hist_target_cdf[i] = (hist_target_cdf[i - 1] + image_hist_target.at<float>(i));
	}

	for (int i = 0; i < 256; i++)
	{
		hist_in_cdf[i] = hist_in_cdf[i] / (image_gray_in.rows * image_gray_in.cols);
		hist_target_cdf[i] = hist_target_cdf[i] / (image_gray_target.rows * image_gray_target.cols);
	}

	// �����ۻ�����֮��Ĳ�ֵ,�����ҵ���ӽ��ĵ�
	float diff_cdf[256][256];
	for (int i = 0; i < 256; i++)
		for (int j = 0; j < 256; j++)
		{
			diff_cdf[i][j] = fabs(hist_in_cdf[i] - hist_target_cdf[j]);
		}

	cv::Mat lut(1, 256, CV_8U);
	for (int i = 0; i < 256; i++)
	{
		// ����Դ�Ҷȼ�Ϊi��ӳ��ҶȺ�i���ۻ����ʲ�ֵ��С�Ĺ涨���Ҷ�
		float min = diff_cdf[i][0];
		int index = 0;
		for (int j = 0; j < 256; j++)
			if (min > diff_cdf[i][j])
			{
				min = diff_cdf[i][j];
				index = j;
			}
		lut.at<uchar>(i) = index;
	}
	cv::LUT(image_gray_in, lut, image_enhanced_in);
	cv::imshow("image_enhanced_in", image_enhanced_in);

	// ����ֱ��ͼ��ʾͼ��

	//int hist_h = 300;
	//int hist_w = 512;
	//int bin_w = hist_w / histsize;
	//cv::Mat histImage_in(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));
	//cv::Mat histImage_target(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));

	//// ���Ʋ���ʾֱ��ͼ : in
	//cv::normalize(image_hist_in, image_hist_in, 0, hist_h, cv::NORM_MINMAX, -1, cv::Mat());
	//for (int i = 1; i < histsize; i++)
	//{
	//	cv::line(histImage_in, cv::Point((i - 1) * bin_w, hist_h - cvRound(image_hist_in.at<float>(i - 1))),
	//		cv::Point((i)*bin_w, hist_h - cvRound(image_hist_in.at<float>(i))), cv::Scalar(255, 0, 0), 2, 8, 0);
	//}

	//// ���Ʋ���ʾֱ��ͼ : target
	//cv::normalize(image_hist_target, image_hist_target, 0, hist_h, cv::NORM_MINMAX, -1, cv::Mat());
	//for (int i = 1; i < histsize; i++)
	//{
	//	cv::line(histImage_target, cv::Point((i - 1) * bin_w, hist_h - cvRound(image_hist_target.at<float>(i - 1))),
	//		cv::Point((i)*bin_w, hist_h - cvRound(image_hist_target.at<float>(i))), cv::Scalar(255, 0, 0), 2, 8, 0);
	//}

	//cv::imshow("histImage_in", histImage_in);
	//cv::imshow("histImage_target", histImage_target);

	cv::waitKey(0);

	return 0;
}