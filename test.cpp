#include <cstdio>
#include <vector>
#include <cassert>
#include <ctime>
#include "AudioDataBuffer.h"
#include <mutex>
#include "snore.h"

using namespace snore;

void readWav(const char *path, I16pcm &dst) {
    dst.channel = 1;
    dst.fs = 44100;
    FILE *fp = fopen(path, "rb");
    assert(fp != nullptr);
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp) - 44;
    dst.length = size / 2;
    dst.raw = (int16_t *) malloc(sizeof(int16_t) * dst.length);
    fseek(fp, 44, SEEK_SET);
    fread(dst.raw, 1, dst.length * 2, fp);
    fclose(fp);
}

uint64_t currentTimeMillis() {
    struct timeval tv{};
    mingw_gettimeofday(&tv, nullptr);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

using std::vector;
using std::mutex;
using std::unique_lock;

int main() {
    const int32_t frame_size = 100, overlap = 30;
    AudioDataBuffer<int16_t> buffer(2000, frame_size, overlap);
    printf("capacity = %d\n", buffer.capacity());
    printf("frame size = %d\n", buffer.getFrameSize());
    printf("overlay = %d\n", buffer.getOverlap());
    auto src = new int16_t[frame_size];
    auto dst = new int16_t[frame_size];
    int16_t i = 100;
    int64_t timestamp = 45;
    while (!buffer.full()) {
        for (int j = 0; j < frame_size; ++j, ++i) {
            src[j] = i;
        }
        int32_t wt = buffer.put(timestamp, src, frame_size);
        timestamp += 50;
        printf("wt = %d\n", wt);
    }
    while (buffer.ready()) {
        int32_t rd = buffer.next(dst, frame_size, timestamp);
        printf("rd = %d\n", rd);
        printf("%d ms\n", timestamp);
        printf("dst = [");
        for (int j = 0; j < rd; ++j) {
            printf("%d, ", dst[j]);
        }
        printf("]\n");
    }
    printf("size = %d\n", buffer.size());
    buffer.clear();
    printf("size = %d\n", buffer.size());
    assert(buffer.empty());
}