#include "vad_wave.h"
#include "eml_i64relops.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "mylock.h"
#include <math.h>

void vad_wave(const coder::array<double, 1U> &array,
              const coder::array<long long, 1U> &starts,
              const coder::array<long long, 1U> &ends,
              coder::array<long long, 1U> &ostarts,
              coder::array<long long, 1U> &oends)
{
    coder::array<long long, 1U> b_ostarts;
    long long k;
    long long qY;
    int bufferHeight;
    int u0;
    int u1;
    u0 = starts.size(0);
    u1 = ends.size(0);
    if (u0 < u1) {
        bufferHeight = u0;
    } else {
        bufferHeight = u1;
    }
    ostarts.set_size(bufferHeight);
    oends.set_size(bufferHeight);
    for (u1 = 0; u1 < bufferHeight; u1++) {
        ostarts[u1] = 0LL;
        oends[u1] = 0LL;
    }
    k = 1LL;
    for (int i = 0; i < bufferHeight; i++) {
        double count;
        long long lowb;
        long long q0;
        int b_i;
        int islow;
        if (coder::eml_i64relops(k, static_cast<double>(oends.size(0)))) {
            u1 = ostarts.size(0);
            ostarts.set_size(ostarts.size(0) + static_cast<int>(k));
            u0 = static_cast<int>(k);
            for (b_i = 0; b_i < u0; b_i++) {
                ostarts[u1 + b_i] = 0LL;
            }
            u1 = oends.size(0);
            oends.set_size(oends.size(0) + static_cast<int>(k));
            u0 = static_cast<int>(k);
            for (b_i = 0; b_i < u0; b_i++) {
                oends[u1 + b_i] = 0LL;
            }
        }
        ostarts[static_cast<int>(k) - 1] = starts[i];
        islow = 0;
        count = 0.0;
        lowb = -1LL;
        q0 = starts[i];
        if (q0 > 9223372036854775806LL) {
            qY = MAX_int64_T;
        } else {
            qY = q0 + 1LL;
        }
        for (long long j = qY; j <= ends[i]; j++) {
            double d;
            boolean_T guard1 = false;
            if (j < -9223372036854775807LL) {
                qY = MIN_int64_T;
            } else {
                qY = j - 1LL;
            }
            d = array[static_cast<int>(j) - 1];
            if (d - array[static_cast<int>(qY) - 1] < -0.01) {
                islow = 1;
            }
            guard1 = false;
            if (islow == 1) {
                if (j < -9223372036854775807LL) {
                    qY = MIN_int64_T;
                } else {
                    qY = j - 1LL;
                }
                if (fabs(d - array[static_cast<int>(qY) - 1]) <= 0.01) {
                    count++;
                    if (lowb == -1LL) {
                        lowb = j;
                    }
                } else {
                    guard1 = true;
                }
            } else {
                guard1 = true;
            }
            if (guard1 && (islow == 1)) {
                if (j < -9223372036854775807LL) {
                    qY = MIN_int64_T;
                } else {
                    qY = j - 1LL;
                }
                if (d < array[static_cast<int>(qY) - 1]) {
                    if (j > 9223372036854775806LL) {
                        qY = MAX_int64_T;
                    } else {
                        qY = j + 1LL;
                    }
                    if (qY < ends[i]) {
                        if (j > 9223372036854775806LL) {
                            qY = MAX_int64_T;
                        } else {
                            qY = j + 1LL;
                        }
                        if (array[static_cast<int>(qY) - 1] - d <= 0.01) {
                            lowb = j;
                        }
                    }
                } else {
                    if (count >= 3.0) {
                        if (coder::eml_i64relops(
                                k, static_cast<double>(oends.size(0)))) {
                            u1 = ostarts.size(0);
                            ostarts.set_size(ostarts.size(0) +
                                             static_cast<int>(k));
                            u0 = static_cast<int>(k);
                            for (b_i = 0; b_i < u0; b_i++) {
                                ostarts[u1 + b_i] = 0LL;
                            }
                            u1 = oends.size(0);
                            oends.set_size(oends.size(0) + static_cast<int>(k));
                            u0 = static_cast<int>(k);
                            for (b_i = 0; b_i < u0; b_i++) {
                                oends[u1 + b_i] = 0LL;
                            }
                        }
                        oends[static_cast<int>(k) - 1] = lowb;
                        if (k > 9223372036854775806LL) {
                            qY = MAX_int64_T;
                        } else {
                            qY = k + 1LL;
                        }
                        k = qY;
                        if (coder::eml_i64relops(
                                qY, static_cast<double>(oends.size(0)))) {
                            u1 = ostarts.size(0);
                            ostarts.set_size(ostarts.size(0) +
                                             static_cast<int>(qY));
                            u0 = static_cast<int>(qY);
                            for (b_i = 0; b_i < u0; b_i++) {
                                ostarts[u1 + b_i] = 0LL;
                            }
                            u1 = oends.size(0);
                            oends.set_size(oends.size(0) +
                                           static_cast<int>(qY));
                            u0 = static_cast<int>(qY);
                            for (b_i = 0; b_i < u0; b_i++) {
                                oends[u1 + b_i] = 0LL;
                            }
                        }
                        if (j < -9223372036854775807LL) {
                            q0 = MIN_int64_T;
                        } else {
                            q0 = j - 1LL;
                        }
                        ostarts[static_cast<int>(qY) - 1] = q0;
                        islow = 0;
                        lowb = -1LL;
                    }
                    count = 0.0;
                }
            }
        }
        if (coder::eml_i64relops(k, static_cast<double>(oends.size(0)))) {
            u1 = ostarts.size(0);
            ostarts.set_size(ostarts.size(0) + static_cast<int>(k));
            u0 = static_cast<int>(k);
            for (b_i = 0; b_i < u0; b_i++) {
                ostarts[u1 + b_i] = 0LL;
            }
            u1 = oends.size(0);
            oends.set_size(oends.size(0) + static_cast<int>(k));
            u0 = static_cast<int>(k);
            for (b_i = 0; b_i < u0; b_i++) {
                oends[u1 + b_i] = 0LL;
            }
        }
        oends[static_cast<int>(k) - 1] = ends[i];
        if (k > 9223372036854775806LL) {
            qY = MAX_int64_T;
        } else {
            qY = k + 1LL;
        }
        k = qY;
    }
    if (k < -9223372036854775807LL) {
        qY = MIN_int64_T;
    } else {
        qY = k - 1LL;
    }
    if (1LL > qY) {
        u0 = 0;
    } else {
        u0 = static_cast<int>(qY);
    }
    b_ostarts.set_size(u0);
    for (u1 = 0; u1 < u0; u1++) {
        b_ostarts[u1] = ostarts[u1];
    }
    ostarts.set_size(b_ostarts.size(0));
    u0 = b_ostarts.size(0);
    for (u1 = 0; u1 < u0; u1++) {
        ostarts[u1] = b_ostarts[u1];
    }
    if (k < -9223372036854775807LL) {
        qY = MIN_int64_T;
    } else {
        qY = k - 1LL;
    }
    if (1LL > qY) {
        u0 = 0;
    } else {
        u0 = static_cast<int>(qY);
    }
    b_ostarts.set_size(u0);
    for (u1 = 0; u1 < u0; u1++) {
        b_ostarts[u1] = oends[u1];
    }
    oends.set_size(b_ostarts.size(0));
    u0 = b_ostarts.size(0);
    for (u1 = 0; u1 < u0; u1++) {
        oends[u1] = b_ostarts[u1];
    }
}
