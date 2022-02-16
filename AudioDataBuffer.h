#ifndef SNORE_AUDIODATABUFFER_H
#define SNORE_AUDIODATABUFFER_H

#include <cstdint>

template<typename T>
class Queue {
public:
    explicit Queue(int32_t capacity = 10) {
        if (capacity < 0) {
            capacity = 0;
        }
        m_capacity = capacity + 1;
        m_array = new T[m_capacity];
    }

    virtual ~Queue() {
        delete[] m_array;
    }

    bool push(T src) {
        if (full()) return false;
        m_array[m_rear] = src;
        m_rear = (m_rear + 1) % m_capacity;
        return true;
    }

    bool pop(T &dst) {
        if (empty()) return false;
        dst = m_array[m_head];
        m_head = (m_head + 1) % m_capacity;
        return true;
    }

    bool reallocate(int32_t capacity) {
        int32_t size = Queue::size();
        if (capacity < size) return false;
        T *array = new T[capacity + 1];
        for (int32_t i = 0, j = m_head; j != m_rear; i = (i + 1) % (capacity + 1), j = (j + 1) % m_capacity) {
            array[i] = m_array[j];
        }
        m_head = 0;
        m_rear = size;
        delete[] m_array;
        m_array = array;
        m_capacity = capacity + 1;
    }

    int32_t capacity() {
        return m_capacity - 1;
    }

    int32_t size() {
        return (m_rear - m_head + m_capacity) % m_capacity;
    }

    bool empty() {
        return m_head == m_rear;
    }

    bool full() {
        return m_head == (m_rear + 1) % m_capacity;
    }

    void clear() {
        m_head = m_rear = 0;
    }

private:
    T *m_array;
    int32_t m_capacity;
    int32_t m_head = 0;
    int32_t m_rear = 0;
};

template<typename T>
class AudioDataBuffer {
public:
    AudioDataBuffer(int32_t sample_rate, int32_t frame, int32_t overlap);

    AudioDataBuffer(int32_t sample_rate, int32_t capacity, int32_t frame, int32_t overlap);

    virtual ~AudioDataBuffer();

    int32_t getFrameSize();

    int32_t getOverlap();

    int32_t size();

    int32_t capacity();

    /**
     * 写入数据
     * @param src 数据指针
     * @param size 数据长度
     * @return 数据写入大小
     */
    int32_t put(int64_t timestamp, T *src, int32_t size);

    /**
     * 读一帧数据
     * @param dst 存放数组指针
     * @param capacity 数组容量
     * @return 若容量不足返回 -1，若未有一帧数据则返回 0，若读到数据则返回帧大小
     */
    int32_t next(T *dst, int32_t capacity, int64_t &timestamp);

    bool ready();

    bool empty();

    bool full();

    void clear();

private:
    T *m_buffer;
    Queue<int64_t> m_timestamp;
    int32_t m_sample_rate;
    int64_t m_sample_count = 0;
    int32_t m_capacity;
    int32_t m_frame;
    int32_t m_overlap;
    int32_t m_head = 0;
    int32_t m_rear = 0;
};

#include "AudioDataBufferImpl.h"

#endif