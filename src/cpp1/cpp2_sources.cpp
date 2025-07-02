#include "color.h"
#include "color.hpp"
#include "stone.h"
#include "stone.hpp"
#include "move.h"
#include "move.hpp"
#include "goban.h"
#include "goban.hpp"
#include "engine.h"
#include "engine.hpp"
#include "io.h"
#include "io.hpp"
#include "cli.h"
#include "cli.hpp"
#include "player.h"
#include "player.hpp"
#include "human.h"
#include "human.hpp"
#include "dumb.h"
#include "dumb.hpp"
#include "random.h"
#include "random.hpp"
#include "ai.h"
#include "ai.hpp"
#include "itself.h"
#include "itself.hpp"
#include "game.h"
#include "game.hpp"
#include "interface.h"
#include "interface.hpp"
#include "cli_interface.h"
#include "cli_interface.hpp"

template class Goban<9>;
template class Goban<13>;
template class Goban<19>;

template class Engine<9>;
template class Engine<13>;
template class Engine<19>;
