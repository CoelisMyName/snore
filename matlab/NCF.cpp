#include "NCF.h"
#include "FFTImplementationCallback.h"
#include "SnoringRecognition_rtwutil.h"
#include "fft.h"
#include "getCandidates.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>

namespace coder {
namespace audio {
namespace internal {
namespace pitch {
void NCF(const ::coder::array<double, 2U> &y, ::coder::array<double, 1U> &f0)
{
    array<creal_T, 2U> x;
    array<double, 2U> Rt;
    array<double, 2U> b_c1;
    array<double, 2U> b_x;
    array<double, 2U> b_y;
    array<double, 2U> c1;
    array<double, 2U> c_y;
    array<double, 2U> r;
    array<double, 2U> result;
    array<double, 2U> varargin_1;
    array<double, 1U> peak;
    double edge[2];
    int i;
    int i1;
    int i2;
    int ibmat;
    int itilerow;
    int jcol;
    int nx;
    int result_tmp;
    short sizes_idx_0;
    unsigned char input_sizes_idx_0;
    boolean_T empty_non_axis_sizes;
    edge[0] = 20.0;
    edge[1] = 160.0;
    fft(y, x);
    nx = x.size(1) << 10;
    c1.set_size(1024, x.size(1));
    for (ibmat = 0; ibmat < nx; ibmat++) {
        c1[ibmat] = rt_hypotd_snf(x[ibmat].re, x[ibmat].im);
    }
    b_y.set_size(1024, c1.size(1));
    nx = c1.size(1) << 10;
    for (ibmat = 0; ibmat < nx; ibmat++) {
        b_y[ibmat] = c1[ibmat] * c1[ibmat];
    }
    if (b_y.size(1) == 0) {
        x.set_size(1024, 0);
    } else {
        nx = b_y.size(1);
        x.set_size(1024, b_y.size(1));
        for (ibmat = 0; ibmat < nx; ibmat++) {
            ::coder::internal::FFTImplementationCallback::b_doHalfLengthRadix2(
                b_y, ibmat << 10, *(creal_T(*)[1024]) & x[1024 * ibmat]);
        }
        nx = 1024 * x.size(1);
        x.set_size(1024, x.size(1));
        for (i = 0; i < nx; i++) {
            x[i].re = 0.0009765625 * x[i].re;
            x[i].im = 0.0009765625 * x[i].im;
        }
    }
    c1.set_size(1024, x.size(1));
    nx = 1024 * x.size(1);
    for (i = 0; i < nx; i++) {
        c1[i] = x[i].re / 32.0;
    }
    c_y.set_size(1, 160);
    for (i = 0; i < 160; i++) {
        c_y[i] = static_cast<double>(i) + 1.0;
    }
    nx = c1.size(1);
    varargin_1.set_size(160, c1.size(1));
    for (i = 0; i < nx; i++) {
        for (i1 = 0; i1 < 160; i1++) {
            varargin_1[i1 + varargin_1.size(0) * i] =
                c1[(static_cast<int>(c_y[i1]) + 1024 * i) + 863];
        }
    }
    if (c1.size(1) != 0) {
        itilerow = c1.size(1);
    } else {
        itilerow = 0;
    }
    empty_non_axis_sizes = (itilerow == 0);
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        input_sizes_idx_0 = 160U;
    } else {
        input_sizes_idx_0 = 0U;
    }
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        sizes_idx_0 = 161;
    } else {
        sizes_idx_0 = 0;
    }
    ibmat = input_sizes_idx_0;
    nx = c1.size(1);
    b_c1.set_size(161, c1.size(1));
    for (i = 0; i < nx; i++) {
        for (i1 = 0; i1 < 161; i1++) {
            b_c1[i1 + b_c1.size(0) * i] = c1[i1 + 1024 * i];
        }
    }
    jcol = sizes_idx_0;
    i = input_sizes_idx_0 + sizes_idx_0;
    result.set_size(i, itilerow);
    for (i1 = 0; i1 < itilerow; i1++) {
        for (i2 = 0; i2 < ibmat; i2++) {
            result[i2 + result.size(0) * i1] =
                varargin_1[i2 + input_sizes_idx_0 * i1];
        }
    }
    for (i1 = 0; i1 < itilerow; i1++) {
        for (i2 = 0; i2 < jcol; i2++) {
            result[(i2 + input_sizes_idx_0) + result.size(0) * i1] =
                b_c1[i2 + sizes_idx_0 * i1];
        }
    }
    nx = c1.size(1);
    b_c1.set_size(161, c1.size(1));
    for (i1 = 0; i1 < nx; i1++) {
        for (i2 = 0; i2 < 161; i2++) {
            b_c1[i2 + b_c1.size(0) * i1] = c1[i2 + 1024 * i1];
        }
    }
    Rt.set_size(i, itilerow);
    for (i = 0; i < itilerow; i++) {
        for (i1 = 0; i1 < ibmat; i1++) {
            Rt[i1 + Rt.size(0) * i] = varargin_1[i1 + input_sizes_idx_0 * i];
        }
    }
    for (i = 0; i < itilerow; i++) {
        for (i1 = 0; i1 < jcol; i1++) {
            Rt[(i1 + input_sizes_idx_0) + Rt.size(0) * i] =
                b_c1[i1 + sizes_idx_0 * i];
        }
    }
    if (181 > result.size(0)) {
        i = -1;
        i1 = -1;
    } else {
        i = 179;
        i1 = Rt.size(0) - 1;
    }
    nx = result.size(1);
    b_x.set_size(1, result.size(1));
    for (i2 = 0; i2 < nx; i2++) {
        b_x[i2] = result[result.size(0) * i2 + 160];
    }
    nx = result.size(1) - 1;
    for (ibmat = 0; ibmat <= nx; ibmat++) {
        b_x[ibmat] = sqrt(b_x[ibmat]);
    }
    result_tmp = i1 - i;
    result.set_size(result_tmp, b_x.size(1));
    nx = b_x.size(1);
    for (jcol = 0; jcol < nx; jcol++) {
        ibmat = jcol * result_tmp;
        for (itilerow = 0; itilerow < result_tmp; itilerow++) {
            result[ibmat + itilerow] = b_x[jcol];
        }
    }
    nx = Rt.size(1) - 1;
    for (i1 = 0; i1 <= nx; i1++) {
        for (i2 = 0; i2 < result_tmp; i2++) {
            Rt[i2 + result_tmp * i1] = Rt[((i + i2) + Rt.size(0) * i1) + 1] /
                                       result[i2 + result.size(0) * i1];
        }
    }
    Rt.set_size(result_tmp, nx + 1);
    if (nx + 1 != 0) {
        itilerow = nx + 1;
    } else if ((result_tmp != 0) && (nx + 1 != 0)) {
        itilerow = nx + 1;
    } else {
        itilerow = nx + 1;
    }
    empty_non_axis_sizes = (itilerow == 0);
    if (empty_non_axis_sizes || (nx + 1 != 0)) {
        input_sizes_idx_0 = 19U;
    } else {
        input_sizes_idx_0 = 0U;
    }
    if (empty_non_axis_sizes || ((result_tmp != 0) && (nx + 1 != 0))) {
        sizes_idx_0 = static_cast<short>(result_tmp);
    } else {
        sizes_idx_0 = 0;
    }
    jcol = sizes_idx_0;
    r.set_size(input_sizes_idx_0 + sizes_idx_0, itilerow);
    for (i = 0; i < itilerow; i++) {
        nx = input_sizes_idx_0;
        for (i1 = 0; i1 < nx; i1++) {
            r[i1 + r.size(0) * i] = 0.0;
        }
    }
    for (i = 0; i < itilerow; i++) {
        for (i1 = 0; i1 < jcol; i1++) {
            r[(i1 + input_sizes_idx_0) + r.size(0) * i] =
                Rt[i1 + sizes_idx_0 * i];
        }
    }
    getCandidates(r, edge, peak, f0);
    nx = f0.size(0);
    for (i = 0; i < nx; i++) {
        f0[i] = 8000.0 / f0[i];
    }
}

void b_NCF(const ::coder::array<double, 2U> &y, ::coder::array<double, 1U> &f0)
{
    array<creal_T, 2U> x;
    array<double, 2U> Rt;
    array<double, 2U> b_c1;
    array<double, 2U> b_x;
    array<double, 2U> b_y;
    array<double, 2U> c1;
    array<double, 2U> c_y;
    array<double, 2U> r;
    array<double, 2U> result;
    array<double, 2U> varargin_1;
    array<double, 1U> locs;
    array<double, 1U> peak;
    double edge[2];
    int i;
    int i1;
    int i2;
    int ibmat;
    int itilerow;
    int jcol;
    int nx;
    int result_tmp;
    short sizes_idx_0;
    unsigned char input_sizes_idx_0;
    boolean_T empty_non_axis_sizes;
    edge[0] = 28.0;
    edge[1] = 221.0;
    b_fft(y, x);
    nx = x.size(1) << 11;
    c1.set_size(2048, x.size(1));
    for (ibmat = 0; ibmat < nx; ibmat++) {
        c1[ibmat] = rt_hypotd_snf(x[ibmat].re, x[ibmat].im);
    }
    b_y.set_size(2048, c1.size(1));
    nx = c1.size(1) << 11;
    for (ibmat = 0; ibmat < nx; ibmat++) {
        b_y[ibmat] = c1[ibmat] * c1[ibmat];
    }
    if (b_y.size(1) == 0) {
        x.set_size(2048, 0);
    } else {
        nx = b_y.size(1);
        x.set_size(2048, b_y.size(1));
        for (ibmat = 0; ibmat < nx; ibmat++) {
            ::coder::internal::FFTImplementationCallback::d_doHalfLengthRadix2(
                b_y, ibmat << 11, *(creal_T(*)[2048]) & x[2048 * ibmat]);
        }
        nx = 2048 * x.size(1);
        x.set_size(2048, x.size(1));
        for (i = 0; i < nx; i++) {
            x[i].re = 0.00048828125 * x[i].re;
            x[i].im = 0.00048828125 * x[i].im;
        }
    }
    c1.set_size(2048, x.size(1));
    nx = 2048 * x.size(1);
    for (i = 0; i < nx; i++) {
        c1[i] = x[i].re / 45.254833995939045;
    }
    c_y.set_size(1, 221);
    for (i = 0; i < 221; i++) {
        c_y[i] = static_cast<double>(i) + 1.0;
    }
    nx = c1.size(1);
    varargin_1.set_size(221, c1.size(1));
    for (i = 0; i < nx; i++) {
        for (i1 = 0; i1 < 221; i1++) {
            varargin_1[i1 + varargin_1.size(0) * i] =
                c1[(static_cast<int>(c_y[i1] + 1827.0) + 2048 * i) - 1];
        }
    }
    if (c1.size(1) != 0) {
        itilerow = c1.size(1);
    } else {
        itilerow = 0;
    }
    empty_non_axis_sizes = (itilerow == 0);
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        input_sizes_idx_0 = 221U;
    } else {
        input_sizes_idx_0 = 0U;
    }
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        sizes_idx_0 = 222;
    } else {
        sizes_idx_0 = 0;
    }
    ibmat = input_sizes_idx_0;
    nx = c1.size(1);
    b_c1.set_size(222, c1.size(1));
    for (i = 0; i < nx; i++) {
        for (i1 = 0; i1 < 222; i1++) {
            b_c1[i1 + b_c1.size(0) * i] = c1[i1 + 2048 * i];
        }
    }
    jcol = sizes_idx_0;
    i = input_sizes_idx_0 + sizes_idx_0;
    result.set_size(i, itilerow);
    for (i1 = 0; i1 < itilerow; i1++) {
        for (i2 = 0; i2 < ibmat; i2++) {
            result[i2 + result.size(0) * i1] =
                varargin_1[i2 + input_sizes_idx_0 * i1];
        }
    }
    for (i1 = 0; i1 < itilerow; i1++) {
        for (i2 = 0; i2 < jcol; i2++) {
            result[(i2 + input_sizes_idx_0) + result.size(0) * i1] =
                b_c1[i2 + sizes_idx_0 * i1];
        }
    }
    nx = c1.size(1);
    b_c1.set_size(222, c1.size(1));
    for (i1 = 0; i1 < nx; i1++) {
        for (i2 = 0; i2 < 222; i2++) {
            b_c1[i2 + b_c1.size(0) * i1] = c1[i2 + 2048 * i1];
        }
    }
    Rt.set_size(i, itilerow);
    for (i = 0; i < itilerow; i++) {
        for (i1 = 0; i1 < ibmat; i1++) {
            Rt[i1 + Rt.size(0) * i] = varargin_1[i1 + input_sizes_idx_0 * i];
        }
    }
    for (i = 0; i < itilerow; i++) {
        for (i1 = 0; i1 < jcol; i1++) {
            Rt[(i1 + input_sizes_idx_0) + Rt.size(0) * i] =
                b_c1[i1 + sizes_idx_0 * i];
        }
    }
    if (250 > result.size(0)) {
        i = -1;
        i1 = -1;
    } else {
        i = 248;
        i1 = Rt.size(0) - 1;
    }
    nx = result.size(1);
    b_x.set_size(1, result.size(1));
    for (i2 = 0; i2 < nx; i2++) {
        b_x[i2] = result[result.size(0) * i2 + 221];
    }
    nx = result.size(1) - 1;
    for (ibmat = 0; ibmat <= nx; ibmat++) {
        b_x[ibmat] = sqrt(b_x[ibmat]);
    }
    result_tmp = i1 - i;
    result.set_size(result_tmp, b_x.size(1));
    nx = b_x.size(1);
    for (jcol = 0; jcol < nx; jcol++) {
        ibmat = jcol * result_tmp;
        for (itilerow = 0; itilerow < result_tmp; itilerow++) {
            result[ibmat + itilerow] = b_x[jcol];
        }
    }
    nx = Rt.size(1) - 1;
    for (i1 = 0; i1 <= nx; i1++) {
        for (i2 = 0; i2 < result_tmp; i2++) {
            Rt[i2 + result_tmp * i1] = Rt[((i + i2) + Rt.size(0) * i1) + 1] /
                                       result[i2 + result.size(0) * i1];
        }
    }
    Rt.set_size(result_tmp, nx + 1);
    if (nx + 1 != 0) {
        itilerow = nx + 1;
    } else if ((result_tmp != 0) && (nx + 1 != 0)) {
        itilerow = nx + 1;
    } else {
        itilerow = nx + 1;
    }
    empty_non_axis_sizes = (itilerow == 0);
    if (empty_non_axis_sizes || (nx + 1 != 0)) {
        input_sizes_idx_0 = 27U;
    } else {
        input_sizes_idx_0 = 0U;
    }
    if (empty_non_axis_sizes || ((result_tmp != 0) && (nx + 1 != 0))) {
        sizes_idx_0 = static_cast<short>(result_tmp);
    } else {
        sizes_idx_0 = 0;
    }
    jcol = sizes_idx_0;
    r.set_size(input_sizes_idx_0 + sizes_idx_0, itilerow);
    for (i = 0; i < itilerow; i++) {
        nx = input_sizes_idx_0;
        for (i1 = 0; i1 < nx; i1++) {
            r[i1 + r.size(0) * i] = 0.0;
        }
    }
    for (i = 0; i < itilerow; i++) {
        for (i1 = 0; i1 < jcol; i1++) {
            r[(i1 + input_sizes_idx_0) + r.size(0) * i] =
                Rt[i1 + sizes_idx_0 * i];
        }
    }
    getCandidates(r, edge, peak, locs);
    f0.set_size(locs.size(0));
    nx = locs.size(0);
    for (i = 0; i < nx; i++) {
        f0[i] = 11025.0 / locs[i];
    }
}

