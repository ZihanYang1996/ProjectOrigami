#import "AppleAudioCaptureHelper.h"
#import <math.h>

@interface AppleAudioCaptureHelper ()
@property (nonatomic, strong) AVAudioEngine *audioEngine;
@property (nonatomic, assign) float micVolume; // Store volume level
@end

@implementation AppleAudioCaptureHelper

+ (instancetype)sharedInstance {
    static AppleAudioCaptureHelper *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[AppleAudioCaptureHelper alloc] init];
    });
    return sharedInstance;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        self.audioEngine = [[AVAudioEngine alloc] init];
        self.micVolume = 0.0f;
    }
    return self;
}

#import <AVFoundation/AVFoundation.h>

- (void)startCapture {
#if PLATFORM_IOS
    // ✅ iOS: Request microphone permission
    [[AVAudioSession sharedInstance] requestRecordPermission:^(BOOL granted) {
        if (!granted) {
            NSLog(@"AppleAudioCaptureHelper: Microphone permission denied.");
            return;
        }
        
        dispatch_async(dispatch_get_main_queue(), ^{
            [self setupAudioEngine];
        });
    }];
#else
    // ✅ macOS: No permission needed, start audio engine directly
    [self setupAudioEngine];
#endif
}

- (void)setupAudioEngine {
    NSError *error = nil;

#if PLATFORM_IOS
    // ✅ iOS: Setup AVAudioSession (Not available on macOS)
    AVAudioSession *session = [AVAudioSession sharedInstance];
    [session setCategory:AVAudioSessionCategoryPlayAndRecord mode:AVAudioSessionModeVideoChat options:AVAudioSessionCategoryOptionAllowBluetooth | AVAudioSessionCategoryOptionDefaultToSpeaker error:&error];
    [session setActive:YES error:&error];

    if (error) {
        NSLog(@"AppleAudioCaptureHelper: Failed to set AVAudioSession category: %@", error.localizedDescription);
    }

    [session setActive:YES error:&error];
    if (error) {
        NSLog(@"AppleAudioCaptureHelper: Failed to activate AVAudioSession: %@", error.localizedDescription);
    }
#endif

    AVAudioInputNode *inputNode = self.audioEngine.inputNode;
    if (!inputNode) {
        NSLog(@"AppleAudioCaptureHelper: No valid input node available.");
        return;
    }

    AVAudioFormat *hardwareFormat = [inputNode inputFormatForBus:0];

    // ✅ Debug: Log the detected format
    NSLog(@"AppleAudioCaptureHelper: HW Sample Rate: %f, HW Channels: %d",
          hardwareFormat.sampleRate, hardwareFormat.channelCount);

    // ✅ Handle invalid sample rate or channel count
    if (hardwareFormat.sampleRate <= 0 || hardwareFormat.channelCount <= 0) {
        NSLog(@"AppleAudioCaptureHelper: Invalid HW format, defaulting to 44100 Hz, 1 channel.");
        hardwareFormat = [[AVAudioFormat alloc] initWithCommonFormat:AVAudioPCMFormatFloat32
                                                          sampleRate:44100
                                                            channels:1
                                                         interleaved:NO];
    }

    // ✅ Set up audio capture
    [inputNode installTapOnBus:0 bufferSize:1024 format:hardwareFormat block:^(AVAudioPCMBuffer *buffer, AVAudioTime *when) {
        float sum = 0.0;
        float *data = buffer.floatChannelData[0];
        int frameCount = buffer.frameLength;

        for (int i = 0; i < frameCount; i++) {
            sum += data[i] * data[i];
        }
        float rms = sqrt(sum / frameCount);
        float volumeDB = 20.0 * log10(rms + 0.0001);
        self.micVolume = fmaxf(0.0f, fminf(1.0f, (volumeDB + 60.0f) / 60.0f));
    }];

    // ✅ Start the audio engine
    [self.audioEngine startAndReturnError:nil];
}

- (void)stopCapture {
    if (self.audioEngine.inputNode) {
        [self.audioEngine.inputNode removeTapOnBus:0];
    }
    [self.audioEngine stop];
    NSLog(@"AppleAudioCaptureHelper: Audio Engine stopped");
}

- (float)getMicVolume {
    return self.micVolume;
}

@end
