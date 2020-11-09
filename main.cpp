#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/photo.hpp"
#include <opencv2/core.hpp>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>
#include <vector>       // std::vector

void docAnh(std::string nameFile,cv::Mat imgOut)
{

}

void lamNet1(cv::Mat imgInput,cv::Mat imgOutput)
{
    cv::fastNlMeansDenoisingColored(imgInput, imgOutput,10,10,7,21);
}

void lamNet2(cv::Mat imgInput,cv::Mat imgOutput)
{
    cv::Mat lab_image;
    cv::cvtColor(imgInput, lab_image,cv::COLOR_BGR2Lab);
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
   cv::cvtColor(lab_image,imgOutput,cv::COLOR_Lab2BGR);
}

void resizeImg(cv::Mat imgInput,cv::Mat imgOutput,float n)
{

}
void canBangHitogram(cv::Mat imgIn,cv::Mat  imageDst)
{
    cv::Mat imageHsv;
    cv::cvtColor(imgIn, imageHsv, cv::COLOR_BGR2HSV_FULL);
    std::vector<cv::Mat> hsvChannels;
    // Tách imageHsv thành 3 kênh màu
    cv::split(imageHsv, hsvChannels);
    // Cân bng histogram kênh màu v (Value)
    cv::equalizeHist(hsvChannels[2], hsvChannels[2]);
    // Tron nh
    cv::merge(hsvChannels, imageHsv);
    // Chuyn đi HSV sang RGB đ hin th
    cv::cvtColor(imageHsv, imageDst, cv::COLOR_HSV2BGR);
    cv::imshow("imageSrc",imgIn);
    cv::imshow("imageDst",  imageDst);
}


int main(int argc, char** argv)
{
    float x,y;float hightnew,n;
    // READ RGB color image and convert it to Lab
    cv::Mat bgr_image = cv::imread("/mnt/c/Users/loanl/Downloads/Telegram Desktop/photo_2020-11-09_10-17-18.jpg");

    cv::imshow("anh goc",bgr_image);

//    lamNet1(bgr_image,bgr_image);
//    cv::imshow("anh lam net 1",bgr_image);
    lamNet2(bgr_image,bgr_image);

   //resize.........
   hightnew = 500;// chieu cao cua anh moi
   n= hightnew/(float)bgr_image.rows;
   y=hightnew;
   x= (float)bgr_image.cols*n;
   printf("x=%f,y=%f,img.rowls=%d,img.cols=%d",x,y,bgr_image.rows,bgr_image.cols);
   cv::resize(bgr_image, bgr_image, cv::Size(x,y));
    // end resize.......
   // canBangHitogram(bgr_image,bgr_image);
   // display the results  (you might also want to see lab_planes[0] before and after).
   cv::imshow("image original", bgr_image);
   cv::imwrite("/mnt/c/Users/loanl/OneDrive/Pictures/Saved Pictures/anhAmVang_change1.jpg",bgr_image);

   cv::waitKey();
}
