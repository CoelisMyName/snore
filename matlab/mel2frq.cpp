//
// File: mel2frq.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "mel2frq.h"
#include "SnoringRecognition_types.h"
#include "abs.h"
#include "exp.h"
#include "rt_nonfinite.h"
#include "sign.h"

// Function Definitions
//
// function [frq, mr] = mel2frq(mel)
//
// MEL2FRQ  Convert Mel frequency scale to Hertz FRQ=(MEL)
//  frq = mel2frq(mel) converts a vector of Mel frequencies
//  to the corresponding real frequencies.
//    mr gives the corresponding gradients in Hz/mel.
//  The Mel scale corresponds to the perceived pitch of a tone
//
// Arguments    : SnoringRecognitionStackData *SD
//                const double mel[4]
//                double frq[4]
// Return Type  : void
//
void mel2frq(SnoringRecognitionStackData *SD, const double mel[4],
             double frq[4]) {
    double b_dv[4];
    // 	The relationship between mel and frq is given by:
    //
    // 	m = ln(1 + f/700) * 1000 / ln(1+1000/700)
    //
    //   	This means that m(1000) = 1000
    //
    // 	References:
    //
    // 	  [1] S. S. Stevens & J. Volkman "The relation of pitch to
    // 		frequency", American J of Psychology, V 53, p329 1940
    // 	  [2] C. G. M. Fant, "Acoustic description & classification
    // 		of phonetic units", Ericsson Tchnics, No 1 1959
    // 		(reprinted in "Speech Sounds & Features", MIT Press 1973)
    // 	  [3] S. B. Davis & P. Mermelstein, "Comparison of parametric
    // 		representations for monosyllabic word recognition in
    // 		continuously spoken sentences", IEEE ASSP, V 28,
    // 		pp 357-366 Aug 1980
    // 	  [4] J. R. Deller Jr, J. G. Proakis, J. H. L. Hansen,
    // 		"Discrete-Time Processing of Speech Signals", p380,
    // 		Macmillan 1993
    // 	  [5] HTK Reference Manual p73
    //
    //       Copyright (C) Mike Brookes 1998
    //       Version: $Id: mel2frq.m,v 1.7 2010/08/01 08:41:57 dmb Exp $
    //
    //    VOICEBOX is a MATLAB toolbox for speech processing.
    //    Home page: http://www.ee.ic.ac.uk/hp/staff/dmb/voicebox/voicebox.html
    //
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //    This program is free software; you can redistribute it and/or modify
    //    it under the terms of the GNU General Public License as published by
    //    the Free Software Foundation; either version 2 of the License, or
    //    (at your option) any later version.
    //
    //    This program is distributed in the hope that it will be useful,
    //    but WITHOUT ANY WARRANTY; without even the implied warranty of
    //    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    //    GNU General Public License for more details.
    //
    //    You can obtain a copy of the GNU General Public License from
    //    http://www.gnu.org/copyleft/gpl.html or by writing to
    //    Free Software Foundation, Inc.,675 Mass Ave, Cambridge, MA 02139, USA.
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // 'mel2frq:54' if isempty(k)
    // 'mel2frq:58' frq = 700 * sign(mel) .* (exp(abs(mel) / k) - 1);
    frq[0] = mel[0];
    frq[1] = mel[1];
    frq[2] = mel[2];
    frq[3] = mel[3];
    coder::c_sign(frq);
    coder::c_abs(mel, b_dv);
    b_dv[0] /= SD->pd->b_k;
    b_dv[1] /= SD->pd->b_k;
    b_dv[2] /= SD->pd->b_k;
    b_dv[3] /= SD->pd->b_k;
    coder::b_exp(b_dv);
    frq[0] = 700.0 * frq[0] * (b_dv[0] - 1.0);
    frq[1] = 700.0 * frq[1] * (b_dv[1] - 1.0);
    frq[2] = 700.0 * frq[2] * (b_dv[2] - 1.0);
    frq[3] = 700.0 * frq[3] * (b_dv[3] - 1.0);
    // 'mel2frq:59' mr = (700 + abs(frq)) / k;
    // 'mel2frq:61' if ~nargout
}

//
// function [frq, mr] = mel2frq(mel)
//
// MEL2FRQ  Convert Mel frequency scale to Hertz FRQ=(MEL)
//  frq = mel2frq(mel) converts a vector of Mel frequencies
//  to the corresponding real frequencies.
//    mr gives the corresponding gradients in Hz/mel.
//  The Mel scale corresponds to the perceived pitch of a tone
//
// Arguments    : SnoringRecognitionStackData *SD
// Return Type  : void
//
void mel2frq_init(SnoringRecognitionStackData *SD) {
    // 'mel2frq:55' k = 1127.01048;
    SD->pd->b_k = 1127.01048;
}

//
// File trailer for mel2frq.cpp
//
// [EOF]
//
