#include "futronic.h"
#include "ftrScanAPI.h"
#include <QDebug>
#include "mainwindow.h"

Futronic::Futronic()
{

}

cv::Mat Futronic::scanFinger(){
    void *hDevice;
    int i;
    FTRSCAN_IMAGE_SIZE ImageSize;
    cv::Mat emptyImg, img;
    unsigned char *pBuffer;

    hDevice = ftrScanOpenDevice();
        if( hDevice == nullptr )
        {
            qDebug()<<"Failed to open device!\n";
            return emptyImg;
        }
        if( !ftrScanGetImageSize( hDevice, &ImageSize ) )
            {
                qDebug()<<"Failed to get image size\n";
                ftrScanCloseDevice( hDevice );
                return emptyImg;
            }
        else
            {
                pBuffer = (unsigned char *)malloc( ImageSize.nImageSize );
                qDebug()<<"Please put your finger on the scanner:\n";
                while(1)
                {
                    if( ftrScanIsFingerPresent( hDevice, nullptr ) )
                        break;
                    for(i=0; i<50; i++);
                }
                qDebug()<<"Capturing fingerprint ......";
                ftrScanSetOptions( hDevice, FTR_OPTIONS_INVERT_IMAGE, FTR_OPTIONS_INVERT_IMAGE );
                if(ftrScanGetFrame(hDevice, pBuffer, nullptr) )
                {
                    qDebug()<<"Done!";
                    img = cv::Mat(ImageSize.nHeight, ImageSize.nWidth, CV_8UC1, pBuffer);
                    return img;
                }
                else
                    qDebug()<<"Failed to get image?\n";
                free( pBuffer );
            }
        ftrScanCloseDevice( hDevice );
        return emptyImg;
}
