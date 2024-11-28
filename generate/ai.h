
#ifndef AI_H_CPP2
#define AI_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/ai.h2"

#line 20 "../src/ai.h2"
class Ai;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/ai.h2"
#include "player.h"
#include "io.h"
#include <snn/neural_network/StraightforwardNeuralNetwork.hpp>

#line 5 "../src/ai.h2"
auto createAi() -> void;

#line 14 "../src/ai.h2"
auto printSnnModel(cpp2::impl::in<std::string> path) -> void;

#line 20 "../src/ai.h2"
class Ai: public Player {

    private: std::string modelPath; 
    private: snn::StraightforwardNeuralNetwork neuralNetwork; 
    private: snn::vector2D<float> inputs; 
    private: std::vector<cpp2::i16> moves; 

    public: Ai(cpp2::impl::in<Color> c, cpp2::impl::in<std::string> path);

#line 37 "../src/ai.h2"
    public: Ai(Ai const& that);

#line 45 "../src/ai.h2"
    private: [[nodiscard]] auto getGobanState(cpp2::impl::in<State<Stone>> state) const& -> std::vector<float>;

#line 70 "../src/ai.h2"
    private: [[nodiscard]] auto chooseBestMove(cpp2::impl::in<std::vector<float>> nn_output) const& -> Move;

#line 106 "../src/ai.h2"
    public: [[nodiscard]] auto getMove(Engine& engine) -> Move override;

#line 119 "../src/ai.h2"
    public: auto train() & -> void;

#line 144 "../src/ai.h2"
    public: auto save() & -> void;

#line 147 "../src/ai.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/ai.h2"

#line 5 "../src/ai.h2"
auto createAi() -> void{
    std::vector<snn::LayerModel> layers {snn::Input(1, 19, 19), 
                                            snn::FullyConnected(500, snn::activation::ReLU), 
                                            snn::FullyConnected(361)}; 
    auto optimizer {snn::StochasticGradientDescent(1e-5f, 0.0f)}; 
    auto neuralNetwork {snn::StraightforwardNeuralNetwork(cpp2::move(layers), cpp2::move(optimizer))}; 
    CPP2_UFCS(saveAs)(cpp2::move(neuralNetwork), "./snn_models/model_dnn_1_hidden_layer.snn");
}

#line 14 "../src/ai.h2"
auto printSnnModel(cpp2::impl::in<std::string> path) -> void{
    auto neuralNetwork {snn::StraightforwardNeuralNetwork::loadFrom(path)}; 
    std::cout << CPP2_UFCS(summary)(cpp2::move(neuralNetwork)) << std::endl;
    waitInput();
}

#line 27 "../src/ai.h2"
    Ai::Ai(cpp2::impl::in<Color> c, cpp2::impl::in<std::string> path)
        : Player{ c }
        , modelPath{ path }
        , neuralNetwork{ snn::StraightforwardNeuralNetwork::loadFrom(modelPath) }
        , inputs{  }
        , moves{  }{

#line 33 "../src/ai.h2"
        CPP2_UFCS(reserve)(inputs, 300);
        CPP2_UFCS(reserve)(moves, 300);
    }

#line 37 "../src/ai.h2"
    Ai::Ai(Ai const& that)
        : Player{ that }
        , modelPath{ that.modelPath }
        , neuralNetwork{ that.neuralNetwork }
        , inputs{ that.inputs }
        , moves{ that.moves }{

#line 42 "../src/ai.h2"
        modelPath = that.modelPath;
    }

#line 45 "../src/ai.h2"
    [[nodiscard]] auto Ai::getGobanState(cpp2::impl::in<State<Stone>> state) const& -> std::vector<float>{
        std::vector<float> vec {}; 
        CPP2_UFCS(reserve)(vec, 361);
{
cpp2::i8 col{0};

#line 49 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(col,CPP2_UFCS(ssize)(state)); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 53 "../src/ai.h2"
            for( ; cpp2::impl::cmp_less(row,CPP2_UFCS(ssize)(CPP2_ASSERT_IN_BOUNDS(state, col))); 
            ++row ) 
            {
                if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, col), row).color == color) {
                    CPP2_UFCS(push_back)(vec, 1.0);
                }
                else {if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, col), row).color == Color::None) {
                    CPP2_UFCS(push_back)(vec, 0.0);
                }
                else {
                    CPP2_UFCS(push_back)(vec, -1.0);
                }}
            }
}
#line 66 "../src/ai.h2"
        }
}
#line 67 "../src/ai.h2"
        return vec; 
    }

