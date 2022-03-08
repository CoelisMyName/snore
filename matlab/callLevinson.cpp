#include "callLevinson.h"
#include "SnoringRecognition_data.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "mylock.h"
#include <math.h>
#include <string.h>

namespace coder {
namespace signal {
namespace internal {
namespace levinson {
void callLevinson(const ::coder::array<creal_T, 1U> &R, double N,
                  creal_T A_data[], int A_size[2], double E_data[],
                  int E_size[2], creal_T K_data[], int K_size[2])
{
    creal_T k_data[13];
    creal_T temp_A_data[12];
    creal_T temp_a_data[12];
    creal_T temp_auf_data[12];
    if (N == 0.0) {
        E_size[0] = 1;
        E_size[1] = 1;
        E_data[0] = R[0].re;
        K_size[0] = 0;
        K_size[1] = 1;
        A_size[0] = 1;
        A_size[1] = 1;
        A_data[0].re = 1.0;
        A_data[0].im = 0.0;
    } else if (R.size(0) == 1) {
        K_size[0] = 0;
        K_size[1] = 1;
        A_size[0] = 1;
        A_size[1] = 1;
        A_data[0].re = 1.0;
        A_data[0].im = 0.0;
        E_size[0] = 1;
        E_size[1] = 1;
        E_data[0] = R[0].re;
    } else {
        double temp_J_im;
        double temp_J_re;
        int i;
        int idx;
        int j;
        int loop_ub_tmp;
        loop_ub_tmp = static_cast<int>(N + 1.0);
        if (0 <= loop_ub_tmp - 1) {
            memset(&k_data[0], 0, loop_ub_tmp * sizeof(creal_T));
        }
        loop_ub_tmp = static_cast<int>(N);
        if (0 <= loop_ub_tmp - 1) {
            memset(&temp_a_data[0], 0, loop_ub_tmp * sizeof(creal_T));
            memset(&temp_A_data[0], 0, loop_ub_tmp * sizeof(creal_T));
            memset(&temp_auf_data[0], 0, loop_ub_tmp * sizeof(creal_T));
        }
        i = !(2.0 > N + 1.0);
        temp_a_data[0].re = -R[0].re;
        temp_a_data[0].im = -R[0].im;
        k_data[0].re = -R[0].re;
        k_data[0].im = -R[0].im;
        temp_J_re = R[0].re;
        temp_J_im = 0.0;
        for (int l = 0; l < loop_ub_tmp; l++) {
            double ar;
            double im;
            double re;
            double s;
            double temp_kprod_im;
            double temp_kprod_re;
            temp_kprod_re = 0.0;
            temp_kprod_im = 0.0;
            for (j = 0; j < l; j++) {
                temp_auf_data[j] = temp_a_data[j];
                idx = static_cast<int>((static_cast<double>(l) + 1.0) -
                                       (static_cast<double>(j) + 1.0));
                temp_kprod_re += temp_a_data[j].re * R[(i + idx) - 1].re -
                                 temp_a_data[j].im * R[(i + idx) - 1].im;
                temp_kprod_im += temp_a_data[j].re * R[(i + idx) - 1].im +
                                 temp_a_data[j].im * R[(i + idx) - 1].re;
            }
            ar = -(R[i + l].re + temp_kprod_re);
            im = -(R[i + l].im + temp_kprod_im);
            if (temp_J_im == 0.0) {
                if (im == 0.0) {
                    re = ar / temp_J_re;
                    im = 0.0;
                } else if (ar == 0.0) {
                    re = 0.0;
                    im /= temp_J_re;
                } else {
                    re = ar / temp_J_re;
                    im /= temp_J_re;
                }
            } else if (temp_J_re == 0.0) {
                if (ar == 0.0) {
                    re = im / temp_J_im;
                    im = 0.0;
                } else if (im == 0.0) {
                    re = 0.0;
                    im = -(ar / temp_J_im);
                } else {
                    re = im / temp_J_im;
                    im = -(ar / temp_J_im);
                }
            } else {
                temp_kprod_im = fabs(temp_J_re);
                temp_kprod_re = fabs(temp_J_im);
                if (temp_kprod_im > temp_kprod_re) {
                    s = temp_J_im / temp_J_re;
                    temp_kprod_re = temp_J_re + s * temp_J_im;
                    re = (ar + s * im) / temp_kprod_re;
                    im = (im - s * ar) / temp_kprod_re;
                } else if (temp_kprod_re == temp_kprod_im) {
                    if (temp_J_re > 0.0) {
                        temp_kprod_re = 0.5;
                    } else {
                        temp_kprod_re = -0.5;
                    }
                    if (temp_J_im > 0.0) {
                        s = 0.5;
                    } else {
                        s = -0.5;
                    }
                    re = (ar * temp_kprod_re + im * s) / temp_kprod_im;
                    im = (im * temp_kprod_re - ar * s) / temp_kprod_im;
                } else {
                    s = temp_J_re / temp_J_im;
                    temp_kprod_re = temp_J_im + s * temp_J_re;
                    re = (s * ar + im) / temp_kprod_re;
                    im = (s * im - ar) / temp_kprod_re;
                }
            }
            temp_kprod_re = re * re - im * -im;
            temp_kprod_im = re * -im + im * re;
            s = (1.0 - temp_kprod_re) * temp_J_re -
                (0.0 - temp_kprod_im) * temp_J_im;
            temp_J_im = (1.0 - temp_kprod_re) * temp_J_im +
                        (0.0 - temp_kprod_im) * temp_J_re;
            temp_J_re = s;
            for (idx = 0; idx < l; idx++) {
                j = static_cast<int>((static_cast<double>(l) + 1.0) -
                                     (static_cast<double>(idx) + 1.0)) -
                    1;
                temp_kprod_re = temp_auf_data[j].re;
                s = -temp_auf_data[j].im;
                temp_a_data[idx].re =
                    temp_auf_data[idx].re + (re * temp_kprod_re - im * s);
                temp_a_data[idx].im =
                    temp_auf_data[idx].im + (re * s + im * temp_kprod_re);
            }
            temp_a_data[l].re = re;
            temp_a_data[l].im = im;
            k_data[l + 1].re = re;
            k_data[l + 1].im = im;
        }
        if (0 <= loop_ub_tmp - 1) {
            memcpy(&temp_A_data[0], &temp_a_data[0],
                   loop_ub_tmp * sizeof(creal_T));
        }
        if (2 > static_cast<int>(N + 1.0)) {
            i = 0;
            j = 0;
        } else {
            i = 1;
            j = static_cast<int>(N + 1.0);
        }
        idx = j - i;
        K_size[0] = idx;
        K_size[1] = 1;
        for (j = 0; j < idx; j++) {
            K_data[j] = k_data[i + j];
        }
        if (1 > static_cast<int>(N)) {
            idx = 0;
        } else {
            idx = static_cast<int>(N);
        }
        A_size[0] = 1;
        A_size[1] = idx + 1;
        A_data[0].re = 1.0;
        A_data[0].im = 0.0;
        if (0 <= idx - 1) {
            memcpy(&A_data[1], &temp_A_data[0], idx * sizeof(creal_T));
        }
        E_size[0] = 1;
        E_size[1] = 1;
        E_data[0] = temp_J_re;
    }
}

} // namespace levinson
} // namespace internal
} // namespace signal
} // namespace coder
