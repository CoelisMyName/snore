#include "gammatoneFilterBank.h"
#include "computeGammatoneCoefficients.h"
#include "filter.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <string.h>

namespace coder {
void gammatoneFilterBank::matlabCodegenDestructor()
{
    if (!this->matlabCodegenIsDeleted) {
        this->matlabCodegenIsDeleted = true;
        if (this->isInitialized == 1) {
            this->isInitialized = 2;
            if (this->isSetupComplete) {
                this->pNumChannels = -1.0;
            }
        }
    }
}

void b_gammatoneFilterBank::matlabCodegenDestructor()
{
    if (!this->matlabCodegenIsDeleted) {
        this->matlabCodegenIsDeleted = true;
        if (this->isInitialized == 1) {
            this->isInitialized = 2;
            if (this->isSetupComplete) {
                this->pNumChannels = -1.0;
            }
        }
    }
}

void c_gammatoneFilterBank::matlabCodegenDestructor()
{
    if (!this->matlabCodegenIsDeleted) {
        this->matlabCodegenIsDeleted = true;
        if (this->isInitialized == 1) {
            this->isInitialized = 2;
            if (this->isSetupComplete) {
                this->pNumChannels = -1.0;
            }
        }
    }
}

void d_gammatoneFilterBank::matlabCodegenDestructor()
{
    if (!this->matlabCodegenIsDeleted) {
        this->matlabCodegenIsDeleted = true;
        if (this->isInitialized == 1) {
            this->isInitialized = 2;
            if (this->isSetupComplete) {
                this->pNumChannels = -1.0;
            }
        }
    }
}

void e_gammatoneFilterBank::matlabCodegenDestructor()
{
    if (!this->matlabCodegenIsDeleted) {
        this->matlabCodegenIsDeleted = true;
        if (this->isInitialized == 1) {
            this->isInitialized = 2;
            if (this->isSetupComplete) {
                this->pNumChannels = -1.0;
            }
        }
    }
}

void f_gammatoneFilterBank::matlabCodegenDestructor()
{
    if (!this->matlabCodegenIsDeleted) {
        this->matlabCodegenIsDeleted = true;
        if (this->isInitialized == 1) {
            this->isInitialized = 2;
            if (this->isSetupComplete) {
                this->pNumChannels = -1.0;
            }
        }
    }
}

void b_gammatoneFilterBank::SystemCore_step(
    const ::coder::array<double, 1U> &varargin_1,
    ::coder::array<double, 2U> &varargout_1)
{
    static const double b_dv[29] = {
        49.999999999999979, 82.7233005714591,   119.28550240725417,
        160.13696236809187, 205.78087047917549, 256.77944800003439,
        313.76087261471372, 377.42701604372127, 448.56208938617988,
        528.042302681641,   616.84665767373031, 716.06900671605956,
        826.93152635662,    950.79977156224845, 1089.1994960143713,
        1243.8354456609175, 1416.6123570149662, 1609.6584188477907,
        1825.3514862669485, 2066.3483700727124, 2335.6175621660427,
        2636.4758001050532, 2972.6289211958369, 3348.2175093400683,
        3767.8678968968775, 4236.7491497770952, 4760.6367376868284,
        5345.9836737819587, 5999.9999999999991};
    array<double, 1U> b_y1;
    array<double, 1U> y2;
    array<double, 1U> y3;
    double b_obj[3];
    double obj[3];
    double c_obj[2];
    unsigned int inSize[8];
    int i;
    int k;
    boolean_T exitg1;
    if (this->isInitialized != 1) {
        this->isSetupComplete = false;
        this->isInitialized = 1;
        this->inputVarSize[0].f1[0] =
            static_cast<unsigned int>(varargin_1.size(0));
        this->inputVarSize[0].f1[1] = 1U;
        for (i = 0; i < 6; i++) {
            this->inputVarSize[0].f1[i + 2] = 1U;
        }
        memcpy(&this->pCenterFrequencies[0], &b_dv[0], 29U * sizeof(double));
        audio::internal::b_computeGammatoneCoefficients(
            this->pSampleRateDialog, this->pCenterFrequencies, this->pCoeffs);
        this->pNumChannels = 1.0;
        this->isSetupComplete = true;
        this->TunablePropsChanged = false;
        memset(&this->pStates[0], 0, 232U * sizeof(double));
    }
    if (this->TunablePropsChanged) {
        this->TunablePropsChanged = false;
        audio::internal::b_computeGammatoneCoefficients(
            this->pSampleRateDialog, this->pCenterFrequencies, this->pCoeffs);
    }
    inSize[0] = static_cast<unsigned int>(varargin_1.size(0));
    inSize[1] = 1U;
    for (i = 0; i < 6; i++) {
        inSize[i + 2] = 1U;
    }
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 8)) {
        if (this->inputVarSize[0].f1[k] != inSize[k]) {
            for (i = 0; i < 8; i++) {
                this->inputVarSize[0].f1[i] = inSize[i];
            }
            exitg1 = true;
        } else {
            k++;
        }
    }
    varargout_1.set_size(varargin_1.size(0), 29);
    k = varargin_1.size(0) * 29;
    for (i = 0; i < k; i++) {
        varargout_1[i] = 0.0;
    }
    k = varargin_1.size(0);
    for (int chan = 0; chan < 29; chan++) {
        int loop_ub;
        obj[0] = this->pCoeffs[24 * chan];
        b_obj[0] = this->pCoeffs[24 * chan + 12];
        obj[1] = this->pCoeffs[24 * chan + 4];
        b_obj[1] = this->pCoeffs[24 * chan + 16];
        obj[2] = this->pCoeffs[24 * chan + 8];
        b_obj[2] = this->pCoeffs[24 * chan + 20];
        y2.set_size(k);
        for (i = 0; i < k; i++) {
            y2[i] = varargin_1[i];
        }
        c_obj[0] = this->pStates[chan << 3];
        c_obj[1] = this->pStates[1 + (chan << 3)];
        filter(obj, b_obj, y2, c_obj, b_y1,
               *(double(*)[2]) & this->pStates[chan << 3]);
        obj[0] = this->pCoeffs[24 * chan + 1];
        b_obj[0] = this->pCoeffs[24 * chan + 13];
        obj[1] = this->pCoeffs[24 * chan + 5];
        b_obj[1] = this->pCoeffs[24 * chan + 17];
        obj[2] = this->pCoeffs[24 * chan + 9];
        b_obj[2] = this->pCoeffs[24 * chan + 21];
        c_obj[0] = this->pStates[(chan << 3) + 2];
        c_obj[1] = this->pStates[(chan << 3) + 3];
        filter(obj, b_obj, b_y1, c_obj, y2,
               *(double(*)[2]) & this->pStates[(chan << 3) + 2]);
        obj[0] = this->pCoeffs[24 * chan + 2];
        b_obj[0] = this->pCoeffs[24 * chan + 14];
        obj[1] = this->pCoeffs[24 * chan + 6];
        b_obj[1] = this->pCoeffs[24 * chan + 18];
        obj[2] = this->pCoeffs[24 * chan + 10];
        b_obj[2] = this->pCoeffs[24 * chan + 22];
        c_obj[0] = this->pStates[(chan << 3) + 4];
        c_obj[1] = this->pStates[(chan << 3) + 5];
        filter(obj, b_obj, y2, c_obj, y3,
               *(double(*)[2]) & this->pStates[(chan << 3) + 4]);
        obj[0] = this->pCoeffs[24 * chan + 3];
        b_obj[0] = this->pCoeffs[24 * chan + 15];
        obj[1] = this->pCoeffs[24 * chan + 7];
        b_obj[1] = this->pCoeffs[24 * chan + 19];
        obj[2] = this->pCoeffs[24 * chan + 11];
        b_obj[2] = this->pCoeffs[24 * chan + 23];
        c_obj[0] = this->pStates[(chan << 3) + 6];
        c_obj[1] = this->pStates[(chan << 3) + 7];
        filter(obj, b_obj, y3, c_obj, b_y1,
               *(double(*)[2]) & this->pStates[(chan << 3) + 6]);
        loop_ub = b_y1.size(0);
        for (i = 0; i < loop_ub; i++) {
            varargout_1[i + varargout_1.size(0) * chan] = b_y1[i];
        }
    }
}

