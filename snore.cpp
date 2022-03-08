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

#include "matlab/bark_feat.h"
#include "matlab/cep_feat.h"
#include "matlab/fmt_feat.h"
#include "matlab/gtcc_feat.h"
#include "matlab/mfcc_feat.h"
#include "matlab/pitch_feat.h"
#include "matlab/pr800_feat.h"
#include "matlab/se_feat.h"
#include "matlab/patient_classifier.h"

#include <cstdio>
#include <cstdlib>
#include <cassert>

#define DEFAULT_PRECISION 16

#define FEAT_MFCC_COLUMN 39

#define FEAT_BARK_COLUMN 17

#define FEAT_CEP_COLUMN 39

#define FEAT_GTCC_COLUMN 20

#ifdef __ANDROID__
#include <android/log.h>
#define LOG_D(tag, ...) __android_log_print(ANDROID_LOG_DEBUG, tag, __VA_ARGS__)
static const char *const TAG = "snore";
#endif

using namespace snore;

using coder::array;

class SNORE_ModelResultImpl : public SNORE_ModelResult {
public:
    SNORE_ModelResultImpl() {
        mSignalStarts = nullptr;
        mSignalEnds = nullptr;
        mSignalLabel = nullptr;
    }

    ~SNORE_ModelResultImpl() override {
        SNORE_ModelResultImpl::clear();
    }

    void print() const override {
        printf("SNORE_ModelResult {\n");
        printf("\tnoiseStart:%fs\n", mNoiseStart);
        printf("\tnoiseLength:%fs\n", mNoiseLength);
        printf("\tsignalStarts:\n");
        printf("\t[");
        for (int64_t i = 0; i < mSignalIndexSize; ++i) {
            printf("%ld, ", mSignalStarts[i]);
        }
        printf("]\n");

        printf("\tsignalEnds:\n");
        printf("\t[");
        for (int64_t i = 0; i < mSignalIndexSize; ++i) {
            printf("%ld, ", mSignalEnds[i]);
        }
        printf("]\n");

        printf("\tsignalLabel:\n");
        printf("\t[");
        for (int64_t i = 0; i < mSignalIndexSize; ++i) {
            printf("%.1f, ", mSignalLabel[i]);
        }
        printf("]\n");

        printf("}\n");
    }

    void clear() override {
        delete[] mSignalStarts;
        delete[] mSignalEnds;
        delete[] mSignalLabel;
        mSignalIndexSize = 0;
        mNoiseStart = mNoiseLength = -1;
    }

    int64_t getSignalIndexSize() override {
        return mSignalIndexSize;
    }

    int64_t getSignalStart(int64_t index) override {
        if (index < 0 || index >= mSignalIndexSize) return -1;
        return mSignalStarts[index];
    }

    int64_t getSignalEnd(int64_t index) override {
        if (index < 0 || index >= mSignalIndexSize) return -1;
        return mSignalEnds[index];
    }

    double getSignalLabel(int64_t index) override {
        if (index < 0 || index >= mSignalIndexSize) return -1;
        return mSignalLabel[index];
    }

    double getNoiseStart() override {
        return mNoiseStart;
    }

    double getNoiseEnd() override {
        return mNoiseLength;
    }

    int64_t *mSignalStarts = nullptr /* 声音起始下标 */;
    int64_t *mSignalEnds = nullptr /* 声音结束下标 */;
    double *mSignalLabel = nullptr /* 分类器检测结果 */;
    int64_t mSignalIndexSize = 0 /* 数据大小 */;
    /* 有声段起始位置和长度（单位：秒） */
    double mNoiseStart = -1;
    double mNoiseLength = -1;
};

class SNORE_PatientModelImpl : public SNORE_PatientModel {
public:
    SNORE_PatientModelImpl() {
        mMFCC.set_size(0, FEAT_MFCC_COLUMN);
        mBARK.set_size(0, FEAT_BARK_COLUMN);
        mCEP.set_size(0, FEAT_CEP_COLUMN);
        mGTCC.set_size(0, FEAT_GTCC_COLUMN);
    }

