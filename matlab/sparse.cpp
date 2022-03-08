#include "sparse.h"
#include "anonymous_function.h"
#include "introsort.h"
#include "rt_nonfinite.h"
#include "sparse1.h"
#include "coder_array.h"
#include "mylock.h"

namespace coder {
void b_sparse(const ::coder::array<double, 2U> &varargin_1,
              const ::coder::array<double, 2U> &varargin_2,
              const ::coder::array<double, 2U> &varargin_3, double varargin_5,
              sparse *y)
{
    anonymous_function b_this;
    array<int, 1U> sortedIndices;
    array<int, 1U> t;
    int c;
    int i;
    int k;
    int nc;
    int ns;
    int ny;
    nc = varargin_2.size(1);
    ns = varargin_1.size(1);
    b_this.workspace.b.set_size(varargin_1.size(1));
    for (k = 0; k < ns; k++) {
        b_this.workspace.b[k] = static_cast<int>(varargin_1[k]);
    }
    ns = varargin_2.size(1);
    b_this.workspace.a.set_size(varargin_2.size(1));
    for (k = 0; k < ns; k++) {
        b_this.workspace.a[k] = static_cast<int>(varargin_2[k]);
    }
    sortedIndices.set_size(varargin_2.size(1));
    for (k = 0; k < nc; k++) {
        sortedIndices[k] = k + 1;
    }
    internal::introsort(sortedIndices, b_this.workspace.a.size(0), &b_this);
    ny = b_this.workspace.a.size(0);
    t.set_size(b_this.workspace.a.size(0));
    ns = b_this.workspace.a.size(0);
    for (i = 0; i < ns; i++) {
        t[i] = b_this.workspace.a[i];
    }
    for (k = 0; k < ny; k++) {
        b_this.workspace.a[k] = t[sortedIndices[k] - 1];
    }
    ny = b_this.workspace.b.size(0);
    t.set_size(b_this.workspace.b.size(0));
    ns = b_this.workspace.b.size(0);
    for (i = 0; i < ns; i++) {
        t[i] = b_this.workspace.b[i];
    }
    for (k = 0; k < ny; k++) {
        b_this.workspace.b[k] = t[sortedIndices[k] - 1];
    }
    ny = static_cast<int>(varargin_5);
    y->n = static_cast<int>(varargin_5);
    if (varargin_2.size(1) >= 1) {
        ns = varargin_2.size(1);
    } else {
        ns = 1;
    }
    y->d.set_size(ns);
    y->colidx.set_size(static_cast<int>(varargin_5) + 1);
    y->colidx[0] = 1;
    y->rowidx.set_size(ns);
    for (i = 0; i < ns; i++) {
        y->d[i] = 0.0;
        y->rowidx[i] = 0;
    }
    ns = 0;
    for (c = 0; c < ny; c++) {
        while ((ns + 1 <= nc) && (b_this.workspace.a[ns] == c + 1)) {
            y->rowidx[ns] = b_this.workspace.b[ns];
            ns++;
        }
        y->colidx[c + 1] = ns + 1;
    }
    for (k = 0; k < nc; k++) {
        y->d[k] = varargin_3[sortedIndices[k] - 1];
    }
    ns = 1;
    i = y->colidx.size(0);
    for (c = 0; c <= i - 2; c++) {
        ny = y->colidx[c];
        y->colidx[c] = ns;
        int exitg1;
        do {
            exitg1 = 0;
            k = y->colidx[c + 1];
            if (ny < k) {
                double val;
                val = 0.0;
                nc = y->rowidx[ny - 1];
                while ((ny < k) && (y->rowidx[ny - 1] == nc)) {
                    val += y->d[ny - 1];
                    ny++;
                }
                if (val != 0.0) {
                    y->d[ns - 1] = val;
                    y->rowidx[ns - 1] = nc;
                    ns++;
                }
            } else {
                exitg1 = 1;
            }
        } while (exitg1 == 0);
    }
    y->colidx[y->colidx.size(0) - 1] = ns;
}

} // namespace coder