gammatoneFilterBank::gammatoneFilterBank()
{
    this->matlabCodegenIsDeleted = true;
}

b_gammatoneFilterBank::b_gammatoneFilterBank()
{
    this->matlabCodegenIsDeleted = true;
}

c_gammatoneFilterBank::c_gammatoneFilterBank()
{
    this->matlabCodegenIsDeleted = true;
}

d_gammatoneFilterBank::d_gammatoneFilterBank()
{
    this->matlabCodegenIsDeleted = true;
}

e_gammatoneFilterBank::e_gammatoneFilterBank()
{
    this->matlabCodegenIsDeleted = true;
}

f_gammatoneFilterBank::f_gammatoneFilterBank()
{
    this->matlabCodegenIsDeleted = true;
}

gammatoneFilterBank::~gammatoneFilterBank()
{
    this->matlabCodegenDestructor();
}

b_gammatoneFilterBank::~b_gammatoneFilterBank()
{
    this->matlabCodegenDestructor();
}

c_gammatoneFilterBank::~c_gammatoneFilterBank()
{
    this->matlabCodegenDestructor();
}

d_gammatoneFilterBank::~d_gammatoneFilterBank()
{
    this->matlabCodegenDestructor();
}

e_gammatoneFilterBank::~e_gammatoneFilterBank()
{
    this->matlabCodegenDestructor();
}

f_gammatoneFilterBank::~f_gammatoneFilterBank()
{
    this->matlabCodegenDestructor();
}

void b_gammatoneFilterBank::handle_matlabCodegenDestructor()
{
    if (!this->matlabCodegenIsDeleted) {
        this->matlabCodegenIsDeleted = true;
        if (this->isInitialized == 1) {
            this->isInitialized = 2;
            if (this->isSetupComplete) {
                this->pNumChannels = -1.0;
            }
        }
    }
}

