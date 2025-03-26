
#ifndef IO_H_CPP2
#error This file is part of a '.h2' header compiled to be consumed from another -pure-cpp2 file. To use this file, write '#include "io.h2"' in a '.h2' or '.cpp2' file compiled with -pure-cpp2.
#endif

#ifndef IO_HPP_CPP2
#define IO_HPP_CPP2



//=== Cpp2 function definitions =================================================

#line 1 "../src/io.h2"
namespace io {

#line 3 "../src/io.h2"
[[nodiscard]] auto getSnnModels(cpp2::impl::in<cpp2::i8> size) -> std::vector<std::array<std::string,2>>{
    std::vector<std::array<std::string,2>> modelFiles {}; 
    std::string path {""}; 
    if (size == 9) {
        path = "./snn_models/9x9";
    }else {if (size == 19) {
        path = "./snn_models/19x19";
    }}

    auto files {std::filesystem::directory_iterator(path)}; 
    for ( 
    auto const& file : cpp2::move(files) ) {
        std::string modelName {CPP2_UFCS(string)(CPP2_UFCS(filename)(CPP2_UFCS(path)(file)))}; 
        std::string modelPath {CPP2_UFCS(string)(CPP2_UFCS(path)(file))}; 
        std::array<std::string,2> modelFile {cpp2::move(modelName), cpp2::move(modelPath)}; 
        CPP2_UFCS(push_back)(modelFiles, cpp2::move(modelFile));
    }
    return modelFiles; 
}
}

#endif
