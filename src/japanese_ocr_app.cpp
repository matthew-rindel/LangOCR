#include <iostream>
#include "japanese_ocr_app.h"
#include <QPushButton>
#include <QtWidgets>
#include <unistd.h>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <cstring>

JapaneseOcrApp::JapaneseOcrApp(QMainWindow *parent):
    QMainWindow(parent)
{
    button_ = new QPushButton(QString("Push to draw."), this);
    overlay_ = new OverlayWindow(this);
    drawWindow_ = new DrawWindow(this);
    overlay_->show();

    this->setCentralWidget(button_);

    QObject::connect(button_, SIGNAL(released()), this, SLOT(onButtonReleased())); 
    QObject::connect(drawWindow_, SIGNAL(newDrawnItem(QPoint, QSize)),
                     overlay_, SLOT(drawRect(QPoint, QSize)));
    QObject::connect(drawWindow_, SIGNAL(newWindowAdded()),
                     this, SLOT(prepareToCapture()));
    QObject::connect(this, SIGNAL(captureWindowDone()),
                     this, SLOT(runTesseract()));
}

JapaneseOcrApp::~JapaneseOcrApp()
{
    return; 

}

void JapaneseOcrApp::onButtonReleased()
{
    drawWindow_->show();
    drawWindow_->move(0,0);
}

void JapaneseOcrApp::prepareToCapture(void)
{
    // Due to reasons I don't understand, we must delay the capture
    // process or we will capture the rubber band used to indicate
    // where the window will be captured.  I think is is because the
    // QT Main event loop hasn't hidden the rubber band yet.

    QTimer::singleShot(100, this, &JapaneseOcrApp::captureWindow);
}

void JapaneseOcrApp::captureWindow()
{ 
    //WId winId = overlay_->winId();
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect rect = overlay_->getRectangle();
    QPixmap pix;
    pix = screen->grabWindow(0,
                             rect.x(),
                             rect.y(),
                             rect.width(),
                             rect.height());
 
    // Save the image to the local directory. 
    if(!pix.save(QString("myPic.jpg"), "jpg", 100))
        std::cout << "Failure to save capture!" << std::endl;

    emit captureWindowDone();
}

void JapaneseOcrApp::runTesseract(void)
{
    char *out;
    tesseract::Orientation orientation;
    tesseract::WritingDirection direction;
    tesseract::TextlineOrder order;
    float deskew_angle;
    
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    
    if(api->Init(NULL,"jpn"))
    {
        fprintf(stderr, "Failed to initalize tesseract. \n");
        exit(1);
    }

    // This is using the leptonica library
    Pix *image = pixRead("myPic.jpg");
    
    // Configure API 
    api->SetImage(image);
    //api->SetPageSegMode(tesseract::PSM_SINGLE_BLOCK_VERT_TEXT);

    tesseract::PageIterator* it =  api->AnalyseLayout();
    //it->Orientation(&orientation, &direction, &order, &deskew_angle);
    //printf("Orientation: %d;\nWritingDirection: %d\nTextlineOrder: %d\n" \
    //       "Deskew angle: %.4f\n",
    //       orientation, direction, order, deskew_angle);

    printf("Got here!\n");
    out = api->GetUTF8Text();
    printf("Also got here!\n");
    printf("OCR Output: \n%s", out);
    api->End();
    delete api;
    delete [] out;
    pixDestroy(&image);
}