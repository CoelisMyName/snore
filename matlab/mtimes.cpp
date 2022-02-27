//
// File: mtimes.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "mtimes.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &A
//                const ::coder::array<double, 2U> &B
//                ::coder::array<double, 2U> &C
// Return Type  : void
//
namespace coder {
    namespace internal {
        namespace blas {
            void mtimes(const ::coder::array<double, 2U> &A,
                        const ::coder::array<double, 2U> &B, ::coder::array<double, 2U> &C) {
                int inner;
                int mc;
                int nc;
                mc = A.size(0);
                inner = A.size(1);
                nc = B.size(1);
                C.set_size(A.size(0), B.size(1));
                for (int j = 0; j < nc; j++) {
                    int boffset;
                    int coffset;
                    int i;
                    coffset = j * mc;
                    boffset = j * B.size(0);
                    for (i = 0; i < mc; i++) {
                        C[coffset + i] = 0.0;
                    }
                    for (int k = 0; k < inner; k++) {
                        double bkj;
                        int aoffset;
                        aoffset = k * A.size(0);
                        bkj = B[boffset + k];
                        for (i = 0; i < mc; i++) {
                            int b_i;
                            b_i = coffset + i;
                            C[b_i] = C[b_i] + A[aoffset + i] * bkj;
                        }
                    }
                }
            }

//
// Arguments    : const ::coder::array<double, 2U> &B
//                ::coder::array<double, 2U> &C
// Return Type  : void
//
            void mtimes(const ::coder::array<double, 2U> &B, ::coder::array<double, 2U> &C) {
                static const double b_dv[169] = {1.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 1.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 1.515716566510398,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 1.9331820449317627,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 2.2973967099940698,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 2.626527804403767,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 2.9301560515835217,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 3.2140958497160383,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 3.4822022531844965,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 3.7371928188465517,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 3.9810717055349722,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 4.2153691330919,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 0.0,
                                                 4.44128606984584};
                int n;
                n = B.size(1);
                C.set_size(13, B.size(1));
                for (int j = 0; j < n; j++) {
                    int coffset_tmp;
                    coffset_tmp = j * 13;
                    for (int i = 0; i < 13; i++) {
                        double s;
                        s = 0.0;
                        for (int k = 0; k < 13; k++) {
                            s += b_dv[k * 13 + i] * B[coffset_tmp + k];
                        }
                        C[coffset_tmp + i] = s;
                    }
                }
            }

//
// Arguments    : const ::coder::array<double, 2U> &A
//                const ::coder::array<double, 2U> &B
//                double C_data[]
//                int *C_size
// Return Type  : void
//
            void mtimes(const ::coder::array<double, 2U> &A,
                        const ::coder::array<double, 2U> &B, double C_data[], int *C_size) {
                int inner;
                inner = A.size(1);
                *C_size = 16;
                memset(&C_data[0], 0, 16U * sizeof(double));
                for (int k = 0; k < inner; k++) {
                    int aoffset;
                    aoffset = k << 4;
                    for (int i = 0; i < 16; i++) {
                        C_data[i] += A[aoffset + i] * B[k];
                    }
                }
            }

        } // namespace blas
    } // namespace internal
} // namespace coder

//
// File trailer for mtimes.cpp
//
// [EOF]
//
