#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

int main() {

	cv::Mat srcImg = cv::imread("logs.jpg");

	cv::namedWindow("srcImg", cv::WINDOW_NORMAL);
	cv::imshow("srcImg", srcImg);

	cv::cvtColor(srcImg, srcImg, cv::COLOR_BGR2GRAY);

	cv::medianBlur(srcImg, srcImg, 5);

	cv::Mat laplacian = (cv::Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	cv::filter2D(srcImg, srcImg, CV_8UC3, laplacian);

	cv::Mat edges;
	cv::Canny(srcImg, edges, 165, 250);

	cv::namedWindow("edges", cv::WINDOW_NORMAL);
	cv::imshow("edges", edges);

	std::vector<cv::Vec3f> houghCircles;
	cv::HoughCircles(edges, houghCircles, cv::HOUGH_GRADIENT, 1, srcImg.rows / 48, 250, 29, srcImg.rows / 96, srcImg.rows / 21);

	cv::cvtColor(srcImg, srcImg, cv::COLOR_GRAY2BGR);
	cv::cvtColor(edges, edges, cv::COLOR_GRAY2BGR);

	for (auto circle : houghCircles) {

		cv::Scalar color(0, 255, 0);
		cv::Point center = cv::Point(circle[0], circle[1]);
		double radius = circle[2];
		cv::circle(srcImg, center, radius, color, 2, cv::LINE_AA);
		cv::circle(edges, center, radius, color, 2, cv::LINE_AA);
	}

	cv::namedWindow("logsCounter", cv::WINDOW_NORMAL);
	cv::imshow("logsCounter", srcImg);
	cv::namedWindow("edgeSearch", cv::WINDOW_NORMAL);
	cv::imshow("edgeSearch", edges);

	std::cout << ("木材数量总共为：") << houghCircles.size();

	cv::waitKey(0);
	return 0;
}