void gammatoneFilterBank::step(const ::coder::array<double, 1U> &varargin_1,
                               ::coder::array<double, 2U> &varargout_1)
{
    static const double b_dv[26] = {49.999999999999979, 82.044965307267248,
                                    117.77132504423244, 157.60200570861718,
                                    202.00852050241792, 251.51655107683092,
                                    306.71217052002123, 368.24878125508866,
                                    436.85484997865314, 513.34253120579331,
                                    598.61728150634724, 693.688578245326,
                                    799.68186971524176, 917.85189812530382,
                                    1049.5975531642205, 1196.4784319721941,
                                    1360.2333015580643, 1542.8006822185719,
                                    1746.3417956250378, 1973.2661492355169,
                                    2226.2600598991589, 2508.3184543134967,
                                    2822.7803227865488, 3173.3682460032642,
                                    3564.2324627117609, 4000.0};
    array<double, 1U> b_y1;
    array<double, 1U> y2;
    array<double, 1U> y3;
    double b_obj[3];
    double obj[3];
    double c_obj[2];
    unsigned int inSize[8];
    int i;
    int k;
    boolean_T exitg1;
    if (this->isInitialized != 1) {
        this->isSetupComplete = false;
        this->isInitialized = 1;
        this->inputVarSize[0].f1[0] =
            static_cast<unsigned int>(varargin_1.size(0));
        this->inputVarSize[0].f1[1] = 1U;
        for (i = 0; i < 6; i++) {
            this->inputVarSize[0].f1[i + 2] = 1U;
        }
        memcpy(&this->pCenterFrequencies[0], &b_dv[0], 26U * sizeof(double));
        audio::internal::computeGammatoneCoefficients(
            this->pSampleRateDialog, this->pCenterFrequencies, this->pCoeffs);
        this->pNumChannels = 1.0;
        this->isSetupComplete = true;
        this->TunablePropsChanged = false;
        memset(&this->pStates[0], 0, 208U * sizeof(double));
    }
    if (this->TunablePropsChanged) {
        this->TunablePropsChanged = false;
        audio::internal::computeGammatoneCoefficients(
            this->pSampleRateDialog, this->pCenterFrequencies, this->pCoeffs);
    }
    inSize[0] = static_cast<unsigned int>(varargin_1.size(0));
    inSize[1] = 1U;
    for (i = 0; i < 6; i++) {
        inSize[i + 2] = 1U;
    }
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 8)) {
        if (this->inputVarSize[0].f1[k] != inSize[k]) {
            for (i = 0; i < 8; i++) {
                this->inputVarSize[0].f1[i] = inSize[i];
            }
            exitg1 = true;
        } else {
            k++;
        }
    }
    varargout_1.set_size(varargin_1.size(0), 26);
    k = varargin_1.size(0) * 26;
    for (i = 0; i < k; i++) {
        varargout_1[i] = 0.0;
    }
    k = varargin_1.size(0);
    for (int chan = 0; chan < 26; chan++) {
        int loop_ub;
        obj[0] = this->pCoeffs[24 * chan];
        b_obj[0] = this->pCoeffs[24 * chan + 12];
        obj[1] = this->pCoeffs[24 * chan + 4];
        b_obj[1] = this->pCoeffs[24 * chan + 16];
        obj[2] = this->pCoeffs[24 * chan + 8];
        b_obj[2] = this->pCoeffs[24 * chan + 20];
        y2.set_size(k);
        for (i = 0; i < k; i++) {
            y2[i] = varargin_1[i];
        }
        c_obj[0] = this->pStates[chan << 3];
        c_obj[1] = this->pStates[1 + (chan << 3)];
        filter(obj, b_obj, y2, c_obj, b_y1,
               *(double(*)[2]) & this->pStates[chan << 3]);
        obj[0] = this->pCoeffs[24 * chan + 1];
        b_obj[0] = this->pCoeffs[24 * chan + 13];
        obj[1] = this->pCoeffs[24 * chan + 5];
        b_obj[1] = this->pCoeffs[24 * chan + 17];
        obj[2] = this->pCoeffs[24 * chan + 9];
        b_obj[2] = this->pCoeffs[24 * chan + 21];
        c_obj[0] = this->pStates[(chan << 3) + 2];
        c_obj[1] = this->pStates[(chan << 3) + 3];
        filter(obj, b_obj, b_y1, c_obj, y2,
               *(double(*)[2]) & this->pStates[(chan << 3) + 2]);
        obj[0] = this->pCoeffs[24 * chan + 2];
        b_obj[0] = this->pCoeffs[24 * chan + 14];
        obj[1] = this->pCoeffs[24 * chan + 6];
        b_obj[1] = this->pCoeffs[24 * chan + 18];
        obj[2] = this->pCoeffs[24 * chan + 10];
        b_obj[2] = this->pCoeffs[24 * chan + 22];
        c_obj[0] = this->pStates[(chan << 3) + 4];
        c_obj[1] = this->pStates[(chan << 3) + 5];
        filter(obj, b_obj, y2, c_obj, y3,
               *(double(*)[2]) & this->pStates[(chan << 3) + 4]);
        obj[0] = this->pCoeffs[24 * chan + 3];
        b_obj[0] = this->pCoeffs[24 * chan + 15];
        obj[1] = this->pCoeffs[24 * chan + 7];
        b_obj[1] = this->pCoeffs[24 * chan + 19];
        obj[2] = this->pCoeffs[24 * chan + 11];
        b_obj[2] = this->pCoeffs[24 * chan + 23];
        c_obj[0] = this->pStates[(chan << 3) + 6];
        c_obj[1] = this->pStates[(chan << 3) + 7];
        filter(obj, b_obj, y3, c_obj, b_y1,
               *(double(*)[2]) & this->pStates[(chan << 3) + 6]);
        loop_ub = b_y1.size(0);
        for (i = 0; i < loop_ub; i++) {
            varargout_1[i + varargout_1.size(0) * chan] = b_y1[i];
        }
    }
}

