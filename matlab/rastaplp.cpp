//
// File: rastaplp.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "rastaplp.h"
#include "audspec.h"
#include "dolpc.h"
#include "lifter.h"
#include "lpc2cep.h"
#include "lpc2spec.h"
#include "postaud.h"
#include "powspec.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function [cepstra, spectra, pspectrum, lpcas, F, M] = rastaplp(samples, sr,
// dorasta, modelorder)
//
// [cepstra, spectra, lpcas] = rastaplp(samples, sr, dorasta, modelorder)
//
//  cheap version of log rasta with fixed parameters
//
//  output is matrix of features, row = feature, col = frame
//
//  sr is sampling rate of samples, defaults to 8000
//  dorasta defaults to 1; if 0, just calculate PLP
//  modelorder is order of PLP model, defaults to 8.  0 -> no PLP
//
//  rastaplp(d, sr, 0, 12) is pretty close to the unix command line
//  feacalc -dith -delta 0 -ras no -plp 12 -dom cep ...
//  except during very quiet areas, where our approach of adding noise
//  in the time domain is different from rasta's approach
//
//  2003-04-12 dpwe@ee.columbia.edu after shire@icsi.berkeley.edu's version
//
// Arguments    : const coder::array<double, 1U> &samples
//                double sr
//                coder::array<double, 2U> &cepstra
//                coder::array<double, 2U> &spectra
// Return Type  : void
//
void rastaplp(const coder::array<double, 1U> &samples, double sr,
              coder::array<double, 2U> &cepstra,
              coder::array<double, 2U> &spectra) {
    coder::array<double, 2U> F;
    coder::array<double, 2U> M;
    coder::array<double, 2U> aspectrum;
    coder::array<double, 2U> b_lpcas;
    coder::array<double, 2U> lpcas;
    coder::array<double, 2U> postspectrum;
    coder::array<double, 2U> pspectrum;
    int i;
    int loop_ub;
    // 'rastaplp:19' if nargin < 2
    // 'rastaplp:23' if nargin < 3
    // 'rastaplp:27' if nargin < 4
    //  add miniscule amount of noise
    // samples = samples + randn(size(samples))*0.0001;
    //  first compute power spectrum
    // 'rastaplp:35' pspectrum = powspec(samples, sr);
    powspec(samples, sr, pspectrum);
    //  next group to critical bands
    // 'rastaplp:38' aspectrum = audspec(pspectrum, sr);
    audspec(pspectrum, sr, aspectrum);
    // 'rastaplp:39' nbands = size(aspectrum, 1);
    // 'rastaplp:41' if dorasta ~= 0
    //  do final auditory compressions
    // 'rastaplp:55' postspectrum = postaud(aspectrum, sr / 2);
    postaud(aspectrum, sr / 2.0, postspectrum);
    //  2012-09-03 bug: was sr
    // 'rastaplp:57' if modelorder > 0
    //  LPC analysis
    // 'rastaplp:60' lpcas = dolpc(postspectrum, modelorder);
    dolpc(postspectrum, lpcas);
    //  convert lpc to cepstra
    // 'rastaplp:63' cepstra = lpc2cep(lpcas, modelorder + 1);
    b_lpcas.set_size(13, lpcas.size(1));
    loop_ub = lpcas.size(0) * lpcas.size(1) - 1;
    for (i = 0; i <= loop_ub; i++) {
        b_lpcas[i] = lpcas[i];
    }
    lpc2cep(b_lpcas, cepstra);
    //  .. or to spectra
    // 'rastaplp:66' [spectra, F, M] = lpc2spec(lpcas, nbands);
    lpc2spec(lpcas, static_cast<double>(aspectrum.size(0)), spectra, F, M);
    // 'rastaplp:76' cepstra = lifter(cepstra, 0.6);
    b_lpcas.set_size(13, cepstra.size(1));
    loop_ub = cepstra.size(0) * cepstra.size(1) - 1;
    for (i = 0; i <= loop_ub; i++) {
        b_lpcas[i] = cepstra[i];
    }
    lifter(b_lpcas, cepstra);
}

//
// File trailer for rastaplp.cpp
//
// [EOF]
//
