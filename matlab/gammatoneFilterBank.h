#ifndef GAMMATONEFILTERBANK_H
#define GAMMATONEFILTERBANK_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

struct cell_wrap_68 {
    unsigned int f1[8];
};

namespace coder {
class gammatoneFilterBank {
  public:
    void step(const ::coder::array<double, 1U> &varargin_1,
              ::coder::array<double, 2U> &varargout_1);
    void matlabCodegenDestructor();
    ~gammatoneFilterBank();
    gammatoneFilterBank();
    boolean_T matlabCodegenIsDeleted;
    int isInitialized;
    double pSampleRateDialog;
    double pNumChannels;

  private:
    boolean_T isSetupComplete;
    boolean_T TunablePropsChanged;
    cell_wrap_68 inputVarSize[1];
    double pCoeffs[624];
    double pStates[208];
    double pCenterFrequencies[26];
};

class b_gammatoneFilterBank {
  public:
    void step(const ::coder::array<double, 1U> &varargin_1,
              ::coder::array<double, 2U> &varargout_1);
    void SystemCore_step(const ::coder::array<double, 1U> &varargin_1,
                         ::coder::array<double, 2U> &varargout_1);
    void matlabCodegenDestructor();
    void handle_matlabCodegenDestructor();
    ~b_gammatoneFilterBank();
    b_gammatoneFilterBank();
    boolean_T matlabCodegenIsDeleted;
    int isInitialized;
    double pSampleRateDialog;
    double pNumChannels;

  private:
    boolean_T isSetupComplete;
    boolean_T TunablePropsChanged;
    cell_wrap_68 inputVarSize[1];
    double pCoeffs[696];
    double pStates[232];
    double pCenterFrequencies[29];
};

class c_gammatoneFilterBank {
  public:
    void step(const ::coder::array<double, 1U> &varargin_1,
              ::coder::array<double, 2U> &varargout_1);
    void matlabCodegenDestructor();
    ~c_gammatoneFilterBank();
    c_gammatoneFilterBank();
    boolean_T matlabCodegenIsDeleted;
    int isInitialized;
    double pSampleRateDialog;
    double pNumChannels;

  private:
    boolean_T isSetupComplete;
    boolean_T TunablePropsChanged;
    cell_wrap_68 inputVarSize[1];
    double pCoeffs[840];
    double pStates[280];
    double pCenterFrequencies[35];
};

class d_gammatoneFilterBank {
  public:
    void step(const ::coder::array<double, 1U> &varargin_1,
              ::coder::array<double, 2U> &varargout_1);
    void matlabCodegenDestructor();
    ~d_gammatoneFilterBank();
    d_gammatoneFilterBank();
    boolean_T matlabCodegenIsDeleted;
    int isInitialized;
    double pSampleRateDialog;
    double pNumChannels;

  private:
    boolean_T isSetupComplete;
    boolean_T TunablePropsChanged;
    cell_wrap_68 inputVarSize[1];
    double pCoeffs[864];
    double pStates[288];
    double pCenterFrequencies[36];
};

class e_gammatoneFilterBank {
  public:
    void step(const ::coder::array<double, 1U> &varargin_1,
              ::coder::array<double, 2U> &varargout_1);
    void matlabCodegenDestructor();
    ~e_gammatoneFilterBank();
    e_gammatoneFilterBank();
    boolean_T matlabCodegenIsDeleted;
    int isInitialized;
    double pSampleRateDialog;
    double pNumChannels;

  private:
    boolean_T isSetupComplete;
    boolean_T TunablePropsChanged;
    cell_wrap_68 inputVarSize[1];
    double pCoeffs[984];
    double pStates[328];
    double pCenterFrequencies[41];
};

class f_gammatoneFilterBank {
  public:
    void step(const ::coder::array<double, 1U> &varargin_1,
              ::coder::array<double, 2U> &varargout_1);
    void matlabCodegenDestructor();
    ~f_gammatoneFilterBank();
    f_gammatoneFilterBank();
    boolean_T matlabCodegenIsDeleted;
    int isInitialized;
    double pSampleRateDialog;
    double pNumChannels;

  private:
    boolean_T isSetupComplete;
    boolean_T TunablePropsChanged;
    cell_wrap_68 inputVarSize[1];
    double pCoeffs[1008];
    double pStates[336];
    double pCenterFrequencies[42];
};

} // namespace coder

#endif