    ~SNORE_PatientModelImpl() override {
        SNORE_PatientModelImpl::clear();
    }

    void digest(SNORE_F64pcm &src) override {
        double fs = src.fs;
        SnoringRecognition_initialize();
        coder::array<double, 1U> sig;
        sig.set(src.raw, src.length);
        featMFCC(sig, fs);
        featBARK(sig, fs);
        featPitch(sig, fs);
        featCEP(sig, fs);
        featFMT(sig, fs);
        featGTCC(sig, fs);
        featPR800(sig, fs);
        featSE(sig, fs);
        mVersion += 1;
    }

    double getResult() override {
        if (mVersion == mResultVersion) {
            return mResult;
        }
        featAssert();
        mResult = patient_classifier(&mStackData, mMFCC, mBARK, mPitchMean, mPitchMax, mPitchMin, mPitchVar, mCEP,
                                     mFMT1, mFMT2,
                                     mFMT3, mGTCC, mPR800Mean, mPR800Max, mPR800Min, mPR800Var, mSEMean, mSEMax, mSEMin,
                                     mSEVar);
        mResultVersion = mVersion;
        return mResult;
    }

    void clear() override {
        mMFCC.clear();
        mMFCC.set_size(0, FEAT_MFCC_COLUMN);
        mBARK.clear();
        mBARK.set_size(0, FEAT_BARK_COLUMN);
        mPitchMean.clear();
        mPitchMean.set_size(0);
        mPitchMax.clear();
        mPitchMax.set_size(0);
        mPR800Min.clear();
        mPR800Min.set_size(0);
        mPR800Var.clear();
        mPR800Var.set_size(0);
        mCEP.clear();
        mCEP.set_size(0, FEAT_CEP_COLUMN);
        mFMT1.clear();
        mFMT1.set_size(0);
        mFMT2.clear();
        mFMT2.set_size(0);
        mFMT3.clear();
        mFMT3.set_size(0);
        mGTCC.clear();
        mGTCC.set_size(0, FEAT_GTCC_COLUMN);
        mPR800Mean.clear();
        mPR800Mean.set_size(0);
        mPR800Max.clear();
        mPR800Max.set_size(0);
        mPR800Min.clear();
        mPR800Min.set_size(0);
        mPR800Var.clear();
        mPR800Var.set_size(0);
        mSEMean.clear();
        mSEMean.set_size(0);
        mSEMax.clear();
        mSEMax.set_size(0);
        mSEMin.clear();
        mSEMin.set_size(0);
        mSEVar.clear();
        mSEVar.set_size(0);
        mVersion = mResultVersion = 0;
        mResult = 0.0;
    }

private:

    SNORE_UNUSED static void printArray(coder::array<double, 2U> &input) {
        for (int i = 0; i < input.size(0); ++i) {
            for (int j = 0; j < input.size(1); ++j) {
                printf("%.4f ", input.at(i, j));
            }
            printf("\n");
        }
        printf("\n");
        printf("\n");
    }

    SNORE_UNUSED static void printArray(coder::array<double, 1U> &input) {
        for (int i = 0; i < input.size(0); ++i) {
            printf("%.4f ", input.at(i));
        }
        printf("\n");
        printf("\n");
    }

    static void setZeros(coder::array<double, 2U> &input) {
        int size = input.size(0) * input.size(1);
        for (int i = 0; i < size; ++i) {
            input[i] = 0;
        }
    }

