
#ifndef AI_H_CPP2
#define AI_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/ai.h2"

#line 16 "../src/ai.h2"
class Ai;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/ai.h2"
#include "player.h"
#include "io.h"
#include <snn/neural_network/StraightforwardNeuralNetwork.hpp>

#line 5 "../src/ai.h2"
auto createAi() -> void;

#line 16 "../src/ai.h2"
class Ai: public Player {

    public: cpp2::i16 randomness; // Randomly select a move from the N best moves.

    private: std::string modelPath; 
    private: snn::StraightforwardNeuralNetwork neuralNetwork; 
    private: snn::vector2D<float> inputs; 
    private: std::vector<cpp2::i16> moves; 
    private: std::deque<int> lastGameWon; 
    private: size_t const numberOfGames {1000}; // TO calculate winrate.
    private: size_t sumOfLastGameWon; 

    public: Ai(cpp2::impl::in<Color> c, cpp2::impl::in<cpp2::i16> r, cpp2::impl::in<std::string> path);

#line 41 "../src/ai.h2"
    public: Ai(Ai const& that);

#line 52 "../src/ai.h2"
    public: [[nodiscard]] auto summary() const& -> std::string;

#line 56 "../src/ai.h2"
    private: template<cpp2::i8 Size> [[nodiscard]] auto getGobanState(cpp2::impl::in<State<Stone,Size>> state) const& -> std::vector<float>;

#line 82 "../src/ai.h2"
    private: template<cpp2::i8 Size> [[nodiscard]] auto chooseBestMove(cpp2::impl::in<std::vector<float>> nn_output) & -> Move;

#line 107 "../src/ai.h2"
    private: template<cpp2::i8 Size> [[nodiscard]] auto getMove(Engine<Size>& engine) & -> Move;

#line 120 "../src/ai.h2"
    public: [[nodiscard]] auto getMove(Engine<9>& engine) -> Move override;

#line 124 "../src/ai.h2"
    public: [[nodiscard]] auto getMove(Engine<19>& engine) -> Move override;

#line 128 "../src/ai.h2"
    public: auto train(cpp2::impl::in<cpp2::i16> gobanSize) & -> void;

#line 155 "../src/ai.h2"
    public: auto save() & -> void;

#line 159 "../src/ai.h2"
    public: auto processStartGame() -> void override;

#line 164 "../src/ai.h2"
    public: auto processEndGame() -> void override;

#line 183 "../src/ai.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/ai.h2"

#line 5 "../src/ai.h2"
auto createAi() -> void{
    std::vector<snn::LayerModel> layers {snn::Input(1, 9, 9), 
                                            snn::FullyConnected(200, snn::activation::ReLU), 
                                            snn::FullyConnected(200, snn::activation::ReLU), 
                                            snn::FullyConnected(200, snn::activation::ReLU), 
                                            snn::FullyConnected(81, snn::activation::tanh)}; 
    auto optimizer {snn::StochasticGradientDescent(3e-5f, 0.7f)}; 
    auto neuralNetwork {snn::StraightforwardNeuralNetwork(cpp2::move(layers), cpp2::move(optimizer))}; 
    CPP2_UFCS(saveAs)(cpp2::move(neuralNetwork), "./snn_models/9x9/model_v8.snn");
}

#line 28 "../src/ai.h2"
    Ai::Ai(cpp2::impl::in<Color> c, cpp2::impl::in<cpp2::i16> r, cpp2::impl::in<std::string> path)
        : Player{ c }
        , randomness{ r }
        , modelPath{ path }
        , neuralNetwork{ snn::StraightforwardNeuralNetwork::loadFrom(modelPath) }
        , inputs{  }
        , moves{  }
        , lastGameWon{  }
        , sumOfLastGameWon{ 0 }{

#line 37 "../src/ai.h2"
        CPP2_UFCS(reserve)(inputs, 300);
        CPP2_UFCS(reserve)(moves, 300);
    }

#line 41 "../src/ai.h2"
    Ai::Ai(Ai const& that)
        : Player{ that }
        , randomness{ that.randomness }
        , modelPath{ that.modelPath }
        , neuralNetwork{ that.neuralNetwork }
        , inputs{ that.inputs }
        , moves{ that.moves }
        , lastGameWon{ that.lastGameWon }
        , numberOfGames{ that.numberOfGames }
        , sumOfLastGameWon{ that.sumOfLastGameWon }{

#line 47 "../src/ai.h2"
        modelPath = that.modelPath;
        lastGameWon = that.lastGameWon;
        sumOfLastGameWon = that.sumOfLastGameWon;
    }

#line 52 "../src/ai.h2"
    [[nodiscard]] auto Ai::summary() const& -> std::string{
        return CPP2_UFCS(summary)(neuralNetwork); 
    }

#line 56 "../src/ai.h2"
    template<cpp2::i8 Size> [[nodiscard]] auto Ai::getGobanState(cpp2::impl::in<State<Stone,Size>> state) const& -> std::vector<float>{
        std::vector<float> vec {}; 
        auto size {CPP2_UFCS(ssize)(state) * CPP2_UFCS(ssize)(state)}; 
        CPP2_UFCS(reserve)(vec, cpp2::move(size));
{
cpp2::i8 col{0};

#line 61 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(col,CPP2_UFCS(ssize)(state)); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 65 "../src/ai.h2"
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
#line 78 "../src/ai.h2"
        }
}
#line 79 "../src/ai.h2"
        return vec; 
    }

