
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

    public: Ai(cpp2::impl::in<Color> c, cpp2::impl::in<cpp2::i16> r, cpp2::impl::in<std::string> path);

#line 36 "../src/ai.h2"
    public: Ai(Ai const& that);

#line 45 "../src/ai.h2"
    public: [[nodiscard]] auto summary() const& -> std::string;

#line 49 "../src/ai.h2"
    private: template<cpp2::i8 Size> [[nodiscard]] auto getGobanState(cpp2::impl::in<State<Stone,Size>> state) const& -> std::vector<float>;

#line 75 "../src/ai.h2"
    private: template<cpp2::i8 Size> [[nodiscard]] auto chooseBestMove(cpp2::impl::in<std::vector<float>> nn_output) & -> Move;

#line 100 "../src/ai.h2"
    private: template<cpp2::i8 Size> [[nodiscard]] auto getMove(Engine<Size>& engine) & -> Move;

#line 113 "../src/ai.h2"
    public: [[nodiscard]] auto getMove(Engine<9>& engine) -> Move override;

#line 117 "../src/ai.h2"
    public: [[nodiscard]] auto getMove(Engine<19>& engine) -> Move override;

#line 121 "../src/ai.h2"
    public: auto train(cpp2::impl::in<cpp2::i16> gobanSize) & -> void;

#line 145 "../src/ai.h2"
    public: auto save() & -> void;

#line 149 "../src/ai.h2"
    public: auto processStartGame() -> void override;

#line 154 "../src/ai.h2"
    public: auto processEndGame() -> void override;

#line 161 "../src/ai.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/ai.h2"

#line 5 "../src/ai.h2"
auto createAi() -> void{
    std::vector<snn::LayerModel> layers {snn::Input(1, 9, 9), 
                                            snn::FullyConnected(100, snn::activation::ReLU), 
                                            snn::FullyConnected(100, snn::activation::ReLU), 
                                            snn::FullyConnected(100, snn::activation::ReLU), 
                                            snn::FullyConnected(81, snn::activation::tanh)}; 
    auto optimizer {snn::StochasticGradientDescent(1e-7f, 0.0f)}; 
    auto neuralNetwork {snn::StraightforwardNeuralNetwork(cpp2::move(layers), cpp2::move(optimizer))}; 
    CPP2_UFCS(saveAs)(cpp2::move(neuralNetwork), "./snn_models/9x9/model_v2.snn");
}

#line 25 "../src/ai.h2"
    Ai::Ai(cpp2::impl::in<Color> c, cpp2::impl::in<cpp2::i16> r, cpp2::impl::in<std::string> path)
        : Player{ c }
        , randomness{ r }
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
        , randomness{ that.randomness }
        , modelPath{ that.modelPath }
        , neuralNetwork{ that.neuralNetwork }
        , inputs{ that.inputs }
        , moves{ that.moves }{

#line 42 "../src/ai.h2"
        modelPath = that.modelPath;
    }

#line 45 "../src/ai.h2"
    [[nodiscard]] auto Ai::summary() const& -> std::string{
        return CPP2_UFCS(summary)(neuralNetwork); 
    }

#line 49 "../src/ai.h2"
    template<cpp2::i8 Size> [[nodiscard]] auto Ai::getGobanState(cpp2::impl::in<State<Stone,Size>> state) const& -> std::vector<float>{
        std::vector<float> vec {}; 
        auto size {CPP2_UFCS(ssize)(state) * CPP2_UFCS(ssize)(state)}; 
        CPP2_UFCS(reserve)(vec, cpp2::move(size));
{
cpp2::i8 col{0};

#line 54 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(col,CPP2_UFCS(ssize)(state)); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 58 "../src/ai.h2"
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
#line 71 "../src/ai.h2"
        }
}
#line 72 "../src/ai.h2"
        return vec; 
    }

#line 75 "../src/ai.h2"
    template<cpp2::i8 Size> [[nodiscard]] auto Ai::chooseBestMove(cpp2::impl::in<std::vector<float>> nn_output) & -> Move{
        cpp2::i16 index {0}; 
        std::vector<Stone> estimatedPositions {}; 
        auto numberOfPositions {Size * Size}; 
        CPP2_UFCS(reserve)(estimatedPositions, cpp2::move(numberOfPositions));
{
cpp2::i8 col{0};

#line 81 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(col,Size); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 85 "../src/ai.h2"
            for( ; cpp2::impl::cmp_less(row,Size); 
            ++row ) 
            {
                auto estimation {CPP2_ASSERT_IN_BOUNDS(nn_output, index)}; 
                auto stone {Stone(color, col, row, cpp2::move(estimation))}; 
                CPP2_UFCS(push_back)(estimatedPositions, cpp2::move(stone));
                ++index;
            }
}
#line 93 "../src/ai.h2"
        }
}
#line 94 "../src/ai.h2"
        std::ranges::sort(estimatedPositions, std::ranges::greater(), &Stone::estimation);
        std::uniform_int_distribution<cpp2::i64> dist {0, 4}; 
        auto s {CPP2_ASSERT_IN_BOUNDS(cpp2::move(estimatedPositions), cpp2::move(dist)(rng))}; 
        return Move(cpp2::move(s)); 
    }

#line 100 "../src/ai.h2"
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

#line 113 "../src/ai.h2"
    [[nodiscard]] auto Ai::getMove(Engine<9>& engine) -> Move{
        return getMove<9>(engine); 
    }

#line 117 "../src/ai.h2"
    [[nodiscard]] auto Ai::getMove(Engine<19>& engine) -> Move{
        return getMove<19>(engine); 
    }

#line 121 "../src/ai.h2"
    auto Ai::train(cpp2::impl::in<cpp2::i16> gobanSize) & -> void{
        auto size {gobanSize * gobanSize}; 
        float expectedValue {-1.0}; 
        if (hasWon) {// CPP2 workaround: Conditional operator not yet supported.
            expectedValue = 1.0;
        }
{
cpp2::i16 i{0};

#line 128 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(i,CPP2_UFCS(ssize)(inputs)); 
        ++i ) 
        {
            auto expected_output {std::vector<float>(size, 0)}; 
{
cpp2::i16 j{0};

#line 133 "../src/ai.h2"
            for( ; cpp2::impl::cmp_less(j,size); 
            ++j ) 
            {
                if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(inputs, i), j) != 0.0) {
                    CPP2_ASSERT_IN_BOUNDS(expected_output, j) = 0;
                }
            }
}
#line 140 "../src/ai.h2"
            CPP2_ASSERT_IN_BOUNDS(expected_output, CPP2_ASSERT_IN_BOUNDS(moves, i)) = expectedValue;
            CPP2_UFCS(trainOnce)(neuralNetwork, CPP2_ASSERT_IN_BOUNDS(inputs, i), cpp2::move(expected_output));
        }
}
#line 143 "../src/ai.h2"
    }

#line 145 "../src/ai.h2"
    auto Ai::save() & -> void{
        CPP2_UFCS(saveAs)(neuralNetwork, modelPath);
    }

#line 149 "../src/ai.h2"
    auto Ai::processStartGame() -> void{
        CPP2_UFCS(clear)(inputs);
        CPP2_UFCS(clear)(moves);
    }

#line 154 "../src/ai.h2"
    auto Ai::processEndGame() -> void{
        std::string state {"lost"}; 
        if (hasWon) {// CPP2 workaround: Conditional operator not yet supported.
            state = "won";
        }
        setNextMessage("AI " + cpp2::move(state) + ".");
    }
#endif

