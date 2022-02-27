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
        virtual ~SNORE_ModelResult() = default;

        virtual SNORE_UNUSED void print() const = 0;

        virtual void clear() = 0;

        virtual SNORE_UNUSED int64_t getSignalIndexSize() = 0;

        virtual SNORE_UNUSED int64_t getSignalStart(int64_t index) = 0;

        virtual SNORE_UNUSED int64_t getSignalEnd(int64_t index) = 0;

        virtual SNORE_UNUSED double getSignalLabel(int64_t index) = 0;

        virtual SNORE_UNUSED double getNoiseStart() = 0;

        virtual SNORE_UNUSED double getNoiseEnd() = 0;
    };

    class SNORE_PatientModel {
    public:
        virtual ~SNORE_PatientModel() = default;

        virtual void digest(SNORE_F64pcm &src) = 0;

        virtual double getResult() = 0;
    };

    SNORE_UNUSED extern SNORE_ModelResult *newModelResult();

    SNORE_UNUSED extern void deleteModelResult(SNORE_ModelResult *ptr);

    SNORE_UNUSED extern SNORE_PatientModel *newPatientModel();

    SNORE_UNUSED extern void deletePatientModel(SNORE_PatientModel *ptr);

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