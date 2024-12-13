
#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/main.cpp2"


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/main.cpp2"
#include "windows.h"

#include "io.h"
#include "game.h"
#include "human.h"
#include "random.h"
#include "ai.h"

#line 9 "../src/main.cpp2"
extern bool isSaving;

void signalHandler(int signal) {
    if (signal == SIGINT) {
        while(isSaving) {
            std::cout << "Cannot stop, saving in progress..." << std::endl;
        }
        std::exit(0);
    }
}

auto gameHumanVsHuman() -> void;

#line 30 "../src/main.cpp2"
auto gameHumanVsRandom() -> void;

#line 40 "../src/main.cpp2"
auto gameHumanVsAi(cpp2::impl::in<std::string> modelPath) -> void;

#line 54 "../src/main.cpp2"
auto gameRandomVsRandom() -> void;

#line 64 "../src/main.cpp2"
auto gameAiVsAi(cpp2::impl::in<std::string> modelPath) -> void;

#line 88 "../src/main.cpp2"
[[nodiscard]] auto loadAi() -> std::string;

#line 97 "../src/main.cpp2"
auto evaluateAi(cpp2::impl::in<std::string> modelPath) -> void;

#line 123 "../src/main.cpp2"
[[nodiscard]] auto cpp2_main() -> int;
#line 157 "../src/main.cpp2"


int main() {
    try { // CPP2 workaround: Try catch not yet supported.
        return cpp2_main();
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
}


//=== Cpp2 function definitions =================================================

#line 1 "../src/main.cpp2"

#line 9 "../src/main.cpp2"
bool isSaving {false}; 

#line 20 "../src/main.cpp2"
auto gameHumanVsHuman() -> void{
    clear();
    setNextMessage("Start a new game.");
    auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::Black)}; 
    auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::White)}; 
    auto game {Game(cpp2::move(player1), cpp2::move(player2))}; 
    CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));
    waitInput();
}

#line 30 "../src/main.cpp2"
auto gameHumanVsRandom() -> void{
    clear();
    setNextMessage("Start a new game.");
    auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::Black)}; 
    auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Random>)(cpp2::shared, Color::White)}; 
    auto game {Game(cpp2::move(player1), cpp2::move(player2))}; 
    CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));
    waitInput();
}

#line 40 "../src/main.cpp2"
auto gameHumanVsAi(cpp2::impl::in<std::string> modelPath) -> void{
    clear();
    if (modelPath == "") {
        setNextMessage("No model selected.");
        return ; 
    }
    setNextMessage("Start a new game.");
    auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::Black)}; 
    auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Ai>)(cpp2::shared, Color::White, modelPath)}; 
    auto game {Game(cpp2::move(player1), cpp2::move(player2))}; 
    CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));
    waitInput();
}

#line 54 "../src/main.cpp2"
auto gameRandomVsRandom() -> void{
    clear();
    setNextMessage("Start a new game.");
    auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<RandomSlow>)(cpp2::shared, Color::Black, 500)}; 
    auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<RandomSlow>)(cpp2::shared, Color::White, 500)}; 
    auto game {Game(cpp2::move(player1), cpp2::move(player2))}; 
    CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));
    waitInput();
}

#line 64 "../src/main.cpp2"
auto gameAiVsAi(cpp2::impl::in<std::string> modelPath) -> void{
    clear();
    if (modelPath == "") {
        setNextMessage("No model selected.");
        return ; 
    }
    auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Ai>)(cpp2::shared, Color::Black, modelPath)}; 
    auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Ai>)(cpp2::shared, Color::White, modelPath)}; 
    auto game {Game(player1, player2)}; 
    cpp2::i32 i {0}; 
    while( true ) 
    {
        CPP2_UFCS_TEMPLATE(play<false>)(game);
        CPP2_UFCS(train)((*cpp2::impl::assert_not_null(player1)));
        CPP2_UFCS(train)((*cpp2::impl::assert_not_null(player2)));
        if (i % 20 == 0) {
            isSaving = true;
            CPP2_UFCS(save)((*cpp2::impl::assert_not_null(player1)));
            isSaving = false;
        }
        ++i;
    }
}

#line 88 "../src/main.cpp2"
[[nodiscard]] auto loadAi() -> std::string{
    clear();
    auto modelPath {SelectSnnModel()}; 
    clear();
    printSnnModel(modelPath);
    setNextMessage(modelPath + " selected.");
    return modelPath; 
}

#line 97 "../src/main.cpp2"
auto evaluateAi(cpp2::impl::in<std::string> modelPath) -> void{
    /*numberOfGame = 100;
    numberOfGameWon = 0;
    player1:= shared.new<Ai>(Color::Black, modelPath);
    player2:= shared.new<Random>(Color::White, modelPath);
    game:= Game(player1, player2);

    (copy i: i32 = 0)
    while i < (numberOfGame / 2)
    next i++
    {
        game.play<false>();
        player1.train();
        player2.train();
        if i % 20 == 0 {
            isSaving = true;
            player1.save();
            isSaving = false;
        }
        if player1.hasWon {
            numberOfGameWon++;
        }
    }*/
}

#line 123 "../src/main.cpp2"
[[nodiscard]] auto cpp2_main() -> int{
    signal(SIGINT, signalHandler);
    SetConsoleOutputCP(CP_UTF8);
    bool exit {false}; 
    std::string modelPath {""}; 
    do {
        printMenu();
        int selection {getInputMenu()}; 
        if (selection == 0) {
            clear("Bye.");
            exit = true;
        }else {if (selection == 1) {
            gameHumanVsHuman();
        }else {if (selection == 2) {
            gameHumanVsRandom();
        }else {if (selection == 3) {
            gameHumanVsAi(modelPath);
        }else {if (selection == 4) {
            gameRandomVsRandom();
        }else {if (selection == 5) {
            gameAiVsAi(modelPath);
        }else {if (selection == 6) {
            evaluateAi(modelPath);
        }else {if (selection == 7) {
            modelPath = loadAi();
        }else {if (cpp2::move(selection) == 9) {
            createAi();
            setNextMessage("AI created.");
        }else {
            setNextMessage("Invalid selection.");
        }}}}}}}}}
    } while ( !(exit));
  return 0; 
}

