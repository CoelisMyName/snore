#include "snore.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "sox.h"

#ifdef __cplusplus
}
#endif

#include "matlab/vad.h"
#include "matlab/noise_segment.h"
#include "matlab/classifier.h"
#include "matlab/aweight.h"
#include "matlab/cweight.h"
#include "matlab/zweight.h"
#include "matlab/SnoringRecognition_initialize.h"

#include <cstdio>
#include <cstdlib>
#include <cassert>

#define DEFAULT_PRECISION 16

#ifdef ANDROID
#include <android/log.h>
#define LOG_D(tag, ...) __android_log_print(ANDROID_LOG_DEBUG, tag, __VA_ARGS__)
static const char *const TAG = "snore";
#endif

using namespace snore;

using coder::array;

typedef array<double, 2U> array1D;

void initialSox() {
    int res = sox_init();
    assert(res == SOX_SUCCESS);
//    assert(sox_format_init() == SOX_SUCCESS);
}

void quitSox() {
    int res = sox_quit();
    assert(res == SOX_SUCCESS);
//    sox_format_quit();
}

void freeEffects(sox_effect_t *effects[], int count) {
    for (int i = 0; i < count; ++i)
        free(effects[i]);
}

sox_signalinfo_t getSignalInfo(const SNORE_I16pcm &src) {
    sox_signalinfo_t info = {src.fs, (uint32_t) src.channel, DEFAULT_PRECISION, (uint64_t) src.length, nullptr};
    return info;
}

sox_encodinginfo_t getEncodingInfo() {
    sox_encodinginfo_t info = {SOX_ENCODING_SIGN2, DEFAULT_PRECISION, 1 / 0.0, sox_option_no, sox_option_no,
                               sox_option_no, sox_false};
    return info;
}

SNORE_UNUSED void snore::generateNoiseProfile(SNORE_I16pcm &src, double start, double duration, const char *filename) {
    initialSox();
    /** double转字符串 */
    char start_str[32], duration_str[32];
    sprintf(start_str, "%lf", start);
    sprintf(duration_str, "%lf", duration);
    /** 获取文件格式描述信息 */
    sox_signalinfo_t inSignal_info = getSignalInfo(src);
    sox_encodinginfo_t inEncoding_info = getEncodingInfo();

    /** 输入输出描述符 */
    sox_format_t *input_ft = sox_open_mem_read(src.raw, src.length * 2, &inSignal_info, &inEncoding_info, "raw");
    sox_format_t *output_ft = sox_open_write("", &input_ft->signal, &input_ft->encoding, "null", nullptr, nullptr);

    /** 创建效果器链 */
    sox_effects_chain_t *chain = sox_create_effects_chain(&input_ft->encoding, &input_ft->encoding);

    sox_effect_t *effects[4];
    char *args[8];
    /** 获取效果器并添加到链上 */
    effects[0] = sox_create_effect(sox_find_effect("input"));
    args[0] = (char *) input_ft;
    sox_effect_options(effects[0], 1, args);
    sox_add_effect(chain, effects[0], &input_ft->signal, &input_ft->signal);

    effects[1] = sox_create_effect(sox_find_effect("trim"));
    args[0] = start_str;
    args[1] = duration_str;
    sox_effect_options(effects[1], 2, args);
    sox_add_effect(chain, effects[1], &input_ft->signal, &input_ft->signal);

    effects[2] = sox_create_effect(sox_find_effect("noiseprof"));
    args[0] = (char *) filename;
    sox_effect_options(effects[2], 1, args);
    sox_add_effect(chain, effects[2], &input_ft->signal, &input_ft->signal);

    effects[3] = sox_create_effect(sox_find_effect("output"));
    args[0] = (char *) output_ft;
    sox_effect_options(effects[3], 1, args);
    sox_add_effect(chain, effects[3], &input_ft->signal, &output_ft->signal);

    /** 启动效果器 */
    sox_flow_effects(chain, nullptr, nullptr);

    /** 释放资源 */
    freeEffects(effects, 4);
    sox_delete_effects_chain(chain);
    sox_close(input_ft);
    sox_close(output_ft);

    quitSox();
}