    void featAssert() {
        assert(mMFCC.size(1) == FEAT_MFCC_COLUMN);
        assert(mBARK.size(1) == FEAT_BARK_COLUMN);
        assert(mCEP.size(1) == FEAT_CEP_COLUMN);
        assert(mGTCC.size(1) == FEAT_GTCC_COLUMN);
        auto row = mMFCC.size(0);
        assert(mMFCC.size(0) == row);
        assert(mBARK.size(0) == row);
        assert(mPitchMean.size(0) == row);
        assert(mPitchMax.size(0) == row);
        assert(mPitchMin.size(0) == row);
        assert(mPitchVar.size(0) == row);
        assert(mCEP.size(0) == row);
        assert(mFMT1.size(0) == row);
        assert(mFMT2.size(0) == row);
        assert(mFMT3.size(0) == row);
        assert(mGTCC.size(0) == row);
        assert(mPR800Mean.size(0) == row);
        assert(mPR800Max.size(0) == row);
        assert(mPR800Min.size(0) == row);
        assert(mPR800Var.size(0) == row);
        assert(mSEMean.size(0) == row);
        assert(mSEMax.size(0) == row);
        assert(mSEMin.size(0) == row);
        assert(mSEVar.size(0) == row);
    }

    void featMFCC(coder::array<double, 1U> &sig, double fs) {
        coder::array<double, 2U> result;
        mfcc_feat(sig, fs, result);
        int length = result.size(0) * result.size(1);
        int oldRow = mMFCC.size(0), oldCol = mMFCC.size(1);
        int newRow = oldRow + 1, newCol = FEAT_MFCC_COLUMN;
        coder::array<double, 2U> temp = mMFCC;
        mMFCC.clear();
        mMFCC.set_size(newRow, newCol);
        setZeros(mMFCC);
        for (int i = 0; i < oldRow; ++i) {
            for (int j = 0; j < oldCol; ++j) {
                mMFCC.at(i, j) = temp.at(i, j);
            }
        }
        for (int i = 0; i < newCol && i < length; ++i) {
            mMFCC.at(newRow - 1, i) = result[i];
        }
    }

    void featBARK(coder::array<double, 1U> &sig, double fs) {
        double result[FEAT_BARK_COLUMN];
        bark_feat(sig, fs, result);
        int length = FEAT_BARK_COLUMN;
        int oldRow = mBARK.size(0), oldCol = mBARK.size(1);
        int newRow = oldRow + 1, newCol = FEAT_BARK_COLUMN;
        coder::array<double, 2U> temp = mBARK;
        mBARK.clear();
        mBARK.set_size(newRow, newCol);
        setZeros(mBARK);
        for (int i = 0; i < oldRow; ++i) {
            for (int j = 0; j < oldCol; ++j) {
                mBARK.at(i, j) = temp.at(i, j);
            }
        }
        for (int i = 0; i < newCol && i < length; ++i) {
            mBARK.at(newRow - 1, i) = result[i];
        }
    }

    void featPitch(coder::array<double, 1U> &sig, double fs) {
        double mean, max, min, var;
        int oldRow, newRow;
        pitch_feat(sig, fs, &mean, &max, &min, &var);
        oldRow = mPitchMean.size(0);
        newRow = oldRow + 1;
        mPitchMean.set_size(newRow);
        mPitchMean[newRow - 1] = mean;

        oldRow = mPitchMax.size(0);
        newRow = oldRow + 1;
        mPitchMax.set_size(newRow);
        mPitchMax[newRow - 1] = max;

        oldRow = mPitchMin.size(0);
        newRow = oldRow + 1;
        mPitchMin.set_size(newRow);
        mPitchMin[newRow - 1] = min;

        oldRow = mPitchVar.size(0);
        newRow = oldRow + 1;
        mPitchVar.set_size(newRow);
        mPitchVar[newRow - 1] = var;
    }

    void featCEP(coder::array<double, 1U> &sig, double fs) {
        double result[FEAT_CEP_COLUMN];
        int size[2];
        cep_feat(sig, fs, result, size);
        int length = size[0] * size[1];
        int oldRow = mCEP.size(0), oldCol = mCEP.size(1);
        int newRow = oldRow + 1, newCol = FEAT_CEP_COLUMN;
        coder::array<double, 2U> temp = mCEP;
        mCEP.clear();
        mCEP.set_size(newRow, newCol);
        setZeros(mCEP);
        for (int i = 0; i < oldRow; ++i) {
            for (int j = 0; j < oldCol; ++j) {
                mCEP.at(i, j) = temp.at(i, j);
            }
        }
        for (int i = 0; i < newCol && i < length; ++i) {
            mCEP.at(newRow - 1, i) = result[i];
        }
    }

