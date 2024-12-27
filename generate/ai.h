
#ifndef AI_H_CPP2
#define AI_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/ai.h2"

#line 15 "../src/ai.h2"
class Ai;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/ai.h2"
#include "player.h"
#include "io.h"
#include <snn/neural_network/StraightforwardNeuralNetwork.hpp>

#line 5 "../src/ai.h2"
auto createAi() -> void;

#line 15 "../src/ai.h2"
class Ai: public Player {

    private: std::string modelPath; 
    private: snn::StraightforwardNeuralNetwork neuralNetwork; 
    private: snn::vector2D<float> inputs; 
    private: std::vector<cpp2::i16> moves; 

    private: cpp2::i32 numberOfGoodMoves {0}; 
    private: cpp2::i32 numberOfAverageMoves {0}; 
    private: cpp2::i32 numberOfBadMoves {0}; 

    public: Ai(cpp2::impl::in<Color> c, cpp2::impl::in<std::string> path);

#line 36 "../src/ai.h2"
    public: Ai(Ai const& that);

#line 47 "../src/ai.h2"
    public: [[nodiscard]] auto summary() const& -> std::string;

#line 51 "../src/ai.h2"
    private: [[nodiscard]] auto getGobanState(cpp2::impl::in<State<Stone>> state) const& -> std::vector<float>;

#line 76 "../src/ai.h2"
    private: [[nodiscard]] auto chooseBestMove(cpp2::impl::in<std::vector<float>> nn_output) & -> Move;

#line 124 "../src/ai.h2"
    public: [[nodiscard]] auto getMove(Engine<19>& engine) -> Move override;

#line 140 "../src/ai.h2"
    public: auto train() & -> void;

#line 165 "../src/ai.h2"
    public: auto save() & -> void;

#line 169 "../src/ai.h2"
    public: auto processEndGame() -> void override;

#line 186 "../src/ai.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/ai.h2"

#line 5 "../src/ai.h2"
auto createAi() -> void{
    std::vector<snn::LayerModel> layers {snn::Input(1, 19, 19), 
                                            snn::FullyConnected(200, snn::activation::ReLU), 
                                            snn::FullyConnected(200, snn::activation::ReLU), 
                                            snn::FullyConnected(361, snn::activation::tanh)}; 
    auto optimizer {snn::StochasticGradientDescent(1e-4f, 0.9f)}; 
    auto neuralNetwork {snn::StraightforwardNeuralNetwork(cpp2::move(layers), cpp2::move(optimizer))}; 
    CPP2_UFCS(saveAs)(cpp2::move(neuralNetwork), "./snn_models/model_big_v2.snn");
}

#line 26 "../src/ai.h2"
    Ai::Ai(cpp2::impl::in<Color> c, cpp2::impl::in<std::string> path)
        : Player{ c }
        , modelPath{ path }
        , neuralNetwork{ snn::StraightforwardNeuralNetwork::loadFrom(modelPath) }
        , inputs{  }
        , moves{  }{

#line 32 "../src/ai.h2"
        CPP2_UFCS(reserve)(inputs, 300);
        CPP2_UFCS(reserve)(moves, 300);
    }

#line 36 "../src/ai.h2"
    Ai::Ai(Ai const& that)
        : Player{ that }
        , modelPath{ that.modelPath }
        , neuralNetwork{ that.neuralNetwork }
        , inputs{ that.inputs }
        , moves{ that.moves }
        , numberOfGoodMoves{ that.numberOfGoodMoves }
        , numberOfAverageMoves{ that.numberOfAverageMoves }
        , numberOfBadMoves{ that.numberOfBadMoves }{

#line 41 "../src/ai.h2"
        modelPath = that.modelPath;
        numberOfGoodMoves = that.numberOfGoodMoves;
        numberOfAverageMoves = that.numberOfAverageMoves;
        numberOfBadMoves = that.numberOfBadMoves;
    }

#line 47 "../src/ai.h2"
    [[nodiscard]] auto Ai::summary() const& -> std::string{
        return CPP2_UFCS(summary)(neuralNetwork); 
    }

#line 51 "../src/ai.h2"
    [[nodiscard]] auto Ai::getGobanState(cpp2::impl::in<State<Stone>> state) const& -> std::vector<float>{
        std::vector<float> vec {}; 
        CPP2_UFCS(reserve)(vec, 361);
{
cpp2::i8 col{0};

#line 55 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(col,CPP2_UFCS(ssize)(state)); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 59 "../src/ai.h2"
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
#line 72 "../src/ai.h2"
        }
}
#line 73 "../src/ai.h2"
        return vec; 
    }