void c_NCF(const ::coder::array<double, 2U> &y, ::coder::array<double, 1U> &f0)
{
    array<creal_T, 2U> x;
    array<double, 2U> Rt;
    array<double, 2U> b_c1;
    array<double, 2U> b_x;
    array<double, 2U> b_y;
    array<double, 2U> c1;
    array<double, 2U> c_y;
    array<double, 2U> r;
    array<double, 2U> result;
    array<double, 2U> varargin_1;
    array<double, 1U> locs;
    array<double, 1U> peak;
    double edge[2];
    int i;
    int i1;
    int i2;
    int ibmat;
    int itilerow;
    int jcol;
    int nx;
    int result_tmp;
    short sizes_idx_0;
    unsigned char input_sizes_idx_0;
    boolean_T empty_non_axis_sizes;
    edge[0] = 30.0;
    edge[1] = 240.0;
    c_fft(y, x);
    nx = x.size(1) << 11;
    c1.set_size(2048, x.size(1));
    for (ibmat = 0; ibmat < nx; ibmat++) {
        c1[ibmat] = rt_hypotd_snf(x[ibmat].re, x[ibmat].im);
    }
    b_y.set_size(2048, c1.size(1));
    nx = c1.size(1) << 11;
    for (ibmat = 0; ibmat < nx; ibmat++) {
        b_y[ibmat] = c1[ibmat] * c1[ibmat];
    }
    if (b_y.size(1) == 0) {
        x.set_size(2048, 0);
    } else {
        nx = b_y.size(1);
        x.set_size(2048, b_y.size(1));
        for (ibmat = 0; ibmat < nx; ibmat++) {
            ::coder::internal::FFTImplementationCallback::d_doHalfLengthRadix2(
                b_y, ibmat << 11, *(creal_T(*)[2048]) & x[2048 * ibmat]);
        }
        nx = 2048 * x.size(1);
        x.set_size(2048, x.size(1));
        for (i = 0; i < nx; i++) {
            x[i].re = 0.00048828125 * x[i].re;
            x[i].im = 0.00048828125 * x[i].im;
        }
    }
    c1.set_size(2048, x.size(1));
    nx = 2048 * x.size(1);
    for (i = 0; i < nx; i++) {
        c1[i] = x[i].re / 45.254833995939045;
    }
    c_y.set_size(1, 240);
    for (i = 0; i < 240; i++) {
        c_y[i] = static_cast<double>(i) + 1.0;
    }
    nx = c1.size(1);
    varargin_1.set_size(240, c1.size(1));
    for (i = 0; i < nx; i++) {
        for (i1 = 0; i1 < 240; i1++) {
            varargin_1[i1 + varargin_1.size(0) * i] =
                c1[(static_cast<int>(c_y[i1]) + 2048 * i) + 1807];
        }
    }
    if (c1.size(1) != 0) {
        itilerow = c1.size(1);
    } else {
        itilerow = 0;
    }
    empty_non_axis_sizes = (itilerow == 0);
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        input_sizes_idx_0 = 240U;
    } else {
        input_sizes_idx_0 = 0U;
    }
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        sizes_idx_0 = 241;
    } else {
        sizes_idx_0 = 0;
    }
    ibmat = input_sizes_idx_0;
    nx = c1.size(1);
    b_c1.set_size(241, c1.size(1));
    for (i = 0; i < nx; i++) {
        for (i1 = 0; i1 < 241; i1++) {
            b_c1[i1 + b_c1.size(0) * i] = c1[i1 + 2048 * i];
        }
    }
    jcol = sizes_idx_0;
    i = input_sizes_idx_0 + sizes_idx_0;
    result.set_size(i, itilerow);
    for (i1 = 0; i1 < itilerow; i1++) {
        for (i2 = 0; i2 < ibmat; i2++) {
            result[i2 + result.size(0) * i1] =
                varargin_1[i2 + input_sizes_idx_0 * i1];
        }
    }
    for (i1 = 0; i1 < itilerow; i1++) {
        for (i2 = 0; i2 < jcol; i2++) {
            result[(i2 + input_sizes_idx_0) + result.size(0) * i1] =
                b_c1[i2 + sizes_idx_0 * i1];
        }
    }
    nx = c1.size(1);
    b_c1.set_size(241, c1.size(1));
    for (i1 = 0; i1 < nx; i1++) {
        for (i2 = 0; i2 < 241; i2++) {
            b_c1[i2 + b_c1.size(0) * i1] = c1[i2 + 2048 * i1];
        }
    }
    Rt.set_size(i, itilerow);
    for (i = 0; i < itilerow; i++) {
        for (i1 = 0; i1 < ibmat; i1++) {
            Rt[i1 + Rt.size(0) * i] = varargin_1[i1 + input_sizes_idx_0 * i];
        }
    }
    for (i = 0; i < itilerow; i++) {
        for (i1 = 0; i1 < jcol; i1++) {
            Rt[(i1 + input_sizes_idx_0) + Rt.size(0) * i] =
                b_c1[i1 + sizes_idx_0 * i];
        }
    }
    if (271 > result.size(0)) {
        i = -1;
        i1 = -1;
    } else {
        i = 269;
        i1 = Rt.size(0) - 1;
    }
    nx = result.size(1);
    b_x.set_size(1, result.size(1));
    for (i2 = 0; i2 < nx; i2++) {
        b_x[i2] = result[result.size(0) * i2 + 240];
    }
    nx = result.size(1) - 1;
    for (ibmat = 0; ibmat <= nx; ibmat++) {
        b_x[ibmat] = sqrt(b_x[ibmat]);
    }
    result_tmp = i1 - i;
    result.set_size(result_tmp, b_x.size(1));
    nx = b_x.size(1);
    for (jcol = 0; jcol < nx; jcol++) {
        ibmat = jcol * result_tmp;
        for (itilerow = 0; itilerow < result_tmp; itilerow++) {
            result[ibmat + itilerow] = b_x[jcol];
        }
    }
    nx = Rt.size(1) - 1;
    for (i1 = 0; i1 <= nx; i1++) {
        for (i2 = 0; i2 < result_tmp; i2++) {
            Rt[i2 + result_tmp * i1] = Rt[((i + i2) + Rt.size(0) * i1) + 1] /
                                       result[i2 + result.size(0) * i1];
        }
    }
    Rt.set_size(result_tmp, nx + 1);
    if (nx + 1 != 0) {
        itilerow = nx + 1;
    } else if ((result_tmp != 0) && (nx + 1 != 0)) {
        itilerow = nx + 1;
    } else {
        itilerow = nx + 1;
    }
    empty_non_axis_sizes = (itilerow == 0);
    if (empty_non_axis_sizes || (nx + 1 != 0)) {
        input_sizes_idx_0 = 29U;
    } else {
        input_sizes_idx_0 = 0U;
    }
    if (empty_non_axis_sizes || ((result_tmp != 0) && (nx + 1 != 0))) {
        sizes_idx_0 = static_cast<short>(result_tmp);
    } else {
        sizes_idx_0 = 0;
    }
    jcol = sizes_idx_0;
    r.set_size(input_sizes_idx_0 + sizes_idx_0, itilerow);
    for (i = 0; i < itilerow; i++) {
        nx = input_sizes_idx_0;
        for (i1 = 0; i1 < nx; i1++) {
            r[i1 + r.size(0) * i] = 0.0;
        }
    }
    for (i = 0; i < itilerow; i++) {
        for (i1 = 0; i1 < jcol; i1++) {
            r[(i1 + input_sizes_idx_0) + r.size(0) * i] =
                Rt[i1 + sizes_idx_0 * i];
        }
    }
    getCandidates(r, edge, peak, locs);
    f0.set_size(locs.size(0));
    nx = locs.size(0);
    for (i = 0; i < nx; i++) {
        f0[i] = 12000.0 / locs[i];
    }
}