    void featFMT(coder::array<double, 1U> &sig, double fs) {
        double fmt1, fmt2, fmt3;
        int oldRow, newRow;
        fmt_feat(sig, fs, &fmt1, &fmt3, &fmt2);
        oldRow = mFMT1.size(0);
        newRow = oldRow + 1;
        mFMT1.set_size(newRow);
        mFMT1[newRow - 1] = fmt1;

        oldRow = mFMT2.size(0);
        newRow = oldRow + 1;
        mFMT2.set_size(newRow);
        mFMT2[newRow - 1] = fmt2;

        oldRow = mFMT3.size(0);
        newRow = oldRow + 1;
        mFMT3.set_size(newRow);
        mFMT3[newRow - 1] = fmt3;
    }

    void featGTCC(coder::array<double, 1U> &sig, double fs) {
        coder::array<double, 2U> result;
        gtcc_feat(&mStackData, sig, fs, result);
        int length = result.size(0) * result.size(1);
        int oldRow = mGTCC.size(0), oldCol = mGTCC.size(1);
        int newRow = oldRow + 1, newCol = FEAT_GTCC_COLUMN;
        coder::array<double, 2U> temp = mGTCC;
        mGTCC.clear();
        mGTCC.set_size(newRow, newCol);
        setZeros(mGTCC);
        for (int i = 0; i < oldRow; ++i) {
            for (int j = 0; j < oldCol; ++j) {
                mGTCC.at(i, j) = temp.at(i, j);
            }
        }
        for (int i = 0; i < newCol && i < length; ++i) {
            mGTCC.at(newRow - 1, i) = result[i];
        }
    }

    void featPR800(coder::array<double, 1U> &sig, double fs) {
        double mean, max, min, var;
        int oldRow, newRow;
        pr800_feat(sig, fs, &mean, &max, &min, &var);
        oldRow = mPR800Mean.size(0);
        newRow = oldRow + 1;
        mPR800Mean.set_size(newRow);
        mPR800Mean[newRow - 1] = mean;

        oldRow = mPR800Max.size(0);
        newRow = oldRow + 1;
        mPR800Max.set_size(newRow);
        mPR800Max[newRow - 1] = max;

        oldRow = mPR800Min.size(0);
        newRow = oldRow + 1;
        mPR800Min.set_size(newRow);
        mPR800Min[newRow - 1] = min;

        oldRow = mPR800Var.size(0);
        newRow = oldRow + 1;
        mPR800Var.set_size(newRow);
        mPR800Var[newRow - 1] = var;
    }

    void featSE(coder::array<double, 1U> &sig, double fs) {
        double mean, max, min, var;
        int oldRow, newRow;
        se_feat(sig, fs, &mean, &max, &min, &var);
        oldRow = mSEMean.size(0);
        newRow = oldRow + 1;
        mSEMean.set_size(newRow);
        mSEMean[newRow - 1] = mean;

        oldRow = mSEMax.size(0);
        newRow = oldRow + 1;
        mSEMax.set_size(newRow);
        mSEMax[newRow - 1] = max;

        oldRow = mSEMin.size(0);
        newRow = oldRow + 1;
        mSEMin.set_size(newRow);
        mSEMin[newRow - 1] = min;

        oldRow = mSEVar.size(0);
        newRow = oldRow + 1;
        mSEVar.set_size(newRow);
        mSEVar[newRow - 1] = var;
    }

    int64_t mVersion = 0;
    int64_t mResultVersion = 0;
    double mResult = 0.0;
    SnoringRecognitionStackData mStackData{};
    coder::array<double, 2U> mMFCC;
    coder::array<double, 2U> mBARK;
    coder::array<double, 1U> mPitchMean;
    coder::array<double, 1U> mPitchMax;
    coder::array<double, 1U> mPitchMin;
    coder::array<double, 1U> mPitchVar;
    coder::array<double, 2U> mCEP;
    coder::array<double, 1U> mFMT1;
    coder::array<double, 1U> mFMT2;
    coder::array<double, 1U> mFMT3;
    coder::array<double, 2U> mGTCC;
    coder::array<double, 1U> mPR800Mean;
    coder::array<double, 1U> mPR800Max;
    coder::array<double, 1U> mPR800Min;
    coder::array<double, 1U> mPR800Var;
    coder::array<double, 1U> mSEMean;
    coder::array<double, 1U> mSEMax;
    coder::array<double, 1U> mSEMin;
    coder::array<double, 1U> mSEVar;
};

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

