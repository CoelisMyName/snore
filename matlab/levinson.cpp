//
// File: levinson.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "levinson.h"
#include "callLevinson.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// Arguments    : const ::coder::array<creal_T, 1U> &R
//                creal_T A_data[]
//                int A_size[2]
//                double E_data[]
//                int E_size[2]
// Return Type  : void
//
namespace coder {
    void b_levinson(const ::coder::array<creal_T, 1U> &R, creal_T A_data[],
                    int A_size[2], double E_data[], int E_size[2]) {
        creal_T K_data[13];
        creal_T b_A_data[13];
        int K_size[2];
        int b_A_size[2];
        int N;
        N = 10;
        if ((10 == R.size(0)) || (10 > R.size(0))) {
            N = R.size(0) - 1;
        }
        signal::internal::levinson::callLevinson(R, static_cast<double>(N),
                                                 b_A_data, b_A_size, E_data, E_size,
                                                 K_data, K_size);
        A_size[0] = 1;
        A_size[1] = b_A_size[1];
        N = b_A_size[1];
        if (0 <= N - 1) {
            memcpy(&A_data[0], &b_A_data[0], N * sizeof(creal_T));
        }
    }

//
// Arguments    : const ::coder::array<double, 2U> &R
//                ::coder::array<double, 2U> &A
//                ::coder::array<double, 1U> &E
// Return Type  : void
//
    void levinson(const ::coder::array<double, 2U> &R,
                  ::coder::array<double, 2U> &A, ::coder::array<double, 1U> &E) {
        array<double, 2U> r;
        array<double, 2U> temp_A;
        array<double, 2U> temp_E;
        double temp_a_data[12];
        double temp_auf_data[12];
        int N;
        int i;
        int i1;
        int j;
        int l;
        signed char sizes_idx_0;
        N = 12;
        if (R.size(1) == 1) {
            r.set_size(R.size(0), 1);
            l = R.size(0);
            for (i = 0; i < l; i++) {
                r[i] = R[i];
            }
        } else {
            r.set_size(R.size(0), R.size(1));
            l = R.size(0) * R.size(1);
            for (i = 0; i < l; i++) {
                r[i] = R[i];
            }
        }
        if ((12 == r.size(0)) || (12 > r.size(0))) {
            N = r.size(0) - 1;
        }
        temp_E.set_size(1, r.size(1));
        temp_A.set_size(N, r.size(1));
        if (0 <= N - 1) {
            memset(&temp_a_data[0], 0, N * sizeof(double));
            memset(&temp_auf_data[0], 0, N * sizeof(double));
        }
        i = r.size(1);
        for (int b_i = 0; b_i < i; b_i++) {
            double temp_J;
            temp_J = r[r.size(0) * b_i];
            temp_a_data[0] = -temp_J;
            for (l = 0; l < N; l++) {
                double temp_kprod;
                temp_kprod = 0.0;
                for (j = 0; j < l; j++) {
                    double d;
                    d = temp_a_data[j];
                    temp_auf_data[j] = d;
                    temp_kprod += d * r[(l - j) + r.size(0) * b_i];
                }
                temp_kprod = -(r[(l + r.size(0) * b_i) + 1] + temp_kprod) / temp_J;
                temp_J *= 1.0 - temp_kprod * temp_kprod;
                for (j = 0; j < l; j++) {
                    temp_a_data[j] =
                            temp_auf_data[j] + temp_kprod * temp_auf_data[(l - j) - 1];
                }
                temp_a_data[l] = temp_kprod;
            }
            temp_E[b_i] = temp_J;
            l = temp_A.size(0);
            for (i1 = 0; i1 < l; i1++) {
                temp_A[i1 + temp_A.size(0) * b_i] = temp_a_data[i1];
            }
        }
        if ((temp_A.size(0) != 0) && (temp_A.size(1) != 0)) {
            sizes_idx_0 = static_cast<signed char>(temp_A.size(0));
        } else {
            sizes_idx_0 = 0;
        }
        N = temp_A.size(0) - 1;
        j = temp_A.size(1) - 1;
        l = temp_A.size(0);
        for (i = 0; i <= j; i++) {
            for (i1 = 0; i1 < l; i1++) {
                temp_A[i1 + (N + 1) * i] = temp_A[i1 + temp_A.size(0) * i];
            }
        }
        temp_A.set_size(N + 1, j + 1);
        N = sizes_idx_0;
        j = r.size(1);
        A.set_size(r.size(1), sizes_idx_0 + 1);
        l = r.size(1);
        for (i = 0; i < 1; i++) {
            for (i1 = 0; i1 < l; i1++) {
                A[i1] = 1.0;
            }
        }
        for (i = 0; i < N; i++) {
            for (i1 = 0; i1 < j; i1++) {
                A[i1 + A.size(0) * (i + 1)] = temp_A[i + sizes_idx_0 * i1];
            }
        }
        E.set_size(temp_E.size(1));
        l = temp_E.size(1);
        for (i = 0; i < l; i++) {
            E[i] = temp_E[i];
        }
    }

//
// Arguments    : const ::coder::array<creal_T, 1U> &R
//                creal_T A_data[]
//                int A_size[2]
//                double E_data[]
//                int E_size[2]
// Return Type  : void
//
    void levinson(const ::coder::array<creal_T, 1U> &R, creal_T A_data[],
                  int A_size[2], double E_data[], int E_size[2]) {
        creal_T K_data[13];
        int K_size[2];
        int N;
        N = 12;
        if ((12 == R.size(0)) || (12 > R.size(0))) {
            N = R.size(0) - 1;
        }
        signal::internal::levinson::callLevinson(R, static_cast<double>(N), A_data,
                                                 A_size, E_data, E_size, K_data,
                                                 K_size);
    }

} // namespace coder

//
// File trailer for levinson.cpp
//
// [EOF]
//
