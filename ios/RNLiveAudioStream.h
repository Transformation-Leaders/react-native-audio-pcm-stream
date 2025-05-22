#import <React/RCTBridgeModule.h>
#import <React/RCTEventEmitter.h>
#import <AVFoundation/AVFoundation.h>

#define kNumberBuffers 3

typedef struct {
    AudioStreamBasicDescription  mDataFormat;
    AudioQueueRef                mQueue;
    AudioQueueBufferRef          mBuffers[kNumberBuffers];
    AudioFileID                  mAudioFile;
    SInt64                       mCurrentPacket;
    bool                         mIsRunning;
    UInt32                       bufferByteSize;
    __unsafe_unretained id       mSelf;
} AQRecordState;

@interface RNLiveAudioStream : RCTEventEmitter <RCTBridgeModule>

@property (nonatomic, assign) AQRecordState recordState;

// Existing methods for recording
RCT_EXPORT_METHOD(init:(NSDictionary *)options);
RCT_EXPORT_METHOD(start);
RCT_EXPORT_METHOD(stop);

// New methods for playback
RCT_EXPORT_METHOD(playChunk:(NSString *)base64Chunk);
RCT_EXPORT_METHOD(stopPlayback);

@end
