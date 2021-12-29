#include <cstdio>
#include <cassert>
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
//    I16pcm src;
//    readWav("0001.wav", src);
//    F64pcm dst = {nullptr, src.length, 1, 44100};
//    convert(src, dst);
//    ModelResult modelResult;
//    calculateModelResult(dst, modelResult);
//    modelResult.print();
//    free(src.raw);
//    free(dst.raw);
}