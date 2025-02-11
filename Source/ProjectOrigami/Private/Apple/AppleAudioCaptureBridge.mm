#import "AppleAudioCaptureBridge.h"
#import "AppleAudioCaptureHelper.h"

void StartAudioCapture() {
    [[AppleAudioCaptureHelper sharedInstance] startCapture];
}

void StopAudioCapture() {
    [[AppleAudioCaptureHelper sharedInstance] stopCapture];
}

float GetMicVolume() {
    return [[AppleAudioCaptureHelper sharedInstance] getMicVolume];
}
