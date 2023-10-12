#include "opencv2/opencv.hpp"
#include <iostream>
#include <algorithm>

/////////////////  Project 1 - Virtual Painter //////////////////////

/////////////////////  COLOR VALUES ////////////////////////////////

struct colorValue {
    cv::Scalar lowerBound;
    cv::Scalar upperBound;
    cv::Scalar drawColor;
};

// @formatter:off
const std::vector<colorValue> myColors = {
        colorValue{ cv::Scalar(124, 48, 117), cv::Scalar(143, 170, 255), cv::Scalar(255, 0, 255)},  // Purple
        colorValue{ cv::Scalar(68, 72, 156), cv::Scalar(102, 126, 255), cv::Scalar(0, 255, 0) }  // Green
};
// @formatter:on
////////////////////////////////////////////////////////////////////

cv::Point getPenPosition(const cv::Mat &image) {

    std::vector < std::vector < cv::Point >> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(image, contours, hierarchy, cv::RETR_EXTERNAL,
            cv::CHAIN_APPROX_SIMPLE);

    cv::Rect boundRect;
    cv::Point p;
    for (const auto &contour : contours) {
        int area = cv::contourArea(contour);
        std::cout << area << std::endl;

        if (area > 1000) {
            boundRect = cv::boundingRect(contour);
            p.x = boundRect.x + boundRect.width / 2;
            p.y = boundRect.y;
        }
    }
    return p;
}

void findColor(const cv::Mat &img,
        std::vector<std::tuple<cv::Point, cv::Scalar>> &points) {
    cv::Mat imgHSV;
    cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

    for (const auto &color : myColors) {
        cv::Mat mask;
        cv::inRange(imgHSV, color.lowerBound, color.upperBound, mask);
        cv::Point p = getPenPosition(mask);
        if (p.x != 0) {
            points.push_back( { p, color.drawColor });
        }
    }
}

void drawCircles(const cv::Mat &img,
        const std::vector<std::tuple<cv::Point, cv::Scalar>> &points) {

//    for (const auto &point : points) {
//        //cv::circle(img, std::get<0>(point), 10, std::get<1>(point), cv::FILLED);
//        auto [center, color] = point;
//        // Using C++17 feature Structured Bindings (nicer)
//        cv::circle(img, center, 10, color, cv::FILLED);
//    }

    std::for_each(std::begin(points), std::end(points), [&img](auto& p) {
        auto [center, color] = p;
        // Using C++17 feature Structured Bindings (nicer)
        cv::circle(img, center, 10, color, cv::FILLED);
    });

}

int main() {

    cv::Mat img;
    cv::VideoCapture cap(1);
    std::vector<std::tuple<cv::Point, cv::Scalar>> points;  // to store all points

    while (true) {

        cap.read(img);
        findColor(img, points);
        drawCircles(img, points);
        cv::imshow("Image", img);
        int key = cv::waitKey(1);
        if (key == 27)
            break;
    }
    return 1;
}

