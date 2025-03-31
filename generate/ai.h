
#ifndef AI_H_CPP2
#define AI_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/ai.h2"

#line 24 "../src/ai.h2"
class Ai;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/ai.h2"
#include "player.h"
#include "snn.h"

#line 4 "../src/ai.h2"
auto createAi() -> void;

#line 24 "../src/ai.h2"
class Ai: public Player {

    public: cpp2::i16 randomness; // Randomly select a move from the N best moves.

    private: std::string modelPath; 
    private: std::shared_ptr<snn::StraightforwardNeuralNetwork> neuralNetwork; 
    private: std::shared_ptr<snn::internal::StochasticGradientDescent> optimizer; 
    private: std::deque<int> lastGameWon; 
    private: size_t const numberOfGames {1000}; // To calculate winrate.
    private: size_t sumOfLastGameWon {0}; 
    private: float defaultLearningRate {1e-4f}; 
    private: float previousWinrate {0.0f}; 
    private: bool isBetter {false}; 

    public: Ai(Interface* i, cpp2::impl::in<Color> c, cpp2::impl::in<cpp2::i16> r, cpp2::impl::in<std::string> path);

#line 47 "../src/ai.h2"
    public: Ai(Interface* i, cpp2::impl::in<Color> c, cpp2::impl::in<cpp2::i16> r, cpp2::impl::in<Ai> ai);

#line 56 "../src/ai.h2"
    public: Ai(Ai const& that);

#line 69 "../src/ai.h2"
    public: [[nodiscard]] auto summary() const& -> std::string;

#line 73 "../src/ai.h2"
    private: template<cpp2::i8 Size> [[nodiscard]] auto getGobanState(cpp2::impl::in<State<Stone,Size>> state) const& -> std::vector<float>;

#line 99 "../src/ai.h2"
    private: template<cpp2::i8 Size> [[nodiscard]] auto chooseBestMove(cpp2::impl::in<std::vector<float>> nnOutput, Engine<Size>& engine) & -> Move;

#line 141 "../src/ai.h2"
    private: template<cpp2::i8 Size> [[nodiscard]] auto getMove(Engine<Size>& engine) & -> Move;

#line 149 "../src/ai.h2"
    public: [[nodiscard]] auto getMove(Engine<9>& engine) -> Move override;

#line 153 "../src/ai.h2"
    public: [[nodiscard]] auto getMove(Engine<13>& engine) -> Move override;

#line 157 "../src/ai.h2"
    public: [[nodiscard]] auto getMove(Engine<19>& engine) -> Move override;

#line 161 "../src/ai.h2"
    private: [[nodiscard]] auto computeLearningRate(cpp2::impl::in<cpp2::i16> gameLength) & -> float;

#line 169 "../src/ai.h2"
    public: template<cpp2::i8 Size> auto train(cpp2::impl::in<Engine<Size>> engine) & -> void;

#line 215 "../src/ai.h2"
    public: auto save() & -> void;

#line 219 "../src/ai.h2"
    public: auto saveIfBetter() & -> void;

#line 226 "../src/ai.h2"
    private: [[nodiscard]] auto calculateWinrate() const& -> float;

#line 230 "../src/ai.h2"
    public: auto processStartGame() -> void override;

#line 244 "../src/ai.h2"
    public: auto processEndGame() -> void override;

#line 267 "../src/ai.h2"
};

#endif
