//
// Created by julee on 16-11-19.
//

#ifndef INSTA360_ATOMCAMERA_H
#define INSTA360_ATOMCAMERA_H

#include <libuvc/libuvc.h>
#include <libuvc/libuvc_ctrl.h>
#include <libuvc/storage_api_20.h>
#include <string>
#include <memory>

enum class StreamFormat { H264, MJPEG };

class Frame;

class AtomCamera
{
public:
    explicit AtomCamera();
    AtomCamera(std::string name, uvc_device_t **device, uvc_context_t *context);
    
    int open(StreamFormat format, int width, int height, int fps, int bitrate);
    void close();
    bool isClosed();
    int getCameraUUID(std::string& UUID);
    int getCameraOffset(std::string& offset);
    std::string name() { return mName; } 
    int readFrame(std::shared_ptr<Frame> *frame);
    
private:
    std::string mTag = "Insta360Air";
    std::string mName;
    uvc_context_t *mUvcContext = nullptr;
    uvc_device_t **mUvcDevice = nullptr;
    uvc_device_handle_t *mUvcDevicheHandle = nullptr;
    uvc_stream_ctrl_t *mStreamCtrl = nullptr;
    uvc_stream_handle_t *mStreamHandle = nullptr; 
    bool mClosed=false;
    bool mInitialStatus = false;

    const char *TAG = nullptr;

private:
    AtomCamera(const AtomCamera &) = delete;
    AtomCamera &operator=(const AtomCamera &) = delete; 
};


#endif //INSTA360_ATOMCAMERA_H
