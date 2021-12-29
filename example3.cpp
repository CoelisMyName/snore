/**
 * 演示如何获取声压级检测结果
 */
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "snore.h"

using namespace snore;

void readWav(const char *path, I16pcm &dst);

int main() {
    I16pcm src;
    readWav("test.wav", src);
    snoreInitial();
    generateNoiseProfile(src, 0, 1, "noiseprof.txt");
    I16pcm dst = {(int16_t *) malloc(sizeof(int16_t) * src.length), src.length, 1, src.fs};
    reduceNoise(src, dst, "noiseprof.txt", 0.21);
    snoreDestroy();
    return 0;
}

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