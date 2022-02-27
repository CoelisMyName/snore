//
// File: permute.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "permute.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 3U> &a
//                ::coder::array<double, 3U> &b
// Return Type  : void
//
namespace coder {
    void b_permute(const ::coder::array<double, 3U> &a,
                   ::coder::array<double, 3U> &b) {
        int k;
        int plast;
        boolean_T b_b;
        b_b = true;
        if (a.size(2) != 0) {
            boolean_T exitg1;
            plast = 0;
            k = 0;
            exitg1 = false;
            while ((!exitg1) && (k < 3)) {
                if (a.size(2 - k) != 1) {
                    if (plast > 3 - k) {
                        b_b = false;
                        exitg1 = true;
                    } else {
                        plast = 3 - k;
                        k++;
                    }
                } else {
                    k++;
                }
            }
        }
        if (b_b) {
            b.set_size(a.size(2), 32, 130);
            plast = (a.size(2) << 5) * 130;
            for (int i = 0; i < plast; i++) {
                b[i] = a[i];
            }
        } else {
            int i;
            b.set_size(a.size(2), 32, 130);
            i = a.size(2);
            for (k = 0; k < i; k++) {
                for (plast = 0; plast < 32; plast++) {
                    for (int b_k = 0; b_k < 130; b_k++) {
                        b[(k + b.size(0) * plast) + b.size(0) * 32 * b_k] =
                                a[(b_k + 130 * plast) + 4160 * k];
                    }
                }
            }
        }
    }

//
// Arguments    : const ::coder::array<double, 2U> &a
//                ::coder::array<double, 2U> &b
// Return Type  : void
//
    void b_permute(const ::coder::array<double, 2U> &a,
                   ::coder::array<double, 2U> &b) {
        int loop_ub;
        b.set_size(32, a.size(0));
        loop_ub = a.size(0);
        for (int i = 0; i < loop_ub; i++) {
            for (int i1 = 0; i1 < 32; i1++) {
                b[i1 + 32 * i] = a[i + a.size(0) * i1];
            }
        }
    }

//
// Arguments    : const ::coder::array<double, 2U> &a
//                ::coder::array<double, 2U> &b
// Return Type  : void
//
    void permute(const ::coder::array<double, 2U> &a, ::coder::array<double, 2U> &b) {
        static const signed char b_iv[3] = {2, 1, 3};
        int i;
        int k;
        int plast;
        boolean_T b_b;
        b_b = true;
        if (a.size(1) != 0) {
            boolean_T exitg1;
            plast = 0;
            k = 0;
            exitg1 = false;
            while ((!exitg1) && (k < 3)) {
                if (b_iv[k] <= 2) {
                    i = a.size(b_iv[k] - 1);
                } else {
                    i = 1;
                }
                if (i != 1) {
                    if (plast > b_iv[k]) {
                        b_b = false;
                        exitg1 = true;
                    } else {
                        plast = b_iv[k];
                        k++;
                    }
                } else {
                    k++;
                }
            }
        }
        if (b_b) {
            b.set_size(a.size(1), 20);
            plast = a.size(1) * 20;
            for (i = 0; i < plast; i++) {
                b[i] = a[i];
            }
        } else {
            b.set_size(a.size(1), 20);
            i = a.size(1);
            for (k = 0; k < i; k++) {
                for (plast = 0; plast < 20; plast++) {
                    b[k + b.size(0) * plast] = a[plast + 20 * k];
                }
            }
        }
    }

//
// Arguments    : const ::coder::array<double, 3U> &a
//                ::coder::array<double, 3U> &b
// Return Type  : void
//
    void permute(const ::coder::array<double, 3U> &a, ::coder::array<double, 3U> &b) {
        static const signed char b_iv[3] = {1, 3, 2};
        int k;
        int plast;
        int subsa_idx_1;
        int subsa_idx_2;
        boolean_T b_b;
        b_b = true;
        if (a.size(0) != 0) {
            boolean_T exitg1;
            plast = 0;
            k = 0;
            exitg1 = false;
            while ((!exitg1) && (k < 3)) {
                if (a.size(b_iv[k] - 1) != 1) {
                    if (plast > b_iv[k]) {
                        b_b = false;
                        exitg1 = true;
                    } else {
                        plast = b_iv[k];
                        k++;
                    }
                } else {
                    k++;
                }
            }
        }
        if (b_b) {
            b.set_size(a.size(0), 32, 130);
            plast = (a.size(0) << 5) * 130;
            for (int i = 0; i < plast; i++) {
                b[i] = a[i];
            }
        } else {
            int i;
            b.set_size(a.size(0), 32, 130);
            i = a.size(0);
            for (k = 0; k < 32; k++) {
                for (plast = 0; plast < 130; plast++) {
                    if (0 <= i - 1) {
                        subsa_idx_1 = plast + 1;
                        subsa_idx_2 = k + 1;
                    }
                    for (int b_k = 0; b_k < i; b_k++) {
                        b[(b_k + b.size(0) * (subsa_idx_2 - 1)) +
                          b.size(0) * 32 * (subsa_idx_1 - 1)] =
                                a[(b_k + a.size(0) * (subsa_idx_1 - 1)) +
                                  a.size(0) * 130 * (subsa_idx_2 - 1)];
                    }
                }
            }
        }
    }

//
// Arguments    : const ::coder::array<double, 2U> &a
//                ::coder::array<double, 1U> &b
// Return Type  : void
//
    void permute(const ::coder::array<double, 2U> &a, ::coder::array<double, 1U> &b) {
        int loop_ub;
        b.set_size(a.size(1));
        loop_ub = a.size(1);
        for (int i = 0; i < loop_ub; i++) {
            b[i] = a[i];
        }
    }

} // namespace coder

//
// File trailer for permute.cpp
//
// [EOF]
//
