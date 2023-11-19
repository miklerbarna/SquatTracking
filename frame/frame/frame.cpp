#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>

#include <map>


int main() {
    // Open the video file
    cv::VideoCapture cap("./vid.mp4");

    std::vector<double> times;

    if (!cap.isOpened()) {
        std::cout << "Error opening video file." << std::endl;
        return -1;
    }

    long double frameTimestamp;
    double framerate;
    int framenum = 0;

    while (true) {
        cv::Mat frame;
        if (!cap.read(frame)) {
            break; // End of video
        }
        framenum++;
        // Check if the video frame contains a timestamp
        frameTimestamp = cap.get(cv::CAP_PROP_POS_MSEC);
        framerate = cap.get(cv::CAP_PROP_FPS);

        std::cout  << frameTimestamp << "    " << framerate << std::endl;
        times.push_back(frameTimestamp);

        // Do something with the frame and timestamp
        // ...

        // Display the frame if needed
        cv::imshow("Video Frame", frame);

        // Break the loop if a key is pressed
        if (cv::waitKey(30) >= 0) {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();

    std::map<long double, int> time_distributions;

    double diff;
    for (size_t i = 0; i < times.size() - 1; i++)
    {
        diff = times.at(i + 1) - times.at(i);
        if (time_distributions.find(diff) == time_distributions.end())
        {
            time_distributions[diff] = 1;
        }
        else
        {
            time_distributions[diff]++;
        }
    }


    for (auto i : time_distributions)
    {
        std::cout << i.first << ": " << i.second << " db" << std::endl;
    }
    
    std::cout << framenum << std::endl;

    return 0;
}
