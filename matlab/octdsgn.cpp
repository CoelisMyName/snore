//
// File: octdsgn.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "octdsgn.h"
#include "butter.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// function [B, A] = octdsgn(Fc, Fs, N)
//
// OCTDSGN  Design of an octave filter.
//     [B,A] = OCTDSGN(Fc,Fs,N) designs a digital octave filter with
//     center frequency Fc for sampling frequency Fs.
//     The filter are designed according to the Order-N specification
//     of the ANSI S1.1-1986 standard. Default value for N is 3.
//     Warning: for meaningful design results, center values used
//     should preferably be in range Fs/200 < Fc < Fs/5.
//     Usage of the filter: Y = FILTER(B,A,X).
//
//     Requires the Signal Processing Toolbox.
//
//     See also OCTSPEC, OCT3DSGN, OCT3SPEC.
//
// Arguments    : double Fc
//                double B[7]
//                double A[7]
// Return Type  : void
//
void octdsgn(double Fc, double B[7], double A[7]) {
    double b_Fc[2];
    //  Author: Christophe Couvreur, Faculte Polytechnique de Mons (Belgium)
    //          couvreur@thor.fpms.ac.be
    //  Last modification: Aug. 22, 1997, 9:00pm.
    //  References:
    //     [1] ANSI S1.1-1986 (ASA 65-1986): Specifications for
    //         Octave-Band and Fractional-Octave-Band Analog and
    //         Digital Filters, 1993.
    // 'octdsgn:24' if (nargin > 3) | (nargin < 2)
    // 'octdsgn:28' if (nargin == 2)
    // 'octdsgn:32' if (Fc > 0.70 * (Fs / 2))
    //  Design Butterworth 2Nth-order octave filter
    //  Note: BUTTER is based on a bilinear transformation, as suggested in [1].
    // W1 = Fc/(Fs/2)*sqrt(1/2);
    // W2 = Fc/(Fs/2)*sqrt(2);
    // 'octdsgn:40' pi = 3.14159265358979;
    // 'octdsgn:41' beta = pi / 2 / N / sin(pi / 2 / N);
    // 'octdsgn:42' alpha = (1 + sqrt(1 + 8 * beta^2)) / 4 / beta;
    // 'octdsgn:43' W1 = Fc / (Fs / 2) * sqrt(1/2) / alpha;
    // 'octdsgn:44' W2 = Fc / (Fs / 2) * sqrt(2) * alpha;
    // 'octdsgn:45' [B, A] = butter(N, [W1, W2]);
    b_Fc[0] = Fc / 22050.0 * 0.70710678118654757 / 0.98505216233236492;
    b_Fc[1] = Fc / 22050.0 * 1.4142135623730951 * 0.98505216233236492;
    coder::butter(b_Fc, B, A);
}

//
// File trailer for octdsgn.cpp
//
// [EOF]
//
