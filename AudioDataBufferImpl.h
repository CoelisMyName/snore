#ifndef SNORE_AUDIODATABUFFERIMPL_H
#define SNORE_AUDIODATABUFFERIMPL_H

#include <cassert>
#include <cstring>
#include <algorithm>
#include "AudioDataBuffer.h"

template<typename T>
AudioDataBuffer<T>::AudioDataBuffer(int32_t sample_rate, int32_t frame, int32_t overlap) : m_timestamp(4) {
    m_sample_rate = sample_rate;
    frame = frame <= 0 ? 1 : frame;
    overlap = overlap < 0 ? 0 : overlap;
    overlap = overlap >= frame ? frame - 1 : overlap;
    int32_t capacity = 3 * (frame - overlap) + overlap;
    m_frame = frame;
    m_overlap = overlap;
    m_capacity = capacity + 1;
    m_buffer = new T[m_capacity];
    m_head = m_rear = 0;
}

template<typename T>
AudioDataBuffer<T>::AudioDataBuffer(int32_t sample_rate, int32_t capacity, int32_t frame, int32_t overlap) {
    m_sample_rate = sample_rate;
    frame = frame <= 0 ? 1 : frame;
    overlap = overlap < 0 ? 0 : overlap;
    capacity = capacity <= 0 ? 1 : capacity;
    capacity = capacity <= frame ? frame + 1 : capacity;
    overlap = overlap >= frame ? frame - 1 : overlap;
    m_timestamp.reallocate((capacity - overlap) / (frame - overlap) + 1);
    m_frame = frame;
    m_overlap = overlap;
    m_capacity = capacity + 1;
    m_buffer = new T[m_capacity];
    m_head = m_rear = 0;
}

template<typename T>
AudioDataBuffer<T>::~AudioDataBuffer() {
    delete[] m_buffer;
}

template<typename T>
int32_t AudioDataBuffer<T>::getFrameSize() {
    return m_frame;
}

template<typename T>
int32_t AudioDataBuffer<T>::getOverlap() {
    return m_overlap;
}

template<typename T>
int32_t AudioDataBuffer<T>::size() {
    return (m_rear - m_head + m_capacity) % m_capacity;
}

template<typename T>
int32_t AudioDataBuffer<T>::capacity() {
    return m_capacity - 1;
}

template<typename T>
int32_t AudioDataBuffer<T>::put(int64_t timestamp, T *src, int32_t size) {
    if (full()) return 0;
    int32_t head = m_rear;
    int32_t empty = (m_head - m_rear + m_capacity - 1) % m_capacity;
    int32_t write = std::min(empty, size);
    int32_t rear = (head + write) % m_capacity;
    if (rear >= head) {
        memcpy(&m_buffer[head], src, write * sizeof(T));
    } else {
        memcpy(&m_buffer[head], src, (m_capacity - head) * sizeof(T));
        memcpy(m_buffer, src, (write - m_capacity + head) * sizeof(T));
    }
    auto skew = (int32_t) (m_sample_count % (m_frame - m_overlap));
    skew = ((m_frame - m_overlap) - skew) % (m_frame - m_overlap);
    double interval = 1000.0 / m_sample_rate;
    for (int32_t i = skew; i < size; i += (m_frame - m_overlap)) {
        int64_t t = timestamp + (int64_t) (i * interval);
        m_timestamp.push(t);
    }
    m_rear = rear;
    m_sample_count += write;
    return write;
}

template<typename T>
int32_t AudioDataBuffer<T>::next(T *dst, int32_t capacity, int64_t &timestamp) {
    if (capacity < m_frame) return -1;
    if (!ready()) return 0;
    int32_t front = m_head;
    int32_t rear = (m_head + m_frame) % m_capacity;
    if (rear >= front) {
        memcpy(dst, &m_buffer[front], m_frame * sizeof(T));
    } else {
        memcpy(dst, &m_buffer[front], (m_capacity - front) * sizeof(T));
        memcpy(&dst[m_capacity - front], m_buffer, rear * sizeof(T));
    }
    m_head = (m_head + m_frame - m_overlap) % m_capacity;
    assert(m_timestamp.pop(timestamp));
    return m_frame;
}

template<typename T>
bool AudioDataBuffer<T>::ready() {
    return size() >= m_frame;
}

template<typename T>
bool AudioDataBuffer<T>::empty() {
    return m_head == m_rear;
}

template<typename T>
bool AudioDataBuffer<T>::full() {
    return m_head == (m_rear + 1) % m_capacity;
}

template<typename T>
void AudioDataBuffer<T>::clear() {
    m_head = m_rear = 0;
    m_sample_count = 0;
    m_timestamp.clear();
}

#endif