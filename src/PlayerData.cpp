#include "PlayerData.hpp"
#include "Macros.hpp"

$on_mod(Loaded) {
    GDI_SET_VALUE(bool, "2pselected", false);
}

int PlayerData::callPosStreak = 0;