void d_NCF(const ::coder::array<double, 2U> &y, ::coder::array<double, 1U> &f0)
{
    array<creal_T, 2U> x;
    array<double, 2U> Rt;
    array<double, 2U> b_c1;
    array<double, 2U> b_x;
    array<double, 2U> b_y;
    array<double, 2U> c1;
    array<double, 2U> c_y;
    array<double, 2U> r;
    array<double, 2U> result;
    array<double, 2U> varargin_1;
    array<double, 1U> locs;
    array<double, 1U> peak;
    double edge[2];
    int i;
    int i1;
    int i2;
    int ibmat;
    int itilerow;
    int jcol;
    int nx;
    int result_tmp;
    short input_sizes_idx_0;
    short sizes_idx_0;
    boolean_T empty_non_axis_sizes;
    edge[0] = 55.0;
    edge[1] = 441.0;
    d_fft(y, x);
    nx = x.size(1) << 12;
    c1.set_size(4096, x.size(1));
    for (ibmat = 0; ibmat < nx; ibmat++) {
        c1[ibmat] = rt_hypotd_snf(x[ibmat].re, x[ibmat].im);
    }
    b_y.set_size(4096, c1.size(1));
    nx = c1.size(1) << 12;
    for (ibmat = 0; ibmat < nx; ibmat++) {
        b_y[ibmat] = c1[ibmat] * c1[ibmat];
    }
    if (b_y.size(1) == 0) {
        x.set_size(4096, 0);
    } else {
        nx = b_y.size(1);
        x.set_size(4096, b_y.size(1));
        for (ibmat = 0; ibmat < nx; ibmat++) {
            ::coder::internal::FFTImplementationCallback::g_doHalfLengthRadix2(
                b_y, ibmat << 12, *(creal_T(*)[4096]) & x[4096 * ibmat]);
        }
        nx = 4096 * x.size(1);
        x.set_size(4096, x.size(1));
        for (i = 0; i < nx; i++) {
            x[i].re = 0.000244140625 * x[i].re;
            x[i].im = 0.000244140625 * x[i].im;
        }
    }
    c1.set_size(4096, x.size(1));
    nx = 4096 * x.size(1);
    for (i = 0; i < nx; i++) {
        c1[i] = x[i].re / 64.0;
    }
    c_y.set_size(1, 441);
    for (i = 0; i < 441; i++) {
        c_y[i] = static_cast<double>(i) + 1.0;
    }
    nx = c1.size(1);
    varargin_1.set_size(441, c1.size(1));
    for (i = 0; i < nx; i++) {
        for (i1 = 0; i1 < 441; i1++) {
            varargin_1[i1 + varargin_1.size(0) * i] =
                c1[(static_cast<int>(c_y[i1]) + 4096 * i) + 3654];
        }
    }
    if (c1.size(1) != 0) {
        itilerow = c1.size(1);
    } else {
        itilerow = 0;
    }
    empty_non_axis_sizes = (itilerow == 0);
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        input_sizes_idx_0 = 441;
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        sizes_idx_0 = 442;
    } else {
        sizes_idx_0 = 0;
    }
    ibmat = input_sizes_idx_0;
    nx = c1.size(1);
    b_c1.set_size(442, c1.size(1));
    for (i = 0; i < nx; i++) {
        for (i1 = 0; i1 < 442; i1++) {
            b_c1[i1 + b_c1.size(0) * i] = c1[i1 + 4096 * i];
        }
    }
    jcol = sizes_idx_0;
    i = input_sizes_idx_0 + sizes_idx_0;
    result.set_size(i, itilerow);
    for (i1 = 0; i1 < itilerow; i1++) {
        for (i2 = 0; i2 < ibmat; i2++) {
            result[i2 + result.size(0) * i1] =
                varargin_1[i2 + input_sizes_idx_0 * i1];
        }
    }
    for (i1 = 0; i1 < itilerow; i1++) {
        for (i2 = 0; i2 < jcol; i2++) {
            result[(i2 + input_sizes_idx_0) + result.size(0) * i1] =
                b_c1[i2 + sizes_idx_0 * i1];
        }
    }
    nx = c1.size(1);
    b_c1.set_size(442, c1.size(1));
    for (i1 = 0; i1 < nx; i1++) {
        for (i2 = 0; i2 < 442; i2++) {
            b_c1[i2 + b_c1.size(0) * i1] = c1[i2 + 4096 * i1];
        }
    }
    Rt.set_size(i, itilerow);
    for (i = 0; i < itilerow; i++) {
        for (i1 = 0; i1 < ibmat; i1++) {
            Rt[i1 + Rt.size(0) * i] = varargin_1[i1 + input_sizes_idx_0 * i];
        }
    }
    for (i = 0; i < itilerow; i++) {
        for (i1 = 0; i1 < jcol; i1++) {
            Rt[(i1 + input_sizes_idx_0) + Rt.size(0) * i] =
                b_c1[i1 + sizes_idx_0 * i];
        }
    }
    if (497 > result.size(0)) {
        i = -1;
        i1 = -1;
    } else {
        i = 495;
        i1 = Rt.size(0) - 1;
    }
    nx = result.size(1);
    b_x.set_size(1, result.size(1));
    for (i2 = 0; i2 < nx; i2++) {
        b_x[i2] = result[result.size(0) * i2 + 441];
    }
    nx = result.size(1) - 1;
    for (ibmat = 0; ibmat <= nx; ibmat++) {
        b_x[ibmat] = sqrt(b_x[ibmat]);
    }
    result_tmp = i1 - i;
    result.set_size(result_tmp, b_x.size(1));
    nx = b_x.size(1);
    for (jcol = 0; jcol < nx; jcol++) {
        ibmat = jcol * result_tmp;
        for (itilerow = 0; itilerow < result_tmp; itilerow++) {
            result[ibmat + itilerow] = b_x[jcol];
        }
    }
    nx = Rt.size(1) - 1;
    for (i1 = 0; i1 <= nx; i1++) {
        for (i2 = 0; i2 < result_tmp; i2++) {
            Rt[i2 + result_tmp * i1] = Rt[((i + i2) + Rt.size(0) * i1) + 1] /
                                       result[i2 + result.size(0) * i1];
        }
    }
    Rt.set_size(result_tmp, nx + 1);
    if (nx + 1 != 0) {
        itilerow = nx + 1;
    } else if ((result_tmp != 0) && (nx + 1 != 0)) {
        itilerow = nx + 1;
    } else {
        itilerow = nx + 1;
    }
    empty_non_axis_sizes = (itilerow == 0);
    if (empty_non_axis_sizes || (nx + 1 != 0)) {
        input_sizes_idx_0 = 54;
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || ((result_tmp != 0) && (nx + 1 != 0))) {
        sizes_idx_0 = static_cast<short>(result_tmp);
    } else {
        sizes_idx_0 = 0;
    }
    jcol = sizes_idx_0;
    r.set_size(input_sizes_idx_0 + sizes_idx_0, itilerow);
    for (i = 0; i < itilerow; i++) {
        nx = input_sizes_idx_0;
        for (i1 = 0; i1 < nx; i1++) {
            r[i1 + r.size(0) * i] = 0.0;
        }
    }
    for (i = 0; i < itilerow; i++) {
        for (i1 = 0; i1 < jcol; i1++) {
            r[(i1 + input_sizes_idx_0) + r.size(0) * i] =
                Rt[i1 + sizes_idx_0 * i];
        }
    }
    getCandidates(r, edge, peak, locs);
    f0.set_size(locs.size(0));
    nx = locs.size(0);
    for (i = 0; i < nx; i++) {
        f0[i] = 22050.0 / locs[i];
    }
}

