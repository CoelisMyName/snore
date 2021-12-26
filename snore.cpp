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
#include "matlab/SnoringRecognition_terminate.h"
#include "matlab/SnoringRecognition_data.h"

#include <cstdio>
#include <cstdlib>
#include <cassert>

#ifdef ANDROID
#include <android/log.h>
#define LOG_D(tag, ...) __android_log_print(ANDROID_LOG_DEBUG, tag, __VA_ARGS__)
static const char *const TAG = "model";
#endif

using namespace snore;

using coder::array;

typedef array<double, 2U> array1D;

void snore::snoreInitial() {
    if (!isInitialized_SnoringRecognition) {
        SnoringRecognition_initialize();
    }
}

void snore::snoreDestroy() {
    if (isInitialized_SnoringRecognition) {
        SnoringRecognition_terminate();
    }
}

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

sox_signalinfo_t getSignalInfo(const I16pcm &src) {
    sox_signalinfo_t info = {src.fs, src.channel, DEFAULT_PRECISION, src.length, nullptr};
    return info;
}

sox_encodinginfo_t getEncodingInfo() {
    sox_encodinginfo_t info = {SOX_ENCODING_SIGN2, DEFAULT_PRECISION, 1 / 0.0, sox_option_no, sox_option_no,
                               sox_option_no, sox_false};
    return info;
}

void snore::generateNoiseProfile(I16pcm &src, double start, double duration, const char *filename) {
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

void snore::reduceNoise(I16pcm &src, I16pcm &dst, const char *filename, double coefficient) {
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

void snore::calculateModelResult(F64pcm &pcm, ModelResult &modelResult) {
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
    noise_segment(w_starts, w_ends, pcm.fs, 0.5 * pcm.fs, 3 * pcm.fs, &modelResult.n_start, &modelResult.n_length);
    /**
     * 分类器分类
     */
#ifdef ANDROID
    LOG_D(TAG, "w_starts %d, w_ends %d", w_starts.size(1), w_ends.size(1));
    for(int i = 0; i < w_starts.size(1); ++i) {
        LOG_D(TAG, "start %.1f, end %.1f", w_starts[i], w_ends[i]);
    }
#endif
    classifier(x, w_starts, w_ends, pcm.fs, label);

    /**
     * 复制到结果
     */
    modelResult.l_size = label.size(1);
    modelResult.label = new double[label.size(1)];
    for (int i = 0; i < label.size(1); ++i) {
        modelResult.label[i] = label[i];
    }

    modelResult.s_size = w_starts.size(1);
    modelResult.starts = new uint32_t[w_starts.size(1)];
    for (int i = 0; i < w_starts.size(1); ++i) {
        modelResult.starts[i] = (uint32_t) w_starts[i];
    }

    modelResult.e_size = w_ends.size(1);
    modelResult.ends = new uint32_t[w_ends.size(1)];
    for (int i = 0; i < w_ends.size(1); ++i) {
        modelResult.ends[i] = (uint32_t) w_ends[i];
    }
}

void snore::calculateSPL(F64pcm &src, SPL &spl) {
    array1D x;
    x.set(src.raw, 1, src.length);
    aweight(x, spl.a_pow, spl.freq, &spl.a_sum);
    cweight(x, spl.c_pow, spl.freq, &spl.c_sum);
    zweight(x, spl.z_pow, spl.freq, &spl.z_sum);
}

void ModelResult::print() const {
    printf("ModelResult {\n");
    printf("\tn_start:%fs\n", n_start);
    printf("\tn_length:%fs\n", n_length);

    printf("\tstarts:\n");
    printf("\t[");
    for (int i = 0; i < s_size; ++i) {
        printf("%d, ", starts[i]);
    }
    printf("]\n");

    printf("\tends:\n");
    printf("\t[");
    for (int i = 0; i < e_size; ++i) {
        printf("%d, ", ends[i]);
    }
    printf("]\n");

    printf("\tlabel:\n");
    printf("\t[");
    for (int i = 0; i < l_size; ++i) {
        printf("%.1f, ", label[i]);
    }
    printf("]\n");

    printf("}\n");
}

ModelResult::~ModelResult() {
    delete[] starts;
    delete[] ends;
    delete[] label;
}

ModelResult::ModelResult() {
    starts = nullptr;
    ends = nullptr;
    label = nullptr;
}

bool snore::convert(I16pcm &src, F64pcm &dst) {
    if (src.raw == nullptr || src.length == 0) return false;
    dst.fs = src.fs;
    dst.length = src.length;
    dst.channel = src.channel;
    dst.raw = (double *) malloc(sizeof(double) * src.length);
    for (int i = 0; i < dst.length; ++i) {
        dst.raw[i] = src.raw[i] / 32768.0;
    }
    return true;
}

bool snore::convert(F64pcm &src, I16pcm &dst) {
    if (src.raw == nullptr || src.length == 0) return false;
    dst.fs = src.fs;
    dst.length = src.length;
    dst.channel = src.channel;
    dst.raw = (int16_t *) malloc(sizeof(int16_t) * src.length);
    for (int i = 0; i < dst.length; ++i) {
        dst.raw[i] = (int16_t) (src.raw[i] * 32768);
    }
    return true;
}