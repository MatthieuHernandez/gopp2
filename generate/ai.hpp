
#ifndef AI_H_CPP2
#error This file is part of a '.h2' header compiled to be consumed from another -pure-cpp2 file. To use this file, write '#include "ai.h2"' in a '.h2' or '.cpp2' file compiled with -pure-cpp2.
#endif

#ifndef AI_HPP_CPP2
#define AI_HPP_CPP2

#include "player.hpp"
#include "snn.hpp"


//=== Cpp2 function definitions =================================================

#line 1 "../src/ai.h2"

#line 4 "../src/ai.h2"
auto createAi() -> void{
    std::vector<snn::LayerModel> layers {snn::Input(1, 9, 9), 
                                            snn::Convolution(16, 3, snn::activation::ReLU), 
                                            snn::Convolution(32, 3, snn::activation::ReLU), 
                                            snn::Convolution(64, 3, snn::activation::ReLU), 
                                            snn::Convolution(128, 3, snn::activation::ReLU), 
                                            snn::FullyConnected(81, snn::activation::tanh)}; 
    /*layers: std::vector<snn::LayerModel> = (snn::Input(1, 9, 9),
                                            snn::FullyConnected(1000, snn::activation::ReLU),
                                            snn::FullyConnected(81, snn::activation::tanh));*/
    auto optimizer {snn::StochasticGradientDescent(1e-4f, 0.0f)}; 
    auto neuralNetwork {snn::StraightforwardNeuralNetwork(cpp2::move(layers), cpp2::move(optimizer))}; 
    CPP2_UFCS(saveAs)(neuralNetwork, "./snn_models/9x9/model_02.snn");
    if (CPP2_UFCS(isValid)(cpp2::move(neuralNetwork)) != snn::errorType::noError) {
        std::cout << "INVALID MODEL !" << std::endl;
        std::exit(0);
    }
    std::cout << "AI created." << std::endl;
}

#line 38 "../src/ai.h2"
    Ai::Ai(Interface* i, cpp2::impl::in<Color> c, cpp2::impl::in<cpp2::i16> r, cpp2::impl::in<std::string> path)
        : Player{ i, c }
        , randomness{ r }
        , modelPath{ path }
        , neuralNetwork{ CPP2_UFCS_TEMPLATE_NONLOCAL(cpp2_new<snn::StraightforwardNeuralNetwork>)(cpp2::shared, snn::StraightforwardNeuralNetwork::loadFrom(modelPath)) }
        , optimizer{ std::static_pointer_cast<snn::internal::StochasticGradientDescent>((*cpp2::impl::assert_not_null(neuralNetwork)).optimizer) }
        , lastGameWon{  }{

#line 45 "../src/ai.h2"
    }

#line 47 "../src/ai.h2"
    Ai::Ai(Interface* i, cpp2::impl::in<Color> c, cpp2::impl::in<cpp2::i16> r, cpp2::impl::in<Ai> ai)
        : Player{ i, c }
        , randomness{ r }
        , modelPath{ "" }
        , neuralNetwork{ ai.neuralNetwork }
        , optimizer{ std::static_pointer_cast<snn::internal::StochasticGradientDescent>((*cpp2::impl::assert_not_null(neuralNetwork)).optimizer) }
        , lastGameWon{  }{

#line 54 "../src/ai.h2"
    }

#line 56 "../src/ai.h2"
    Ai::Ai(Ai const& that)
        : Player{ that }
        , randomness{ that.randomness }
        , modelPath{ that.modelPath }
        , neuralNetwork{ that.neuralNetwork }
        , optimizer{ that.optimizer }
        , lastGameWon{ that.lastGameWon }
        , numberOfGames{ that.numberOfGames }
        , sumOfLastGameWon{ that.sumOfLastGameWon }
        , defaultLearningRate{ that.defaultLearningRate }
        , previousWinrate{ that.previousWinrate }
        , isBetter{ that.isBetter }{

#line 61 "../src/ai.h2"
        modelPath = that.modelPath;
        lastGameWon = that.lastGameWon;
        sumOfLastGameWon = that.sumOfLastGameWon;
        defaultLearningRate = that.defaultLearningRate;
        previousWinrate = that.previousWinrate;
        isBetter = that.isBetter;
    }

#line 69 "../src/ai.h2"
    [[nodiscard]] auto Ai::summary() const& -> std::string{
        return CPP2_UFCS(summary)((*cpp2::impl::assert_not_null(neuralNetwork))); 
    }