void e_NCF(const ::coder::array<double, 2U> &y, ::coder::array<double, 1U> &f0)
{
    array<creal_T, 2U> x;
    array<double, 2U> Rt;
    array<double, 2U> b_c1;
    array<double, 2U> b_x;
    array<double, 2U> b_y;
    array<double, 2U> c1;
    array<double, 2U> c_y;
    array<double, 2U> r;
    array<double, 2U> result;
    array<double, 2U> varargin_1;
    array<double, 1U> locs;
    array<double, 1U> peak;
    double edge[2];
    int i;
    int i1;
    int i2;
    int ibmat;
    int itilerow;
    int jcol;
    int nx;
    int result_tmp;
    short input_sizes_idx_0;
    short sizes_idx_0;
    boolean_T empty_non_axis_sizes;
    edge[0] = 60.0;
    edge[1] = 480.0;
    e_fft(y, x);
    nx = x.size(1) << 12;
    c1.set_size(4096, x.size(1));
    for (ibmat = 0; ibmat < nx; ibmat++) {
        c1[ibmat] = rt_hypotd_snf(x[ibmat].re, x[ibmat].im);
    }
    b_y.set_size(4096, c1.size(1));
    nx = c1.size(1) << 12;
    for (ibmat = 0; ibmat < nx; ibmat++) {
        b_y[ibmat] = c1[ibmat] * c1[ibmat];
    }
    if (b_y.size(1) == 0) {
        x.set_size(4096, 0);
    } else {
        nx = b_y.size(1);
        x.set_size(4096, b_y.size(1));
        for (ibmat = 0; ibmat < nx; ibmat++) {
            ::coder::internal::FFTImplementationCallback::g_doHalfLengthRadix2(
                b_y, ibmat << 12, *(creal_T(*)[4096]) & x[4096 * ibmat]);
        }
        nx = 4096 * x.size(1);
        x.set_size(4096, x.size(1));
        for (i = 0; i < nx; i++) {
            x[i].re = 0.000244140625 * x[i].re;
            x[i].im = 0.000244140625 * x[i].im;
        }
    }
    c1.set_size(4096, x.size(1));
    nx = 4096 * x.size(1);
    for (i = 0; i < nx; i++) {
        c1[i] = x[i].re / 64.0;
    }
    c_y.set_size(1, 480);
    for (i = 0; i < 480; i++) {
        c_y[i] = static_cast<double>(i) + 1.0;
    }
    nx = c1.size(1);
    varargin_1.set_size(480, c1.size(1));
    for (i = 0; i < nx; i++) {
        for (i1 = 0; i1 < 480; i1++) {
            varargin_1[i1 + varargin_1.size(0) * i] =
                c1[(static_cast<int>(c_y[i1]) + 4096 * i) + 3615];
        }
    }
    if (c1.size(1) != 0) {
        itilerow = c1.size(1);
    } else {
        itilerow = 0;
    }
    empty_non_axis_sizes = (itilerow == 0);
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        input_sizes_idx_0 = 480;
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        sizes_idx_0 = 481;
    } else {
        sizes_idx_0 = 0;
    }
    ibmat = input_sizes_idx_0;
    nx = c1.size(1);
    b_c1.set_size(481, c1.size(1));
    for (i = 0; i < nx; i++) {
        for (i1 = 0; i1 < 481; i1++) {
            b_c1[i1 + b_c1.size(0) * i] = c1[i1 + 4096 * i];
        }
    }
    jcol = sizes_idx_0;
    i = input_sizes_idx_0 + sizes_idx_0;
    result.set_size(i, itilerow);
    for (i1 = 0; i1 < itilerow; i1++) {
        for (i2 = 0; i2 < ibmat; i2++) {
            result[i2 + result.size(0) * i1] =
                varargin_1[i2 + input_sizes_idx_0 * i1];
        }
    }
    for (i1 = 0; i1 < itilerow; i1++) {
        for (i2 = 0; i2 < jcol; i2++) {
            result[(i2 + input_sizes_idx_0) + result.size(0) * i1] =
                b_c1[i2 + sizes_idx_0 * i1];
        }
    }
    nx = c1.size(1);
    b_c1.set_size(481, c1.size(1));
    for (i1 = 0; i1 < nx; i1++) {
        for (i2 = 0; i2 < 481; i2++) {
            b_c1[i2 + b_c1.size(0) * i1] = c1[i2 + 4096 * i1];
        }
    }
    Rt.set_size(i, itilerow);
    for (i = 0; i < itilerow; i++) {
        for (i1 = 0; i1 < ibmat; i1++) {
            Rt[i1 + Rt.size(0) * i] = varargin_1[i1 + input_sizes_idx_0 * i];
        }
    }
    for (i = 0; i < itilerow; i++) {
        for (i1 = 0; i1 < jcol; i1++) {
            Rt[(i1 + input_sizes_idx_0) + Rt.size(0) * i] =
                b_c1[i1 + sizes_idx_0 * i];
        }
    }
    if (541 > result.size(0)) {
        i = -1;
        i1 = -1;
    } else {
        i = 539;
        i1 = Rt.size(0) - 1;
    }
    nx = result.size(1);
    b_x.set_size(1, result.size(1));
    for (i2 = 0; i2 < nx; i2++) {
        b_x[i2] = result[result.size(0) * i2 + 480];
    }
    nx = result.size(1) - 1;
    for (ibmat = 0; ibmat <= nx; ibmat++) {
        b_x[ibmat] = sqrt(b_x[ibmat]);
    }
    result_tmp = i1 - i;
    result.set_size(result_tmp, b_x.size(1));
    nx = b_x.size(1);
    for (jcol = 0; jcol < nx; jcol++) {
        ibmat = jcol * result_tmp;
        for (itilerow = 0; itilerow < result_tmp; itilerow++) {
            result[ibmat + itilerow] = b_x[jcol];
        }
    }
    nx = Rt.size(1) - 1;
    for (i1 = 0; i1 <= nx; i1++) {
        for (i2 = 0; i2 < result_tmp; i2++) {
            Rt[i2 + result_tmp * i1] = Rt[((i + i2) + Rt.size(0) * i1) + 1] /
                                       result[i2 + result.size(0) * i1];
        }
    }
    Rt.set_size(result_tmp, nx + 1);
    if (nx + 1 != 0) {
        itilerow = nx + 1;
    } else if ((result_tmp != 0) && (nx + 1 != 0)) {
        itilerow = nx + 1;
    } else {
        itilerow = nx + 1;
    }
    empty_non_axis_sizes = (itilerow == 0);
    if (empty_non_axis_sizes || (nx + 1 != 0)) {
        input_sizes_idx_0 = 59;
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || ((result_tmp != 0) && (nx + 1 != 0))) {
        sizes_idx_0 = static_cast<short>(result_tmp);
    } else {
        sizes_idx_0 = 0;
    }
    jcol = sizes_idx_0;
    r.set_size(input_sizes_idx_0 + sizes_idx_0, itilerow);
    for (i = 0; i < itilerow; i++) {
        nx = input_sizes_idx_0;
        for (i1 = 0; i1 < nx; i1++) {
            r[i1 + r.size(0) * i] = 0.0;
        }
    }
    for (i = 0; i < itilerow; i++) {
        for (i1 = 0; i1 < jcol; i1++) {
            r[(i1 + input_sizes_idx_0) + r.size(0) * i] =
                Rt[i1 + sizes_idx_0 * i];
        }
    }
    getCandidates(r, edge, peak, locs);
    f0.set_size(locs.size(0));
    nx = locs.size(0);
    for (i = 0; i < nx; i++) {
        f0[i] = 24000.0 / locs[i];
    }
}

