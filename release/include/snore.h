#ifndef SNORING_RECOGNITION_SNOR_H
#define SNORING_RECOGNITION_SNOR_H

#include <cstdint>

namespace snore {

#define DEFAULT_PRECISION 16

/**
 * PCM结构体
 */
    typedef struct I16pcm {
        int16_t *raw /* 数据 */;
        uint32_t length /* 数据长度 */;
        uint32_t channel; /* 通道数 */
        double fs /* 采样率 */;
    } I16pcm;

    typedef struct F64pcm {
        double *raw; /* 归一化数据 */;
        uint32_t length /* 数据长度 */;
        uint32_t channel; /* 通道数 */
        double fs /* 采样率 */;
    } F64pcm;

/**
 * SPL结构体，存储声压级测量数据
 */
    typedef struct SPL {
        double a_sum /* A计权总和 */;
        double c_sum /* C计权总和 */;
        double z_sum /* Z计权总和 */;
        double freq[8] /* 中心频率 */;
        double a_pow[8] /* A计权 */;
        double c_pow[8] /* C计权 */;
        double z_pow[8] /* Z计权 */;
    } SPL;

/**
 * 模型返回结果
 */
    class ModelResult {
    public:
        ModelResult();

        ~ModelResult();

        void print() const;

        uint32_t *starts = nullptr /* 声音起始下标 */, *ends = nullptr /* 声音结束下标 */;
        double *label = nullptr /* 分类器检测结果 */;
        uint32_t s_size = 0, e_size = 0, l_size = 0; /* 数据大小 */
        double n_start = -1, n_length = -1; /* 有声段起始位置和长度（单位：秒） */
    };

/**
 * 模型入口函数
 * @param src 输入音频数据
 * @param modelResult 输出模型运算结果
 */
    extern void calculateModelResult(F64pcm &src, ModelResult &modelResult);

/**
 * 生成噪声特征文件
 * @param src 输入音频数据
 * @param start 裁剪起始位置（单位：秒）
 * @param duration 裁剪长度（单位：秒）
 * @param filename noiseprof输出文件路径
 */
    extern void generateNoiseProfile(I16pcm &src, double start, double duration, const char *filename);

/**
 * 降噪
 * @param src 输入音频数据
 * @param dst 输出音频数据
 * @param filename 噪声文件名
 * @param coefficient 降噪系数
 */
    extern void reduceNoise(I16pcm &src, I16pcm &dst, const char *filename, double coefficient);

/**
 * 计算声压级，只支持44.1k
 * @param src 输入音频数据
 * @param spl 输出声压级
 */
    extern void calculateSPL(F64pcm &src, SPL &spl);
}

#endif