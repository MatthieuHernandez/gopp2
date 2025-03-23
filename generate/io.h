
#ifndef IO_H_CPP2
#define IO_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/io.h2"
namespace io {

#line 22 "../src/io.h2"
}


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/io.h2"
namespace io {

#line 3 "../src/io.h2"
[[nodiscard]] auto getSnnModels(cpp2::impl::in<cpp2::i8> size) -> std::vector<std::array<std::string,2>>;

#line 22 "../src/io.h2"
}


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
