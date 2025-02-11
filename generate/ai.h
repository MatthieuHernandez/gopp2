
#ifndef AI_H_CPP2
#define AI_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/ai.h2"

#line 26 "../src/ai.h2"
class Ai;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/ai.h2"
#include "player.h"
#include "io.h"
#include <snn/neural_network/StraightforwardNeuralNetwork.hpp>

#line 5 "../src/ai.h2"
auto createAi() -> void;

#line 26 "../src/ai.h2"
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
    private: float defaultLearningRate {1e-6f}; 
    private: float previousWinrate {0.0f}; 
    private: bool isBetter {false}; 

    public: Ai(cpp2::impl::in<Color> c, cpp2::impl::in<cpp2::i16> r, cpp2::impl::in<std::string> path);

#line 55 "../src/ai.h2"
    public: Ai(Ai const& that);

#line 70 "../src/ai.h2"
    public: [[nodiscard]] auto summary() const& -> std::string;

#line 74 "../src/ai.h2"
    private: template<cpp2::i8 Size> [[nodiscard]] auto getGobanState(cpp2::impl::in<State<Stone,Size>> state) const& -> std::vector<float>;

#line 100 "../src/ai.h2"
    private: template<cpp2::i8 Size> [[nodiscard]] auto chooseBestMove(cpp2::impl::in<std::vector<float>> nn_output, Engine<Size>& engine) & -> Move;

#line 146 "../src/ai.h2"
    private: template<cpp2::i8 Size> [[nodiscard]] auto getMove(Engine<Size>& engine) & -> Move;

#line 158 "../src/ai.h2"
    public: [[nodiscard]] auto getMove(Engine<9>& engine) -> Move override;

#line 162 "../src/ai.h2"
    public: [[nodiscard]] auto getMove(Engine<19>& engine) -> Move override;

#line 166 "../src/ai.h2"
    private: [[nodiscard]] auto computeLearningRate() & -> float;

#line 196 "../src/ai.h2"
    public: auto train(cpp2::impl::in<cpp2::i16> gobanSize) & -> void;

#line 227 "../src/ai.h2"
    public: auto save() & -> void;

#line 231 "../src/ai.h2"
    public: auto saveIfBetter() & -> void;

#line 238 "../src/ai.h2"
    private: [[nodiscard]] auto calculateWinrate() const& -> float;

#line 242 "../src/ai.h2"
    public: auto processStartGame() -> void override;

#line 254 "../src/ai.h2"
    public: auto processEndGame() -> void override;

#line 277 "../src/ai.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/ai.h2"

#line 5 "../src/ai.h2"
auto createAi() -> void{
    std::vector<snn::LayerModel> layers {snn::Input(1, 9, 9), 
                                            snn::Convolution(16, 3, snn::activation::ReLU), 
                                            snn::Convolution(32, 3, snn::activation::ReLU), 
                                            snn::Convolution(64, 3, snn::activation::ReLU), 
                                            snn::Convolution(128, 3, snn::activation::ReLU), 
                                            snn::FullyConnected(81, snn::activation::tanh)}; 
    /*layers: std::vector<snn::LayerModel> = (snn::Input(1, 9, 9),
                                            snn::FullyConnected(300, snn::activation::ReLU),
                                            snn::FullyConnected(300, snn::activation::ReLU),
                                            snn::FullyConnected(81, snn::activation::tanh));*/
    auto optimizer {snn::StochasticGradientDescent(1e-6f, 0.0f)}; 
    auto neuralNetwork {snn::StraightforwardNeuralNetwork(cpp2::move(layers), cpp2::move(optimizer))}; 
    CPP2_UFCS(saveAs)(neuralNetwork, "./snn_models/9x9/model_v02.snn");
    if (CPP2_UFCS(isValid)(cpp2::move(neuralNetwork)) != snn::errorType::noError) {
        std::cout << "INVALID MODEL !" << std::endl;
        std::exit(0);
    }
    setNextMessage("AI created.");
}

