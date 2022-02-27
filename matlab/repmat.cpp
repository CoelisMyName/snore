//
// File: repmat.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "repmat.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// Arguments    : const double a[13]
//                double b[26]
// Return Type  : void
//
namespace coder {
    void b_repmat(const double a[13], double b[26]) {
        for (int jtilecol = 0; jtilecol < 2; jtilecol++) {
            int ibtile;
            ibtile = jtilecol * 13;
            memcpy(&b[ibtile], &a[0], 13U * sizeof(double));
        }
    }

//
// Arguments    : const ::coder::array<double, 2U> &a
//                ::coder::array<double, 2U> &b
// Return Type  : void
//
    void b_repmat(const ::coder::array<double, 2U> &a,
                  ::coder::array<double, 2U> &b) {
        int ncols;
        b.set_size(31, a.size(1));
        ncols = a.size(1);
        for (int jcol = 0; jcol < ncols; jcol++) {
            int ibmat;
            ibmat = jcol * 31;
            for (int itilerow = 0; itilerow < 31; itilerow++) {
                b[ibmat + itilerow] = a[jcol];
            }
        }
    }

//
// Arguments    : const ::coder::array<double, 1U> &a
//                double varargin_2
//                ::coder::array<double, 2U> &b
// Return Type  : void
//
    void repmat(const ::coder::array<double, 1U> &a, double varargin_2,
                ::coder::array<double, 2U> &b) {
        int i;
        int nrows;
        i = static_cast<int>(varargin_2);
        b.set_size(a.size(0), i);
        nrows = a.size(0);
        for (int jtilecol = 0; jtilecol < i; jtilecol++) {
            int ibtile;
            ibtile = jtilecol * nrows;
            for (int k = 0; k < nrows; k++) {
                b[ibtile + k] = a[k];
            }
        }
    }

//
// Arguments    : const ::coder::array<double, 2U> &a
//                ::coder::array<double, 2U> &b
// Return Type  : void
//
    void repmat(const ::coder::array<double, 2U> &a, ::coder::array<double, 2U> &b) {
        int ncols;
        b.set_size(13, a.size(1));
        ncols = a.size(1);
        for (int jcol = 0; jcol < ncols; jcol++) {
            int ibmat;
            ibmat = jcol * 13;
            for (int itilerow = 0; itilerow < 13; itilerow++) {
                b[ibmat + itilerow] = a[jcol];
            }
        }
    }

//
// Arguments    : const ::coder::array<double, 2U> &a
//                double varargin_1
//                ::coder::array<double, 2U> &b
// Return Type  : void
//
    void repmat(const ::coder::array<double, 2U> &a, double varargin_1,
                ::coder::array<double, 2U> &b) {
        int i;
        int ncols;
        i = static_cast<int>(varargin_1);
        b.set_size(i, a.size(1));
        ncols = a.size(1);
        for (int jcol = 0; jcol < ncols; jcol++) {
            int ibmat;
            ibmat = jcol * static_cast<int>(varargin_1);
            for (int itilerow = 0; itilerow < i; itilerow++) {
                b[ibmat + itilerow] = a[jcol];
            }
        }
    }

//
// Arguments    : const double a[13]
//                double b[52]
// Return Type  : void
//
    void repmat(const double a[13], double b[52]) {
        for (int jtilecol = 0; jtilecol < 4; jtilecol++) {
            int ibtile;
            ibtile = jtilecol * 13;
            memcpy(&b[ibtile], &a[0], 13U * sizeof(double));
        }
    }

//
// Arguments    : const ::coder::array<double, 2U> &a
//                ::coder::array<double, 3U> &b
// Return Type  : void
//
    void repmat(const ::coder::array<double, 2U> &a, ::coder::array<double, 3U> &b) {
        int nrows;
        b.set_size(a.size(0), 130, 32);
        nrows = a.size(0);
        for (int jtilecol = 0; jtilecol < 32; jtilecol++) {
            int ibtile;
            ibtile = jtilecol * (nrows * 130) - 1;
            for (int jcol = 0; jcol < 130; jcol++) {
                int iacol_tmp;
                int ibmat;
                iacol_tmp = jcol * nrows;
                ibmat = ibtile + iacol_tmp;
                for (int k = 0; k < nrows; k++) {
                    b[(ibmat + k) + 1] = a[iacol_tmp + k];
                }
            }
        }
    }

//
// Arguments    : const double a[32]
//                const double varargin_1[2]
//                ::coder::array<double, 2U> &b
// Return Type  : void
//
    void repmat(const double a[32], const double varargin_1[2],
                ::coder::array<double, 2U> &b) {
        int i;
        i = static_cast<int>(varargin_1[0]);
        b.set_size(i, 32);
        for (int jcol = 0; jcol < 32; jcol++) {
            int ibmat;
            ibmat = jcol * i;
            for (int itilerow = 0; itilerow < i; itilerow++) {
                b[ibmat + itilerow] = a[jcol];
            }
        }
    }

//
// Arguments    : const double a[4160]
//                const double varargin_1[3]
//                ::coder::array<double, 3U> &b
// Return Type  : void
//
    void repmat(const double a[4160], const double varargin_1[3],
                ::coder::array<double, 3U> &b) {
        int tile_size[3];
        int ibtile;
        int k;
        int ntilecols;
        tile_size[0] = 1;
        tile_size[1] = 1;
        ibtile = static_cast<int>(varargin_1[2]);
        tile_size[2] = static_cast<int>(varargin_1[2]);
        b.set_size(130, 32, ibtile);
        ntilecols = 1;
        k = 3;
        if (static_cast<int>(varargin_1[2]) == 1) {
            k = 2;
        }
        for (ibtile = 2; ibtile <= k; ibtile++) {
            ntilecols *= tile_size[ibtile - 1];
        }
        for (int jtilecol = 0; jtilecol < ntilecols; jtilecol++) {
            ibtile = jtilecol * 4160 - 1;
            for (int jcol = 0; jcol < 32; jcol++) {
                int iacol;
                int ibmat;
                iacol = jcol * 130;
                ibmat = ibtile + jcol * 130;
                for (k = 0; k < 130; k++) {
                    b[(ibmat + k) + 1] = a[iacol + k];
                }
            }
        }
    }

} // namespace coder

//
// File trailer for repmat.cpp
//
// [EOF]
//
