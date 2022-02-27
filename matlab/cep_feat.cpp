//
// File: cep_feat.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "cep_feat.h"
#include "deltas.h"
#include "mean.h"
#include "rastaplp.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// function cep = cep_feat(sig, fs)
//
// plp特征+一阶差分+二阶差分合集39阶特征
//
// Arguments    : const coder::array<double, 1U> &sig
//                double fs
//                double cep_data[]
//                int cep_size[2]
// Return Type  : void
//
void cep_feat(const coder::array<double, 1U> &sig, double fs, double cep_data[],
              int cep_size[2]) {
    coder::array<double, 2U> a__1;
    coder::array<double, 2U> b_cep2;
    coder::array<double, 2U> cep2;
    coder::array<double, 2U> ddel;
    coder::array<double, 2U> del;
    coder::array<double, 2U> r;
    double tmp_data[39];
    int c_input_sizes_idx_0;
    int d_input_sizes_idx_0;
    int i;
    int i1;
    int loop_ub;
    signed char b_input_sizes_idx_0;
    signed char input_sizes_idx_0;
    signed char sizes_idx_0;
    boolean_T empty_non_axis_sizes;
    // 'cep_feat:3' [cep2, ~] = rastaplp(sig, fs, 0, 12);
    rastaplp(sig, fs, cep2, a__1);
    // 'cep_feat:4' del = deltas(cep2);
    deltas(cep2, del);
    // 'cep_feat:5' ddel = deltas(deltas(cep2, 5), 5);
    b_deltas(cep2, r);
    b_deltas(r, ddel);
    // 'cep_feat:6' cepDpDD = [cep2; del; ddel];
    empty_non_axis_sizes = (cep2.size(1) == 0);
    if (empty_non_axis_sizes || (cep2.size(1) != 0)) {
        input_sizes_idx_0 = 13;
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || (del.size(1) != 0)) {
        b_input_sizes_idx_0 = 13;
    } else {
        b_input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || (ddel.size(1) != 0)) {
        sizes_idx_0 = 13;
    } else {
        sizes_idx_0 = 0;
    }
    // 'cep_feat:7' cep1 = mean(cepDpDD, 2);
    // 取均值
    // 'cep_feat:8' cep = cep1';
    c_input_sizes_idx_0 = input_sizes_idx_0;
    d_input_sizes_idx_0 = b_input_sizes_idx_0;
    b_cep2.set_size((input_sizes_idx_0 + b_input_sizes_idx_0) + sizes_idx_0,
                    cep2.size(1));
    loop_ub = cep2.size(1);
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < c_input_sizes_idx_0; i1++) {
            b_cep2[i1 + b_cep2.size(0) * i] = cep2[i1 + 13 * i];
        }
    }
    loop_ub = cep2.size(1);
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < d_input_sizes_idx_0; i1++) {
            b_cep2[(i1 + input_sizes_idx_0) + b_cep2.size(0) * i] =
                    del[i1 + 13 * i];
        }
    }
    loop_ub = cep2.size(1);
    for (i = 0; i < loop_ub; i++) {
        c_input_sizes_idx_0 = sizes_idx_0;
        for (i1 = 0; i1 < c_input_sizes_idx_0; i1++) {
            b_cep2[((i1 + input_sizes_idx_0) + b_input_sizes_idx_0) +
                   b_cep2.size(0) * i] = ddel[i1 + 13 * i];
        }
    }
    coder::mean(b_cep2, tmp_data, &c_input_sizes_idx_0);
    cep_size[0] = 1;
    cep_size[1] = c_input_sizes_idx_0;
    if (0 <= c_input_sizes_idx_0 - 1) {
        memcpy(&cep_data[0], &tmp_data[0],
               c_input_sizes_idx_0 * sizeof(double));
    }
}

//
// File trailer for cep_feat.cpp
//
// [EOF]
//