#line 42 "../src/ai.h2"
    Ai::Ai(cpp2::impl::in<Color> c, cpp2::impl::in<cpp2::i16> r, cpp2::impl::in<std::string> path)
        : Player{ c }
        , randomness{ r }
        , modelPath{ path }
        , neuralNetwork{ snn::StraightforwardNeuralNetwork::loadFrom(modelPath) }
        , optimizer{ std::static_pointer_cast<snn::internal::StochasticGradientDescent>(neuralNetwork.optimizer) }
        , inputs{  }
        , moves{  }
        , lastGameWon{  }{

#line 51 "../src/ai.h2"
        CPP2_UFCS(reserve)(inputs, 300);
        CPP2_UFCS(reserve)(moves, 300);
    }

#line 55 "../src/ai.h2"
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
        , defaultLearningRate{ that.defaultLearningRate }
        , previousWinrate{ that.previousWinrate }
        , isBetter{ that.isBetter }{

#line 62 "../src/ai.h2"
        modelPath = that.modelPath;
        lastGameWon = that.lastGameWon;
        sumOfLastGameWon = that.sumOfLastGameWon;
        defaultLearningRate = that.defaultLearningRate;
        previousWinrate = that.previousWinrate;
        isBetter = that.isBetter;
    }

#line 70 "../src/ai.h2"
    [[nodiscard]] auto Ai::summary() const& -> std::string{
        return CPP2_UFCS(summary)(neuralNetwork); 
    }

#line 74 "../src/ai.h2"
    template<cpp2::i8 Size> [[nodiscard]] auto Ai::getGobanState(cpp2::impl::in<State<Stone,Size>> state) const& -> std::vector<float>{
        std::vector<float> vec {}; 
        auto size {CPP2_UFCS(ssize)(state) * CPP2_UFCS(ssize)(state)}; 
        CPP2_UFCS(reserve)(vec, cpp2::move(size));
{
cpp2::i8 col{0};

#line 79 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(col,CPP2_UFCS(ssize)(state)); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 83 "../src/ai.h2"
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
#line 96 "../src/ai.h2"
        }
}
#line 97 "../src/ai.h2"
        return vec; 
    }

#line 100 "../src/ai.h2"
    template<cpp2::i8 Size> [[nodiscard]] auto Ai::chooseBestMove(cpp2::impl::in<std::vector<float>> nn_output, Engine<Size>& engine) & -> Move{
        cpp2::i16 index {0}; 
        std::vector<Stone> estimatedPositions {}; 
        auto numberOfPositions {Size * Size}; 
        CPP2_UFCS(reserve)(estimatedPositions, cpp2::move(numberOfPositions));
{
cpp2::i8 col{0};

#line 106 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(col,Size); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 110 "../src/ai.h2"
            for( ; cpp2::impl::cmp_less(row,Size); 
            ++row ) 
            {
                auto estimation {CPP2_ASSERT_IN_BOUNDS(nn_output, index)}; 
                auto stone {Stone(color, col, row, cpp2::move(estimation))}; 
                CPP2_UFCS(push_back)(estimatedPositions, cpp2::move(stone));
                ++index;
            }
}
#line 118 "../src/ai.h2"
        }
}
#line 119 "../src/ai.h2"
        std::ranges::sort(estimatedPositions, std::ranges::greater(), &Stone::estimation);
        std::uniform_int_distribution<cpp2::i64> dist {0, randomness - 1}; 
        auto picked_index {cpp2::move(dist)(rng)}; 
        auto s {CPP2_ASSERT_IN_BOUNDS(cpp2::move(estimatedPositions), cpp2::move(picked_index))}; 
        auto m {Move(cpp2::move(s))}; 
        CPP2_UFCS(closerValidMove)(engine, m);
        return m; 
        /*if engine.isValidMove(m) {
            engine.closerValidMove(m);
            return m;
        }
        (copy index2: i16 = 0)
        while index2 < numberOfPositions
        next index2++
        {
            if (index2 != picked_index) {
                s2:= estimatedPositions[index2];
                m2:= Move(s2);
                if engine.isValidMove(m2) {
                    return m2;
                }
            }
        }
        engine.closerValidMove(m);
        return m;*/
    }

#line 146 "../src/ai.h2"
    template<cpp2::i8 Size> [[nodiscard]] auto Ai::getMove(Engine<Size>& engine) & -> Move{
        auto input {getGobanState<Size>(engine.goban.state)}; 
        auto output {CPP2_UFCS(computeOutput)(neuralNetwork, input)}; 
        auto m {chooseBestMove<Size>(cpp2::move(output), engine)}; 
        auto moveIndex {CPP2_UFCS_TEMPLATE(getIndex<Size>)(m.stone)}; 
        if (cpp2::impl::cmp_greater_eq(moveIndex,0)) {
            CPP2_UFCS(push_back)(inputs, cpp2::move(input));
            CPP2_UFCS(push_back)(moves, cpp2::move(moveIndex));
        }
        return m; 
    }

