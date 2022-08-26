#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <iostream>
#include <exception>


namespace py = pybind11;

py::array_t<uint8_t> s32_to_u8(py::array_t<uint32_t>& src){
    try{

        py::buffer_info input = src.request();
        if(input.ndim!=1){
            return py::array_t<uint8_t>();
            // throw std::runtime_error("Number of dimensions must be one");
        }

        auto dst = py::array_t<uint8_t>(input.size*4);
        py::buffer_info output = dst.request(true);

        uint32_t* input_ptr = (uint32_t*)input.ptr;
        uint8_t* output_ptr = (uint8_t*) output.ptr;

        for(auto i=0;i<input.shape[0];++i){
            auto temp = input_ptr[i];

            output_ptr[i*4] = temp;
            output_ptr[i*4+1] = temp>>8;
            output_ptr[i*4+2] = temp>>16;
            output_ptr[i*4+3] = temp>>24;

            // output_ptr[i*4] = temp;
            // output_ptr[i*4+1] = temp>>8 ;
            // output_ptr[i*4+2] = temp>>16 ;
            // output_ptr[i*4+3] = temp>>24;

            // output_ptr[i*4] = temp & 0xFF;
            // output_ptr[i*4+1] = (temp>>8) & 0xFF;
            // output_ptr[i*4+2] = (temp>>16) & 0xFF;
            // output_ptr[i*4+3] = (temp>>24) & 0xFF;

            // output_ptr[i*4] = (temp>>24) & 0xFF;
            // output_ptr[i*4+1] = (temp>>16) & 0xFF;
            // output_ptr[i*4+2] = (temp>>8) & 0xFF;
            // output_ptr[i*4+3] = temp & 0xFF;

            // output_ptr[i*4] = *((uint8_t *)&temp +3);
            // output_ptr[i*4+1] = *((uint8_t *)&temp+2);
            // output_ptr[i*4+2] = *((uint8_t *)&temp+1);
            // output_ptr[i*4+3] = *((uint8_t *)&temp);

            // output_ptr[i*4] = *((uint8_t *)&temp+0);
            // output_ptr[i*4+1] = *((uint8_t *)&temp+1);
            // output_ptr[i*4+2] = *((uint8_t *)&temp+2);
            // output_ptr[i*4+3] = *((uint8_t *)&temp +3);
        }

        return dst;

    }catch(std::exception& e){
        std::cout<<"s32_to_u8 exception"<<e.what()<<std::endl;
        return py::array_t<uint8_t>();
    }
    
}


PYBIND11_MODULE(bit_convert,b){
    b.doc() = "pybind11 32s to 8u";
    b.def("s32_to_u8",&s32_to_u8);
    b.def("test",[]()->std::string const {return "hello world";});
}