void b_gammatoneFilterBank::step(const ::coder::array<double, 1U> &varargin_1,
                                 ::coder::array<double, 2U> &varargout_1)
{
    static const double b_dv[29] = {49.999999999999979,
                                    81.817505991619782,
                                    117.26432986498368,
                                    156.75445593081074,
                                    200.7490903236193,
                                    249.76204743929193,
                                    304.3657507857946,
                                    365.19791833112862,
                                    432.96901042685579,
                                    508.47052729167484,
                                    592.58425296156008,
                                    686.29255366678069,
                                    790.6898509107898,
                                    906.99540324535212,
                                    1036.5675460205709,
                                    1180.9195554161922,
                                    1341.7373220305965,
                                    1520.8990404377503,
                                    1720.4971446669219,
                                    1942.862745790158,
                                    2190.592857024712,
                                    2466.580724313018,
                                    2774.0496166118219,
                                    3116.5904705280445,
                                    3498.2038289539969,
                                    3923.3465635042949,
                                    4396.9839264268858,
                                    4924.647539903809,
                                    5512.5};
    array<double, 1U> b_y1;
    array<double, 1U> y2;
    array<double, 1U> y3;
    double b_obj[3];
    double obj[3];
    double c_obj[2];
    unsigned int inSize[8];
    int i;
    int k;
    boolean_T exitg1;
    if (this->isInitialized != 1) {
        this->isSetupComplete = false;
        this->isInitialized = 1;
        this->inputVarSize[0].f1[0] =
            static_cast<unsigned int>(varargin_1.size(0));
        this->inputVarSize[0].f1[1] = 1U;
        for (i = 0; i < 6; i++) {
            this->inputVarSize[0].f1[i + 2] = 1U;
        }
        memcpy(&this->pCenterFrequencies[0], &b_dv[0], 29U * sizeof(double));
        audio::internal::b_computeGammatoneCoefficients(
            this->pSampleRateDialog, this->pCenterFrequencies, this->pCoeffs);
        this->pNumChannels = 1.0;
        this->isSetupComplete = true;
        this->TunablePropsChanged = false;
        memset(&this->pStates[0], 0, 232U * sizeof(double));
    }
    if (this->TunablePropsChanged) {
        this->TunablePropsChanged = false;
        audio::internal::b_computeGammatoneCoefficients(
            this->pSampleRateDialog, this->pCenterFrequencies, this->pCoeffs);
    }
    inSize[0] = static_cast<unsigned int>(varargin_1.size(0));
    inSize[1] = 1U;
    for (i = 0; i < 6; i++) {
        inSize[i + 2] = 1U;
    }
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 8)) {
        if (this->inputVarSize[0].f1[k] != inSize[k]) {
            for (i = 0; i < 8; i++) {
                this->inputVarSize[0].f1[i] = inSize[i];
            }
            exitg1 = true;
        } else {
            k++;
        }
    }
    varargout_1.set_size(varargin_1.size(0), 29);
    k = varargin_1.size(0) * 29;
    for (i = 0; i < k; i++) {
        varargout_1[i] = 0.0;
    }
    k = varargin_1.size(0);
    for (int chan = 0; chan < 29; chan++) {
        int loop_ub;
        obj[0] = this->pCoeffs[24 * chan];
        b_obj[0] = this->pCoeffs[24 * chan + 12];
        obj[1] = this->pCoeffs[24 * chan + 4];
        b_obj[1] = this->pCoeffs[24 * chan + 16];
        obj[2] = this->pCoeffs[24 * chan + 8];
        b_obj[2] = this->pCoeffs[24 * chan + 20];
        y2.set_size(k);
        for (i = 0; i < k; i++) {
            y2[i] = varargin_1[i];
        }
        c_obj[0] = this->pStates[chan << 3];
        c_obj[1] = this->pStates[1 + (chan << 3)];
        filter(obj, b_obj, y2, c_obj, b_y1,
               *(double(*)[2]) & this->pStates[chan << 3]);
        obj[0] = this->pCoeffs[24 * chan + 1];
        b_obj[0] = this->pCoeffs[24 * chan + 13];
        obj[1] = this->pCoeffs[24 * chan + 5];
        b_obj[1] = this->pCoeffs[24 * chan + 17];
        obj[2] = this->pCoeffs[24 * chan + 9];
        b_obj[2] = this->pCoeffs[24 * chan + 21];
        c_obj[0] = this->pStates[(chan << 3) + 2];
        c_obj[1] = this->pStates[(chan << 3) + 3];
        filter(obj, b_obj, b_y1, c_obj, y2,
               *(double(*)[2]) & this->pStates[(chan << 3) + 2]);
        obj[0] = this->pCoeffs[24 * chan + 2];
        b_obj[0] = this->pCoeffs[24 * chan + 14];
        obj[1] = this->pCoeffs[24 * chan + 6];
        b_obj[1] = this->pCoeffs[24 * chan + 18];
        obj[2] = this->pCoeffs[24 * chan + 10];
        b_obj[2] = this->pCoeffs[24 * chan + 22];
        c_obj[0] = this->pStates[(chan << 3) + 4];
        c_obj[1] = this->pStates[(chan << 3) + 5];
        filter(obj, b_obj, y2, c_obj, y3,
               *(double(*)[2]) & this->pStates[(chan << 3) + 4]);
        obj[0] = this->pCoeffs[24 * chan + 3];
        b_obj[0] = this->pCoeffs[24 * chan + 15];
        obj[1] = this->pCoeffs[24 * chan + 7];
        b_obj[1] = this->pCoeffs[24 * chan + 19];
        obj[2] = this->pCoeffs[24 * chan + 11];
        b_obj[2] = this->pCoeffs[24 * chan + 23];
        c_obj[0] = this->pStates[(chan << 3) + 6];
        c_obj[1] = this->pStates[(chan << 3) + 7];
        filter(obj, b_obj, y3, c_obj, b_y1,
               *(double(*)[2]) & this->pStates[(chan << 3) + 6]);
        loop_ub = b_y1.size(0);
        for (i = 0; i < loop_ub; i++) {
            varargout_1[i + varargout_1.size(0) * chan] = b_y1[i];
        }
    }
}

