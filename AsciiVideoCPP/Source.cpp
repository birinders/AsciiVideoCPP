#include <opencv2\opencv.hpp>
#include <stdlib.h>


using namespace cv;

using namespace std;

int main() {

	Mat frame;

	//namedWindow("Display window");

	VideoCapture video_capture(0);

	video_capture >> frame;

	float video_height = frame.rows;
	float video_width = frame.cols;

	float depth = frame.dims;

	float letter_width = 10;
	float letter_height = 20;

	float ascii_width = 100;
	float ascii_height = ascii_width * (video_height / video_width) * (letter_width / letter_height);

	int int_ascii_width = static_cast<int>(ascii_width);
	int int_ascii_height = static_cast<int>(ascii_height);
	//cout << ascii_height;

	int brt_max = 256;
	string brt_str = R"($@BM#*o/\f|()1{}[]?-_+i!lI;:," ^ `'.                  )";
	reverse(brt_str.begin(), brt_str.end());
	int brt_len = brt_str.length();

	if (!video_capture.isOpened()) {

		cout << "cannot open camera";

	}

	cout << int_ascii_height << "," << int_ascii_width;

	while (true) {

		system("cls");

		video_capture >> frame;
		Mat gray;
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		Mat gray_resized;
		resize(gray, gray_resized, cv::Size(int_ascii_width,int_ascii_height));
		//cout << gray_resized.at<int>(0, 0);
		//cv::Vec3b pixel = gray_resized.at<cv::Vec3b>(0,0);
		//cout<<pixel[0]
		//int pixelValue = gray_resized.at<uchar>(0,0);
		//cout << pixelValue;

		//vector<vector<int>> ascii_arr[int_ascii_height][int_ascii_width];

		for (int j = 0; j < int_ascii_height; j++) {
			for (int i = 0; i < int_ascii_width; i++) {
				//ascii_arr[j][i] = gray_resized.at<int>(j, i);
				int brt = gray_resized.at<uchar>(j,i);
				int index = brt * brt_len / brt_max;
				cout << brt_str[index];
			}
			cout << "\n";
		}

		imshow("out", gray_resized);

		waitKey(25);

	}

	return 0;

}