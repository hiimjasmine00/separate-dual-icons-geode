#include "PlayerData.hpp"
#include "Macros.hpp"
#include <Geode/modify/PlayerObject.hpp>


class $modify(MyPlayerObject, PlayerObject) {
    void setupStreak() {
        // thanks alphalaneous for the fucking genius code
        // theres no way i dont copy this
        auto GM = GameManager::get();
        int origStreak = GM->m_playerStreak;
        int origShipStreak = GM->m_playerShipFire;
        bool origGlow = GM->m_playerGlow;

        if (m_gameLayer) {
            if (PlayerData::callPosStreak == 1) {
                GM->m_playerStreak = GDI_GET_VALUE(int64_t, "trail", 1);
                GM->m_playerShipFire = GDI_GET_VALUE(int64_t, "shiptrail", 1);
                GM->m_playerGlow = GDI_GET_VALUE(bool, "glow", false);
            }

            PlayerData::callPosStreak++;
            if (PlayerData::callPosStreak == 2) PlayerData::callPosStreak = 0;
        }

        PlayerObject::setupStreak();

        GM->m_playerStreak = origStreak;
        GM->m_playerShipFire = origShipStreak;
        GM->m_playerGlow = origGlow;
    }

    void playDeathEffect() {
        auto GM = GameManager::get();
        int origDeath = GM->m_playerDeathEffect;
        bool orgDeathExplode = GM->getGameVariable("0153");

        if (m_gameLayer && this == m_gameLayer->m_player2) {
            GM->m_playerDeathEffect = GDI_GET_VALUE(int64_t, "death", 1);
            GM->setGameVariable("0153", GDI_GET_VALUE(bool, "deathexplode", false));
        }

        PlayerObject::playDeathEffect();

        GM->m_playerDeathEffect = origDeath;
        GM->setGameVariable("0153", orgDeathExplode);
    }

    void setColor(ccColor3B const &color) {
        PlayerObject::setColor(m_gameLayer && this == m_gameLayer->m_player2 ? GameManager::get()->colorForIdx(GDI_GET_VALUE(int64_t, "color1", 0)) : color);
    }

    void setSecondColor(ccColor3B const &color) {
        PlayerObject::setSecondColor(m_gameLayer && this == m_gameLayer->m_player2 ? GameManager::get()->colorForIdx(GDI_GET_VALUE(int64_t, "color2", 0)) : color);
    }

    void updatePlayerFrame(int p0) {
        PlayerObject::updatePlayerFrame(p0 != 0 && m_gameLayer && this == m_gameLayer->m_player2 ? GDI_GET_VALUE(int64_t, "cube", 1) : p0);
    }
    
	void updatePlayerShipFrame(int p0) {
        PlayerObject::updatePlayerShipFrame(m_gameLayer && this == m_gameLayer->m_player2 ? GDI_GET_VALUE(int64_t, "ship", 1) : p0);
    }

    void updatePlayerRollFrame(int p0) {
        PlayerObject::updatePlayerRollFrame(p0 != 0 && m_gameLayer && this == m_gameLayer->m_player2 ? GDI_GET_VALUE(int64_t, "roll", 1) : p0);
    }

    void updatePlayerBirdFrame(int p0) {
        PlayerObject::updatePlayerBirdFrame(m_gameLayer && this == m_gameLayer->m_player2 ? GDI_GET_VALUE(int64_t, "bird", 1) : p0);
    }

    void updatePlayerDartFrame(int p0) {
        PlayerObject::updatePlayerDartFrame(m_gameLayer && this == m_gameLayer->m_player2 ? GDI_GET_VALUE(int64_t, "dart", 1) : p0); 
    }

    void createRobot(int p0) {
        PlayerObject::createRobot(m_gameLayer && this == m_gameLayer->m_player2 ? GDI_GET_VALUE(int64_t, "robot", 1) : p0);
    }

    void createSpider(int p0) {
        PlayerObject::createSpider(m_gameLayer && this == m_gameLayer->m_player2 ? GDI_GET_VALUE(int64_t, "spider", 1) : p0);
    }

    void updatePlayerSwingFrame(int p0) {
        PlayerObject::updatePlayerSwingFrame(m_gameLayer && this == m_gameLayer->m_player2 ? GDI_GET_VALUE(int64_t, "swing", 1) : p0);
    }

    void updatePlayerJetpackFrame(int p0) {
        PlayerObject::updatePlayerJetpackFrame(m_gameLayer && this == m_gameLayer->m_player2 ? GDI_GET_VALUE(int64_t, "jetpack", 1) : p0);
    }

    void updateGlowColor() {
        if (m_gameLayer && this == m_gameLayer->m_player2) {
            enableCustomGlowColor(GameManager::get()->colorForIdx(GDI_GET_VALUE(int64_t, "colorglow", 0)));
        }
        PlayerObject::updateGlowColor();
    }
};