void f_gammatoneFilterBank::step(const ::coder::array<double, 1U> &varargin_1,
                                 ::coder::array<double, 2U> &varargout_1)
{
    static const double b_dv[42] = {
        49.999999999999979, 82.087577614812787, 117.86634695584952,
        157.76092394529971, 202.24477016137683, 251.84581179415014,
        307.15270497747667, 368.82182185285296, 437.58504027451863,
        514.2584296026165,  599.75193566582061, 695.08017983280354,
        801.374500353964,   919.89637887785682, 1052.0524114857878,
        1199.4110019180841, 1363.720975104203,  1546.9323318986847,
        1751.2193913363558, 1979.0065950548731, 2232.9972801267886,
        2516.2057617718738, 2831.9931067014886, 3184.1070216465469,
        3576.7263304588423, 4014.51056763191,   4502.6552768082747,
        5046.95367054573,   5653.8653831095116, 6330.59313223598,
        7085.1681996757115, 7926.5457449834612, 8864.7110837218079,
        9910.7981913687054, 11077.221839311909, 12377.824931096091,
        13828.042787482475, 15445.086330026114, 17248.146337160284,
        19258.621196861757, 21500.370858824561, 24000.000000000007};
    array<double, 1U> b_y1;
    array<double, 1U> y2;
    array<double, 1U> y3;
    double b_obj[3];
    double obj[3];
    double c_obj[2];
    unsigned int inSize[8];
    int i;
    int k;
    boolean_T exitg1;
    if (this->isInitialized != 1) {
        this->isSetupComplete = false;
        this->isInitialized = 1;
        this->inputVarSize[0].f1[0] =
            static_cast<unsigned int>(varargin_1.size(0));
        this->inputVarSize[0].f1[1] = 1U;
        for (i = 0; i < 6; i++) {
            this->inputVarSize[0].f1[i + 2] = 1U;
        }
        memcpy(&this->pCenterFrequencies[0], &b_dv[0], 42U * sizeof(double));
        audio::internal::f_computeGammatoneCoefficients(
            this->pSampleRateDialog, this->pCenterFrequencies, this->pCoeffs);
        this->pNumChannels = 1.0;
        this->isSetupComplete = true;
        this->TunablePropsChanged = false;
        memset(&this->pStates[0], 0, 336U * sizeof(double));
    }
    if (this->TunablePropsChanged) {
        this->TunablePropsChanged = false;
        audio::internal::f_computeGammatoneCoefficients(
            this->pSampleRateDialog, this->pCenterFrequencies, this->pCoeffs);
    }
    inSize[0] = static_cast<unsigned int>(varargin_1.size(0));
    inSize[1] = 1U;
    for (i = 0; i < 6; i++) {
        inSize[i + 2] = 1U;
    }
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 8)) {
        if (this->inputVarSize[0].f1[k] != inSize[k]) {
            for (i = 0; i < 8; i++) {
                this->inputVarSize[0].f1[i] = inSize[i];
            }
            exitg1 = true;
        } else {
            k++;
        }
    }
    varargout_1.set_size(varargin_1.size(0), 42);
    k = varargin_1.size(0) * 42;
    for (i = 0; i < k; i++) {
        varargout_1[i] = 0.0;
    }
    k = varargin_1.size(0);
    for (int chan = 0; chan < 42; chan++) {
        int loop_ub;
        obj[0] = this->pCoeffs[24 * chan];
        b_obj[0] = this->pCoeffs[24 * chan + 12];
        obj[1] = this->pCoeffs[24 * chan + 4];
        b_obj[1] = this->pCoeffs[24 * chan + 16];
        obj[2] = this->pCoeffs[24 * chan + 8];
        b_obj[2] = this->pCoeffs[24 * chan + 20];
        y2.set_size(k);
        for (i = 0; i < k; i++) {
            y2[i] = varargin_1[i];
        }
        c_obj[0] = this->pStates[chan << 3];
        c_obj[1] = this->pStates[1 + (chan << 3)];
        filter(obj, b_obj, y2, c_obj, b_y1,
               *(double(*)[2]) & this->pStates[chan << 3]);
        obj[0] = this->pCoeffs[24 * chan + 1];
        b_obj[0] = this->pCoeffs[24 * chan + 13];
        obj[1] = this->pCoeffs[24 * chan + 5];
        b_obj[1] = this->pCoeffs[24 * chan + 17];
        obj[2] = this->pCoeffs[24 * chan + 9];
        b_obj[2] = this->pCoeffs[24 * chan + 21];
        c_obj[0] = this->pStates[(chan << 3) + 2];
        c_obj[1] = this->pStates[(chan << 3) + 3];
        filter(obj, b_obj, b_y1, c_obj, y2,
               *(double(*)[2]) & this->pStates[(chan << 3) + 2]);
        obj[0] = this->pCoeffs[24 * chan + 2];
        b_obj[0] = this->pCoeffs[24 * chan + 14];
        obj[1] = this->pCoeffs[24 * chan + 6];
        b_obj[1] = this->pCoeffs[24 * chan + 18];
        obj[2] = this->pCoeffs[24 * chan + 10];
        b_obj[2] = this->pCoeffs[24 * chan + 22];
        c_obj[0] = this->pStates[(chan << 3) + 4];
        c_obj[1] = this->pStates[(chan << 3) + 5];
        filter(obj, b_obj, y2, c_obj, y3,
               *(double(*)[2]) & this->pStates[(chan << 3) + 4]);
        obj[0] = this->pCoeffs[24 * chan + 3];
        b_obj[0] = this->pCoeffs[24 * chan + 15];
        obj[1] = this->pCoeffs[24 * chan + 7];
        b_obj[1] = this->pCoeffs[24 * chan + 19];
        obj[2] = this->pCoeffs[24 * chan + 11];
        b_obj[2] = this->pCoeffs[24 * chan + 23];
        c_obj[0] = this->pStates[(chan << 3) + 6];
        c_obj[1] = this->pStates[(chan << 3) + 7];
        filter(obj, b_obj, y3, c_obj, b_y1,
               *(double(*)[2]) & this->pStates[(chan << 3) + 6]);
        loop_ub = b_y1.size(0);
        for (i = 0; i < loop_ub; i++) {
            varargout_1[i + varargout_1.size(0) * chan] = b_y1[i];
        }
    }
}

