#include "HImage.h"

#include "utils/log/easylogging++.h"

namespace image
{
    HImage::HImage()
    {      
    }

    HImage::~HImage()
    {       
    }

    bool HImage::LoadMat(std::string name, std::string image)
    {
        _name = name;
        _image = image;

        LOG(INFO)<< "LoadMat ..." << _name << " - " << _image;

        _mat = cv::imread(_image);
        if (!_mat.data)
        {
            LOG(ERROR) << "no image data: " << _image;
            return false;
        }

        LOG(INFO) << "image "<< _image <<" : "<< _mat.rows << ", " << _mat.cols;

        return true;
    }

    bool HImage::Resize(double x_scale, double y_scale)
    {
        // 最基本的做法
        std::cout << "before resize: " << _mat.rows << ", " << _mat.cols << std::endl;
        cv::resize(_mat, _mat, cv::Size(_mat.rows * x_scale, _mat.cols * y_scale));
        std::cout << "after resize: " << _mat.rows << ", " << _mat.cols << std::endl;

        return true;
    }

    bool HImage::MResize(double x_scale, double y_scale)
    {
        //最近邻域插值法
        int sourceRows = _mat.rows;        //原来的行数
        int sourceCols = _mat.cols;        //原来的列数
        int newRows = _mat.rows * x_scale; //新的行数
        int newCols = _mat.cols * y_scale; //新的列数

        std::cout << "sourceRows: " << sourceRows << ", sourceCols: " << sourceCols
            << ", newRows: " << newRows << ", newCols: " << newCols << std::endl;

        //初始化矩阵，并把颜色（0，0，0）赋值给给个矩阵的每个元素
        cv::Mat tmpMat(newRows, newCols, CV_8UC3, cv::Scalar(0, 0, 0));
        for (int i = 0; i < newRows; i++)
        {
            for (int j = 0; j < newCols; j++)
            {
                // sourceI/i = sourceRows/newRows，但如果newRows大于sourceRows，会一直是0，因此需要乘1.0变成浮点型
                int iSource = i * (sourceRows * 1.0 / newRows);
                int jSource = j * (sourceCols * 1.0 / newCols);

                tmpMat.at<cv::Vec3b>(i, j) = _mat.at<cv::Vec3b>(iSource, jSource);
            }
        }

        _mat = tmpMat;

        return true;
    }

    bool HImage::Show()
    {
        cv::imshow(_name, _mat);

        cv::waitKey(0);
        return true;
    }

    bool HImage::MCut(int x1, int y1, int x2, int y2)
    {
        int sourceRows = _mat.rows;        //原来的行数
        int sourceCols = _mat.cols;        //原来的列数

        if ((x1 < 0) || (y1 < 0) || (x2 <= x1) || (y2 <= y1) || (y2 > sourceRows) || (x2 > sourceCols))
        {
            std::cout << "传入的参数有误" << std::endl;
            return false;
        }

        int newRows = y2 - y1; //新的行数
        int newCols = x2 - x1; //新的列数

        std::cout << "MCut sourceRows: " << sourceRows << ", sourceCols: " << sourceCols
            << ", newRows: " << newRows << ", newCols: " << newCols << std::endl;

        //初始化矩阵，并把颜色（0，0，0）赋值给给个矩阵的每个元素
        cv::Mat tmpMat(newRows, newCols, CV_8UC3, cv::Scalar(0, 0, 0));
        for (int i = 0; i < newRows; i++)
        {
            for (int j = 0; j < newCols; j++)
            {
                tmpMat.at<cv::Vec3b>(i, j) = _mat.at<cv::Vec3b>(y1 + i, x1 + j);
            }
        }

        _mat = tmpMat;
        return true;
    }

} // namespace image