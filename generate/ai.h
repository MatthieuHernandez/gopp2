
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

    public: cpp2::i16 randomness; // Randomly select a move from the N best moves.

    private: std::string modelPath; 
    private: snn::StraightforwardNeuralNetwork neuralNetwork; 
    private: std::shared_ptr<snn::internal::StochasticGradientDescent> optimizer; 
    private: snn::vector2D<float> inputs; 
    private: std::vector<cpp2::i16> moves; 
    private: std::deque<int> lastGameWon; 
    private: size_t const numberOfGames {1000}; // To calculate winrate.
    private: size_t sumOfLastGameWon {0}; 
    private: float learningRateUpdateRatio {0.5f}; 
    private: float previousWinrate {0.0f}; 
    private: bool isBetter {false}; 

    public: Ai(cpp2::impl::in<Color> c, cpp2::impl::in<cpp2::i16> r, cpp2::impl::in<std::string> path);

#line 45 "../src/ai.h2"
    public: Ai(Ai const& that);

#line 60 "../src/ai.h2"
    public: [[nodiscard]] auto summary() const& -> std::string;

#line 64 "../src/ai.h2"
    private: template<cpp2::i8 Size> [[nodiscard]] auto getGobanState(cpp2::impl::in<State<Stone,Size>> state) const& -> std::vector<float>;

#line 90 "../src/ai.h2"
    private: template<cpp2::i8 Size> [[nodiscard]] auto chooseBestMove(cpp2::impl::in<std::vector<float>> nn_output) & -> Move;

#line 115 "../src/ai.h2"
    private: template<cpp2::i8 Size> [[nodiscard]] auto getMove(Engine<Size>& engine) & -> Move;

#line 128 "../src/ai.h2"
    public: [[nodiscard]] auto getMove(Engine<9>& engine) -> Move override;

#line 132 "../src/ai.h2"
    public: [[nodiscard]] auto getMove(Engine<19>& engine) -> Move override;

#line 136 "../src/ai.h2"
    public: auto train(cpp2::impl::in<cpp2::i16> gobanSize) & -> void;

#line 171 "../src/ai.h2"
    public: auto saveIfBetter() & -> void;

#line 178 "../src/ai.h2"
    private: [[nodiscard]] auto calculateWinrate() const& -> float;

#line 182 "../src/ai.h2"
    public: auto processStartGame() -> void override;

#line 194 "../src/ai.h2"
    public: auto processEndGame() -> void override;

#line 216 "../src/ai.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/ai.h2"

#line 5 "../src/ai.h2"
auto createAi() -> void{
    std::vector<snn::LayerModel> layers {snn::Input(1, 9, 9), 
                                            snn::FullyConnected(500, snn::activation::ReLU), 
                                            snn::FullyConnected(500, snn::activation::ReLU), 
                                            snn::FullyConnected(81, snn::activation::tanh)}; 
    auto optimizer {snn::StochasticGradientDescent(1e-5f, 0.0f)}; 
    auto neuralNetwork {snn::StraightforwardNeuralNetwork(cpp2::move(layers), cpp2::move(optimizer))}; 
    CPP2_UFCS(saveAs)(cpp2::move(neuralNetwork), "./snn_models/9x9/model_v9.snn");
}

#line 31 "../src/ai.h2"
    Ai::Ai(cpp2::impl::in<Color> c, cpp2::impl::in<cpp2::i16> r, cpp2::impl::in<std::string> path)
        : Player{ c }
        , randomness{ r }
        , modelPath{ path }
        , neuralNetwork{ snn::StraightforwardNeuralNetwork::loadFrom(modelPath) }
        , optimizer{ std::static_pointer_cast<snn::internal::StochasticGradientDescent>(neuralNetwork.optimizer) }
        , inputs{  }
        , moves{  }
        , lastGameWon{  }{

#line 40 "../src/ai.h2"
        CPP2_UFCS(reserve)(inputs, 300);
        CPP2_UFCS(reserve)(moves, 300);
        (*cpp2::impl::assert_not_null(optimizer)).learningRate = 1e-8f;
    }

#line 45 "../src/ai.h2"
    Ai::Ai(Ai const& that)
        : Player{ that }
        , randomness{ that.randomness }
        , modelPath{ that.modelPath }
        , neuralNetwork{ that.neuralNetwork }
        , optimizer{ that.optimizer }
        , inputs{ that.inputs }
        , moves{ that.moves }
        , lastGameWon{ that.lastGameWon }
        , numberOfGames{ that.numberOfGames }
        , sumOfLastGameWon{ that.sumOfLastGameWon }
        , learningRateUpdateRatio{ that.learningRateUpdateRatio }
        , previousWinrate{ that.previousWinrate }
        , isBetter{ that.isBetter }{

#line 52 "../src/ai.h2"
        modelPath = that.modelPath;
        lastGameWon = that.lastGameWon;
        sumOfLastGameWon = that.sumOfLastGameWon;
        learningRateUpdateRatio = that.learningRateUpdateRatio;
        previousWinrate = that.previousWinrate;
        isBetter = that.isBetter;
    }

#line 60 "../src/ai.h2"
    [[nodiscard]] auto Ai::summary() const& -> std::string{
        return CPP2_UFCS(summary)(neuralNetwork); 
    }

#line 64 "../src/ai.h2"
    template<cpp2::i8 Size> [[nodiscard]] auto Ai::getGobanState(cpp2::impl::in<State<Stone,Size>> state) const& -> std::vector<float>{
        std::vector<float> vec {}; 
        auto size {CPP2_UFCS(ssize)(state) * CPP2_UFCS(ssize)(state)}; 
        CPP2_UFCS(reserve)(vec, cpp2::move(size));
{
cpp2::i8 col{0};

#line 69 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(col,CPP2_UFCS(ssize)(state)); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 73 "../src/ai.h2"
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
#line 86 "../src/ai.h2"
        }
}
#line 87 "../src/ai.h2"
        return vec; 
    }

