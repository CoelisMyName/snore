//
// File: introsort.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "introsort.h"
#include "anonymous_function.h"
#include "heapsort.h"
#include "insertionsort.h"
#include "nextpow2.h"
#include "rt_nonfinite.h"
#include "stack1.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : ::coder::array<int, 1U> &x
//                int xend
//                const anonymous_function *cmp
// Return Type  : void
//
namespace coder {
    namespace internal {
        void introsort(::coder::array<int, 1U> &x, int xend,
                       const anonymous_function *cmp) {
            stack st;
            struct_T frame;
            if (1 < xend) {
                if (xend <= 32) {
                    insertionsort(x, 1, xend, cmp);
                } else {
                    int MAXDEPTH;
                    int i;
                    int t;
                    MAXDEPTH = (nextpow2(xend) - 1) << 1;
                    frame.xstart = 1;
                    frame.xend = xend;
                    frame.depth = 0;
                    t = MAXDEPTH << 1;
                    st.d.set_size(t);
                    for (i = 0; i < t; i++) {
                        st.d[i] = frame;
                    }
                    st.d[0] = frame;
                    st.n = 1;
                    while (st.n > 0) {
                        int frame_tmp_tmp;
                        frame_tmp_tmp = st.n - 1;
                        frame = st.d[st.n - 1];
                        st.n--;
                        i = frame.xend - frame.xstart;
                        if (i + 1 <= 32) {
                            insertionsort(x, frame.xstart, frame.xend, cmp);
                        } else if (frame.depth == MAXDEPTH) {
                            b_heapsort(x, frame.xstart, frame.xend, cmp);
                        } else {
                            int b_i;
                            int pivot;
                            int xmid;
                            boolean_T varargout_1;
                            xmid = (frame.xstart + i / 2) - 1;
                            i = x[frame.xstart - 1];
                            t = cmp->workspace.a[x[xmid] - 1];
                            b_i = cmp->workspace.a[i - 1];
                            varargout_1 =
                                    ((t < b_i) || ((t == b_i) && (cmp->workspace.b[x[xmid] - 1] <
                                                                  cmp->workspace.b[i - 1])));
                            if (varargout_1) {
                                x[frame.xstart - 1] = x[xmid];
                                x[xmid] = i;
                            }
                            if (cmp->workspace.a[x[frame.xend - 1] - 1] <
                                cmp->workspace.a[x[frame.xstart - 1] - 1]) {
                                varargout_1 = true;
                            } else {
                                i = x[frame.xend - 1] - 1;
                                t = x[frame.xstart - 1] - 1;
                                varargout_1 = ((cmp->workspace.a[i] == cmp->workspace.a[t]) &&
                                               (cmp->workspace.b[i] < cmp->workspace.b[t]));
                            }
                            if (varargout_1) {
                                t = x[frame.xstart - 1];
                                x[frame.xstart - 1] = x[frame.xend - 1];
                                x[frame.xend - 1] = t;
                            }
                            if (cmp->workspace.a[x[frame.xend - 1] - 1] <
                                cmp->workspace.a[x[xmid] - 1]) {
                                varargout_1 = true;
                            } else {
                                i = x[frame.xend - 1] - 1;
                                varargout_1 =
                                        ((cmp->workspace.a[i] == cmp->workspace.a[x[xmid] - 1]) &&
                                         (cmp->workspace.b[i] < cmp->workspace.b[x[xmid] - 1]));
                            }
                            if (varargout_1) {
                                t = x[xmid];
                                x[xmid] = x[frame.xend - 1];
                                x[frame.xend - 1] = t;
                            }
                            pivot = x[xmid] - 1;
                            x[xmid] = x[frame.xend - 2];
                            x[frame.xend - 2] = pivot + 1;
                            b_i = frame.xstart - 1;
                            xmid = frame.xend - 2;
                            int exitg1;
                            do {
                                int exitg2;
                                exitg1 = 0;
                                b_i++;
                                do {
                                    exitg2 = 0;
                                    i = cmp->workspace.a[x[b_i] - 1];
                                    varargout_1 =
                                            ((i < cmp->workspace.a[pivot]) ||
                                             ((i == cmp->workspace.a[pivot]) &&
                                              (cmp->workspace.b[x[b_i] - 1] < cmp->workspace.b[pivot])));
                                    if (varargout_1) {
                                        b_i++;
                                    } else {
                                        exitg2 = 1;
                                    }
                                } while (exitg2 == 0);
                                xmid--;
                                do {
                                    exitg2 = 0;
                                    i = cmp->workspace.a[x[xmid] - 1];
                                    varargout_1 =
                                            ((cmp->workspace.a[pivot] < i) ||
                                             ((cmp->workspace.a[pivot] == i) &&
                                              (cmp->workspace.b[pivot] < cmp->workspace.b[x[xmid] - 1])));
                                    if (varargout_1) {
                                        xmid--;
                                    } else {
                                        exitg2 = 1;
                                    }
                                } while (exitg2 == 0);
                                if (b_i + 1 >= xmid + 1) {
                                    exitg1 = 1;
                                } else {
                                    t = x[b_i];
                                    x[b_i] = x[xmid];
                                    x[xmid] = t;
                                }
                            } while (exitg1 == 0);
                            x[frame.xend - 2] = x[b_i];
                            x[b_i] = pivot + 1;
                            if (b_i + 2 < frame.xend) {
                                st.d[frame_tmp_tmp].xstart = b_i + 2;
                                st.d[frame_tmp_tmp].xend = frame.xend;
                                st.d[frame_tmp_tmp].depth = frame.depth + 1;
                                st.n = frame_tmp_tmp + 1;
                            }
                            if (frame.xstart < b_i + 1) {
                                st.d[st.n].xstart = frame.xstart;
                                st.d[st.n].xend = b_i + 1;
                                st.d[st.n].depth = frame.depth + 1;
                                st.n++;
                            }
                        }
                    }
                }
            }
        }

    } // namespace internal
} // namespace coder

//
// File trailer for introsort.cpp
//
// [EOF]
//
