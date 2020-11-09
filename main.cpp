#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/photo.hpp"
#include <QTextStream>
#include <QFileInfo>
#include <QDir>
#include <vector>       // std::vector

int main(int argc, char** argv)
{
    // READ RGB color image and convert it to Lab
    cv::Mat bgr_image = cv::imread("/mnt/c/Users/loanl/Downloads/Telegram Desktop/Sang_7_12h/84110baa-5e9a-4d7d-aa9d-da206c6f106d.jpg");
    cv::Mat lab_image;
    cv::imshow("anh goc",bgr_image);
    cv::fastNlMeansDenoisingColored(bgr_image, bgr_image,10,10,7,21);

    cv::cvtColor(bgr_image, lab_image,cv::COLOR_BGR2Lab);
    cv::imshow("lab",lab_image);
    // Extract the L channel
    std::vector<cv::Mat> lab_planes(3);
    cv::split(lab_image, lab_planes);  // now we have the L image in lab_planes[0]
   // apply the CLAHE algorithm to the L channel
    cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
    clahe->setClipLimit(4);
    cv::Mat dst;
    clahe->apply(lab_planes[0], dst);

    // Merge the the color planes back into an Lab image
    dst.copyTo(lab_planes[0]);
    cv::merge(lab_planes, lab_image);

   // convert back to RGB
   cv::Mat image_clahe;
   cv::cvtColor(lab_image, image_clahe,cv::COLOR_Lab2BGR);

   // display the results  (you might also want to see lab_planes[0] before and after).
   cv::imshow("image original", bgr_image);
   cv::imshow("image CLAHE", image_clahe);
   cv::imwrite("/mnt/c/Users/loanl/OneDrive/Pictures/Saved Pictures/anhAmVang_change1.jpg",image_clahe);

   cv::waitKey();
}
