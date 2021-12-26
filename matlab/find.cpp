//
// File: find.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "find.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<boolean_T, 2U> &x
//                int i_data[]
//                int i_size[2]
// Return Type  : void
//
namespace coder {
void eml_find(const ::coder::array<boolean_T, 2U> &x, int i_data[],
              int i_size[2])
{
  int idx;
  int ii;
  int k;
  boolean_T exitg1;
  k = (1 <= x.size(1));
  idx = 0;
  i_size[0] = 1;
  i_size[1] = k;
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii <= x.size(1) - 1)) {
    if (x[ii]) {
      idx = 1;
      i_data[0] = ii + 1;
      exitg1 = true;
    } else {
      ii++;
    }
  }
  if (k == 1) {
    if (idx == 0) {
      i_size[0] = 1;
      i_size[1] = 0;
    }
  } else {
    i_size[1] = (1 <= idx);
  }
}

} // namespace coder

//
// File trailer for find.cpp
//
// [EOF]
//
