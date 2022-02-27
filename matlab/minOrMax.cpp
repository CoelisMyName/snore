//
// File: minOrMax.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : const double x_data[]
//                double *ex
//                int *idx
// Return Type  : void
//
namespace coder {
    namespace internal {
        void b_maximum(const double x_data[], double *ex, int *idx) {
            int k;
            if (!rtIsNaN(x_data[0])) {
                *idx = 1;
            } else {
                boolean_T exitg1;
                *idx = 0;
                k = 2;
                exitg1 = false;
                while ((!exitg1) && (k <= 20)) {
                    if (!rtIsNaN(x_data[k - 1])) {
                        *idx = k;
                        exitg1 = true;
                    } else {
                        k++;
                    }
                }
            }
            if (*idx == 0) {
                *ex = x_data[0];
                *idx = 1;
            } else {
                int i;
                *ex = x_data[*idx - 1];
                i = *idx + 1;
                for (k = i; k < 21; k++) {
                    double d;
                    d = x_data[k - 1];
                    if (*ex < d) {
                        *ex = d;
                        *idx = k;
                    }
                }
            }
        }

//
// Arguments    : const ::coder::array<double, 2U> &x
//                double ex_data[]
//                int ex_size[2]
// Return Type  : void
//
        void maximum(const ::coder::array<double, 2U> &x, double ex_data[],
                     int ex_size[2]) {
            int m;
            m = x.size(0);
            ex_size[0] = 1;
            ex_size[1] = x.size(1);
            if (x.size(1) >= 1) {
                ex_data[0] = x[0];
                for (int i = 2; i <= m; i++) {
                    double b;
                    boolean_T p;
                    b = x[i - 1];
                    if (rtIsNaN(b)) {
                        p = false;
                    } else if (rtIsNaN(ex_data[0])) {
                        p = true;
                    } else {
                        p = (ex_data[0] < b);
                    }
                    if (p) {
                        ex_data[0] = b;
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
// Return Type  : double
//
        double maximum(const ::coder::array<double, 2U> &x) {
            double ex;
            int last;
            last = x.size(1);
            if (x.size(1) <= 2) {
                if (x.size(1) == 1) {
                    ex = x[0];
                } else if ((x[0] < x[x.size(1) - 1]) ||
                           (rtIsNaN(x[0]) && (!rtIsNaN(x[x.size(1) - 1])))) {
                    ex = x[x.size(1) - 1];
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
// Arguments    : const ::coder::array<double, 1U> &x
// Return Type  : double
//
        double maximum(const ::coder::array<double, 1U> &x) {
            double ex;
            int last;
            last = x.size(0);
            if (x.size(0) <= 2) {
                if (x.size(0) == 1) {
                    ex = x[0];
                } else if ((x[0] < x[x.size(0) - 1]) ||
                           (rtIsNaN(x[0]) && (!rtIsNaN(x[x.size(0) - 1])))) {
                    ex = x[x.size(0) - 1];
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
            int n;
            n = x.size(1);
            ex.set_size(1, x.size(1));
            for (int j = 0; j < n; j++) {
                double a;
                double b;
                boolean_T p;
                a = x[2 * j];
                ex[j] = a;
                b = x[2 * j + 1];
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

//
// Arguments    : const ::coder::array<double, 2U> &x
//                double ex_data[]
//                int ex_size[2]
// Return Type  : void
//
        void minimum(const ::coder::array<double, 2U> &x, double ex_data[],
                     int ex_size[2]) {
            int m;
            m = x.size(0);
            ex_size[0] = 1;
            ex_size[1] = x.size(1);
            if (x.size(1) >= 1) {
                ex_data[0] = x[0];
                for (int i = 2; i <= m; i++) {
                    double b;
                    boolean_T p;
                    b = x[i - 1];
                    if (rtIsNaN(b)) {
                        p = false;
                    } else if (rtIsNaN(ex_data[0])) {
                        p = true;
                    } else {
                        p = (ex_data[0] > b);
                    }
                    if (p) {
                        ex_data[0] = b;
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

//
// Arguments    : const double x[2]
// Return Type  : double
//
        double minimum(const double x[2]) {
            double ex;
            if ((x[0] > x[1]) || (rtIsNaN(x[0]) && (!rtIsNaN(x[1])))) {
                ex = x[1];
            } else {
                ex = x[0];
            }
            return ex;
        }

//
// Arguments    : const ::coder::array<double, 1U> &x
// Return Type  : double
//
        double minimum(const ::coder::array<double, 1U> &x) {
            double ex;
            int last;
            last = x.size(0);
            if (x.size(0) <= 2) {
                if (x.size(0) == 1) {
                    ex = x[0];
                } else if ((x[0] > x[x.size(0) - 1]) ||
                           (rtIsNaN(x[0]) && (!rtIsNaN(x[x.size(0) - 1])))) {
                    ex = x[x.size(0) - 1];
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
// Arguments    : const ::coder::array<double, 2U> &x
// Return Type  : double
//
        double minimum(const ::coder::array<double, 2U> &x) {
            double ex;
            int last;
            last = x.size(1);
            if (x.size(1) <= 2) {
                if (x.size(1) == 1) {
                    ex = x[0];
                } else if ((x[0] > x[x.size(1) - 1]) ||
                           (rtIsNaN(x[0]) && (!rtIsNaN(x[x.size(1) - 1])))) {
                    ex = x[x.size(1) - 1];
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
// Arguments    : const ::coder::array<double, 2U> &y
//                ::coder::array<double, 2U> &ex
// Return Type  : void
//
        void minimum2(const ::coder::array<double, 2U> &y,
                      ::coder::array<double, 2U> &ex) {
            int nx;
            ex.set_size(1, y.size(1));
            nx = y.size(1);
            for (int k = 0; k < nx; k++) {
                double d;
                d = y[k];
                if ((0.0 < d) || rtIsNaN(d)) {
                    ex[k] = 0.0;
                } else {
                    ex[k] = d;
                }
            }
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