void f_NCF(const ::coder::array<double, 2U> &y, ::coder::array<double, 1U> &f0)
{
    array<creal_T, 2U> x;
    array<double, 2U> Rt;
    array<double, 2U> b_c1;
    array<double, 2U> b_x;
    array<double, 2U> b_y;
    array<double, 2U> c1;
    array<double, 2U> c_y;
    array<double, 2U> r;
    array<double, 2U> result;
    array<double, 2U> varargin_1;
    array<double, 1U> locs;
    array<double, 1U> peak;
    double edge[2];
    int i;
    int i1;
    int i2;
    int ibmat;
    int itilerow;
    int jcol;
    int nx;
    int result_tmp;
    short input_sizes_idx_0;
    short sizes_idx_0;
    boolean_T empty_non_axis_sizes;
    edge[0] = 110.0;
    edge[1] = 882.0;
    f_fft(y, x);
    nx = x.size(1) << 13;
    c1.set_size(8192, x.size(1));
    for (ibmat = 0; ibmat < nx; ibmat++) {
        c1[ibmat] = rt_hypotd_snf(x[ibmat].re, x[ibmat].im);
    }
    b_y.set_size(8192, c1.size(1));
    nx = c1.size(1) << 13;
    for (ibmat = 0; ibmat < nx; ibmat++) {
        b_y[ibmat] = c1[ibmat] * c1[ibmat];
    }
    if (b_y.size(1) == 0) {
        x.set_size(8192, 0);
    } else {
        nx = b_y.size(1);
        x.set_size(8192, b_y.size(1));
        for (ibmat = 0; ibmat < nx; ibmat++) {
            ::coder::internal::FFTImplementationCallback::j_doHalfLengthRadix2(
                b_y, ibmat << 13, *(creal_T(*)[8192]) & x[8192 * ibmat]);
        }
        nx = 8192 * x.size(1);
        x.set_size(8192, x.size(1));
        for (i = 0; i < nx; i++) {
            x[i].re = 0.0001220703125 * x[i].re;
            x[i].im = 0.0001220703125 * x[i].im;
        }
    }
    c1.set_size(8192, x.size(1));
    nx = 8192 * x.size(1);
    for (i = 0; i < nx; i++) {
        c1[i] = x[i].re / 90.509667991878089;
    }
    c_y.set_size(1, 882);
    for (i = 0; i < 882; i++) {
        c_y[i] = static_cast<double>(i) + 1.0;
    }
    nx = c1.size(1);
    varargin_1.set_size(882, c1.size(1));
    for (i = 0; i < nx; i++) {
        for (i1 = 0; i1 < 882; i1++) {
            varargin_1[i1 + varargin_1.size(0) * i] =
                c1[(static_cast<int>(c_y[i1]) + 8192 * i) + 7309];
        }
    }
    if (c1.size(1) != 0) {
        itilerow = c1.size(1);
    } else {
        itilerow = 0;
    }
    empty_non_axis_sizes = (itilerow == 0);
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        input_sizes_idx_0 = 882;
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        sizes_idx_0 = 883;
    } else {
        sizes_idx_0 = 0;
    }
    ibmat = input_sizes_idx_0;
    nx = c1.size(1);
    b_c1.set_size(883, c1.size(1));
    for (i = 0; i < nx; i++) {
        for (i1 = 0; i1 < 883; i1++) {
            b_c1[i1 + b_c1.size(0) * i] = c1[i1 + 8192 * i];
        }
    }
    jcol = sizes_idx_0;
    i = input_sizes_idx_0 + sizes_idx_0;
    result.set_size(i, itilerow);
    for (i1 = 0; i1 < itilerow; i1++) {
        for (i2 = 0; i2 < ibmat; i2++) {
            result[i2 + result.size(0) * i1] =
                varargin_1[i2 + input_sizes_idx_0 * i1];
        }
    }
    for (i1 = 0; i1 < itilerow; i1++) {
        for (i2 = 0; i2 < jcol; i2++) {
            result[(i2 + input_sizes_idx_0) + result.size(0) * i1] =
                b_c1[i2 + sizes_idx_0 * i1];
        }
    }
    nx = c1.size(1);
    b_c1.set_size(883, c1.size(1));
    for (i1 = 0; i1 < nx; i1++) {
        for (i2 = 0; i2 < 883; i2++) {
            b_c1[i2 + b_c1.size(0) * i1] = c1[i2 + 8192 * i1];
        }
    }
    Rt.set_size(i, itilerow);
    for (i = 0; i < itilerow; i++) {
        for (i1 = 0; i1 < ibmat; i1++) {
            Rt[i1 + Rt.size(0) * i] = varargin_1[i1 + input_sizes_idx_0 * i];
        }
    }
    for (i = 0; i < itilerow; i++) {
        for (i1 = 0; i1 < jcol; i1++) {
            Rt[(i1 + input_sizes_idx_0) + Rt.size(0) * i] =
                b_c1[i1 + sizes_idx_0 * i];
        }
    }
    if (993 > result.size(0)) {
        i = -1;
        i1 = -1;
    } else {
        i = 991;
        i1 = Rt.size(0) - 1;
    }
    nx = result.size(1);
    b_x.set_size(1, result.size(1));
    for (i2 = 0; i2 < nx; i2++) {
        b_x[i2] = result[result.size(0) * i2 + 882];
    }
    nx = result.size(1) - 1;
    for (ibmat = 0; ibmat <= nx; ibmat++) {
        b_x[ibmat] = sqrt(b_x[ibmat]);
    }
    result_tmp = i1 - i;
    result.set_size(result_tmp, b_x.size(1));
    nx = b_x.size(1);
    for (jcol = 0; jcol < nx; jcol++) {
        ibmat = jcol * result_tmp;
        for (itilerow = 0; itilerow < result_tmp; itilerow++) {
            result[ibmat + itilerow] = b_x[jcol];
        }
    }
    nx = Rt.size(1) - 1;
    for (i1 = 0; i1 <= nx; i1++) {
        for (i2 = 0; i2 < result_tmp; i2++) {
            Rt[i2 + result_tmp * i1] = Rt[((i + i2) + Rt.size(0) * i1) + 1] /
                                       result[i2 + result.size(0) * i1];
        }
    }
    Rt.set_size(result_tmp, nx + 1);
    if (nx + 1 != 0) {
        itilerow = nx + 1;
    } else if ((result_tmp != 0) && (nx + 1 != 0)) {
        itilerow = nx + 1;
    } else {
        itilerow = nx + 1;
    }
    empty_non_axis_sizes = (itilerow == 0);
    if (empty_non_axis_sizes || (nx + 1 != 0)) {
        input_sizes_idx_0 = 109;
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || ((result_tmp != 0) && (nx + 1 != 0))) {
        sizes_idx_0 = static_cast<short>(result_tmp);
    } else {
        sizes_idx_0 = 0;
    }
    jcol = sizes_idx_0;
    r.set_size(input_sizes_idx_0 + sizes_idx_0, itilerow);
    for (i = 0; i < itilerow; i++) {
        nx = input_sizes_idx_0;
        for (i1 = 0; i1 < nx; i1++) {
            r[i1 + r.size(0) * i] = 0.0;
        }
    }
    for (i = 0; i < itilerow; i++) {
        for (i1 = 0; i1 < jcol; i1++) {
            r[(i1 + input_sizes_idx_0) + r.size(0) * i] =
                Rt[i1 + sizes_idx_0 * i];
        }
    }
    getCandidates(r, edge, peak, locs);
    f0.set_size(locs.size(0));
    nx = locs.size(0);
    for (i = 0; i < nx; i++) {
        f0[i] = 44100.0 / locs[i];
    }
}

