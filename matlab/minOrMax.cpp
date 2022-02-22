//
// File: minOrMax.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<double, 2U> &ex
// Return Type  : void
//
namespace coder {
    namespace internal {
        void maximum(const ::coder::array<double, 2U> &x,
                     ::coder::array<double, 2U> &ex) {
            int m;
            int n;
            m = x.size(0);
            n = x.size(1);
            ex.set_size(1, x.size(1));
            if (x.size(0) == 0) {
                m = x.size(1);
                ex.set_size(1, x.size(1));
                for (n = 0; n < m; n++) {
                    ex[n] = rtNaN;
                }
            } else if (x.size(1) >= 1) {
                for (int j = 0; j < n; j++) {
                    ex[j] = x[x.size(0) * j];
                    for (int i = 2; i <= m; i++) {
                        double a;
                        double b;
                        boolean_T p;
                        a = ex[j];
                        b = x[(i + x.size(0) * j) - 1];
                        if (rtIsNaN(b)) {
                            p = false;
                        } else if (rtIsNaN(a)) {
                            p = true;
                        } else {
                            p = (a < b);
                        }
                        if (p) {
                            ex[j] = b;
                        }
                    }
                }
            }
        }

//
// Arguments    : const ::coder::array<double, 2U> &x
//                double ex[12]
// Return Type  : void
//
        void maximum(const ::coder::array<double, 2U> &x, double ex[12]) {
            int m;
            m = x.size(0);
            if (x.size(0) == 0) {
                for (m = 0; m < 12; m++) {
                    ex[m] = rtNaN;
                }
            } else {
                for (int j = 0; j < 12; j++) {
                    ex[j] = x[x.size(0) * j];
                    for (int i = 2; i <= m; i++) {
                        double b;
                        boolean_T p;
                        b = x[(i + x.size(0) * j) - 1];
                        if (rtIsNaN(b)) {
                            p = false;
                        } else if (rtIsNaN(ex[j])) {
                            p = true;
                        } else {
                            p = (ex[j] < b);
                        }
                        if (p) {
                            ex[j] = b;
                        }
                    }
                }
            }
        }

//
// Arguments    : const ::coder::array<double, 1U> &x
// Return Type  : double
//
        double maximum(const ::coder::array<double, 1U> &x) {
            double ex;
            int last;
            last = x.size(0);
            if (x.size(0) <= 2) {
                if (x.size(0) == 0) {
                    ex = rtNaN;
                } else if (x.size(0) == 1) {
                    ex = x[0];
                } else if ((x[0] < x[1]) || (rtIsNaN(x[0]) && (!rtIsNaN(x[1])))) {
                    ex = x[1];
                } else {
                    ex = x[0];
                }
            } else {
                int idx;
                int k;
                if (!rtIsNaN(x[0])) {
                    idx = 1;
                } else {
                    boolean_T exitg1;
                    idx = 0;
                    k = 2;
                    exitg1 = false;
                    while ((!exitg1) && (k <= last)) {
                        if (!rtIsNaN(x[k - 1])) {
                            idx = k;
                            exitg1 = true;
                        } else {
                            k++;
                        }
                    }
                }
                if (idx == 0) {
                    ex = x[0];
                } else {
                    ex = x[idx - 1];
                    idx++;
                    for (k = idx; k <= last; k++) {
                        double d;
                        d = x[k - 1];
                        if (ex < d) {
                            ex = d;
                        }
                    }
                }
            }
            return ex;
        }

//
// Arguments    : const double x[200]
//                double *ex
//                int *idx
// Return Type  : void
//
        void maximum(const double x[200], double *ex, int *idx) {
            int k;
            if (!rtIsNaN(x[0])) {
                *idx = 1;
            } else {
                boolean_T exitg1;
                *idx = 0;
                k = 2;
                exitg1 = false;
                while ((!exitg1) && (k < 201)) {
                    if (!rtIsNaN(x[k - 1])) {
                        *idx = k;
                        exitg1 = true;
                    } else {
                        k++;
                    }
                }
            }
            if (*idx == 0) {
                *ex = x[0];
                *idx = 1;
            } else {
                int i;
                *ex = x[*idx - 1];
                i = *idx + 1;
                for (k = i; k < 201; k++) {
                    double d;
                    d = x[k - 1];
                    if (*ex < d) {
                        *ex = d;
                        *idx = k;
                    }
                }
            }
        }

//
// Arguments    : const ::coder::array<double, 2U> &x
//                double *ex
//                int *idx
// Return Type  : void
//
        void maximum(const ::coder::array<double, 2U> &x, double *ex, int *idx) {
            int last;
            last = x.size(1);
            if (x.size(1) <= 2) {
                if (x.size(1) == 0) {
                    *ex = rtNaN;
                    *idx = 1;
                } else if (x.size(1) == 1) {
                    *ex = x[0];
                    *idx = 1;
                } else if ((x[0] < x[1]) || (rtIsNaN(x[0]) && (!rtIsNaN(x[1])))) {
                    *ex = x[1];
                    *idx = 2;
                } else {
                    *ex = x[0];
                    *idx = 1;
                }
            } else {
                int k;
                if (!rtIsNaN(x[0])) {
                    *idx = 1;
                } else {
                    boolean_T exitg1;
                    *idx = 0;
                    k = 2;
                    exitg1 = false;
                    while ((!exitg1) && (k <= last)) {
                        if (!rtIsNaN(x[k - 1])) {
                            *idx = k;
                            exitg1 = true;
                        } else {
                            k++;
                        }
                    }
                }
                if (*idx == 0) {
                    *ex = x[0];
                    *idx = 1;
                } else {
                    int i;
                    *ex = x[*idx - 1];
                    i = *idx + 1;
                    for (k = i; k <= last; k++) {
                        double d;
                        d = x[k - 1];
                        if (*ex < d) {
                            *ex = d;
                            *idx = k;
                        }
                    }
                }
            }
        }

//
// Arguments    : const ::coder::array<double, 2U> &x
// Return Type  : double
//
        double maximum(const ::coder::array<double, 2U> &x) {
            double ex;
            int last;
            last = x.size(1);
            if (x.size(1) <= 2) {
                if (x.size(1) == 0) {
                    ex = rtNaN;
                } else if (x.size(1) == 1) {
                    ex = x[0];
                } else if ((x[0] < x[1]) || (rtIsNaN(x[0]) && (!rtIsNaN(x[1])))) {
                    ex = x[1];
                } else {
                    ex = x[0];
                }
            } else {
                int idx;
                int k;
                if (!rtIsNaN(x[0])) {
                    idx = 1;
                } else {
                    boolean_T exitg1;
                    idx = 0;
                    k = 2;
                    exitg1 = false;
                    while ((!exitg1) && (k <= last)) {
                        if (!rtIsNaN(x[k - 1])) {
                            idx = k;
                            exitg1 = true;
                        } else {
                            k++;
                        }
                    }
                }
                if (idx == 0) {
                    ex = x[0];
                } else {
                    ex = x[idx - 1];
                    idx++;
                    for (k = idx; k <= last; k++) {
                        double d;
                        d = x[k - 1];
                        if (ex < d) {
                            ex = d;
                        }
                    }
                }
            }
            return ex;
        }

//
// Arguments    : double x
//                double y
// Return Type  : double
//
        double maximum2(double x, double y) {
            double ex;
            if ((x > y) || rtIsNaN(y)) {
                ex = x;
            } else {
                ex = y;
            }
            return ex;
        }

//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<double, 2U> &ex
// Return Type  : void
//
        void minimum(const ::coder::array<double, 2U> &x,
                     ::coder::array<double, 2U> &ex) {
            int m;
            int n;
            m = x.size(0);
            n = x.size(1);
            ex.set_size(1, x.size(1));
            if (x.size(0) == 0) {
                m = x.size(1);
                ex.set_size(1, x.size(1));
                for (n = 0; n < m; n++) {
                    ex[n] = rtNaN;
                }
            } else if (x.size(1) >= 1) {
                for (int j = 0; j < n; j++) {
                    ex[j] = x[x.size(0) * j];
                    for (int i = 2; i <= m; i++) {
                        double a;
                        double b;
                        boolean_T p;
                        a = ex[j];
                        b = x[(i + x.size(0) * j) - 1];
                        if (rtIsNaN(b)) {
                            p = false;
                        } else if (rtIsNaN(a)) {
                            p = true;
                        } else {
                            p = (a > b);
                        }
                        if (p) {
                            ex[j] = b;
                        }
                    }
                }
            }
        }

//
// Arguments    : const ::coder::array<double, 2U> &x
//                double ex[12]
// Return Type  : void
//
        void minimum(const ::coder::array<double, 2U> &x, double ex[12]) {
            int m;
            m = x.size(0);
            if (x.size(0) == 0) {
                for (m = 0; m < 12; m++) {
                    ex[m] = rtNaN;
                }
            } else {
                for (int j = 0; j < 12; j++) {
                    ex[j] = x[x.size(0) * j];
                    for (int i = 2; i <= m; i++) {
                        double b;
                        boolean_T p;
                        b = x[(i + x.size(0) * j) - 1];
                        if (rtIsNaN(b)) {
                            p = false;
                        } else if (rtIsNaN(ex[j])) {
                            p = true;
                        } else {
                            p = (ex[j] > b);
                        }
                        if (p) {
                            ex[j] = b;
                        }
                    }
                }
            }
        }

//
// Arguments    : const ::coder::array<double, 2U> &x
// Return Type  : double
//
        double minimum(const ::coder::array<double, 2U> &x) {
            double ex;
            int last;
            last = x.size(1);
            if (x.size(1) <= 2) {
                if (x.size(1) == 0) {
                    ex = rtNaN;
                } else if (x.size(1) == 1) {
                    ex = x[0];
                } else if ((x[0] > x[1]) || (rtIsNaN(x[0]) && (!rtIsNaN(x[1])))) {
                    ex = x[1];
                } else {
                    ex = x[0];
                }
            } else {
                int idx;
                int k;
                if (!rtIsNaN(x[0])) {
                    idx = 1;
                } else {
                    boolean_T exitg1;
                    idx = 0;
                    k = 2;
                    exitg1 = false;
                    while ((!exitg1) && (k <= last)) {
                        if (!rtIsNaN(x[k - 1])) {
                            idx = k;
                            exitg1 = true;
                        } else {
                            k++;
                        }
                    }
                }
                if (idx == 0) {
                    ex = x[0];
                } else {
                    ex = x[idx - 1];
                    idx++;
                    for (k = idx; k <= last; k++) {
                        double d;
                        d = x[k - 1];
                        if (ex > d) {
                            ex = d;
                        }
                    }
                }
            }
            return ex;
        }

//
// Arguments    : double x
//                double y
// Return Type  : double
//
        double minimum2(double x, double y) {
            double ex;
            if ((x < y) || rtIsNaN(y)) {
                ex = x;
            } else {
                ex = y;
            }
            return ex;
        }

    } // namespace internal
} // namespace coder

//
// File trailer for minOrMax.cpp
//
// [EOF]
//