SNORE_UNUSED void snore::snoreInitialize() {
    SnoringRecognition_initialize();
}

SNORE_UNUSED void snore::snoreTerminate() {
    SnoringRecognition_terminate();
}

SNORE_UNUSED void snore::generateNoiseProfile(SNORE_I16pcm &src, double start, double duration, const char *filename) {
    sox_init();
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

    sox_quit();
}

SNORE_UNUSED void snore::reduceNoise(SNORE_I16pcm &src, SNORE_I16pcm &dst, const char *filename, double coefficient) {
    sox_init();
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
    sox_quit();
}

SNORE_UNUSED void snore::calculateModelResult(SNORE_F64pcm &pcm, SNORE_ModelResult &modelResult) {
    auto &modelResultImpl = dynamic_cast<SNORE_ModelResultImpl &>(modelResult);
    modelResultImpl.clear();
    snoreInitialize();
    double fs = pcm.fs;
    coder::array<double, 1U> x;
    coder::array<long long, 1U> starts, ends;
    coder::array<double, 1U> label;
    //默认是单声道
    x.set(pcm.raw, pcm.length);

    /**
     * 端点检测
     */
    vad(x, fs, starts, ends);
    /**
     * 有声段检测
     */
    noise_segment(starts, ends, fs, 0.5 * fs, 3 * fs, &modelResultImpl.mNoiseStart,
                  &modelResultImpl.mNoiseLength);
    /**
     * 分类器分类
     */
    classifier(x, fs, starts, ends, label);
    int64_t labelSize = label.size(0), startsSize = starts.size(0), endsSize = starts.size(0);
    modelResultImpl.mSignalIndexSize = std::min(labelSize, std::min(startsSize, endsSize));
    modelResultImpl.mSignalLabel = new double[modelResultImpl.mSignalIndexSize];
    for (int i = 0; i < modelResultImpl.mSignalIndexSize; ++i) {
        modelResultImpl.mSignalLabel[i] = label[i];
    }
    modelResultImpl.mSignalStarts = new int64_t[modelResultImpl.mSignalIndexSize];
    for (int i = 0; i < modelResultImpl.mSignalIndexSize; ++i) {
        modelResultImpl.mSignalStarts[i] = starts[i] - 1;
    }
    modelResultImpl.mSignalEnds = new int64_t[modelResultImpl.mSignalIndexSize];
    for (int i = 0; i < modelResultImpl.mSignalIndexSize; ++i) {
        modelResultImpl.mSignalEnds[i] = ends[i];
    }
}

SNORE_UNUSED void snore::calculateSPL(SNORE_F64pcm &src, SNORE_SPL &spl) {
    coder::array<double, 1U> x;
    x.set(src.raw, src.length);
    snoreInitialize();
    aweight(x, spl.a_pow, spl.freq, &spl.a_sum);
    cweight(x, spl.c_pow, spl.freq, &spl.c_sum);
    zweight(x, spl.z_pow, spl.freq, &spl.z_sum);
}

SNORE_UNUSED SNORE_ModelResult *snore::newModelResult() {
    return new SNORE_ModelResultImpl();
}

SNORE_UNUSED void snore::deleteModelResult(SNORE_ModelResult *ptr) {
    delete ptr;
}

SNORE_UNUSED SNORE_PatientModel *snore::newPatientModel() {
    return new SNORE_PatientModelImpl;
}

SNORE_UNUSED void snore::deletePatientModel(SNORE_PatientModel *ptr) {
    delete ptr;
}