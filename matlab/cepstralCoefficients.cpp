#include "cepstralCoefficients.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>
#include <string.h>

namespace coder {
void cepstralCoefficients(::coder::array<double, 2U> &S,
                          ::coder::array<double, 2U> &coeffs)
{
    static const signed char b_iv[3] = {2, 1, 3};
    array<double, 2U> b_coeffs;
    array<int, 1U> r;
    double DCTmatrix_data[520];
    double A;
    double B;
    double piCCast;
    int DCTmatrix_size_idx_1;
    int b_i;
    int coffset;
    int i;
    int k;
    int nx;
    boolean_T b;
    coffset = S.size(0) * S.size(1) - 1;
    nx = 0;
    for (i = 0; i <= coffset; i++) {
        if (S[i] == 0.0) {
            nx++;
        }
    }
    r.set_size(nx);
    nx = 0;
    for (i = 0; i <= coffset; i++) {
        if (S[i] == 0.0) {
            r[nx] = i + 1;
            nx++;
        }
    }
    nx = r.size(0) - 1;
    for (b_i = 0; b_i <= nx; b_i++) {
        S[r[b_i] - 1] = 2.2250738585072014E-308;
    }
    nx = S.size(0) * S.size(1);
    for (k = 0; k < nx; k++) {
        S[k] = log10(S[k]);
    }
    DCTmatrix_size_idx_1 = S.size(0);
    nx = 13 * S.size(0);
    if (0 <= nx - 1) {
        memset(&DCTmatrix_data[0], 0, nx * sizeof(double));
    }
    A = sqrt(1.0 / static_cast<double>(S.size(0)));
    B = sqrt(2.0 / static_cast<double>(S.size(0)));
    piCCast = 6.2831853071795862 / (2.0 * static_cast<double>(S.size(0)));
    nx = S.size(0);
    for (b_i = 0; b_i < nx; b_i++) {
        DCTmatrix_data[13 * b_i] = A;
    }
    b_i = S.size(0);
    for (k = 0; k < b_i; k++) {
        for (nx = 0; nx < 12; nx++) {
            DCTmatrix_data[(nx + 13 * k) + 1] =
                B * cos(piCCast * ((static_cast<double>(nx) + 2.0) - 1.0) *
                        ((static_cast<double>(k) + 1.0) - 0.5));
        }
    }
    nx = S.size(1);
    b_coeffs.set_size(13, S.size(1));
    for (int j = 0; j < nx; j++) {
        int boffset;
        coffset = j * 13;
        boffset = j * S.size(0);
        for (i = 0; i < 13; i++) {
            b_coeffs[coffset + i] = 0.0;
        }
        for (k = 0; k < DCTmatrix_size_idx_1; k++) {
            int aoffset;
            aoffset = k * 13;
            A = S[boffset + k];
            for (i = 0; i < 13; i++) {
                b_i = coffset + i;
                b_coeffs[b_i] = b_coeffs[b_i] + DCTmatrix_data[aoffset + i] * A;
            }
        }
    }
    b_coeffs.set_size(13, S.size(1));
    b = true;
    if (S.size(1) != 0) {
        boolean_T exitg1;
        nx = 0;
        k = 0;
        exitg1 = false;
        while ((!exitg1) && (k < 3)) {
            if (b_iv[k] <= 2) {
                b_i = b_coeffs.size(b_iv[k] - 1);
            } else {
                b_i = 1;
            }
            if (b_i != 1) {
                if (nx > b_iv[k]) {
                    b = false;
                    exitg1 = true;
                } else {
                    nx = b_iv[k];
                    k++;
                }
            } else {
                k++;
            }
        }
    }
    if (b) {
        coeffs.set_size(S.size(1), 13);
        nx = S.size(1) * 13;
        for (b_i = 0; b_i < nx; b_i++) {
            coeffs[b_i] = b_coeffs[b_i];
        }
    } else {
        coeffs.set_size(S.size(1), 13);
        b_i = S.size(1);
        for (k = 0; k < b_i; k++) {
            for (nx = 0; nx < 13; nx++) {
                coeffs[k + coeffs.size(0) * nx] = b_coeffs[nx + 13 * k];
            }
        }
    }
}

} // namespace coder