#line 70 "../src/ai.h2"
    [[nodiscard]] auto Ai::chooseBestMove(cpp2::impl::in<std::vector<float>> nn_output) const& -> Move{
        cpp2::i16 index {0}; 
        float max {0}; 
        cpp2::i8 max_col {0}; 
        cpp2::i8 max_row {0}; 
        std::vector<std::array<cpp2::i8,2>> goodMoves {}; 
{
cpp2::i8 col{0};

#line 77 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(col,19); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 81 "../src/ai.h2"
            for( ; cpp2::impl::cmp_less(row,19); 
            ++row ) 
            {
                if (cpp2::impl::cmp_greater(CPP2_ASSERT_IN_BOUNDS(nn_output, index),0.95)) {
                    std::array<cpp2::i8,2> a {col, row}; 
                    CPP2_UFCS(push_back)(goodMoves, cpp2::move(a));
                }else {if (cpp2::impl::cmp_less(max,CPP2_ASSERT_IN_BOUNDS(nn_output, index))) {
                    max = CPP2_ASSERT_IN_BOUNDS(nn_output, index);
                    max_col = col;
                    max_row = row;
                }}
                ++index;
            }
}
#line 94 "../src/ai.h2"
        }
}
#line 95 "../src/ai.h2"
        if (!(CPP2_UFCS(empty)(goodMoves))) {
            std::uniform_int_distribution<cpp2::i64> dist {0, CPP2_UFCS(ssize)(goodMoves) - 1}; 
            auto goodMove {CPP2_ASSERT_IN_BOUNDS(cpp2::move(goodMoves), cpp2::move(dist)(rng))}; 
            auto m {Move(color, CPP2_ASSERT_IN_BOUNDS_LITERAL(goodMove, 0), CPP2_ASSERT_IN_BOUNDS_LITERAL(cpp2::move(goodMove), 0))}; 
            return m; 
        }else {
            auto m {Move(color, cpp2::move(max_col), cpp2::move(max_row))}; 
            return m; 
        }
    }

#line 106 "../src/ai.h2"
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

#line 119 "../src/ai.h2"
    auto Ai::train() & -> void{
        float expectedValue {-1.0}; 
        if (hasWon) {// CPP2 workaround: Conditional operator not yet supported.
            expectedValue = -1;
        }
{
cpp2::i16 i{0};

#line 125 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(i,CPP2_UFCS(ssize)(inputs)); 
        ++i ) 
        {
            auto expected_output {CPP2_ASSERT_IN_BOUNDS(inputs, i)}; 
{
cpp2::i16 j{0};

#line 130 "../src/ai.h2"
            for( ; cpp2::impl::cmp_less(j,361); 
            ++j ) 
            {
                if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(inputs, i), j) != 0.0) {
                    CPP2_ASSERT_IN_BOUNDS(expected_output, j) = -1;
                }
            }
}
#line 137 "../src/ai.h2"
            CPP2_ASSERT_IN_BOUNDS(expected_output, CPP2_ASSERT_IN_BOUNDS(moves, i)) = expectedValue;
            CPP2_UFCS(trainOnce)(neuralNetwork, CPP2_ASSERT_IN_BOUNDS(inputs, i), cpp2::move(expected_output));
        }
}
#line 140 "../src/ai.h2"
        inputs = {  };
        moves = {  };
    }

#line 144 "../src/ai.h2"
    auto Ai::save() & -> void{
        CPP2_UFCS(saveAs)(neuralNetwork, modelPath);
    }
#endif

