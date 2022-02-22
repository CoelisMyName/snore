//
// File: find.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "find.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<boolean_T, 2U> &x
//                ::coder::array<int, 2U> &i
// Return Type  : void
//
namespace coder {
    void b_eml_find(const ::coder::array<boolean_T, 2U> &x,
                    ::coder::array<int, 2U> &i) {
        array<int, 2U> b_i;
        int idx;
        int nd2;
        int xtmp;
        boolean_T exitg1;
        nd2 = (1 <= x.size(1));
        xtmp = x.size(1);
        idx = 0;
        i.set_size(1, nd2);
        exitg1 = false;
        while ((!exitg1) && (xtmp > 0)) {
            if (x[xtmp - 1]) {
                idx++;
                i[idx - 1] = xtmp;
                if (idx >= nd2) {
                    exitg1 = true;
                } else {
                    xtmp--;
                }
            } else {
                xtmp--;
            }
        }
        if (nd2 == 1) {
            if (idx == 0) {
                i.set_size(1, 0);
            }
        } else {
            int loop_ub;
            if (1 > idx) {
                loop_ub = -1;
            } else {
                loop_ub = 0;
            }
            b_i.set_size(1, loop_ub + 1);
            for (idx = 0; idx <= loop_ub; idx++) {
                b_i[0] = i[0];
            }
            i.set_size(1, loop_ub + 1);
            nd2 = loop_ub + 1;
            for (idx = 0; idx < nd2; idx++) {
                i[0] = b_i[0];
            }
            nd2 = (loop_ub + 1) / 2;
            for (idx = 0; idx < nd2; idx++) {
                xtmp = i[0];
                i[0] = i[loop_ub];
                i[loop_ub] = xtmp;
            }
        }
    }

//
// Arguments    : const ::coder::array<boolean_T, 2U> &x
//                ::coder::array<int, 2U> &i
// Return Type  : void
//
    void eml_find(const ::coder::array<boolean_T, 2U> &x,
                  ::coder::array<int, 2U> &i) {
        array<int, 2U> b_i;
        int idx;
        int ii;
        int k;
        boolean_T exitg1;
        k = (1 <= x.size(1));
        idx = 0;
        i.set_size(1, k);
        ii = 0;
        exitg1 = false;
        while ((!exitg1) && (ii <= x.size(1) - 1)) {
            if (x[ii]) {
                idx++;
                i[idx - 1] = ii + 1;
                if (idx >= k) {
                    exitg1 = true;
                } else {
                    ii++;
                }
            } else {
                ii++;
            }
        }
        if (k == 1) {
            if (idx == 0) {
                i.set_size(1, 0);
            }
        } else {
            if (1 > idx) {
                k = -1;
            } else {
                k = 0;
            }
            b_i.set_size(1, k + 1);
            for (idx = 0; idx <= k; idx++) {
                b_i[0] = i[0];
            }
            i.set_size(1, k + 1);
            k++;
            for (idx = 0; idx < k; idx++) {
                i[0] = b_i[0];
            }
        }
    }

} // namespace coder

//
// File trailer for find.cpp
//
// [EOF]
//