SNORE_UNUSED void snore::reduceNoise(SNORE_I16pcm &src, SNORE_I16pcm &dst, const char *filename, double coefficient) {
    initialSox();
    /** double转字符串 */
    char coefficient_str[32];
    sprintf(coefficient_str, "%lf", coefficient);

    /** 获取文件格式描述信息 */
    sox_signalinfo_t inSignal_info = getSignalInfo(src);
    sox_encodinginfo_t inEncoding_info = getEncodingInfo();

    sox_signalinfo_t outSignal_info = getSignalInfo(dst);
    outSignal_info.length = 0;
    sox_encodinginfo_t outEncoding_info = getEncodingInfo();

    /** 输入输出描述符 */
    sox_format_t *input_ft = sox_open_mem_read(src.raw, src.length * 2, &inSignal_info, &inEncoding_info, "raw");
    sox_format_t *output_ft = sox_open_mem_write(dst.raw, dst.length * 2, &outSignal_info, &outEncoding_info, "raw",
                                                 nullptr);

    /** 创建效果器链 */
    sox_effects_chain_t *chain = sox_create_effects_chain(&input_ft->encoding,
                                                          &output_ft->encoding);

    sox_effect_t *effects[3];
    char *args[4];
    /** 获取效果器并添加到链上 */
    effects[0] = sox_create_effect(sox_find_effect("input"));
    char *args0[1];
    args0[0] = (char *) input_ft;
    sox_effect_options(effects[0], 1, args0);
    sox_add_effect(chain, effects[0], &input_ft->signal, &input_ft->signal);

    effects[1] = sox_create_effect(sox_find_effect("noisered"));
    args[0] = (char *) filename;
    args[1] = coefficient_str;
    sox_effect_options(effects[1], 2, args);
    sox_add_effect(chain, effects[1], &input_ft->signal, &input_ft->signal);

    effects[2] = sox_create_effect(sox_find_effect("output"));
    args[0] = (char *) output_ft;
    sox_effect_options(effects[2], 1, args);
    sox_add_effect(chain, effects[2], &input_ft->signal, &output_ft->signal);

    /** 启动效果器 */
    sox_flow_effects(chain, nullptr, nullptr);

    /** 释放资源 */
    freeEffects(effects, 3);
    sox_delete_effects_chain(chain);
    dst.length = output_ft->olength;
    sox_close(input_ft);
    sox_close(output_ft);
    quitSox();
}

SNORE_UNUSED void snore::calculateModelResult(SNORE_F64pcm &pcm, SNORE_ModelResult &modelResult) {
    SnoringRecognitionStackData stackData{};
    SnoringRecognitionPersistentData persistentData{};
    stackData.pd = &persistentData;
    SnoringRecognition_initialize(&stackData);
    array1D x, w_starts, w_ends, label;
    //TODO 默认是单声道
    x.set(pcm.raw, 1, pcm.length);
    /**
     * 端点检测
     */
    vad(x, pcm.fs, w_starts, w_ends);
    /**
     * 有声段检测
     */
    noise_segment(w_starts, w_ends, pcm.fs, 0.5 * pcm.fs, 3 * pcm.fs, &modelResult.noiseStart,
                  &modelResult.noiseLength);
    /**
     * 分类器分类
     */
//#ifdef ANDROID
//    LOG_D(TAG, "w_starts %d, w_ends %d", w_starts.size(1), w_ends.size(1));
//    for(int i = 0; i < w_starts.size(1); ++i) {
//        LOG_D(TAG, "start %.1f, end %.1f", w_starts[i], w_ends[i]);
//    }
//#endif
    classifier(&stackData, x, w_starts, w_ends, pcm.fs, label);
    modelResult.clear();
    int64_t labelSize = label.size(1), startsSize = w_starts.size(1), endsSize = w_ends.size(1);
    modelResult.signalIndexSize = std::min(labelSize, std::min(startsSize, endsSize));
    modelResult.signalLabel = new double[modelResult.signalIndexSize];
    for (int i = 0; i < modelResult.signalIndexSize; ++i) {
        modelResult.signalLabel[i] = label[i];
    }
    modelResult.signalStarts = new int64_t[modelResult.signalIndexSize];
    for (int i = 0; i < modelResult.signalIndexSize; ++i) {
        modelResult.signalStarts[i] = (uint32_t) w_starts[i] - 1;
    }
    modelResult.signalEnds = new int64_t[modelResult.signalIndexSize];
    for (int i = 0; i < modelResult.signalIndexSize; ++i) {
        modelResult.signalEnds[i] = (uint32_t) w_ends[i];
    }
}

SNORE_UNUSED  void snore::calculateSPL(SNORE_F64pcm &src, SNORE_SPL &spl) {
    array1D x;
    x.set(src.raw, 1, src.length);
    aweight(x, spl.a_pow, spl.freq, &spl.a_sum);
    cweight(x, spl.c_pow, spl.freq, &spl.c_sum);
    zweight(x, spl.z_pow, spl.freq, &spl.z_sum);
}

SNORE_UNUSED  void SNORE_ModelResult::print() const {
    printf("SNORE_ModelResult {\n");
    printf("\tnoiseStart:%fs\n", noiseStart);
    printf("\tnoiseLength:%fs\n", noiseLength);
    printf("\tsignalStarts:\n");
    printf("\t[");
    for (int64_t i = 0; i < signalIndexSize; ++i) {
        printf("%ld, ", signalStarts[i]);
    }
    printf("]\n");

    printf("\tsignalEnds:\n");
    printf("\t[");
    for (int64_t i = 0; i < signalIndexSize; ++i) {
        printf("%ld, ", signalEnds[i]);
    }
    printf("]\n");

    printf("\tsignalLabel:\n");
    printf("\t[");
    for (int64_t i = 0; i < signalIndexSize; ++i) {
        printf("%.1f, ", signalLabel[i]);
    }
    printf("]\n");

    printf("}\n");
}

void SNORE_ModelResult::clear() {
    delete[] signalStarts;
    delete[] signalEnds;
    delete[] signalLabel;
    signalIndexSize = 0;
    noiseStart = noiseLength = -1;
}

SNORE_ModelResult::~SNORE_ModelResult() {
    clear();
}

SNORE_ModelResult::SNORE_ModelResult() {
    signalStarts = nullptr;
    signalEnds = nullptr;
    signalLabel = nullptr;
}