#line 73 "../src/ai.h2"
    template<cpp2::i8 Size> [[nodiscard]] auto Ai::getGobanState(cpp2::impl::in<State<Stone,Size>> state) const& -> std::vector<float>{
        std::vector<float> vec {}; 
        auto size {CPP2_UFCS(ssize)(state) * CPP2_UFCS(ssize)(state)}; 
        CPP2_UFCS(reserve)(vec, cpp2::move(size));
{
cpp2::i8 col{0};

#line 78 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(col,CPP2_UFCS(ssize)(state)); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 82 "../src/ai.h2"
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
#line 95 "../src/ai.h2"
        }
}
#line 96 "../src/ai.h2"
        return vec; 
    }

#line 99 "../src/ai.h2"
    template<cpp2::i8 Size> [[nodiscard]] auto Ai::chooseBestMove(cpp2::impl::in<std::vector<float>> nnOutput, Engine<Size>& engine) & -> Move{
        cpp2::i16 index {0}; 
        std::vector<Stone> estimatedPositions {}; 
        auto numberOfPositions {Size * Size}; 
        CPP2_UFCS(reserve)(estimatedPositions, numberOfPositions);
{
cpp2::i8 col{0};

#line 105 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(col,Size); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 109 "../src/ai.h2"
            for( ; cpp2::impl::cmp_less(row,Size); 
            ++row ) 
            {
                auto estimation {CPP2_ASSERT_IN_BOUNDS(nnOutput, index)}; 
                auto stone {Stone(color, col, row, cpp2::move(estimation))}; 
                CPP2_UFCS(push_back)(estimatedPositions, cpp2::move(stone));
                ++index;
            }
}
#line 117 "../src/ai.h2"
        }
}
#line 118 "../src/ai.h2"
        std::ranges::sort(estimatedPositions, std::ranges::greater(), &Stone::estimation);
        std::uniform_int_distribution<cpp2::i64> dist {0, randomness - 1}; 
        auto pickedIndex {cpp2::move(dist)(rng)}; 
        auto s {CPP2_ASSERT_IN_BOUNDS(estimatedPositions, pickedIndex)}; 
        auto m {Move(cpp2::move(s))}; 
        if (CPP2_UFCS(isValidMove)(engine, m)) {
            return m; 
        }
{
cpp2::i16 index2{0};

#line 127 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(index2,numberOfPositions); 
        ++index2 ) 
        {
            if ((index2 != pickedIndex)) {
                auto s2 {CPP2_ASSERT_IN_BOUNDS(estimatedPositions, index2)}; 
                auto m2 {Move(cpp2::move(s2))}; 
                if (CPP2_UFCS(isValidMove)(engine, m2)) {
                    return m2; 
                }
            }
        }
}
#line 138 "../src/ai.h2"
        return pass(color); 
    }

#line 141 "../src/ai.h2"
    template<cpp2::i8 Size> [[nodiscard]] auto Ai::getMove(Engine<Size>& engine) & -> Move{

        auto input {getGobanState<Size>(engine.goban.state)}; 
        auto output {CPP2_UFCS(computeOutput)((*cpp2::impl::assert_not_null(neuralNetwork)), cpp2::move(input))}; 
        auto m {chooseBestMove<Size>(cpp2::move(output), engine)}; 
        return m; 
    }

#line 149 "../src/ai.h2"
    [[nodiscard]] auto Ai::getMove(Engine<9>& engine) -> Move{
        return getMove<9>(engine); 
    }

#line 153 "../src/ai.h2"
    [[nodiscard]] auto Ai::getMove(Engine<13>& engine) -> Move{
        return getMove<13>(engine); 
    }

#line 157 "../src/ai.h2"
    [[nodiscard]] auto Ai::getMove(Engine<19>& engine) -> Move{
        return getMove<19>(engine); 
    }

#line 161 "../src/ai.h2"
    [[nodiscard]] auto Ai::computeLearningRate(cpp2::impl::in<cpp2::i16> gameLength) & -> float{
        auto learningRate {defaultLearningRate}; 
        if (cpp2::impl::cmp_greater(calculateWinrate(),0.8)) {
            learningRate /= CPP2_ASSERT_NOT_ZERO_LITERAL(CPP2_TYPEOF(learningRate),2);
        }
        return learningRate; 
    }

