#include "median_filter.h"
#include "quickselect.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"

void median_filter(const coder::array<double, 1U> &array,
                   coder::array<double, 1U> &output)
{
    double temp[10];
    double b;
    double m;
    int a__3;
    int i;
    int ilast;
    int k;
    output.set_size(array.size(0));
    i = array.size(0);
    for (int b_i = 0; b_i < i; b_i++) {
        for (int j = 0; j < 10; j++) {
            int b_index;
            b_index = (b_i + j) - 4;
            if (b_index < 1) {
                temp[j] = 0.0;
            } else if (b_index > array.size(0)) {
                temp[j] = 0.0;
            } else {
                temp[j] = array[b_index - 1];
            }
        }
        k = 0;
        int exitg1;
        do {
            exitg1 = 0;
            if (k < 10) {
                if (rtIsNaN(temp[k])) {
                    output[b_i] = rtNaN;
                    exitg1 = 1;
                } else {
                    k++;
                }
            } else {
                coder::internal::quickselect(temp, 6, 10, &m, &k, &ilast);
                output[b_i] = m;
                if (5 < k) {
                    coder::internal::quickselect(temp, 5, ilast - 1, &b, &k,
                                                 &a__3);
                    if (((m < 0.0) != (b < 0.0)) || rtIsInf(m)) {
                        output[b_i] = (m + b) / 2.0;
                    } else {
                        output[b_i] = m + (b - m) / 2.0;
                    }
                }
                exitg1 = 1;
            }
        } while (exitg1 == 0);
    }
}