#line 90 "../src/ai.h2"
    template<cpp2::i8 Size> [[nodiscard]] auto Ai::chooseBestMove(cpp2::impl::in<std::vector<float>> nn_output) & -> Move{
        cpp2::i16 index {0}; 
        std::vector<Stone> estimatedPositions {}; 
        auto numberOfPositions {Size * Size}; 
        CPP2_UFCS(reserve)(estimatedPositions, cpp2::move(numberOfPositions));
{
cpp2::i8 col{0};

#line 96 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(col,Size); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 100 "../src/ai.h2"
            for( ; cpp2::impl::cmp_less(row,Size); 
            ++row ) 
            {
                auto estimation {CPP2_ASSERT_IN_BOUNDS(nn_output, index)}; 
                auto stone {Stone(color, col, row, cpp2::move(estimation))}; 
                CPP2_UFCS(push_back)(estimatedPositions, cpp2::move(stone));
                ++index;
            }
}
#line 108 "../src/ai.h2"
        }
}
#line 109 "../src/ai.h2"
        std::ranges::sort(estimatedPositions, std::ranges::greater(), &Stone::estimation);
        std::uniform_int_distribution<cpp2::i64> dist {0, randomness - 1}; 
        auto s {CPP2_ASSERT_IN_BOUNDS_LITERAL(cpp2::move(estimatedPositions), 0)}; 
        return Move(cpp2::move(s)); 
    }

#line 115 "../src/ai.h2"
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

#line 128 "../src/ai.h2"
    [[nodiscard]] auto Ai::getMove(Engine<9>& engine) -> Move{
        return getMove<9>(engine); 
    }

#line 132 "../src/ai.h2"
    [[nodiscard]] auto Ai::getMove(Engine<19>& engine) -> Move{
        return getMove<19>(engine); 
    }

#line 136 "../src/ai.h2"
    auto Ai::train(cpp2::impl::in<cpp2::i16> gobanSize) & -> void{
        if (cpp2::impl::cmp_greater(CPP2_UFCS(ssize)(inputs),75)) {// Only train on "short" game.
            return ; 
        }
        if (randomness == 1 && cpp2::impl::cmp_greater(CPP2_UFCS(ssize)(lastGameWon),100)) {// Only process on "accurate" game.
            auto winrate {calculateWinrate()}; 
            if (!(hasWon)) {
                (*cpp2::impl::assert_not_null(optimizer)).learningRate = 1e-7f * cpp2::move(winrate);
            }else {
                (*cpp2::impl::assert_not_null(optimizer)).learningRate = 1e-7f * (1 - cpp2::move(winrate));
            }
        }
        auto size {gobanSize * gobanSize}; 
        float expectedValue {-1.0f}; 
        if (hasWon) {// CPP2 workaround: Conditional operator not yet supported.
            expectedValue = 1.0f;
        }
{
cpp2::i16 i{0};

#line 154 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(i,CPP2_UFCS(ssize)(inputs)); 
        ++i ) 
        {
            auto expected_output {std::vector<float>(size, NAN)}; 
{
cpp2::i16 j{0};

#line 159 "../src/ai.h2"
            for( ; cpp2::impl::cmp_less(j,size); 
            ++j ) 
            {
                if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(inputs, i), j) != 0.0) {
                    CPP2_ASSERT_IN_BOUNDS(expected_output, j) = 0;
                }
            }
}
#line 166 "../src/ai.h2"
            CPP2_ASSERT_IN_BOUNDS(expected_output, CPP2_ASSERT_IN_BOUNDS(moves, i)) = expectedValue;
            CPP2_UFCS(trainOnce)(neuralNetwork, CPP2_ASSERT_IN_BOUNDS(inputs, i), cpp2::move(expected_output));
        }
}
#line 169 "../src/ai.h2"
    }

#line 171 "../src/ai.h2"
    auto Ai::saveIfBetter() & -> void{
        if (isBetter) {
            CPP2_UFCS(saveAs)(neuralNetwork, modelPath);
            isBetter = false;
        }
    }

#line 178 "../src/ai.h2"
    [[nodiscard]] auto Ai::calculateWinrate() const& -> float{
        return sumOfLastGameWon / CPP2_ASSERT_NOT_ZERO(CPP2_TYPEOF(sumOfLastGameWon),(float)(CPP2_UFCS(size)(lastGameWon))); 
    }

#line 182 "../src/ai.h2"
    auto Ai::processStartGame() -> void{
        CPP2_UFCS(clear)(inputs);
        CPP2_UFCS(clear)(moves);
        auto currentWinRate {calculateWinrate()}; 
        if (CPP2_UFCS(ssize)(lastGameWon) == numberOfGames 
        && cpp2::impl::cmp_greater(currentWinRate,previousWinrate)) {
            previousWinrate = cpp2::move(currentWinRate);
            isBetter = true;

        }
    }

#line 194 "../src/ai.h2"
    auto Ai::processEndGame() -> void{
        if (randomness == 1) {// Only process on "accurate" game.
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
        }
        if (cpp2::impl::cmp_greater(CPP2_UFCS(ssize)(lastGameWon),100)) {
            setNextMessage("AI winrate: " + std::to_string(calculateWinrate() * 100.0f) + " %");
        }else {
            setNextMessage("AI winrate: ...");
        }
        std::ostringstream oss {}; 
        oss << "AI learning rate: " << std::scientific << std::setprecision(2) << (*cpp2::impl::assert_not_null(optimizer)).learningRate;
        setNextMessage(CPP2_UFCS(str)(cpp2::move(oss)));
    }
#endif

