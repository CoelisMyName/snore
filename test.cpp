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

int main() {
    I16pcm src;
    readWav("1min.wav", src);
    F64pcm dst;
    dst.length = src.length;
    dst.fs = src.fs;
    dst.raw = (double *)malloc(sizeof(double) * dst.length);
    for(int i = 0; i < dst.length; ++i) {
        dst.raw[i] = src.raw[i] / 32768.0;
    }
    printf("%d\n", dst.length);
    ModelResult result;
    calculateModelResult(dst, result);
    result.print();
    return 0;
}