void e_gammatoneFilterBank::step(const ::coder::array<double, 1U> &varargin_1,
                                 ::coder::array<double, 2U> &varargout_1)
{
    static const double b_dv[41] = {49.999999999999979,
                                    82.281871716003181,
                                    118.29977170418434,
                                    158.48607598577638,
                                    203.32320009191875,
                                    253.34939020939345,
                                    309.16518454413489,
                                    371.44062246779794,
                                    440.92328798941145,
                                    518.44728410978155,
                                    604.94324579106888,
                                    701.44951174199127,
                                    809.12458913008436,
                                    929.2610608533596,
                                    1063.3011023208687,
                                    1212.8537940130018,
                                    1379.714437649729,
                                    1565.8861078472733,
                                    1773.6036979795601,
                                    2005.3607489024116,
                                    2263.9393826052715,
                                    2552.44370012826,
                                    2874.3370446690647,
                                    3233.4835772037413,
                                    3634.1946637149817,
                                    4081.2806308821987,
                                    4580.1085115334072,
                                    5136.6664730627863,
                                    5757.63570224331,
                                    6450.47060937401,
                                    7223.4883145705644,
                                    8085.9684904353489,
                                    9048.26475966582,
                                    10121.928984871241,
                                    11319.849942631761,
                                    12656.408046509472,
                                    14147.647976379954,
                                    15811.471286409113,
                                    17667.851303833173,
                                    19739.072898288974,
                                    22050.0};
    array<double, 1U> b_y1;
    array<double, 1U> y2;
    array<double, 1U> y3;
    double b_obj[3];
    double obj[3];
    double c_obj[2];
    unsigned int inSize[8];
    int i;
    int k;
    boolean_T exitg1;
    if (this->isInitialized != 1) {
        this->isSetupComplete = false;
        this->isInitialized = 1;
        this->inputVarSize[0].f1[0] =
            static_cast<unsigned int>(varargin_1.size(0));
        this->inputVarSize[0].f1[1] = 1U;
        for (i = 0; i < 6; i++) {
            this->inputVarSize[0].f1[i + 2] = 1U;
        }
        memcpy(&this->pCenterFrequencies[0], &b_dv[0], 41U * sizeof(double));
        audio::internal::e_computeGammatoneCoefficients(
            this->pSampleRateDialog, this->pCenterFrequencies, this->pCoeffs);
        this->pNumChannels = 1.0;
        this->isSetupComplete = true;
        this->TunablePropsChanged = false;
        memset(&this->pStates[0], 0, 328U * sizeof(double));
    }
    if (this->TunablePropsChanged) {
        this->TunablePropsChanged = false;
        audio::internal::e_computeGammatoneCoefficients(
            this->pSampleRateDialog, this->pCenterFrequencies, this->pCoeffs);
    }
    inSize[0] = static_cast<unsigned int>(varargin_1.size(0));
    inSize[1] = 1U;
    for (i = 0; i < 6; i++) {
        inSize[i + 2] = 1U;
    }
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 8)) {
        if (this->inputVarSize[0].f1[k] != inSize[k]) {
            for (i = 0; i < 8; i++) {
                this->inputVarSize[0].f1[i] = inSize[i];
            }
            exitg1 = true;
        } else {
            k++;
        }
    }
    varargout_1.set_size(varargin_1.size(0), 41);
    k = varargin_1.size(0) * 41;
    for (i = 0; i < k; i++) {
        varargout_1[i] = 0.0;
    }
    k = varargin_1.size(0);
    for (int chan = 0; chan < 41; chan++) {
        int loop_ub;
        obj[0] = this->pCoeffs[24 * chan];
        b_obj[0] = this->pCoeffs[24 * chan + 12];
        obj[1] = this->pCoeffs[24 * chan + 4];
        b_obj[1] = this->pCoeffs[24 * chan + 16];
        obj[2] = this->pCoeffs[24 * chan + 8];
        b_obj[2] = this->pCoeffs[24 * chan + 20];
        y2.set_size(k);
        for (i = 0; i < k; i++) {
            y2[i] = varargin_1[i];
        }
        c_obj[0] = this->pStates[chan << 3];
        c_obj[1] = this->pStates[1 + (chan << 3)];
        filter(obj, b_obj, y2, c_obj, b_y1,
               *(double(*)[2]) & this->pStates[chan << 3]);
        obj[0] = this->pCoeffs[24 * chan + 1];
        b_obj[0] = this->pCoeffs[24 * chan + 13];
        obj[1] = this->pCoeffs[24 * chan + 5];
        b_obj[1] = this->pCoeffs[24 * chan + 17];
        obj[2] = this->pCoeffs[24 * chan + 9];
        b_obj[2] = this->pCoeffs[24 * chan + 21];
        c_obj[0] = this->pStates[(chan << 3) + 2];
        c_obj[1] = this->pStates[(chan << 3) + 3];
        filter(obj, b_obj, b_y1, c_obj, y2,
               *(double(*)[2]) & this->pStates[(chan << 3) + 2]);
        obj[0] = this->pCoeffs[24 * chan + 2];
        b_obj[0] = this->pCoeffs[24 * chan + 14];
        obj[1] = this->pCoeffs[24 * chan + 6];
        b_obj[1] = this->pCoeffs[24 * chan + 18];
        obj[2] = this->pCoeffs[24 * chan + 10];
        b_obj[2] = this->pCoeffs[24 * chan + 22];
        c_obj[0] = this->pStates[(chan << 3) + 4];
        c_obj[1] = this->pStates[(chan << 3) + 5];
        filter(obj, b_obj, y2, c_obj, y3,
               *(double(*)[2]) & this->pStates[(chan << 3) + 4]);
        obj[0] = this->pCoeffs[24 * chan + 3];
        b_obj[0] = this->pCoeffs[24 * chan + 15];
        obj[1] = this->pCoeffs[24 * chan + 7];
        b_obj[1] = this->pCoeffs[24 * chan + 19];
        obj[2] = this->pCoeffs[24 * chan + 11];
        b_obj[2] = this->pCoeffs[24 * chan + 23];
        c_obj[0] = this->pStates[(chan << 3) + 6];
        c_obj[1] = this->pStates[(chan << 3) + 7];
        filter(obj, b_obj, y3, c_obj, b_y1,
               *(double(*)[2]) & this->pStates[(chan << 3) + 6]);
        loop_ub = b_y1.size(0);
        for (i = 0; i < loop_ub; i++) {
            varargout_1[i + varargout_1.size(0) * chan] = b_y1[i];
        }
    }
}