#line 82 "../src/ai.h2"
    template<cpp2::i8 Size> [[nodiscard]] auto Ai::chooseBestMove(cpp2::impl::in<std::vector<float>> nn_output) & -> Move{
        cpp2::i16 index {0}; 
        std::vector<Stone> estimatedPositions {}; 
        auto numberOfPositions {Size * Size}; 
        CPP2_UFCS(reserve)(estimatedPositions, cpp2::move(numberOfPositions));
{
cpp2::i8 col{0};

#line 88 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(col,Size); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 92 "../src/ai.h2"
            for( ; cpp2::impl::cmp_less(row,Size); 
            ++row ) 
            {
                auto estimation {CPP2_ASSERT_IN_BOUNDS(nn_output, index)}; 
                auto stone {Stone(color, col, row, cpp2::move(estimation))}; 
                CPP2_UFCS(push_back)(estimatedPositions, cpp2::move(stone));
                ++index;
            }
}
#line 100 "../src/ai.h2"
        }
}
#line 101 "../src/ai.h2"
        std::ranges::sort(estimatedPositions, std::ranges::greater(), &Stone::estimation);
        std::uniform_int_distribution<cpp2::i64> dist {0, randomness - 1}; 
        auto s {CPP2_ASSERT_IN_BOUNDS_LITERAL(cpp2::move(estimatedPositions), 0)}; 
        return Move(cpp2::move(s)); 
    }

#line 107 "../src/ai.h2"
    template<cpp2::i8 Size> [[nodiscard]] auto Ai::getMove(Engine<Size>& engine) & -> Move{
        auto input {getGobanState<Size>(engine.goban.state)}; 
        auto output {CPP2_UFCS(computeOutput)(neuralNetwork, input)}; 
        auto m {chooseBestMove<Size>(cpp2::move(output))}; 
        CPP2_UFCS(closerValidMove)(engine, m);
        auto moveIndex {CPP2_UFCS_TEMPLATE(getIndex<Size>)(m.stone)}; 
        if (cpp2::impl::cmp_greater_eq(moveIndex,0)) {
            CPP2_UFCS(push_back)(inputs, cpp2::move(input));
            CPP2_UFCS(push_back)(moves, cpp2::move(moveIndex));
        }
        return m; 
    }

#line 120 "../src/ai.h2"
    [[nodiscard]] auto Ai::getMove(Engine<9>& engine) -> Move{
        return getMove<9>(engine); 
    }

#line 124 "../src/ai.h2"
    [[nodiscard]] auto Ai::getMove(Engine<19>& engine) -> Move{
        return getMove<19>(engine); 
    }

#line 128 "../src/ai.h2"
    auto Ai::train(cpp2::impl::in<cpp2::i16> gobanSize) & -> void{
        if (cpp2::impl::cmp_greater(CPP2_UFCS(ssize)(inputs),120)) {// Only train on "short" game.
            return ; 
        }
        auto size {gobanSize * gobanSize}; 
        float expectedValue {-1.0f}; 
        if (hasWon) {// CPP2 workaround: Conditional operator not yet supported.
            expectedValue = 1.0f;
        }
{
cpp2::i16 i{0};

#line 138 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(i,CPP2_UFCS(ssize)(inputs)); 
        ++i ) 
        {
            auto expected_output {std::vector<float>(size, NAN)}; 
{
cpp2::i16 j{0};

#line 143 "../src/ai.h2"
            for( ; cpp2::impl::cmp_less(j,size); 
            ++j ) 
            {
                if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(inputs, i), j) != 0.0) {
                    CPP2_ASSERT_IN_BOUNDS(expected_output, j) = 0;
                }
            }
}
#line 150 "../src/ai.h2"
            CPP2_ASSERT_IN_BOUNDS(expected_output, CPP2_ASSERT_IN_BOUNDS(moves, i)) = expectedValue;
            CPP2_UFCS(trainOnce)(neuralNetwork, CPP2_ASSERT_IN_BOUNDS(inputs, i), cpp2::move(expected_output));
        }
}
#line 153 "../src/ai.h2"
    }

#line 155 "../src/ai.h2"
    auto Ai::save() & -> void{
        CPP2_UFCS(saveAs)(neuralNetwork, modelPath);
    }

#line 159 "../src/ai.h2"
    auto Ai::processStartGame() -> void{
        CPP2_UFCS(clear)(inputs);
        CPP2_UFCS(clear)(moves);
    }

#line 164 "../src/ai.h2"
    auto Ai::processEndGame() -> void{
        if (hasWon) {// CPP2 workaround: Conditional operator not yet supported.
            CPP2_UFCS(push_back)(lastGameWon, 1);
            sumOfLastGameWon += 1;
        }else {
            CPP2_UFCS(push_back)(lastGameWon, 0);
        }
        if ((cpp2::impl::cmp_greater(CPP2_UFCS(size)(lastGameWon),numberOfGames))) {
            sumOfLastGameWon -= CPP2_UFCS(front)(lastGameWon);
            CPP2_UFCS(pop_front)(lastGameWon);
        }
        if (cpp2::impl::cmp_greater(CPP2_UFCS(ssize)(lastGameWon),100)) {
            float winrate {sumOfLastGameWon / CPP2_ASSERT_NOT_ZERO(CPP2_TYPEOF(sumOfLastGameWon),(float)(CPP2_UFCS(size)(lastGameWon))) * 100.0f}; 
            std::string str {std::to_string(cpp2::move(winrate))}; 
            setNextMessage("AI winrate: " + cpp2::move(str) + " %");
        }else {
            setNextMessage("AI winrate: ...");
        }
    }
#endif

