/*
 * RBAnnotator
 *
 * Author: Davide Moltisanti
 * Code released under GPL license
 *
 * For this class I used code from http://codingexodus.blogspot.co.uk/2012/12/working-with-video-using-opencv-and-qt.html
 *
*/

#include "player.h"

Player::Player(QObject *parent) : QThread(parent) {
    stop = true;
    videoLoaded = false;
}

bool Player::loadVideo() {
    capture.open("C:\\Users\\Wittawat\\Downloads\\VID.mp4");

    if (capture.isOpened()) {
        frameRate = capture.get(CV_CAP_PROP_FPS);
        videoLoaded = true;
        numberOfFrames = capture.get(CV_CAP_PROP_FRAME_COUNT);
       //capture.set(CV_CAP_PROP_FRAME_WIDTH,360);
     //   capture.set(CV_CAP_PROP_FRAME_HEIGHT,360);
        setCurrentFrame(0); // read the first frame in order to get the size
    } else {
        videoLoaded = false;
    }

    return videoLoaded;
}

void Player::playVideo() {
    if (!isRunning()) {
        if (isStopped()){
            stop = false;
        }

        start(TimeCriticalPriority);
    }
}

bool Player::isVideoLoaded() const {
    return videoLoaded;
}

QImage Player::getCurrentFrameImg() const {
    return img;
}

Mat Player::returnFrame() const
{
    return RGBframe;
}

VideoCapture *Player::getCapture() {
    return &capture;
}

void Player::getFrameSize(int *width, int *height) {
    // sometimes opencv doesn't return the right size, so it's better to do this
    *width = frame.cols;
    *height = frame.rows;
}

void Player::readCurrentFrame() {
    if (frame.channels() == 3) {
        cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
        img = QImage((const unsigned char*)(RGBframe.data), RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);
    } else {
        img = QImage((const unsigned char*)(frame.data), frame.cols,frame.rows,QImage::Format_Indexed8);
    }
}
/*
void Player::run() {
    int delay = (1000/frameRate);

    while(!stop){
        if (!capture.read(frame)) {
            stop = true;
        }

        readCurrentFrame();

        emit processedImage(img);
        this->msleep(delay);
    }
}
*/
Player::~Player() {
    mutex.lock();
    stop = true;
    capture.release();
    condition.wakeOne();
    mutex.unlock();
    wait();
}

void Player::stopVideo() {
    stop = true;
}

/*void Player::msleep(int ms){
   struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}
*/
bool Player::isStopped() const{
    return this->stop;
}

int Player::getNumberOfFrames() {
    return numberOfFrames;
}

int Player::getLengthMs() {
    return round(getNumberOfFrames() * frameRate);
}

int Player::getCurrentFramePosition() {
    return capture.get(CV_CAP_PROP_POS_FRAMES) -1 ; // 0-based index of the frame to be decoded/captured next. This is why we need -1
}

void Player::setCurrentFrame(int framePosition) {
    //if(framePosition > 0 && framePosition << getNumberOfFrames()) { // the property not always works
    capture.set(CV_CAP_PROP_POS_FRAMES, framePosition);
    capture.read(frame);
    resize(frame, frame, Size(640, 360), 0, 0, INTER_CUBIC);
    readCurrentFrame();
//    emit processedImage(img);
    //}
}

void Player::setCurrentMs(double ms) {
    // capture.set(CV_CAP_PROP_POS_MSEC, ms); // does not always work
    setCurrentFrame(round((ms/1000.0*frameRate)));
}

void Player::skipOneFrame(Mat frame) {
  //  setCurrentFrame(capture.get(CV_CAP_PROP_POS_FRAMES));
    img = QImage((const unsigned char*)(frame.data), frame.cols,frame.rows,QImage::Format_Indexed8);

}

int Player::getCurrentMsPosition() {
    //return capture.get(CV_CAP_PROP_POS_MSEC); // does not always work
    return round(frameRate * getCurrentFramePosition());
}