void d_gammatoneFilterBank::step(const ::coder::array<double, 1U> &varargin_1,
                                 ::coder::array<double, 2U> &varargout_1)
{
    static const double b_dv[36] = {
        49.999999999999979, 81.817295931464358, 117.26386182309389,
        156.7536737862504,  200.74792850906724, 249.76042951621,
        304.36358781745292, 365.19510702591151, 432.96543102061025,
        508.46604113372757, 592.5786997643529,  686.28574837379074,
        790.681580131442,   906.98542119889214, 1036.5555699232573,
        1180.9052602375923, 1341.7203345350733, 1520.8789324162917,
        1720.473425252135,  1942.8348527333328, 2190.5601467981405,
        2466.5424608830995, 2774.0049587084673, 3116.538457213418,
        3498.143363268277,  3923.276393937489,  4396.9026259335933,
        4924.5534821413921, 5512.3913324298719, 6167.2814632168411,
        6896.8722563100409, 7709.6845134236273, 8615.2109695801,
        9624.0271576026134, 10747.91491847044,  11999.999999999996};
    array<double, 1U> b_y1;
    array<double, 1U> y2;
    array<double, 1U> y3;
    double b_obj[3];
    double obj[3];
    double c_obj[2];
    unsigned int inSize[8];
    int i;
    int k;
    boolean_T exitg1;
    if (this->isInitialized != 1) {
        this->isSetupComplete = false;
        this->isInitialized = 1;
        this->inputVarSize[0].f1[0] =
            static_cast<unsigned int>(varargin_1.size(0));
        this->inputVarSize[0].f1[1] = 1U;
        for (i = 0; i < 6; i++) {
            this->inputVarSize[0].f1[i + 2] = 1U;
        }
        memcpy(&this->pCenterFrequencies[0], &b_dv[0], 36U * sizeof(double));
        audio::internal::d_computeGammatoneCoefficients(
            this->pSampleRateDialog, this->pCenterFrequencies, this->pCoeffs);
        this->pNumChannels = 1.0;
        this->isSetupComplete = true;
        this->TunablePropsChanged = false;
        memset(&this->pStates[0], 0, 288U * sizeof(double));
    }
    if (this->TunablePropsChanged) {
        this->TunablePropsChanged = false;
        audio::internal::d_computeGammatoneCoefficients(
            this->pSampleRateDialog, this->pCenterFrequencies, this->pCoeffs);
    }
    inSize[0] = static_cast<unsigned int>(varargin_1.size(0));
    inSize[1] = 1U;
    for (i = 0; i < 6; i++) {
        inSize[i + 2] = 1U;
    }
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 8)) {
        if (this->inputVarSize[0].f1[k] != inSize[k]) {
            for (i = 0; i < 8; i++) {
                this->inputVarSize[0].f1[i] = inSize[i];
            }
            exitg1 = true;
        } else {
            k++;
        }
    }
    varargout_1.set_size(varargin_1.size(0), 36);
    k = varargin_1.size(0) * 36;
    for (i = 0; i < k; i++) {
        varargout_1[i] = 0.0;
    }
    k = varargin_1.size(0);
    for (int chan = 0; chan < 36; chan++) {
        int loop_ub;
        obj[0] = this->pCoeffs[24 * chan];
        b_obj[0] = this->pCoeffs[24 * chan + 12];
        obj[1] = this->pCoeffs[24 * chan + 4];
        b_obj[1] = this->pCoeffs[24 * chan + 16];
        obj[2] = this->pCoeffs[24 * chan + 8];
        b_obj[2] = this->pCoeffs[24 * chan + 20];
        y2.set_size(k);
        for (i = 0; i < k; i++) {
            y2[i] = varargin_1[i];
        }
        c_obj[0] = this->pStates[chan << 3];
        c_obj[1] = this->pStates[1 + (chan << 3)];
        filter(obj, b_obj, y2, c_obj, b_y1,
               *(double(*)[2]) & this->pStates[chan << 3]);
        obj[0] = this->pCoeffs[24 * chan + 1];
        b_obj[0] = this->pCoeffs[24 * chan + 13];
        obj[1] = this->pCoeffs[24 * chan + 5];
        b_obj[1] = this->pCoeffs[24 * chan + 17];
        obj[2] = this->pCoeffs[24 * chan + 9];
        b_obj[2] = this->pCoeffs[24 * chan + 21];
        c_obj[0] = this->pStates[(chan << 3) + 2];
        c_obj[1] = this->pStates[(chan << 3) + 3];
        filter(obj, b_obj, b_y1, c_obj, y2,
               *(double(*)[2]) & this->pStates[(chan << 3) + 2]);
        obj[0] = this->pCoeffs[24 * chan + 2];
        b_obj[0] = this->pCoeffs[24 * chan + 14];
        obj[1] = this->pCoeffs[24 * chan + 6];
        b_obj[1] = this->pCoeffs[24 * chan + 18];
        obj[2] = this->pCoeffs[24 * chan + 10];
        b_obj[2] = this->pCoeffs[24 * chan + 22];
        c_obj[0] = this->pStates[(chan << 3) + 4];
        c_obj[1] = this->pStates[(chan << 3) + 5];
        filter(obj, b_obj, y2, c_obj, y3,
               *(double(*)[2]) & this->pStates[(chan << 3) + 4]);
        obj[0] = this->pCoeffs[24 * chan + 3];
        b_obj[0] = this->pCoeffs[24 * chan + 15];
        obj[1] = this->pCoeffs[24 * chan + 7];
        b_obj[1] = this->pCoeffs[24 * chan + 19];
        obj[2] = this->pCoeffs[24 * chan + 11];
        b_obj[2] = this->pCoeffs[24 * chan + 23];
        c_obj[0] = this->pStates[(chan << 3) + 6];
        c_obj[1] = this->pStates[(chan << 3) + 7];
        filter(obj, b_obj, y3, c_obj, b_y1,
               *(double(*)[2]) & this->pStates[(chan << 3) + 6]);
        loop_ub = b_y1.size(0);
        for (i = 0; i < loop_ub; i++) {
            varargout_1[i + varargout_1.size(0) * chan] = b_y1[i];
        }
    }
}

