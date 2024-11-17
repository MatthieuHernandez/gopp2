
#ifndef AI_H_CPP2
#define AI_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/ai.h2"

#line 6 "../src/ai.h2"
class Ai;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/ai.h2"
#include "player.h"
#include <snn/neural_network/StraightforwardNeuralNetwork.hpp>

#line 6 "../src/ai.h2"
class Ai: public Player {

    private: snn::StraightforwardNeuralNetwork neuralNetwork; 
    private: snn::vector2D<float> inputs; 
    private: std::vector<Move> moves; 

    private: [[nodiscard]] static auto getLayers() -> std::vector<snn::LayerModel>;

#line 19 "../src/ai.h2"
    public: explicit Ai(cpp2::impl::in<Color> c);

#line 28 "../src/ai.h2"
    public: Ai(Ai const& that);

#line 33 "../src/ai.h2"
    private: [[nodiscard]] auto getGobanState(cpp2::impl::in<State<Stone>> state) const& -> std::vector<float>;

#line 58 "../src/ai.h2"
    private: [[nodiscard]] auto chooseBestMove(cpp2::impl::in<std::vector<float>> nn_output) const& -> Move;

#line 83 "../src/ai.h2"
    public: [[nodiscard]] auto getMove(Engine& engine) -> Move override;

#line 93 "../src/ai.h2"
    public: auto train() & -> void;

#line 99 "../src/ai.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/ai.h2"

#line 12 "../src/ai.h2"
    [[nodiscard]] auto Ai::getLayers() -> std::vector<snn::LayerModel>{
        std::vector<snn::LayerModel> layers {snn::Input(361), 
                                                snn::FullyConnected(100), 
                                                snn::FullyConnected(361)}; 
        return layers; 
    }

#line 19 "../src/ai.h2"
    Ai::Ai(cpp2::impl::in<Color> c)
        : Player{ c }
        , neuralNetwork{ getLayers() }
        , inputs{  }
        , moves{  }{

#line 24 "../src/ai.h2"
        CPP2_UFCS(reserve)(inputs, 300);
        CPP2_UFCS(reserve)(moves, 300);
    }

#line 28 "../src/ai.h2"
    Ai::Ai(Ai const& that)
        : Player{ that }
        , neuralNetwork{ that.neuralNetwork }
        , inputs{ that.inputs }
        , moves{ that.moves }{

#line 31 "../src/ai.h2"
    }

#line 33 "../src/ai.h2"
    [[nodiscard]] auto Ai::getGobanState(cpp2::impl::in<State<Stone>> state) const& -> std::vector<float>{
        std::vector<float> vec {}; 
        CPP2_UFCS(reserve)(vec, 361);
{
cpp2::i8 col{0};

#line 37 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(col,CPP2_UFCS(ssize)(state)); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 41 "../src/ai.h2"
            for( ; cpp2::impl::cmp_less(row,CPP2_UFCS(ssize)(CPP2_ASSERT_IN_BOUNDS(state, col))); 
            ++row ) 
            {
                if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, col), row).color == color) {
                    CPP2_UFCS(push_back)(vec, 1.0);
                }
                if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, col), row).color == Color::None) {
                    CPP2_UFCS(push_back)(vec, 0.0);
                }
                else {
                    CPP2_UFCS(push_back)(vec, -1.0);
                }
            }
}
#line 54 "../src/ai.h2"
        }
}
#line 55 "../src/ai.h2"
        return vec; 
    }

#line 58 "../src/ai.h2"
    [[nodiscard]] auto Ai::chooseBestMove(cpp2::impl::in<std::vector<float>> nn_output) const& -> Move{
        cpp2::i16 index {0}; 
        float max {0}; 
        cpp2::i8 max_col {0}; 
        cpp2::i8 max_row {0}; 
{
cpp2::i8 col{0};

#line 64 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(col,19); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 68 "../src/ai.h2"
            for( ; cpp2::impl::cmp_less(row,19); 
            ++row ) 
            {
                if (cpp2::impl::cmp_less(max,CPP2_ASSERT_IN_BOUNDS(nn_output, index))) {
                    max = CPP2_ASSERT_IN_BOUNDS(nn_output, index);
                    max_col = col;
                    max_row = row;
                }
                ++index;
            }
}
#line 78 "../src/ai.h2"
        }
}
#line 79 "../src/ai.h2"
        auto m {Move(color, cpp2::move(max_col), cpp2::move(max_row))}; 
        return m; 
    }

#line 83 "../src/ai.h2"
    [[nodiscard]] auto Ai::getMove(Engine& engine) -> Move{
        auto input {getGobanState(engine.goban.state)}; 
        CPP2_UFCS(push_back)(inputs, input);
        auto output {CPP2_UFCS(computeOutput)(neuralNetwork, cpp2::move(input))}; 
        auto m {chooseBestMove(cpp2::move(output))}; 
        CPP2_UFCS(closerValidMove)(engine, m);
        CPP2_UFCS(push_back)(moves, m);
        return m; 
    }

#line 93 "../src/ai.h2"
    auto Ai::train() & -> void{

        /*if win 1 else -1 otherwise 0
        for all move 
        inputs -> expected output ==> getExpectedOutput(choosedMove)*/
    }
#endif

