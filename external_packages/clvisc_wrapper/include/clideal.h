#ifndef __CL_IDEAL__
#define __CL_IDEAL__
/*!< Use cpp exceptionn to handel errors */
#define __CL_ENABLE_EXCEPTIONS 
// System includes
//#include <CL/cl.hpp>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <map>

#include <random>

#include "Config.h"
#include "cl.hpp"
#include "opencl_backend.h"

/*! \class CLIdeal c++ wrapper for JetScape 
 *  */
class CLIdeal
{
    private:
    std::string  data_path_;
    int viscous_on_;
    int gpu_id_;

    CompileOption opts_;
    OpenclBackend backend_;

    std::vector<cl_real4> h_ev;
    cl::Buffer d_ev0;
    cl::Buffer d_ev1;
    cl::Buffer d_ev2;
    cl::Buffer d_src;

    // submax and d_submax is used to compute the maximum
    // energy density of the fluctuating QGP
    std::vector<cl_real> submax;
    cl::Buffer d_submax;

    // stores the maximum energy density history
    std::vector<cl_real> max_ed_history;

	cl::Kernel kernel_kt_src_christofeel_;
	cl::Kernel kernel_kt_src_alongx_;
	cl::Kernel kernel_kt_src_alongy_;
	cl::Kernel kernel_kt_src_alongz_;
	cl::Kernel kernel_update_ev_;

	cl::Buffer d_pi_;
    
    public:

	CLIdeal(std::string config_file_path, std::string device_type, int device_id);

	~CLIdeal();

	void clean(); /*!< delete pointers if there is any */
};


#endif 


/*! \mainpage 
 *  \section  */

/*! 
 *  \example 
*
 *  \code
 *
 *


 * \endcode
*/


