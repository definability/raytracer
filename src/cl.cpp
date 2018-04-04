#define CL_USE_DEPRECATED_OPENCL_2_0_APIS

#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <tuple>

#include <CL/cl.hpp>

#include "cl.hpp"

using std::ifstream;
using std::istreambuf_iterator;
using std::string;
using std::vector;
using std::make_pair;
using std::cout;
using std::endl;

using cl::Context;
using cl::Device;
using cl::Platform;
using cl::Program;

Program createProgram(const string& filename)
{
    return createProgram(vector<string>{filename});
}

Program createProgram(const vector<string>& filenames)
{
    vector<Platform> platforms;
    Platform::get(&platforms);

    Platform platform = platforms.front();
    vector<Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);

    Device device = devices.front();

    Program::Sources sources(filenames.size());
    vector<string> sourceStrings(filenames.size());

    for (unsigned i = 0; i < filenames.size(); ++i)
    {
        ifstream file{filenames[i]};
        sourceStrings[i] = string{
            istreambuf_iterator<char>{file},
            istreambuf_iterator<char>{}
        };
        sources[i] = {sourceStrings[i].c_str(), sourceStrings[i].length()};
    }

    Context context{devices};
    Program program{context, sources};

    program.build("-cl-std=CL1.1 -I ./src");
    return program;
}


/**
 * Based on
 * https://github.com/WanghongLin/miscellaneous/blob/master/tools/clext.py
 */
const string clGetErrorString(int errorCode)
{
    switch (errorCode) {
        case     0: return "CL_SUCCESS";
        case -   1: return "CL_DEVICE_NOT_FOUND";
        case -   2: return "CL_DEVICE_NOT_AVAILABLE";
        case -   3: return "CL_COMPILER_NOT_AVAILABLE";
        case -   4: return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
        case -   5: return "CL_OUT_OF_RESOURCES";
        case -   6: return "CL_OUT_OF_HOST_MEMORY";
        case -   7: return "CL_PROFILING_INFO_NOT_AVAILABLE";
        case -   8: return "CL_MEM_COPY_OVERLAP";
        case -   9: return "CL_IMAGE_FORMAT_MISMATCH";
        case -  10: return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
        case -  12: return "CL_MAP_FAILURE";
        case -  13: return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
        case -  14: return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
        case -  15: return "CL_COMPILE_PROGRAM_FAILURE";
        case -  16: return "CL_LINKER_NOT_AVAILABLE";
        case -  17: return "CL_LINK_PROGRAM_FAILURE";
        case -  18: return "CL_DEVICE_PARTITION_FAILED";
        case -  19: return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";
        case -  30: return "CL_INVALID_VALUE";
        case -  31: return "CL_INVALID_DEVICE_TYPE";
        case -  32: return "CL_INVALID_PLATFORM";
        case -  33: return "CL_INVALID_DEVICE";
        case -  34: return "CL_INVALID_CONTEXT";
        case -  35: return "CL_INVALID_QUEUE_PROPERTIES";
        case -  36: return "CL_INVALID_COMMAND_QUEUE";
        case -  37: return "CL_INVALID_HOST_PTR";
        case -  38: return "CL_INVALID_MEM_OBJECT";
        case -  39: return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
        case -  40: return "CL_INVALID_IMAGE_SIZE";
        case -  41: return "CL_INVALID_SAMPLER";
        case -  42: return "CL_INVALID_BINARY";
        case -  43: return "CL_INVALID_BUILD_OPTIONS";
        case -  44: return "CL_INVALID_PROGRAM";
        case -  45: return "CL_INVALID_PROGRAM_EXECUTABLE";
        case -  46: return "CL_INVALID_KERNEL_NAME";
        case -  47: return "CL_INVALID_KERNEL_DEFINITION";
        case -  48: return "CL_INVALID_KERNEL";
        case -  49: return "CL_INVALID_ARG_INDEX";
        case -  50: return "CL_INVALID_ARG_VALUE";
        case -  51: return "CL_INVALID_ARG_SIZE";
        case -  52: return "CL_INVALID_KERNEL_ARGS";
        case -  53: return "CL_INVALID_WORK_DIMENSION";
        case -  54: return "CL_INVALID_WORK_GROUP_SIZE";
        case -  55: return "CL_INVALID_WORK_ITEM_SIZE";
        case -  56: return "CL_INVALID_GLOBAL_OFFSET";
        case -  57: return "CL_INVALID_EVENT_WAIT_LIST";
        case -  58: return "CL_INVALID_EVENT";
        case -  59: return "CL_INVALID_OPERATION";
        case -  60: return "CL_INVALID_GL_OBJECT";
        case -  61: return "CL_INVALID_BUFFER_SIZE";
        case -  62: return "CL_INVALID_MIP_LEVEL";
        case -  63: return "CL_INVALID_GLOBAL_WORK_SIZE";
        case -  64: return "CL_INVALID_PROPERTY";
        case -  65: return "CL_INVALID_IMAGE_DESCRIPTOR";
        case -  66: return "CL_INVALID_COMPILER_OPTIONS";
        case -  67: return "CL_INVALID_LINKER_OPTIONS";
        case -  68: return "CL_INVALID_DEVICE_PARTITION_COUNT";
        case -  69: return "CL_INVALID_PIPE_SIZE";
        case -  70: return "CL_INVALID_DEVICE_QUEUE";
        case -1000: return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
        case -1001: return "CL_PLATFORM_NOT_FOUND_KHR";
        case -1002: return "CL_INVALID_D3D10_DEVICE_KHR";
        case -1003: return "CL_INVALID_D3D10_RESOURCE_KHR";
        case -1004: return "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR";
        case -1005: return "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR";
        case -1006: return "CL_INVALID_D3D11_DEVICE_KHR";
        case -1007: return "CL_INVALID_D3D11_RESOURCE_KHR";
        case -1008: return "CL_D3D11_RESOURCE_ALREADY_ACQUIRED_KHR";
        case -1009: return "CL_D3D11_RESOURCE_NOT_ACQUIRED_KHR";
        case -1010: return "CL_INVALID_DX9_MEDIA_ADAPTER_KHR";
        case -1011: return "CL_INVALID_DX9_MEDIA_SURFACE_KHR";
        case -1012: return "CL_DX9_MEDIA_SURFACE_ALREADY_ACQUIRED_KHR";
        case -1013: return "CL_DX9_MEDIA_SURFACE_NOT_ACQUIRED_KHR";
        case -1057: return "CL_DEVICE_PARTITION_FAILED_EXT";
        case -1058: return "CL_INVALID_PARTITION_COUNT_EXT";
        case -1059: return "CL_INVALID_PARTITION_NAME_EXT";
        case -1092: return "CL_EGL_RESOURCE_NOT_ACQUIRED_KHR";
        case -1093: return "CL_INVALID_EGL_OBJECT_KHR";
        default: return "CL_UNKNOWN_ERROR";
    }
}