#line 76 "../src/ai.h2"
    [[nodiscard]] auto Ai::chooseBestMove(cpp2::impl::in<std::vector<float>> nn_output) & -> Move{
        cpp2::i16 index {0}; 
        std::vector<std::array<cpp2::i8,2>> goodMoves {}; 
        std::vector<std::array<cpp2::i8,2>> averageMoves {}; 
        std::vector<std::array<cpp2::i8,2>> badMoves {}; 
{
cpp2::i8 col{0};

#line 82 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(col,19); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 86 "../src/ai.h2"
            for( ; cpp2::impl::cmp_less(row,19); 
            ++row ) 
            {
                std::array<cpp2::i8,2> a {col, row}; 
                if (cpp2::impl::cmp_greater(CPP2_ASSERT_IN_BOUNDS(nn_output, index),0.5f)) {
                    CPP2_UFCS(push_back)(goodMoves, cpp2::move(a));
                }else {if (CPP2_UFCS(empty)(goodMoves) && cpp2::impl::cmp_greater(CPP2_ASSERT_IN_BOUNDS(nn_output, index),0.0f)) {
                    CPP2_UFCS(push_back)(averageMoves, cpp2::move(a));
                }else {if (CPP2_UFCS(empty)(goodMoves) && CPP2_UFCS(empty)(averageMoves)) {
                    CPP2_UFCS(push_back)(badMoves, cpp2::move(a));
                }}}
                ++index;
            }
}
#line 99 "../src/ai.h2"
        }
}
#line 100 "../src/ai.h2"
        if (!(CPP2_UFCS(empty)(goodMoves))) {
            ++numberOfGoodMoves;
            std::uniform_int_distribution<cpp2::i64> dist {0, CPP2_UFCS(ssize)(goodMoves) - 1}; 
            auto goodMove {CPP2_ASSERT_IN_BOUNDS(cpp2::move(goodMoves), cpp2::move(dist)(rng))}; 
            auto m {Move(color, CPP2_ASSERT_IN_BOUNDS_LITERAL(goodMove, 0), CPP2_ASSERT_IN_BOUNDS_LITERAL(cpp2::move(goodMove), 1))}; 
            return m; 
        }
        if (!(CPP2_UFCS(empty)(averageMoves))) {
            ++numberOfAverageMoves;
            std::uniform_int_distribution<cpp2::i64> dist {0, CPP2_UFCS(ssize)(averageMoves) - 1}; 
            auto averageMove {CPP2_ASSERT_IN_BOUNDS(cpp2::move(averageMoves), cpp2::move(dist)(rng))}; 
            auto m {Move(color, CPP2_ASSERT_IN_BOUNDS_LITERAL(averageMove, 0), CPP2_ASSERT_IN_BOUNDS_LITERAL(cpp2::move(averageMove), 1))}; 
            return m; 
        }
        if (!(CPP2_UFCS(empty)(badMoves))) {
            ++numberOfBadMoves;
            std::uniform_int_distribution<cpp2::i64> dist {0, CPP2_UFCS(ssize)(badMoves) - 1}; 
            auto badMove {CPP2_ASSERT_IN_BOUNDS(cpp2::move(badMoves), cpp2::move(dist)(rng))}; 
            auto m {Move(color, CPP2_ASSERT_IN_BOUNDS_LITERAL(badMove, 0), CPP2_ASSERT_IN_BOUNDS_LITERAL(cpp2::move(badMove), 1))}; 
            return m; 
        }
        return pass(color); 
    }

#line 124 "../src/ai.h2"
    [[nodiscard]] auto Ai::getMove(Engine<19>& engine) -> Move{
        auto input {getGobanState(engine.goban.state)}; 
        auto output {CPP2_UFCS(computeOutput)(neuralNetwork, input)}; 
        auto m {chooseBestMove(cpp2::move(output))}; 
        if (m.pass) {
            return m; 
        }
        CPP2_UFCS(closerValidMove)(engine, m);
        auto moveIndex {CPP2_UFCS(getIndex)(m.stone, size)}; 
        if (cpp2::impl::cmp_greater_eq(moveIndex,0)) {
            CPP2_UFCS(push_back)(inputs, cpp2::move(input));
            CPP2_UFCS(push_back)(moves, cpp2::move(moveIndex));
        }
        return m; 
    }

#line 140 "../src/ai.h2"
    auto Ai::train() & -> void{
        float expectedValue {-1.0}; 
        if (hasWon) {// CPP2 workaround: Conditional operator not yet supported.
            expectedValue = 1.0;
        }
{
cpp2::i16 i{0};

#line 146 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(i,CPP2_UFCS(ssize)(inputs)); 
        ++i ) 
        {
            auto expected_output {std::vector<float>(361, 0)}; 
{
cpp2::i16 j{0};

#line 151 "../src/ai.h2"
            for( ; cpp2::impl::cmp_less(j,361); 
            ++j ) 
            {
                if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(inputs, i), j) != 0.0) {
                    CPP2_ASSERT_IN_BOUNDS(expected_output, j) = 0;
                }
            }
}
#line 158 "../src/ai.h2"
            CPP2_ASSERT_IN_BOUNDS(expected_output, CPP2_ASSERT_IN_BOUNDS(moves, i)) = expectedValue;
            CPP2_UFCS(trainOnce)(neuralNetwork, CPP2_ASSERT_IN_BOUNDS(inputs, i), cpp2::move(expected_output));
        }
}
#line 161 "../src/ai.h2"
        inputs = {  };
        moves = {  };
    }

#line 165 "../src/ai.h2"
    auto Ai::save() & -> void{
        CPP2_UFCS(saveAs)(neuralNetwork, modelPath);
    }

#line 169 "../src/ai.h2"
    auto Ai::processEndGame() -> void{
        std::string state {"lost"}; 
        if (hasWon) {// CPP2 workaround: Conditional operator not yet supported.
            state = "won";
        }
        if (color == Color::Black) {
            setNextMessage("Black " + cpp2::move(state) + ":");
        }else {
            setNextMessage("White " + cpp2::move(state) + ":");
        }
        setNextMessage("  " + cpp2::impl::as_<std::string>(numberOfGoodMoves) + " moves were considered good.");
        setNextMessage("  " + cpp2::impl::as_<std::string>(numberOfAverageMoves) + " moves were considered average.");
        setNextMessage("  " + cpp2::impl::as_<std::string>(numberOfBadMoves) + " moves were considered bad.");
        numberOfGoodMoves = 0;
        numberOfAverageMoves = 0;
        numberOfBadMoves = 0;
    }
#endif