#line 158 "../src/ai.h2"
    [[nodiscard]] auto Ai::getMove(Engine<9>& engine) -> Move{
        return getMove<9>(engine); 
    }

#line 162 "../src/ai.h2"
    [[nodiscard]] auto Ai::getMove(Engine<19>& engine) -> Move{
        return getMove<19>(engine); 
    }

#line 166 "../src/ai.h2"
    [[nodiscard]] auto Ai::computeLearningRate() & -> float{
        auto learningRate {defaultLearningRate}; 
        if (randomness == 1) {
            learningRate *= 0.75;
        }else {
            learningRate *= 1.25;
        }
        /*if hasWon {
            learningRate = 0.9;
        }
        else {
            learningRate = 1.1;
        }*/
        if (cpp2::impl::cmp_less(CPP2_UFCS(ssize)(inputs),40)) {
           learningRate *= 16;
        }
        else {if (cpp2::impl::cmp_less(CPP2_UFCS(ssize)(inputs),50)) {
            learningRate *= 8;
        }
        else {if (cpp2::impl::cmp_less(CPP2_UFCS(ssize)(inputs),60)) {
            learningRate *= 4;
        }
        else {if (cpp2::impl::cmp_less(CPP2_UFCS(ssize)(inputs),70)) {
            learningRate *= 2;
        }else {
            learningRate *= 1;
        }}}}
        return learningRate; 
    }

#line 196 "../src/ai.h2"
    auto Ai::train(cpp2::impl::in<cpp2::i16> gobanSize) & -> void{
        if (CPP2_UFCS(isValid)(neuralNetwork) != snn::errorType::noError) {
            std::cout << "INVALID MODEL !" << std::endl;
            std::exit(0);
        }
        (*cpp2::impl::assert_not_null(optimizer)).learningRate = computeLearningRate();
        auto size {gobanSize * gobanSize}; 
        float expectedValue {-1.0f}; 
        if (hasWon) {// CPP2 workaround: Conditional operator not yet supported.
            expectedValue = 1.0f;
        }
{
cpp2::i16 i{0};

#line 208 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(i,CPP2_UFCS(ssize)(inputs)); 
        ++i ) 
        {
            auto expected_output {std::vector<float>(size, NAN)}; 
            auto weighting {std::vector<float>(size, 1.0f)}; 
{
cpp2::i16 j{0};

#line 214 "../src/ai.h2"
            for( ; cpp2::impl::cmp_less(j,size); 
            ++j ) 
            {
                if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(inputs, i), j) != 0.0) {
                    CPP2_ASSERT_IN_BOUNDS(expected_output, j) = 0;
                    CPP2_ASSERT_IN_BOUNDS(weighting, j) = 1e-3f;
                }
            }
}
#line 222 "../src/ai.h2"
            CPP2_ASSERT_IN_BOUNDS(expected_output, CPP2_ASSERT_IN_BOUNDS(moves, i)) = expectedValue;
            CPP2_UFCS(trainOnce)(neuralNetwork, CPP2_ASSERT_IN_BOUNDS(inputs, i), cpp2::move(expected_output), cpp2::move(weighting));
        }
}
#line 225 "../src/ai.h2"
    }

#line 227 "../src/ai.h2"
    auto Ai::save() & -> void{
        CPP2_UFCS(saveAs)(neuralNetwork, modelPath);
    }

#line 231 "../src/ai.h2"
    auto Ai::saveIfBetter() & -> void{
        if (isBetter) {
            save();
            isBetter = false;
        }
    }

#line 238 "../src/ai.h2"
    [[nodiscard]] auto Ai::calculateWinrate() const& -> float{
        return sumOfLastGameWon / CPP2_ASSERT_NOT_ZERO(CPP2_TYPEOF(sumOfLastGameWon),(float)(CPP2_UFCS(size)(lastGameWon))); 
    }

#line 242 "../src/ai.h2"
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

#line 254 "../src/ai.h2"
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
        setNextMessage("AI randomness: " + std::to_string(randomness));
    }
#endif