void c_gammatoneFilterBank::step(const ::coder::array<double, 1U> &varargin_1,
                                 ::coder::array<double, 2U> &varargout_1)
{
    static const double b_dv[35] = {49.999999999999979,
                                    82.045229975099559,
                                    117.77191519136613,
                                    157.60299262579284,
                                    202.00998756482898,
                                    251.51859557981521,
                                    306.71490577703815,
                                    368.25233899402241,
                                    436.85938307729356,
                                    513.34821681280289,
                                    598.62432460018044,
                                    693.69721569053684,
                                    799.69237488349233,
                                    917.86458615728623,
                                    1049.6127869587654,
                                    1196.4966290001983,
                                    1360.2549416117083,
                                    1542.8263162207995,
                                    1746.3720556406281,
                                    1973.3017598435654,
                                    2226.3018511076511,
                                    2508.3673762201965,
                                    2822.8374622169977,
                                    3173.4348453866605,
                                    3564.3099414893359,
                                    4000.0899788986258,
                                    4485.9337763109816,
                                    5027.5928134879432,
                                    5631.4793179943717,
                                    6304.7421739519368,
                                    7055.351551425314,
                                    7892.1932582942254,
                                    8825.1739315607356,
                                    9865.33831335965,
                                    11025.0};
    array<double, 1U> b_y1;
    array<double, 1U> y2;
    array<double, 1U> y3;
    double b_obj[3];
    double obj[3];
    double c_obj[2];
    unsigned int inSize[8];
    int i;
    int k;
    boolean_T exitg1;
    if (this->isInitialized != 1) {
        this->isSetupComplete = false;
        this->isInitialized = 1;
        this->inputVarSize[0].f1[0] =
            static_cast<unsigned int>(varargin_1.size(0));
        this->inputVarSize[0].f1[1] = 1U;
        for (i = 0; i < 6; i++) {
            this->inputVarSize[0].f1[i + 2] = 1U;
        }
        memcpy(&this->pCenterFrequencies[0], &b_dv[0], 35U * sizeof(double));
        audio::internal::c_computeGammatoneCoefficients(
            this->pSampleRateDialog, this->pCenterFrequencies, this->pCoeffs);
        this->pNumChannels = 1.0;
        this->isSetupComplete = true;
        this->TunablePropsChanged = false;
        memset(&this->pStates[0], 0, 280U * sizeof(double));
    }
    if (this->TunablePropsChanged) {
        this->TunablePropsChanged = false;
        audio::internal::c_computeGammatoneCoefficients(
            this->pSampleRateDialog, this->pCenterFrequencies, this->pCoeffs);
    }
    inSize[0] = static_cast<unsigned int>(varargin_1.size(0));
    inSize[1] = 1U;
    for (i = 0; i < 6; i++) {
        inSize[i + 2] = 1U;
    }
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 8)) {
        if (this->inputVarSize[0].f1[k] != inSize[k]) {
            for (i = 0; i < 8; i++) {
                this->inputVarSize[0].f1[i] = inSize[i];
            }
            exitg1 = true;
        } else {
            k++;
        }
    }
    varargout_1.set_size(varargin_1.size(0), 35);
    k = varargin_1.size(0) * 35;
    for (i = 0; i < k; i++) {
        varargout_1[i] = 0.0;
    }
    k = varargin_1.size(0);
    for (int chan = 0; chan < 35; chan++) {
        int loop_ub;
        obj[0] = this->pCoeffs[24 * chan];
        b_obj[0] = this->pCoeffs[24 * chan + 12];
        obj[1] = this->pCoeffs[24 * chan + 4];
        b_obj[1] = this->pCoeffs[24 * chan + 16];
        obj[2] = this->pCoeffs[24 * chan + 8];
        b_obj[2] = this->pCoeffs[24 * chan + 20];
        y2.set_size(k);
        for (i = 0; i < k; i++) {
            y2[i] = varargin_1[i];
        }
        c_obj[0] = this->pStates[chan << 3];
        c_obj[1] = this->pStates[1 + (chan << 3)];
        filter(obj, b_obj, y2, c_obj, b_y1,
               *(double(*)[2]) & this->pStates[chan << 3]);
        obj[0] = this->pCoeffs[24 * chan + 1];
        b_obj[0] = this->pCoeffs[24 * chan + 13];
        obj[1] = this->pCoeffs[24 * chan + 5];
        b_obj[1] = this->pCoeffs[24 * chan + 17];
        obj[2] = this->pCoeffs[24 * chan + 9];
        b_obj[2] = this->pCoeffs[24 * chan + 21];
        c_obj[0] = this->pStates[(chan << 3) + 2];
        c_obj[1] = this->pStates[(chan << 3) + 3];
        filter(obj, b_obj, b_y1, c_obj, y2,
               *(double(*)[2]) & this->pStates[(chan << 3) + 2]);
        obj[0] = this->pCoeffs[24 * chan + 2];
        b_obj[0] = this->pCoeffs[24 * chan + 14];
        obj[1] = this->pCoeffs[24 * chan + 6];
        b_obj[1] = this->pCoeffs[24 * chan + 18];
        obj[2] = this->pCoeffs[24 * chan + 10];
        b_obj[2] = this->pCoeffs[24 * chan + 22];
        c_obj[0] = this->pStates[(chan << 3) + 4];
        c_obj[1] = this->pStates[(chan << 3) + 5];
        filter(obj, b_obj, y2, c_obj, y3,
               *(double(*)[2]) & this->pStates[(chan << 3) + 4]);
        obj[0] = this->pCoeffs[24 * chan + 3];
        b_obj[0] = this->pCoeffs[24 * chan + 15];
        obj[1] = this->pCoeffs[24 * chan + 7];
        b_obj[1] = this->pCoeffs[24 * chan + 19];
        obj[2] = this->pCoeffs[24 * chan + 11];
        b_obj[2] = this->pCoeffs[24 * chan + 23];
        c_obj[0] = this->pStates[(chan << 3) + 6];
        c_obj[1] = this->pStates[(chan << 3) + 7];
        filter(obj, b_obj, y3, c_obj, b_y1,
               *(double(*)[2]) & this->pStates[(chan << 3) + 6]);
        loop_ub = b_y1.size(0);
        for (i = 0; i < loop_ub; i++) {
            varargout_1[i + varargout_1.size(0) * chan] = b_y1[i];
        }
    }
}

} // namespace coder
