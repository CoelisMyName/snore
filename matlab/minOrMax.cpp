#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "mylock.h"
#include "rt_nonfinite.h"

namespace coder {
namespace internal {
void maximum(const ::coder::array<double, 2U> &x, double ex_data[],
             int ex_size[2])
{
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

double maximum(const ::coder::array<double, 2U> &x)
{
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

double maximum(const ::coder::array<double, 1U> &x)
{
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

void minimum(const ::coder::array<double, 2U> &x, double ex_data[],
             int ex_size[2])
{
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

double minimum(const ::coder::array<double, 1U> &x)
{
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

double minimum(const ::coder::array<double, 2U> &x)
{
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

} // namespace internal
} // namespace coder
