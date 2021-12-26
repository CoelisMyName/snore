//
// File: vad.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "vad.h"
#include "SnoringRecognition_data.h"
#include "SnoringRecognition_initialize.h"
#include "amax_group.h"
#include "combineVectorElements.h"
#include "hist.h"
#include "median_filter.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "sum_group.h"
#include "yuzhiSpeci.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// function [w_starts, w_ends] = vad(x, fs)
//
// %% -------------------音频最小长度60秒---------------------------
//
// Arguments    : coder::array<double, 2U> &x
//                double fs
//                coder::array<double, 2U> &w_starts
//                coder::array<double, 2U> &w_ends
// Return Type  : void
//
void vad(coder::array<double, 2U> &x, double fs,
         coder::array<double, 2U> &w_starts, coder::array<double, 2U> &w_ends)
{
  coder::array<double, 2U> b_sorted_sums;
  coder::array<double, 2U> b_w_starts;
  coder::array<double, 2U> nx1;
  coder::array<double, 2U> nx3;
  coder::array<double, 2U> r;
  coder::array<double, 2U> sorted_sums;
  coder::array<double, 2U> sums;
  coder::array<int, 2U> b_w_ends;
  coder::array<int, 2U> nx2;
  coder::array<int, 2U> nx4;
  double a__1[200];
  double bins[200];
  double MIN_LEN;
  double b_len;
  double count;
  int b_i;
  int i;
  int i1;
  int k;
  int len;
  int lowb;
  if (!isInitialized_SnoringRecognition) {
    SnoringRecognition_initialize();
  }
  //  只接受1分钟长度的音频，多的截去，少的补0
  // 'vad:5' MIN_LEN = 60 * fs;
  MIN_LEN = 60.0 * fs;
  // 'vad:6' if(length(x) > MIN_LEN)
  if (x.size(1) > MIN_LEN) {
    // 'vad:7' x = x(1:MIN_LEN);
    if (1.0 > MIN_LEN) {
      i = 0;
    } else {
      i = static_cast<int>(MIN_LEN);
    }
    x.set_size(x.size(0), i);
  }
  // 'vad:9' if(length(x) < MIN_LEN)
  if (x.size(1) < MIN_LEN) {
    // 'vad:10' x = [x zeros(1,MIN_LEN - length(x))];
    len = static_cast<int>(MIN_LEN - static_cast<double>(x.size(1)));
    i = x.size(1);
    x.set_size(1, x.size(1) + len);
    if (static_cast<int>(len < 1200)) {
      for (i1 = 0; i1 < len; i1++) {
        x[i1 + i] = 0.0;
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

      for (i1 = 0; i1 < len; i1++) {
        x[i1 + i] = 0.0;
      }
    }
  }
  // 'vad:13' maxs = amax_group(x, 50);
  // 'vad:14' sums = sum_group(maxs, 50);
  // 'vad:15' sums = median_filter(sums, 10);
  amax_group(x, r);
  sum_group(r, sorted_sums);
  median_filter(sorted_sums, sums);
  // 'vad:17' [bins, ~] = hist(sums, 200);
  coder::hist(sums, bins, a__1);
  // 'vad:18' [~, position] = max(bins);
  if (!std::isnan(bins[0])) {
    len = 1;
  } else {
    boolean_T exitg1;
    len = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 201)) {
      if (!std::isnan(bins[k - 1])) {
        len = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  if (len == 0) {
    len = 1;
  } else {
    MIN_LEN = bins[len - 1];
    i = len + 1;
    for (k = i; k < 201; k++) {
      b_len = bins[k - 1];
      if (MIN_LEN < b_len) {
        MIN_LEN = b_len;
        len = k;
      }
    }
  }
  // 'vad:19' bins = sort(bins);
  coder::internal::sort(bins);
  // 'vad:20' tis = bins(end) / bins(end - 1);
  MIN_LEN = bins[199] / bins[198];
  // 'vad:21' sorted_sums = sort(sums);
  sorted_sums.set_size(1, sums.size(1));
  lowb = sums.size(1);
  if (static_cast<int>(sums.size(1) < 1200)) {
    for (i1 = 0; i1 < lowb; i1++) {
      sorted_sums[i1] = sums[i1];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

    for (i1 = 0; i1 < lowb; i1++) {
      sorted_sums[i1] = sums[i1];
    }
  }
  coder::internal::sort(sorted_sums);
  // 前60%的平均值
  // 'vad:23' ddth = mean(sorted_sums(1:fix(length(sorted_sums) * 0.6)));
  i = static_cast<int>(
      std::trunc(static_cast<double>(sorted_sums.size(1)) * 0.6));
  if (1 > i) {
    lowb = 0;
  } else {
    lowb = i;
  }
  // 难道这是取阈值？
  // 'vad:26' dth = vad_threshold(tis, sorted_sums, position);
  // 阈值生成
  // 'vad_threshold:4' if tis > 50
  if (MIN_LEN > 50.0) {
    // 'vad_threshold:5' dth = yuzhiSpeci(sorted_sums, position);
    MIN_LEN = yuzhiSpeci(sorted_sums, static_cast<double>(len));
  } else if (MIN_LEN > 20.0) {
    // 'vad_threshold:6' elseif tis > 20
    // 'vad_threshold:7' dth = ((max(sorted_sums) - min(sorted_sums)) / 200) *
    // (position + 1.5) + min(sorted_sums);
    MIN_LEN = coder::internal::minimum(sorted_sums);
    MIN_LEN += (coder::internal::maximum(sorted_sums) - MIN_LEN) / 200.0 *
               (static_cast<double>(len) + 1.5);
  } else if (MIN_LEN > 7.0) {
    // 'vad_threshold:8' elseif tis > 7
    // 'vad_threshold:9' dth = ((max(sorted_sums) - min(sorted_sums)) / 200) *
    // (-1/13 * tis + 20/13 + position + 2.5) + min(sorted_sums);
    MIN_LEN = (coder::internal::maximum(sorted_sums) -
               coder::internal::minimum(sorted_sums)) /
                  200.0 *
                  (((-0.076923076923076927 * MIN_LEN + 1.5384615384615385) +
                    static_cast<double>(len)) +
                   2.5) +
              coder::internal::minimum(sorted_sums);
  } else if (MIN_LEN > 2.0) {
    // 'vad_threshold:10' elseif tis > 2
    // 'vad_threshold:11' dth = ((max(sorted_sums) - min(sorted_sums)) / 200) *
    // (position + (-0.6 * tis + 5.2) + 2.5) + min(sorted_sums);
    MIN_LEN = (coder::internal::maximum(sorted_sums) -
               coder::internal::minimum(sorted_sums)) /
                  200.0 *
                  ((static_cast<double>(len) + (-0.6 * MIN_LEN + 5.2)) + 2.5) +
              coder::internal::minimum(sorted_sums);
  } else {
    // 'vad_threshold:12' else
    // 'vad_threshold:13' dth = ((max(sorted_sums) - min(sorted_sums)) / 200) *
    // (position + 6.5) + min(sorted_sums);
    MIN_LEN = (coder::internal::maximum(sorted_sums) -
               coder::internal::minimum(sorted_sums)) /
                  200.0 * (static_cast<double>(len) + 6.5) +
              coder::internal::minimum(sorted_sums);
  }
  // 'vad:28' w_starts = [];
  b_w_starts.set_size(0, 0);
  // 'vad:29' w_ends = [];
  b_w_ends.set_size(0, 0);
  // 'vad:31' if max(sorted_sums) >= ddth * 5
  b_sorted_sums.set_size(1, lowb);
  if (static_cast<int>(lowb < 1200)) {
    for (i1 = 0; i1 < lowb; i1++) {
      b_sorted_sums[i1] = sorted_sums[i1];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

    for (i1 = 0; i1 < lowb; i1++) {
      b_sorted_sums[i1] = sorted_sums[i1];
    }
  }
  if (coder::internal::maximum(sorted_sums) >=
      coder::combineVectorElements(b_sorted_sums) / static_cast<double>(lowb) *
          5.0) {
    // 'vad:32' [nx1, nx2] = vad_below_threshold(sums, dth, 6);
    //  获取高于阈值的段 x数组，dth阈值，width宽度
    // 'vad_below_threshold:3' starts = zeros(1,ceil(length(xn) / width));
    len = static_cast<int>(std::ceil(static_cast<double>(sums.size(1)) / 6.0));
    nx1.set_size(1, len);
    if (static_cast<int>(len < 1200)) {
      for (i1 = 0; i1 < len; i1++) {
        nx1[i1] = 0.0;
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

      for (i1 = 0; i1 < len; i1++) {
        nx1[i1] = 0.0;
      }
    }
    // 'vad_below_threshold:4' ends = zeros(1,ceil(length(xn)/ width));
    len = static_cast<int>(std::ceil(static_cast<double>(sums.size(1)) / 6.0));
    nx2.set_size(1, len);
    if (static_cast<int>(len < 1200)) {
      for (i1 = 0; i1 < len; i1++) {
        nx2[i1] = 0;
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

      for (i1 = 0; i1 < len; i1++) {
        nx2[i1] = 0;
      }
    }
    // 'vad_below_threshold:5' len = 0;
    len = 0;
    // 'vad_below_threshold:6' count = 0;
    count = 0.0;
    // 'vad_below_threshold:8' for i = 1:length(xn)
    i = sums.size(1);
    for (b_i = 0; b_i < i; b_i++) {
      // 'vad_below_threshold:10' if xn(i) > dth
      b_len = sums[b_i];
      if (b_len > MIN_LEN) {
        // 'vad_below_threshold:11' count = count + 1;
        count++;
      }
      // 'vad_below_threshold:14' if xn(i) <= dth && count >= width
      if ((b_len <= MIN_LEN) && (count >= 6.0)) {
        // 'vad_below_threshold:15' len = len + 1;
        len++;
        // 'vad_below_threshold:16' starts(len) = i - count;
        nx1[len - 1] = (static_cast<double>(b_i) + 1.0) - count;
        // 'vad_below_threshold:17' ends(len) = i - 1;
        nx2[len - 1] = b_i;
      }
      // 'vad_below_threshold:20' if xn(i) <= dth
      if (b_len <= MIN_LEN) {
        // 'vad_below_threshold:21' count = 0;
        count = 0.0;
      }
    }
    //  到末尾，有声段可能大于
    // 'vad_below_threshold:27' if count >= width
    if (count >= 6.0) {
      // 'vad_below_threshold:28' len = len + 1;
      len++;
      // 'vad_below_threshold:29' starts(len) = length(xn) - count + 1;
      nx1[len - 1] = (static_cast<double>(sums.size(1)) - count) + 1.0;
      // 'vad_below_threshold:30' ends(len) = length(xn);
      nx2[len - 1] = sums.size(1);
    }
    // 'vad_below_threshold:33' starts = starts(1:len);
    if (1 > len) {
      lowb = 0;
    } else {
      lowb = len;
    }
    nx1.set_size(nx1.size(0), lowb);
    // 'vad_below_threshold:34' ends = ends(1:len);
    if (1 > len) {
      len = 0;
    }
    nx2.set_size(nx2.size(0), len);
    // 'vad:33' [nx3, nx4] = vad_wave(sums, nx1, nx2);
    //  按波形重新分段
    // 'vad_wave:3' w_starts = zeros(1, length(s_starts));
    nx3.set_size(1, lowb);
    if (static_cast<int>(lowb < 1200)) {
      for (i1 = 0; i1 < lowb; i1++) {
        nx3[i1] = 0.0;
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

      for (i1 = 0; i1 < lowb; i1++) {
        nx3[i1] = 0.0;
      }
    }
    // 'vad_wave:4' w_ends = zeros(1, length(s_ends));
    nx4.set_size(1, len);
    if (static_cast<int>(len < 1200)) {
      for (i1 = 0; i1 < len; i1++) {
        nx4[i1] = 0;
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

      for (i1 = 0; i1 < len; i1++) {
        nx4[i1] = 0;
      }
    }
    // 'vad_wave:5' k = 1;
    k = 0;
    // 'vad_wave:7' for i = 1:min(length(s_starts), length(s_ends))
    i = static_cast<int>(
        std::fmin(static_cast<double>(lowb), static_cast<double>(len)));
    for (b_i = 0; b_i < i; b_i++) {
      int i2;
      // 'vad_wave:9' w_starts(k) = s_starts(i);
      b_len = nx1[b_i];
      nx3[k] = b_len;
      // 'vad_wave:10' islow = 0;
      len = 0;
      // 'vad_wave:11' count = 0;
      count = 0.0;
      // 'vad_wave:12' lowb = -1;
      lowb = -1;
      // 'vad_wave:14' for j = s_starts(i) + 1:s_ends(i)
      i2 = static_cast<int>(static_cast<double>(nx2[b_i]) +
                            (1.0 - (b_len + 1.0)));
      for (int j{0}; j < i2; j++) {
        MIN_LEN = (nx1[b_i] + 1.0) + static_cast<double>(j);
        // 'vad_wave:16' if array(j) - array(j - 1) < -0.01
        b_len = sums[static_cast<int>(MIN_LEN) - 1];
        if (b_len - sums[static_cast<int>(MIN_LEN - 1.0) - 1] < -0.01) {
          // 'vad_wave:17' islow = 1;
          len = 1;
        }
        // 'vad_wave:20' if islow == 1 && abs(array(j) - array(j - 1)) <= 0.01
        if ((len == 1) &&
            (std::abs(b_len - sums[static_cast<int>(MIN_LEN) - 2]) <= 0.01)) {
          // 'vad_wave:21' count = count + 1;
          count++;
          // 'vad_wave:23' if (lowb == -1)
          if (lowb == -1) {
            // 'vad_wave:24' lowb = j;
            lowb = static_cast<int>(MIN_LEN);
          }
        } else if (len == 1) {
          // 'vad_wave:27' elseif islow == 1
          // 连续下降的特殊情况
          // 'vad_wave:29' if array(j) < array(j - 1)
          if (b_len < sums[static_cast<int>(MIN_LEN) - 2]) {
            // 后一个点抬升
            // 'vad_wave:31' if (j + 1 < s_ends(i) && array(j + 1) - array(j) <=
            // 0.01)
            if ((static_cast<int>(MIN_LEN) + 1 < nx2[b_i]) &&
                (sums[static_cast<int>(MIN_LEN)] - b_len <= 0.01)) {
              // 'vad_wave:32' lowb = j;
              lowb = static_cast<int>(MIN_LEN);
              // j+1;
              // %lowb针对连续下降不断往后推，直到碰到抬升点，lowb记录的是最后一个非上升点，波谷的前一个点
            }
          } else {
            // 'vad_wave:35' else
            // 'vad_wave:37' if (count >= 3)
            if (count >= 3.0) {
              // 'vad_wave:38' w_ends(k) = lowb;
              nx4[k] = lowb;
              // 'vad_wave:39' k = k + 1;
              k++;
              // 'vad_wave:40' w_starts(k) = j - 1;
              nx3[k] = MIN_LEN - 1.0;
              // 'vad_wave:41' islow = 0;
              len = 0;
              // 'vad_wave:42' lowb = -1;
              lowb = -1;
            }
            // 'vad_wave:45' count = 0;
            count = 0.0;
          }
        }
      }
      // 'vad_wave:52' w_ends(k) = s_ends(i);
      nx4[k] = nx2[b_i];
      // 'vad_wave:53' k = k + 1;
      k++;
    }
    // 'vad_wave:57' w_starts = w_starts(1:k - 1);
    if (1 > k) {
      lowb = 0;
      i = 0;
    } else {
      lowb = k;
      i = k;
    }
    nx3.set_size(nx3.size(0), i);
    // 'vad_wave:58' w_ends = w_ends(1:k - 1);
    if (1 > k) {
      k = 0;
    }
    nx4.set_size(nx4.size(0), k);
    //  映射至实际区间
    // 'vad:35' w_starts = (nx3 - 1) * 2500 + 1;
    b_w_starts.set_size(1, lowb);
    if (static_cast<int>(lowb < 1200)) {
      for (i1 = 0; i1 < lowb; i1++) {
        b_w_starts[i1] = (nx3[i1] - 1.0) * 2500.0 + 1.0;
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

      for (i1 = 0; i1 < lowb; i1++) {
        b_w_starts[i1] = (nx3[i1] - 1.0) * 2500.0 + 1.0;
      }
    }
    // 'vad:36' w_ends = nx4 * 2500;
    b_w_ends.set_size(1, nx4.size(1));
    lowb = nx4.size(1);
    if (static_cast<int>(nx4.size(1) < 1200)) {
      for (i1 = 0; i1 < lowb; i1++) {
        b_w_ends[i1] = nx4[i1] * 2500;
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

      for (i1 = 0; i1 < lowb; i1++) {
        b_w_ends[i1] = nx4[i1] * 2500;
      }
    }
  }
  // 截取段过滤
  // 'vad:40' [w_starts, w_ends] = vad_length_filter(w_starts, w_ends, 0.03 *
  // fs, 5 * fs);
  MIN_LEN = 0.03 * fs;
  count = 5.0 * fs;
  // vad_length_filter: stars 开始 ends 结束 min_len 最小长度 max_len 最大长度
  // 'vad_length_filter:3' k = 0;
  k = 0;
  // 'vad_length_filter:4' fstarts = zeros(1, length(starts));
  if ((b_w_starts.size(0) == 0) || (b_w_starts.size(1) == 0)) {
    lowb = 0;
  } else {
    lowb = b_w_starts.size(1);
  }
  w_starts.set_size(1, lowb);
  if (static_cast<int>(lowb < 1200)) {
    for (i1 = 0; i1 < lowb; i1++) {
      w_starts[i1] = 0.0;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

    for (i1 = 0; i1 < lowb; i1++) {
      w_starts[i1] = 0.0;
    }
  }
  // 'vad_length_filter:5' fends = zeros(1, length(ends));
  if ((b_w_ends.size(0) == 0) || (b_w_ends.size(1) == 0)) {
    lowb = 0;
  } else {
    lowb = b_w_ends.size(1);
  }
  w_ends.set_size(1, lowb);
  if (static_cast<int>(lowb < 1200)) {
    for (i1 = 0; i1 < lowb; i1++) {
      w_ends[i1] = 0.0;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

    for (i1 = 0; i1 < lowb; i1++) {
      w_ends[i1] = 0.0;
    }
  }
  // 'vad_length_filter:7' for i = 1:min(length(starts), length(ends))
  if ((b_w_starts.size(0) == 0) || (b_w_starts.size(1) == 0)) {
    lowb = 0;
  } else {
    lowb = b_w_starts.size(1);
  }
  if ((b_w_ends.size(0) == 0) || (b_w_ends.size(1) == 0)) {
    len = 0;
  } else {
    len = b_w_ends.size(1);
  }
  i = static_cast<int>(
      std::fmin(static_cast<double>(lowb), static_cast<double>(len)));
  for (b_i = 0; b_i < i; b_i++) {
    // 'vad_length_filter:8' len = ends(i) - starts(i) + 1;
    b_len = (static_cast<double>(b_w_ends[b_i]) - b_w_starts[b_i]) + 1.0;
    //  小于限定长度或大于限定长度的都抛弃
    // 'vad_length_filter:10' if len > min_len && len < max_len
    if ((b_len > MIN_LEN) && (b_len < count)) {
      // 'vad_length_filter:11' k = k + 1;
      k++;
      // 'vad_length_filter:12' fstarts(k) = starts(i);
      w_starts[k - 1] = b_w_starts[b_i];
      // 'vad_length_filter:13' fends(k) = ends(i);
      w_ends[k - 1] = b_w_ends[b_i];
    }
  }
  //  对结果进行裁剪
  // 'vad_length_filter:18' fstarts = fstarts(1:k);
  if (1 > k) {
    i = 0;
  } else {
    i = k;
  }
  w_starts.set_size(w_starts.size(0), i);
  // 'vad_length_filter:19' fends = fends(1:k);
  if (1 > k) {
    k = 0;
  }
  w_ends.set_size(w_ends.size(0), k);
}

//
// File trailer for vad.cpp
//
// [EOF]
//
