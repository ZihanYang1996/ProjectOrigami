#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

@interface AppleAudioCaptureHelper : NSObject

// Singleton accessor
+ (instancetype)sharedInstance;

// Starts audio capture using AVAudioEngine
- (void)startCapture;

// Stops audio capture
- (void)stopCapture;

// Returns real-time mic volume
- (float)getMicVolume;

@end