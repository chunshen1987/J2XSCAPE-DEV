/** CLVisc C++ Version by LongGang Pang 
 * Served as a c++ wrapper for JetScape
 * This file wrap the commonly used OpenCL functionalities*/
#ifndef __OPENCL_BACKEND_H__
#define __OPENCL_BACKEND_H__

#define __CL_ENABLE_EXCEPTIONS
//#if defined(__APPLE__) || defined(__MACOSX)
//#include <OpenCL/cl.hpp>
//#else
//#include <CL/cl.hpp>
//#endif
#include "cl.hpp"

#include <map>
#include <ctime>
#include <algorithm>
#include <random>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <type_traits>

#ifdef OPENCL_USE_SINGLE_PRECISION
/*!< typedef cl_float to cl_real for easier switch from double to float */
 typedef cl_float cl_real;
 typedef cl_float2 cl_real2;
 typedef cl_float4 cl_real4;
 typedef cl_float3 cl_real3;
 typedef cl_float8 cl_real8;
#else
 typedef cl_double cl_real;
 typedef cl_double2 cl_real2;
 typedef cl_double4 cl_real4;
 typedef cl_double3 cl_real3;
 typedef cl_double8 cl_real8;
#endif


/* compile options to build opencl kernel files on device*/
class CompileOption {
    public:
        std::stringstream opt;

        CompileOption();
        /*! \breif if you see strange behaviour in opencl, please
         *  set compilation option optimize=false */
        CompileOption(bool use_single_precision, bool optimize);
        void Define(std::string name);
        void SetDoubleConst(std::string name, double value);
        void SetFloatConst(std::string name, float value);
        void SetIntConst(std::string name, int value);
        void KernelIncludePath(std::string abs_path);
};

class OpenclBackend {
  public:
    OpenclBackend(std::string device_type, int device_id);
    std::map<std::string, cl::Program> programs;
    std::map<std::string, cl::Kernel> kernel_funcs;
    std::map<std::string, cl::Buffer> buffers;

    /*!\breif helper functions: Build each program in programs vector with given options
    *  \note The compiling error of the kernel *.cl can be print out
    */
    cl::Program BuildProgram(std::string fname, const CompileOption & option);

    cl::Kernel CreateKernel(const cl::Program & prg, std::string func_name) {
        return cl::Kernel(prg, func_name.c_str());
    }


    /*! \breif printout the available devices*/
    void DeviceInfo();
 
    /*! \breif utility to compute the excution time of one event */
    float ExcutionTime(cl::Event & event);

    /*! \breif create a buffer on GPU, e.g., for one cl_real array of N elements,
     * the bytes_of_buffer = N * sizeof(cl_real) */
    cl::Buffer CreateBuffer(size_t bytes_of_buffer);

    /*! \breif create a buffer on GPU, with the same size and content as source_vector */
    template <class ValueType>
    cl::Buffer CreateBufferByCopyVector(std::vector<ValueType> source_vector, bool read_only);

  private:
    cl_int device_type_;
    std::vector<cl::Device> devices_;
    cl_int device_id_;
    cl::Device device_;
    cl::Context context_;
    cl::CommandQueue queue_;

    /*! \breif helper functions: create context from the device type with one platform which support it 
     * \return one context in the type of cl::Context
     */
    cl::Context CreateContext_(const cl_int & device_type);
    
    /*! \breif CreateContext, AddProgram, Build program, Initialize Buffer*/
};

#endif
