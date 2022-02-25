#ifndef SNORING_RECOGNITION_SNOR_H
#define SNORING_RECOGNITION_SNOR_H

#include <cstdint>

namespace snore {

#define SNORE_UNUSED __attribute__((unused))

    /**
     * PCM结构体
     */
    typedef struct {
        int16_t *raw /* 数据 */;
        int64_t length /* 数据长度 */;
        int32_t channel /* 通道数 */;
        double fs /* 采样率 */;
    } SNORE_I16pcm;

    typedef struct {
        double *raw; /* 归一化数据 */;
        int64_t length /* 数据长度 */;
        int32_t channel; /* 通道数 */
        double fs /* 采样率 */;
    } SNORE_F64pcm;

    /**
     * SNORE_SPL结构体，存储声压级测量数据
     */
    typedef struct {
        double a_sum /* A计权总和 */;
        double c_sum /* C计权总和 */;
        double z_sum /* Z计权总和 */;
        double freq[8] /* 中心频率 */;
        double a_pow[8] /* A计权 */;
        double c_pow[8] /* C计权 */;
        double z_pow[8] /* Z计权 */;
    } SNORE_SPL;

    /**
     * 模型返回结果
     */
    class SNORE_ModelResult {
    public:
        SNORE_ModelResult();

        ~SNORE_ModelResult();

        SNORE_UNUSED void print() const;

        void clear();

        int64_t *signalStarts = nullptr /* 声音起始下标 */, *signalEnds = nullptr /* 声音结束下标 */;
        double *signalLabel = nullptr /* 分类器检测结果 */;
        int64_t signalIndexSize = 0; /* 数据大小 */
        double noiseStart = -1, noiseLength = -1; /* 有声段起始位置和长度（单位：秒） */
    };

    /**
     * 模型入口函数
     * @param src 输入音频数据
     * @param modelResult 输出模型运算结果
     */
    SNORE_UNUSED extern void calculateModelResult(SNORE_F64pcm &src, SNORE_ModelResult &modelResult);

    /**
     * 生成噪声特征文件
     * @param src 输入音频数据
     * @param start 裁剪起始位置（单位：秒）
     * @param duration 裁剪长度（单位：秒）
     * @param filename noiseprof输出文件路径
     */
    SNORE_UNUSED extern void
    generateNoiseProfile(SNORE_I16pcm &src, double start, double duration, const char *filename);

    /**
     * 降噪
     * @param src 输入音频数据
     * @param dst 输出音频数据
     * @param filename 噪声文件名
     * @param coefficient 降噪系数
     */
    SNORE_UNUSED extern void
    reduceNoise(SNORE_I16pcm &src, SNORE_I16pcm &dst, const char *filename, double coefficient);

    /**
     * 计算声压级，只支持44.1k
     * @param src 输入音频数据
     * @param spl 输出声压级
     */
    SNORE_UNUSED extern void calculateSPL(SNORE_F64pcm &src, SNORE_SPL &spl);
}

#endif