#line 169 "../src/ai.h2"
    template<cpp2::i8 Size> auto Ai::train(cpp2::impl::in<Engine<Size>> engine) & -> void{
        if ((cpp2::impl::cmp_greater(CPP2_UFCS(ssize)(engine.moves),291))) {
            return ; 
        }
        cpp2::i16 gameLength {cpp2::unchecked_narrow<cpp2::i16>(CPP2_UFCS(size)(engine.moves))}; 
        (*cpp2::impl::assert_not_null(optimizer)).learningRate = computeLearningRate(cpp2::move(gameLength));
        auto size {Size * Size}; 
        cpp2::impl::deferred_init<float> expectedBlack; 
        cpp2::impl::deferred_init<float> expectedWhite; 
        if ((hasWon && color == Color::Black) || 
           (!(hasWon) && color == Color::White)) {// CPP2 workaround: Conditional operator not yet supported.
            expectedBlack.construct(1.0f);
            expectedWhite.construct(-1.0f);
        }else {
            expectedBlack.construct(-1.0f);
            expectedWhite.construct(1.0f);
        }
{
cpp2::i16 i{0};

#line 187 "../src/ai.h2"
        for( ; cpp2::impl::cmp_less(i,(CPP2_UFCS(ssize)(engine.moves))); 
        ++i ) 
        {
            if ((CPP2_ASSERT_IN_BOUNDS(engine.moves, i).isPass == true)) {
                return ; 
            }
            auto inputs {getGobanState<Size>(CPP2_ASSERT_IN_BOUNDS(engine.states, i))}; 
            auto expectedOutputs {std::vector<float>(size, NAN)}; 
            auto weighting {std::vector<float>(size, 1.0f)}; 
{
cpp2::i16 j{0};

#line 197 "../src/ai.h2"
            for( ; cpp2::impl::cmp_less(j,size); 
            ++j ) 
            {
                if (CPP2_ASSERT_IN_BOUNDS(inputs, j) != 0.0) {
                    CPP2_ASSERT_IN_BOUNDS(expectedOutputs, j) = 0;
                    CPP2_ASSERT_IN_BOUNDS(weighting, j) = 1e-3f;
                }
            }
}
#line 205 "../src/ai.h2"
            auto expectedIndex {CPP2_UFCS_TEMPLATE(getIndex<Size>)(CPP2_ASSERT_IN_BOUNDS(engine.moves, i).stone)}; 
            if (i % 2 == 0) {
                CPP2_ASSERT_IN_BOUNDS(expectedOutputs, expectedIndex) = expectedBlack.value();
            }else {
                CPP2_ASSERT_IN_BOUNDS(expectedOutputs, expectedIndex) = expectedWhite.value();
            }
            CPP2_UFCS(trainOnce)((*cpp2::impl::assert_not_null(neuralNetwork)), cpp2::move(inputs), cpp2::move(expectedOutputs), cpp2::move(weighting));
        }
}
#line 213 "../src/ai.h2"
    }

#line 215 "../src/ai.h2"
    auto Ai::save() & -> void{
        CPP2_UFCS(saveAs)((*cpp2::impl::assert_not_null(neuralNetwork)), modelPath);
    }

#line 219 "../src/ai.h2"
    auto Ai::saveIfBetter() & -> void{
        if (isBetter) {
            save();
            isBetter = false;
        }
    }

#line 226 "../src/ai.h2"
    [[nodiscard]] auto Ai::calculateWinrate() const& -> float{
        return sumOfLastGameWon / CPP2_ASSERT_NOT_ZERO(CPP2_TYPEOF(sumOfLastGameWon),(float)(CPP2_UFCS(size)(lastGameWon))); 
    }

#line 230 "../src/ai.h2"
    auto Ai::processStartGame() -> void{
        if (CPP2_UFCS(isValid)((*cpp2::impl::assert_not_null(neuralNetwork))) != snn::errorType::noError) {
            std::cout << "INVALID MODEL !" << std::endl;
            std::exit(0);
        }
        auto currentWinRate {calculateWinrate()}; 
        if (CPP2_UFCS(ssize)(lastGameWon) == numberOfGames 
        && cpp2::impl::cmp_greater(currentWinRate,previousWinrate)) {
            previousWinrate = cpp2::move(currentWinRate);
            isBetter = true;

        }
    }

#line 244 "../src/ai.h2"
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
            CPP2_UFCS(printLater)((*cpp2::impl::assert_not_null(interface)), "AI winrate: " + std::to_string(calculateWinrate() * 100.0f) + " %");
        }else {
            CPP2_UFCS(print)((*cpp2::impl::assert_not_null(interface)), "AI winrate: ...");
        }
        std::ostringstream oss {}; 
        oss << "AI learning rate: " << std::scientific << std::setprecision(2) << (*cpp2::impl::assert_not_null(optimizer)).learningRate;
        CPP2_UFCS(printLater)((*cpp2::impl::assert_not_null(interface)), CPP2_UFCS(str)(cpp2::move(oss)));
        CPP2_UFCS(printLater)((*cpp2::impl::assert_not_null(interface)), "AI randomness: " + std::to_string(randomness));
    }
#endif

