//
// File: patient_classifier.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "patient_classifier.h"
#include "GMM_score.h"
#include "SnoringRecognition_types.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function label_OSA = patient_classifier(MFCC_feature, BARKEE, period_mean,
// period_max, period_min, period_var,...
//     cep, Formant1, Formant2, Formant3, GTCCmean, PR800mean, PR800max,
//     PR800min, PR800var,... SE_mean, SE_max, SE_min, SE_var)
//
// Arguments    : SnoringRecognitionStackData *SD
//                const coder::array<double, 2U> &MFCC_feature
//                const coder::array<double, 2U> &BARKEE
//                const coder::array<double, 1U> &period_mean
//                const coder::array<double, 1U> &period_max
//                const coder::array<double, 1U> &period_min
//                const coder::array<double, 1U> &period_var
//                const coder::array<double, 2U> &cep
//                const coder::array<double, 1U> &Formant1
//                const coder::array<double, 1U> &Formant2
//                const coder::array<double, 1U> &Formant3
//                const coder::array<double, 2U> &GTCCmean
//                const coder::array<double, 1U> &PR800mean
//                const coder::array<double, 1U> &PR800max
//                const coder::array<double, 1U> &PR800min
//                const coder::array<double, 1U> &PR800var
//                const coder::array<double, 1U> &SE_mean
//                const coder::array<double, 1U> &SE_max
//                const coder::array<double, 1U> &SE_min
//                const coder::array<double, 1U> &SE_var
// Return Type  : double
//
double patient_classifier(SnoringRecognitionStackData *SD,
                          const coder::array<double, 2U> &MFCC_feature,
                          const coder::array<double, 2U> &BARKEE,
                          const coder::array<double, 1U> &period_mean,
                          const coder::array<double, 1U> &period_max,
                          const coder::array<double, 1U> &period_min,
                          const coder::array<double, 1U> &period_var,
                          const coder::array<double, 2U> &cep,
                          const coder::array<double, 1U> &Formant1,
                          const coder::array<double, 1U> &Formant2,
                          const coder::array<double, 1U> &Formant3,
                          const coder::array<double, 2U> &GTCCmean,
                          const coder::array<double, 1U> &PR800mean,
                          const coder::array<double, 1U> &PR800max,
                          const coder::array<double, 1U> &PR800min,
                          const coder::array<double, 1U> &PR800var,
                          const coder::array<double, 1U> &SE_mean,
                          const coder::array<double, 1U> &SE_max,
                          const coder::array<double, 1U> &SE_min,
                          const coder::array<double, 1U> &SE_var) {
    static const unsigned char uv[130] = {
            120U, 65U, 107U, 10U, 129U, 113U, 128U, 58U, 127U, 4U, 60U, 123U,
            106U, 13U, 42U, 112U, 124U, 72U, 14U, 111U, 40U, 8U, 21U, 130U,
            23U, 104U, 125U, 64U, 43U, 61U, 6U, 114U, 3U, 12U, 59U, 27U,
            74U, 62U, 26U, 45U, 87U, 46U, 11U, 100U, 119U, 115U, 78U, 71U,
            122U, 110U, 15U, 54U, 16U, 47U, 126U, 56U, 41U, 73U, 109U, 55U,
            17U, 88U, 66U, 76U, 83U, 2U, 20U, 70U, 77U, 48U, 5U, 29U,
            36U, 101U, 90U, 51U, 121U, 52U, 89U, 44U, 34U, 85U, 79U, 53U,
            102U, 80U, 86U, 25U, 50U, 39U, 33U, 63U, 22U, 97U, 67U, 105U,
            98U, 69U, 7U, 118U, 32U, 49U, 19U, 24U, 31U, 35U, 108U, 103U,
            9U, 91U, 1U, 84U, 28U, 30U, 82U, 99U, 117U, 18U, 81U, 38U,
            93U, 95U, 57U, 75U, 37U, 96U, 116U, 94U, 92U, 68U};
    coder::array<double, 2U> feature;
    coder::array<double, 2U> feature_1;
    int b_result_idx_1_tmp;
    int i;
    int i1;
    int result;
    int result_idx_1_tmp;
    signed char b_input_sizes_idx_1;
    signed char c_input_sizes_idx_1;
    signed char d_input_sizes_idx_1;
    signed char e_input_sizes_idx_1;
    signed char f_input_sizes_idx_1;
    signed char g_input_sizes_idx_1;
    signed char h_input_sizes_idx_1;
    signed char i_input_sizes_idx_1;
    signed char input_sizes_idx_1;
    signed char j_input_sizes_idx_1;
    signed char k_input_sizes_idx_1;
    signed char l_input_sizes_idx_1;
    signed char m_input_sizes_idx_1;
    signed char n_input_sizes_idx_1;
    signed char o_input_sizes_idx_1;
    signed char p_input_sizes_idx_1;
    signed char q_input_sizes_idx_1;
    signed char r_input_sizes_idx_1;
    signed char sizes_idx_1;
    boolean_T empty_non_axis_sizes;
    // 'patient_classifier:5' feature = [MFCC_feature, BARKEE, period_mean,
    // period_max, period_min, period_var,... 'patient_classifier:6' cep,
    // Formant1, Formant2, Formant3, GTCCmean, PR800mean, PR800max, PR800min,
    // PR800var,... 'patient_classifier:7'         SE_mean, SE_max, SE_min,
    // SE_var];
    if (MFCC_feature.size(0) != 0) {
        result = MFCC_feature.size(0);
    } else if (BARKEE.size(0) != 0) {
        result = BARKEE.size(0);
    } else if (period_mean.size(0) != 0) {
        result = period_mean.size(0);
    } else if (period_max.size(0) != 0) {
        result = period_max.size(0);
    } else if (period_min.size(0) != 0) {
        result = period_min.size(0);
    } else if (period_var.size(0) != 0) {
        result = period_var.size(0);
    } else if (cep.size(0) != 0) {
        result = cep.size(0);
    } else if (Formant1.size(0) != 0) {
        result = Formant1.size(0);
    } else if (Formant2.size(0) != 0) {
        result = Formant2.size(0);
    } else if (Formant3.size(0) != 0) {
        result = Formant3.size(0);
    } else if (GTCCmean.size(0) != 0) {
        result = GTCCmean.size(0);
    } else if (PR800mean.size(0) != 0) {
        result = PR800mean.size(0);
    } else if (PR800max.size(0) != 0) {
        result = PR800max.size(0);
    } else if (PR800min.size(0) != 0) {
        result = PR800min.size(0);
    } else if (PR800var.size(0) != 0) {
        result = PR800var.size(0);
    } else if (SE_mean.size(0) != 0) {
        result = SE_mean.size(0);
    } else if (SE_max.size(0) != 0) {
        result = SE_max.size(0);
    } else if (SE_min.size(0) != 0) {
        result = SE_min.size(0);
    } else if (SE_var.size(0) != 0) {
        result = SE_var.size(0);
    } else {
        result = 0;
    }
    empty_non_axis_sizes = (result == 0);
    if (empty_non_axis_sizes || (MFCC_feature.size(0) != 0)) {
        input_sizes_idx_1 = 39;
    } else {
        input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (BARKEE.size(0) != 0)) {
        b_input_sizes_idx_1 = 17;
    } else {
        b_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (period_mean.size(0) != 0)) {
        c_input_sizes_idx_1 = 1;
    } else {
        c_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (period_max.size(0) != 0)) {
        d_input_sizes_idx_1 = 1;
    } else {
        d_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (period_min.size(0) != 0)) {
        e_input_sizes_idx_1 = 1;
    } else {
        e_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (period_var.size(0) != 0)) {
        f_input_sizes_idx_1 = 1;
    } else {
        f_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (cep.size(0) != 0)) {
        g_input_sizes_idx_1 = 39;
    } else {
        g_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (Formant1.size(0) != 0)) {
        h_input_sizes_idx_1 = 1;
    } else {
        h_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (Formant2.size(0) != 0)) {
        i_input_sizes_idx_1 = 1;
    } else {
        i_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (Formant3.size(0) != 0)) {
        j_input_sizes_idx_1 = 1;
    } else {
        j_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (GTCCmean.size(0) != 0)) {
        k_input_sizes_idx_1 = 20;
    } else {
        k_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (PR800mean.size(0) != 0)) {
        l_input_sizes_idx_1 = 1;
    } else {
        l_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (PR800max.size(0) != 0)) {
        m_input_sizes_idx_1 = 1;
    } else {
        m_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (PR800min.size(0) != 0)) {
        n_input_sizes_idx_1 = 1;
    } else {
        n_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (PR800var.size(0) != 0)) {
        o_input_sizes_idx_1 = 1;
    } else {
        o_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (SE_mean.size(0) != 0)) {
        p_input_sizes_idx_1 = 1;
    } else {
        p_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (SE_max.size(0) != 0)) {
        q_input_sizes_idx_1 = 1;
    } else {
        q_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (SE_min.size(0) != 0)) {
        r_input_sizes_idx_1 = 1;
    } else {
        r_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (SE_var.size(0) != 0)) {
        sizes_idx_1 = 1;
    } else {
        sizes_idx_1 = 0;
    }
    result_idx_1_tmp = input_sizes_idx_1;
    b_result_idx_1_tmp = g_input_sizes_idx_1;
    feature.set_size(result,
                     (((((((((((((((((input_sizes_idx_1 + b_input_sizes_idx_1) +
                                     c_input_sizes_idx_1) +
                                    d_input_sizes_idx_1) +
                                   e_input_sizes_idx_1) +
                                  f_input_sizes_idx_1) +
                                 g_input_sizes_idx_1) +
                                h_input_sizes_idx_1) +
                               i_input_sizes_idx_1) +
                              j_input_sizes_idx_1) +
                             k_input_sizes_idx_1) +
                            l_input_sizes_idx_1) +
                           m_input_sizes_idx_1) +
                          n_input_sizes_idx_1) +
                         o_input_sizes_idx_1) +
                        p_input_sizes_idx_1) +
                       q_input_sizes_idx_1) +
                      r_input_sizes_idx_1) +
                     sizes_idx_1);
    for (i = 0; i < result_idx_1_tmp; i++) {
        for (i1 = 0; i1 < result; i1++) {
            feature[i1 + feature.size(0) * i] =
                    MFCC_feature[i1 + MFCC_feature.size(0) * i];
        }
    }
    result_idx_1_tmp = b_input_sizes_idx_1;
    for (i = 0; i < result_idx_1_tmp; i++) {
        for (i1 = 0; i1 < result; i1++) {
            feature[i1 + feature.size(0) * (i + input_sizes_idx_1)] =
                    BARKEE[i1 + result * i];
        }
    }
    result_idx_1_tmp = c_input_sizes_idx_1;
    for (i = 0; i < result_idx_1_tmp; i++) {
        for (i1 = 0; i1 < result; i1++) {
            feature[i1 + feature.size(0) *
                         (input_sizes_idx_1 + b_input_sizes_idx_1)] =
                    period_mean[i1];
        }
    }
    result_idx_1_tmp = d_input_sizes_idx_1;
    for (i = 0; i < result_idx_1_tmp; i++) {
        for (i1 = 0; i1 < result; i1++) {
            feature[i1 + feature.size(0) *
                         ((input_sizes_idx_1 + b_input_sizes_idx_1) +
                          c_input_sizes_idx_1)] = period_max[i1];
        }
    }
    result_idx_1_tmp = e_input_sizes_idx_1;
    for (i = 0; i < result_idx_1_tmp; i++) {
        for (i1 = 0; i1 < result; i1++) {
            feature[i1 + feature.size(0) *
                         (((input_sizes_idx_1 + b_input_sizes_idx_1) +
                           c_input_sizes_idx_1) +
                          d_input_sizes_idx_1)] = period_min[i1];
        }
    }
    result_idx_1_tmp = f_input_sizes_idx_1;
    for (i = 0; i < result_idx_1_tmp; i++) {
        for (i1 = 0; i1 < result; i1++) {
            feature[i1 + feature.size(0) *
                         ((((input_sizes_idx_1 + b_input_sizes_idx_1) +
                            c_input_sizes_idx_1) +
                           d_input_sizes_idx_1) +
                          e_input_sizes_idx_1)] = period_var[i1];
        }
    }
    for (i = 0; i < b_result_idx_1_tmp; i++) {
        for (i1 = 0; i1 < result; i1++) {
            feature[i1 + feature.size(0) * ((((((i + input_sizes_idx_1) +
                                                b_input_sizes_idx_1) +
                                               c_input_sizes_idx_1) +
                                              d_input_sizes_idx_1) +
                                             e_input_sizes_idx_1) +
                                            f_input_sizes_idx_1)] =
                    cep[i1 + cep.size(0) * i];
        }
    }
    result_idx_1_tmp = h_input_sizes_idx_1;
    for (i = 0; i < result_idx_1_tmp; i++) {
        for (i1 = 0; i1 < result; i1++) {
            feature[i1 + feature.size(0) *
                         ((((((input_sizes_idx_1 + b_input_sizes_idx_1) +
                              c_input_sizes_idx_1) +
                             d_input_sizes_idx_1) +
                            e_input_sizes_idx_1) +
                           f_input_sizes_idx_1) +
                          g_input_sizes_idx_1)] = Formant1[i1];
        }
    }
    result_idx_1_tmp = i_input_sizes_idx_1;
    for (i = 0; i < result_idx_1_tmp; i++) {
        for (i1 = 0; i1 < result; i1++) {
            feature[i1 + feature.size(0) *
                         (((((((input_sizes_idx_1 + b_input_sizes_idx_1) +
                               c_input_sizes_idx_1) +
                              d_input_sizes_idx_1) +
                             e_input_sizes_idx_1) +
                            f_input_sizes_idx_1) +
                           g_input_sizes_idx_1) +
                          h_input_sizes_idx_1)] = Formant2[i1];
        }
    }
    result_idx_1_tmp = j_input_sizes_idx_1;
    for (i = 0; i < result_idx_1_tmp; i++) {
        for (i1 = 0; i1 < result; i1++) {
            feature[i1 + feature.size(0) *
                         ((((((((input_sizes_idx_1 + b_input_sizes_idx_1) +
                                c_input_sizes_idx_1) +
                               d_input_sizes_idx_1) +
                              e_input_sizes_idx_1) +
                             f_input_sizes_idx_1) +
                            g_input_sizes_idx_1) +
                           h_input_sizes_idx_1) +
                          i_input_sizes_idx_1)] = Formant3[i1];
        }
    }
    result_idx_1_tmp = k_input_sizes_idx_1;
    for (i = 0; i < result_idx_1_tmp; i++) {
        for (i1 = 0; i1 < result; i1++) {
            feature[i1 + feature.size(0) * ((((((((((i + input_sizes_idx_1) +
                                                    b_input_sizes_idx_1) +
                                                   c_input_sizes_idx_1) +
                                                  d_input_sizes_idx_1) +
                                                 e_input_sizes_idx_1) +
                                                f_input_sizes_idx_1) +
                                               g_input_sizes_idx_1) +
                                              h_input_sizes_idx_1) +
                                             i_input_sizes_idx_1) +
                                            j_input_sizes_idx_1)] =
                    GTCCmean[i1 + result * i];
        }
    }
    result_idx_1_tmp = l_input_sizes_idx_1;
    for (i = 0; i < result_idx_1_tmp; i++) {
        for (i1 = 0; i1 < result; i1++) {
            feature[i1 + feature.size(0) * ((((((((((input_sizes_idx_1 +
                                                     b_input_sizes_idx_1) +
                                                    c_input_sizes_idx_1) +
                                                   d_input_sizes_idx_1) +
                                                  e_input_sizes_idx_1) +
                                                 f_input_sizes_idx_1) +
                                                g_input_sizes_idx_1) +
                                               h_input_sizes_idx_1) +
                                              i_input_sizes_idx_1) +
                                             j_input_sizes_idx_1) +
                                            k_input_sizes_idx_1)] =
                    PR800mean[i1];
        }
    }
    result_idx_1_tmp = m_input_sizes_idx_1;
    for (i = 0; i < result_idx_1_tmp; i++) {
        for (i1 = 0; i1 < result; i1++) {
            feature[i1 +
                    feature.size(0) *
                    (((((((((((input_sizes_idx_1 + b_input_sizes_idx_1) +
                              c_input_sizes_idx_1) +
                             d_input_sizes_idx_1) +
                            e_input_sizes_idx_1) +
                           f_input_sizes_idx_1) +
                          g_input_sizes_idx_1) +
                         h_input_sizes_idx_1) +
                        i_input_sizes_idx_1) +
                       j_input_sizes_idx_1) +
                      k_input_sizes_idx_1) +
                     l_input_sizes_idx_1)] = PR800max[i1];
        }
    }
    result_idx_1_tmp = n_input_sizes_idx_1;
    for (i = 0; i < result_idx_1_tmp; i++) {
        for (i1 = 0; i1 < result; i1++) {
            feature[i1 +
                    feature.size(0) *
                    ((((((((((((input_sizes_idx_1 + b_input_sizes_idx_1) +
                               c_input_sizes_idx_1) +
                              d_input_sizes_idx_1) +
                             e_input_sizes_idx_1) +
                            f_input_sizes_idx_1) +
                           g_input_sizes_idx_1) +
                          h_input_sizes_idx_1) +
                         i_input_sizes_idx_1) +
                        j_input_sizes_idx_1) +
                       k_input_sizes_idx_1) +
                      l_input_sizes_idx_1) +
                     m_input_sizes_idx_1)] = PR800min[i1];
        }
    }
    result_idx_1_tmp = o_input_sizes_idx_1;
    for (i = 0; i < result_idx_1_tmp; i++) {
        for (i1 = 0; i1 < result; i1++) {
            feature[i1 +
                    feature.size(0) *
                    (((((((((((((input_sizes_idx_1 + b_input_sizes_idx_1) +
                                c_input_sizes_idx_1) +
                               d_input_sizes_idx_1) +
                              e_input_sizes_idx_1) +
                             f_input_sizes_idx_1) +
                            g_input_sizes_idx_1) +
                           h_input_sizes_idx_1) +
                          i_input_sizes_idx_1) +
                         j_input_sizes_idx_1) +
                        k_input_sizes_idx_1) +
                       l_input_sizes_idx_1) +
                      m_input_sizes_idx_1) +
                     n_input_sizes_idx_1)] = PR800var[i1];
        }
    }
    result_idx_1_tmp = p_input_sizes_idx_1;
    for (i = 0; i < result_idx_1_tmp; i++) {
        for (i1 = 0; i1 < result; i1++) {
            feature[i1 +
                    feature.size(0) *
                    ((((((((((((((input_sizes_idx_1 + b_input_sizes_idx_1) +
                                 c_input_sizes_idx_1) +
                                d_input_sizes_idx_1) +
                               e_input_sizes_idx_1) +
                              f_input_sizes_idx_1) +
                             g_input_sizes_idx_1) +
                            h_input_sizes_idx_1) +
                           i_input_sizes_idx_1) +
                          j_input_sizes_idx_1) +
                         k_input_sizes_idx_1) +
                        l_input_sizes_idx_1) +
                       m_input_sizes_idx_1) +
                      n_input_sizes_idx_1) +
                     o_input_sizes_idx_1)] = SE_mean[i1];
        }
    }
    result_idx_1_tmp = q_input_sizes_idx_1;
    for (i = 0; i < result_idx_1_tmp; i++) {
        for (i1 = 0; i1 < result; i1++) {
            feature[i1 + feature.size(0) * (((((((((((((((input_sizes_idx_1 +
                                                          b_input_sizes_idx_1) +
                                                         c_input_sizes_idx_1) +
                                                        d_input_sizes_idx_1) +
                                                       e_input_sizes_idx_1) +
                                                      f_input_sizes_idx_1) +
                                                     g_input_sizes_idx_1) +
                                                    h_input_sizes_idx_1) +
                                                   i_input_sizes_idx_1) +
                                                  j_input_sizes_idx_1) +
                                                 k_input_sizes_idx_1) +
                                                l_input_sizes_idx_1) +
                                               m_input_sizes_idx_1) +
                                              n_input_sizes_idx_1) +
                                             o_input_sizes_idx_1) +
                                            p_input_sizes_idx_1)] = SE_max[i1];
        }
    }
    result_idx_1_tmp = r_input_sizes_idx_1;
    for (i = 0; i < result_idx_1_tmp; i++) {
        for (i1 = 0; i1 < result; i1++) {
            feature[i1 +
                    feature.size(0) * ((((((((((((((((input_sizes_idx_1 +
                                                      b_input_sizes_idx_1) +
                                                     c_input_sizes_idx_1) +
                                                    d_input_sizes_idx_1) +
                                                   e_input_sizes_idx_1) +
                                                  f_input_sizes_idx_1) +
                                                 g_input_sizes_idx_1) +
                                                h_input_sizes_idx_1) +
                                               i_input_sizes_idx_1) +
                                              j_input_sizes_idx_1) +
                                             k_input_sizes_idx_1) +
                                            l_input_sizes_idx_1) +
                                           m_input_sizes_idx_1) +
                                          n_input_sizes_idx_1) +
                                         o_input_sizes_idx_1) +
                                        p_input_sizes_idx_1) +
                                       q_input_sizes_idx_1)] = SE_min[i1];
        }
    }
    result_idx_1_tmp = sizes_idx_1;
    for (i = 0; i < result_idx_1_tmp; i++) {
        for (i1 = 0; i1 < result; i1++) {
            feature[i1 +
                    feature.size(0) * (((((((((((((((((input_sizes_idx_1 +
                                                       b_input_sizes_idx_1) +
                                                      c_input_sizes_idx_1) +
                                                     d_input_sizes_idx_1) +
                                                    e_input_sizes_idx_1) +
                                                   f_input_sizes_idx_1) +
                                                  g_input_sizes_idx_1) +
                                                 h_input_sizes_idx_1) +
                                                i_input_sizes_idx_1) +
                                               j_input_sizes_idx_1) +
                                              k_input_sizes_idx_1) +
                                             l_input_sizes_idx_1) +
                                            m_input_sizes_idx_1) +
                                           n_input_sizes_idx_1) +
                                          o_input_sizes_idx_1) +
                                         p_input_sizes_idx_1) +
                                        q_input_sizes_idx_1) +
                                       r_input_sizes_idx_1)] = SE_var[i1];
        }
    }
    // 'patient_classifier:9' indexModel = coder.load('index.mat');
    // 'patient_classifier:11' feature_1 = feature(:, indexModel.index);
    result_idx_1_tmp = feature.size(0);
    feature_1.set_size(feature.size(0), 130);
    for (i = 0; i < 130; i++) {
        for (i1 = 0; i1 < result_idx_1_tmp; i1++) {
            feature_1[i1 + feature_1.size(0) * i] =
                    feature[i1 + feature.size(0) * (uv[i] - 1)];
        }
    }
    // 'patient_classifier:13' threshold = -15;
    //  阈值 由实验得出
    // 'patient_classifier:14' model = coder.load('GMMmodel.mat');
    // 'patient_classifier:15' [label_OSA] = GMM_score(feature_1,
    // model.speakerGmm, threshold);
    return GMM_score(SD, feature_1);
}

//
// File trailer for patient_classifier.cpp
//
// [EOF]
//
