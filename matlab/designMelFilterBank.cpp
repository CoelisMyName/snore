//
// File: designMelFilterBank.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "designMelFilterBank.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions
//
// Arguments    : double fs
//                const double bandEdges_data[]
//                const int bandEdges_size[2]
//                double NFFT
//                ::coder::array<double, 2U> &filterBank
// Return Type  : void
//
namespace coder {
    namespace audio {
        namespace internal {
            void designMelFilterBank(double fs, const double bandEdges_data[],
                                     const int bandEdges_size[2], double NFFT,
                                     ::coder::array<double, 2U> &filterBank) {
                array<double, 2U> linFq;
                array<double, 1U> b_filterBank;
                array<boolean_T, 2U> x;
                double y1_data[41];
                double weightPerBand_data[40];
                double work_data;
                unsigned int p_data[42];
                int dimSize;
                int i;
                int nz;
                int vlen;
                x.set_size(1, bandEdges_size[1]);
                work_data = fs / 2.0;
                vlen = bandEdges_size[1];
                for (i = 0; i < vlen; i++) {
                    x[i] = (bandEdges_data[i] - work_data < 1.4901161193847656E-8);
                }
                vlen = x.size(1);
                if (x.size(1) == 0) {
                    nz = 0;
                } else {
                    nz = x[0];
                    for (dimSize = 2; dimSize <= vlen; dimSize++) {
                        nz += x[dimSize - 1];
                    }
                }
                filterBank.set_size(static_cast<int>(NFFT), bandEdges_size[1] - 2);
                vlen = static_cast<int>(NFFT) * (bandEdges_size[1] - 2);
                for (i = 0; i < vlen; i++) {
                    filterBank[i] = 0.0;
                }
                if (NFFT - 1.0 < 0.0) {
                    linFq.set_size(linFq.size(0), 0);
                } else if (rtIsInf(NFFT - 1.0) && (0.0 == NFFT - 1.0)) {
                    linFq.set_size(1, 1);
                    linFq[0] = rtNaN;
                } else {
                    vlen = static_cast<int>(floor(NFFT - 1.0));
                    linFq.set_size(1, vlen + 1);
                    for (i = 0; i <= vlen; i++) {
                        linFq[i] = i;
                    }
                }
                linFq.set_size(1, linFq.size(1));
                vlen = linFq.size(1) - 1;
                for (i = 0; i <= vlen; i++) {
                    linFq[i] = linFq[i] / NFFT * fs;
                }
                for (dimSize = 0; dimSize < nz; dimSize++) {
                    boolean_T exitg1;
                    vlen = 0;
                    exitg1 = false;
                    while ((!exitg1) && (vlen <= linFq.size(1) - 1)) {
                        if (linFq[vlen] > bandEdges_data[dimSize]) {
                            p_data[dimSize] = static_cast<unsigned int>(vlen + 1);
                            exitg1 = true;
                        } else {
                            vlen++;
                        }
                    }
                }
                dimSize = bandEdges_size[1];
                if (bandEdges_size[1] != 0) {
                    vlen = bandEdges_size[1] - 1;
                    if (vlen >= 1) {
                        vlen = 1;
                    }
                    if ((vlen >= 1) &&
                        (static_cast<signed char>(bandEdges_size[1] - 1) != 0)) {
                        work_data = bandEdges_data[0];
                        for (vlen = 2; vlen <= dimSize; vlen++) {
                            double d;
                            double tmp1;
                            tmp1 = bandEdges_data[vlen - 1];
                            d = tmp1;
                            tmp1 -= work_data;
                            work_data = d;
                            y1_data[vlen - 2] = tmp1;
                        }
                    }
                }
                for (dimSize = 0; dimSize <= nz - 3; dimSize++) {
                    unsigned int j;
                    unsigned int u;
                    u = p_data[dimSize + 1];
                    i = static_cast<int>(u) - static_cast<int>(p_data[dimSize]);
                    for (vlen = 0; vlen < i; vlen++) {
                        j = p_data[dimSize] + vlen;
                        filterBank[(static_cast<int>(j) + filterBank.size(0) * dimSize) -
                                   1] =
                                (linFq[static_cast<int>(j) - 1] - bandEdges_data[dimSize]) /
                                y1_data[dimSize];
                    }
                    i = static_cast<int>(p_data[dimSize + 2]) - static_cast<int>(u);
                    for (vlen = 0; vlen < i; vlen++) {
                        j = u + vlen;
                        filterBank[(static_cast<int>(j) + filterBank.size(0) * dimSize) -
                                   1] =
                                (bandEdges_data[dimSize + 2] - linFq[static_cast<int>(j) - 1]) /
                                y1_data[dimSize + 1];
                    }
                }
                if (3 > bandEdges_size[1]) {
                    i = 0;
                    dimSize = 0;
                } else {
                    i = 2;
                    dimSize = bandEdges_size[1];
                }
                vlen = dimSize - i;
                for (dimSize = 0; dimSize < vlen; dimSize++) {
                    weightPerBand_data[dimSize] =
                            (bandEdges_data[i + dimSize] - bandEdges_data[dimSize]) / 2.0;
                }
                i = bandEdges_size[1];
                for (nz = 0; nz <= i - 3; nz++) {
                    vlen = filterBank.size(0) - 1;
                    work_data = weightPerBand_data[nz];
                    b_filterBank.set_size(filterBank.size(0));
                    for (dimSize = 0; dimSize <= vlen; dimSize++) {
                        b_filterBank[dimSize] =
                                filterBank[dimSize + filterBank.size(0) * nz] / work_data;
                    }
                    vlen = b_filterBank.size(0);
                    for (dimSize = 0; dimSize < vlen; dimSize++) {
                        filterBank[dimSize + filterBank.size(0) * nz] =
                                b_filterBank[dimSize];
                    }
                }
            }

        } // namespace internal
    } // namespace audio
} // namespace coder

//
// File trailer for designMelFilterBank.cpp
//
// [EOF]
//