void g_NCF(const ::coder::array<double, 2U> &y, ::coder::array<double, 1U> &f0)
{
    array<creal_T, 2U> x;
    array<double, 2U> Rt;
    array<double, 2U> b_c1;
    array<double, 2U> b_x;
    array<double, 2U> b_y;
    array<double, 2U> c1;
    array<double, 2U> c_y;
    array<double, 2U> r;
    array<double, 2U> result;
    array<double, 2U> varargin_1;
    array<double, 1U> locs;
    array<double, 1U> peak;
    double edge[2];
    int i;
    int i1;
    int i2;
    int ibmat;
    int itilerow;
    int jcol;
    int nx;
    int result_tmp;
    short input_sizes_idx_0;
    short sizes_idx_0;
    boolean_T empty_non_axis_sizes;
    edge[0] = 120.0;
    edge[1] = 960.0;
    g_fft(y, x);
    nx = x.size(1) << 13;
    c1.set_size(8192, x.size(1));
    for (ibmat = 0; ibmat < nx; ibmat++) {
        c1[ibmat] = rt_hypotd_snf(x[ibmat].re, x[ibmat].im);
    }
    b_y.set_size(8192, c1.size(1));
    nx = c1.size(1) << 13;
    for (ibmat = 0; ibmat < nx; ibmat++) {
        b_y[ibmat] = c1[ibmat] * c1[ibmat];
    }
    if (b_y.size(1) == 0) {
        x.set_size(8192, 0);
    } else {
        nx = b_y.size(1);
        x.set_size(8192, b_y.size(1));
        for (ibmat = 0; ibmat < nx; ibmat++) {
            ::coder::internal::FFTImplementationCallback::j_doHalfLengthRadix2(
                b_y, ibmat << 13, *(creal_T(*)[8192]) & x[8192 * ibmat]);
        }
        nx = 8192 * x.size(1);
        x.set_size(8192, x.size(1));
        for (i = 0; i < nx; i++) {
            x[i].re = 0.0001220703125 * x[i].re;
            x[i].im = 0.0001220703125 * x[i].im;
        }
    }
    c1.set_size(8192, x.size(1));
    nx = 8192 * x.size(1);
    for (i = 0; i < nx; i++) {
        c1[i] = x[i].re / 90.509667991878089;
    }
    c_y.set_size(1, 960);
    for (i = 0; i < 960; i++) {
        c_y[i] = static_cast<double>(i) + 1.0;
    }
    nx = c1.size(1);
    varargin_1.set_size(960, c1.size(1));
    for (i = 0; i < nx; i++) {
        for (i1 = 0; i1 < 960; i1++) {
            varargin_1[i1 + varargin_1.size(0) * i] =
                c1[(static_cast<int>(c_y[i1]) + 8192 * i) + 7231];
        }
    }
    if (c1.size(1) != 0) {
        itilerow = c1.size(1);
    } else {
        itilerow = 0;
    }
    empty_non_axis_sizes = (itilerow == 0);
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        input_sizes_idx_0 = 960;
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        sizes_idx_0 = 961;
    } else {
        sizes_idx_0 = 0;
    }
    ibmat = input_sizes_idx_0;
    nx = c1.size(1);
    b_c1.set_size(961, c1.size(1));
    for (i = 0; i < nx; i++) {
        for (i1 = 0; i1 < 961; i1++) {
            b_c1[i1 + b_c1.size(0) * i] = c1[i1 + 8192 * i];
        }
    }
    jcol = sizes_idx_0;
    i = input_sizes_idx_0 + sizes_idx_0;
    result.set_size(i, itilerow);
    for (i1 = 0; i1 < itilerow; i1++) {
        for (i2 = 0; i2 < ibmat; i2++) {
            result[i2 + result.size(0) * i1] =
                varargin_1[i2 + input_sizes_idx_0 * i1];
        }
    }
    for (i1 = 0; i1 < itilerow; i1++) {
        for (i2 = 0; i2 < jcol; i2++) {
            result[(i2 + input_sizes_idx_0) + result.size(0) * i1] =
                b_c1[i2 + sizes_idx_0 * i1];
        }
    }
    nx = c1.size(1);
    b_c1.set_size(961, c1.size(1));
    for (i1 = 0; i1 < nx; i1++) {
        for (i2 = 0; i2 < 961; i2++) {
            b_c1[i2 + b_c1.size(0) * i1] = c1[i2 + 8192 * i1];
        }
    }
    Rt.set_size(i, itilerow);
    for (i = 0; i < itilerow; i++) {
        for (i1 = 0; i1 < ibmat; i1++) {
            Rt[i1 + Rt.size(0) * i] = varargin_1[i1 + input_sizes_idx_0 * i];
        }
    }
    for (i = 0; i < itilerow; i++) {
        for (i1 = 0; i1 < jcol; i1++) {
            Rt[(i1 + input_sizes_idx_0) + Rt.size(0) * i] =
                b_c1[i1 + sizes_idx_0 * i];
        }
    }
    if (1081 > result.size(0)) {
        i = -1;
        i1 = -1;
    } else {
        i = 1079;
        i1 = Rt.size(0) - 1;
    }
    nx = result.size(1);
    b_x.set_size(1, result.size(1));
    for (i2 = 0; i2 < nx; i2++) {
        b_x[i2] = result[result.size(0) * i2 + 960];
    }
    nx = result.size(1) - 1;
    for (ibmat = 0; ibmat <= nx; ibmat++) {
        b_x[ibmat] = sqrt(b_x[ibmat]);
    }
    result_tmp = i1 - i;
    result.set_size(result_tmp, b_x.size(1));
    nx = b_x.size(1);
    for (jcol = 0; jcol < nx; jcol++) {
        ibmat = jcol * result_tmp;
        for (itilerow = 0; itilerow < result_tmp; itilerow++) {
            result[ibmat + itilerow] = b_x[jcol];
        }
    }
    nx = Rt.size(1) - 1;
    for (i1 = 0; i1 <= nx; i1++) {
        for (i2 = 0; i2 < result_tmp; i2++) {
            Rt[i2 + result_tmp * i1] = Rt[((i + i2) + Rt.size(0) * i1) + 1] /
                                       result[i2 + result.size(0) * i1];
        }
    }
    Rt.set_size(result_tmp, nx + 1);
    if (nx + 1 != 0) {
        itilerow = nx + 1;
    } else if ((result_tmp != 0) && (nx + 1 != 0)) {
        itilerow = nx + 1;
    } else {
        itilerow = nx + 1;
    }
    empty_non_axis_sizes = (itilerow == 0);
    if (empty_non_axis_sizes || (nx + 1 != 0)) {
        input_sizes_idx_0 = 119;
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || ((result_tmp != 0) && (nx + 1 != 0))) {
        sizes_idx_0 = static_cast<short>(result_tmp);
    } else {
        sizes_idx_0 = 0;
    }
    jcol = sizes_idx_0;
    r.set_size(input_sizes_idx_0 + sizes_idx_0, itilerow);
    for (i = 0; i < itilerow; i++) {
        nx = input_sizes_idx_0;
        for (i1 = 0; i1 < nx; i1++) {
            r[i1 + r.size(0) * i] = 0.0;
        }
    }
    for (i = 0; i < itilerow; i++) {
        for (i1 = 0; i1 < jcol; i1++) {
            r[(i1 + input_sizes_idx_0) + r.size(0) * i] =
                Rt[i1 + sizes_idx_0 * i];
        }
    }
    getCandidates(r, edge, peak, locs);
    f0.set_size(locs.size(0));
    nx = locs.size(0);
    for (i = 0; i < nx; i++) {
        f0[i] = 48000.0 / locs[i];
    }
}

} // namespace pitch
} // namespace internal
} // namespace audio
} // namespace coder
