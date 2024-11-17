
#ifndef AI_H_CPP2
#define AI_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/ai.h2"

#line 14 "../src/ai.h2"
class Ai;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/ai.h2"
#include "player.h"
#include <snn/neural_network/StraightforwardNeuralNetwork.hpp>

#line 4 "../src/ai.h2"
auto createAi() -> void;

#line 14 "../src/ai.h2"
class Ai: public Player {

    private: snn::StraightforwardNeuralNetwork neuralNetwork; 
    private: snn::vector2D<float> inputs; 
    private: std::vector<cpp2::i16> moves; 

    public: explicit Ai(cpp2::impl::in<Color> c);

#line 30 "../src/ai.h2"
    public: Ai(Ai const& that);

#line 35 "../src/ai.h2"
    private: [[nodiscard]] auto getGobanState(cpp2::impl::in<State<Stone>> state) const& -> std::vector<float>;

#line 60 "../src/ai.h2"
    private: [[nodiscard]] auto chooseBestMove(cpp2::impl::in<std::vector<float>> nn_output) const& -> Move;

#line 85 "../src/ai.h2"
    public: [[nodiscard]] auto getMove(Engine& engine) -> Move override;

#line 98 "../src/ai.h2"
    public: auto train() & -> void;

#line 121 "../src/ai.h2"
    public: auto save() & -> void;

#line 124 "../src/ai.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/ai.h2"

#line 4 "../src/ai.h2"
auto createAi() -> void{
    std::vector<snn::LayerModel> layers {snn::Input(361), 
                                                snn::FullyConnected(100), 
                                                snn::FullyConnected(361)}; 
    auto optimizer {snn::StochasticGradientDescent(0.0001f, 0.0f)}; 
    auto neuralNetwork {snn::StraightforwardNeuralNetwork(cpp2::move(layers), cpp2::move(optimizer))}; 
    CPP2_UFCS(saveAs)(cpp2::move(neuralNetwork), "./snn_models/first_model.snn");
}

#line 20 "../src/ai.h2"
    Ai::Ai(cpp2::impl::in<Color> c)
        : Player{ c }
        , neuralNetwork{ snn::StraightforwardNeuralNetwork::loadFrom("./snn_models/first_model.snn") }
        , inputs{  }
        , moves{  }{

#line 25 "../src/ai.h2"
        CPP2_UFCS(reserve)(inputs, 300);
        CPP2_UFCS(reserve)(moves, 300);
        setNextMessage("AI loaded.");
    }

#line 30 "../src/ai.h2"
    Ai::Ai(Ai const& that)
        : Player{ that }
        , neuralNetwork{ that.neuralNetwork }
        , inputs{ that.inputs }
        , moves{ that.moves }{

#line 33 "../src/ai.h2"
    }

#line 35 "../src/ai.h2"
    [[nodiscard]] auto Ai::getGobanState(cpp2::impl::in<State<Stone>> state) const& -> std::vector<float>{
        std::vector<float> vec {}; 
        CPP2_UFCS(reserve)(vec, 361);
{
cpp2::i8 col{0};

#line 39 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(col,CPP2_UFCS(ssize)(state)); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 43 "../src/ai.h2"
            for( ; cpp2::impl::cmp_less(row,CPP2_UFCS(ssize)(CPP2_ASSERT_IN_BOUNDS(state, col))); 
            ++row ) 
            {
                if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, col), row).color == color) {
                    CPP2_UFCS(push_back)(vec, 0.5);
                }
                if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, col), row).color == Color::None) {
                    CPP2_UFCS(push_back)(vec, 0.5);
                }
                else {
                    CPP2_UFCS(push_back)(vec, 0.5);
                }
            }
}
#line 56 "../src/ai.h2"
        }
}
#line 57 "../src/ai.h2"
        return vec; 
    }

#line 60 "../src/ai.h2"
    [[nodiscard]] auto Ai::chooseBestMove(cpp2::impl::in<std::vector<float>> nn_output) const& -> Move{
        cpp2::i16 index {0}; 
        float max {0}; 
        cpp2::i8 max_col {0}; 
        cpp2::i8 max_row {0}; 
{
cpp2::i8 col{0};

#line 66 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(col,19); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 70 "../src/ai.h2"
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
#line 80 "../src/ai.h2"
        }
}
#line 81 "../src/ai.h2"
        auto m {Move(color, cpp2::move(max_col), cpp2::move(max_row))}; 
        return m; 
    }

#line 85 "../src/ai.h2"
    [[nodiscard]] auto Ai::getMove(Engine& engine) -> Move{
        auto input {getGobanState(engine.goban.state)}; 
        auto output {CPP2_UFCS(computeOutput)(neuralNetwork, input)}; 
        auto m {chooseBestMove(cpp2::move(output))}; 
        CPP2_UFCS(closerValidMove)(engine, m);
        auto moveIndex {CPP2_UFCS(getIndex)(m.stone)}; 
        if (cpp2::impl::cmp_greater_eq(moveIndex,0)) {
            CPP2_UFCS(push_back)(inputs, cpp2::move(input));
            CPP2_UFCS(push_back)(moves, cpp2::move(moveIndex));
        }
        return m; 
    }

#line 98 "../src/ai.h2"
    auto Ai::train() & -> void{
        float expectedValue {-1.0}; 
        if (hasWon) {// CPP2 workaround: Conditional operator not yet supported.
            expectedValue = -1;
        }
{
cpp2::i16 i{0};

#line 104 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(i,CPP2_UFCS(ssize)(inputs)); 
        ++i ) 
        {
            auto expected_output {CPP2_ASSERT_IN_BOUNDS(inputs, i)}; 
{
cpp2::i16 j{0};

#line 109 "../src/ai.h2"
            for( ; cpp2::impl::cmp_less(j,361); 
            ++j ) 
            {
                if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(inputs, i), j) != 0.0) {
                    CPP2_ASSERT_IN_BOUNDS(expected_output, j) = -1;
                }
            }
}
#line 116 "../src/ai.h2"
            CPP2_ASSERT_IN_BOUNDS(expected_output, CPP2_ASSERT_IN_BOUNDS(moves, i)) = expectedValue;
            CPP2_UFCS(trainOnce)(neuralNetwork, CPP2_ASSERT_IN_BOUNDS(inputs, i), cpp2::move(expected_output));
        }
}
#line 119 "../src/ai.h2"
    }

#line 121 "../src/ai.h2"
    auto Ai::save() & -> void{
        CPP2_UFCS(saveAs)(neuralNetwork, "./snn_models/first_model.snn");
    }
#endif

