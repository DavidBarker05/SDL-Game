#pragma once

// This file is long

#include "Types.h"

enum class InputDevice : UINT8
{
    eDEVICE_KEYBOARD,
    eDEVICE_MOUSE,
    eDEVICE_GAMEPAD,
    COUNT
};

enum class InputType : UINT8
{
    eTYPE_STARTED,
    eTYPE_HELD,
    eTYPE_RELEASED,
    COUNT
};

// https://usb.org/sites/default/files/hut1_5.pdf (p = 0x07)
enum class KeyCode : UINT32
{
    eUNKNOWN = 0u,
    eENTER_ANY, // Keyboard or keypad enter
    eCONTROL_ANY, // Left control or right control
    eSHIFT_ANY, // Left shift or right shift
    eALT_ANY, // Left alt or right alt
    eGUI_ANY, // Left GUI or right GUI
    eA, // Different symbol depending on language but same code
    eB,
    eC, // Different symbol depending on language but same code
    eD,
    eE,
    eF,
    eG,
    eH,
    eI,
    eJ,
    eK,
    eL,
    eM, // Different symbol depending on language but same code
    eN,
    eO, // Different symbol depending on language but same code
    eP, // Different symbol depending on language but same code
    eQ, // Different symbol depending on language but same code
    eR,
    eS,
    eT,
    eU,
    eV,
    eW, // Different symbol depending on language but same code
    eX, // Different symbol depending on language but same code
    eY, // Different symbol depending on language but same code
    eZ, // Different symbol depending on language but same code
    e1, // Different symbol depending on language but same code
    e2, // Different symbol depending on language but same code
    e3, // Different symbol depending on language but same code
    e4, // Different symbol depending on language but same code
    e5, // Different symbol depending on language but same code
    e6, // Different symbol depending on language but same code
    e7, // Different symbol depending on language but same code
    e8, // Different symbol depending on language but same code
    e9, // Different symbol depending on language but same code
    e0, // Different symbol depending on language but same code
    eENTER,
    eESCAPE,
    eBACKSPACE,
    eTAB,
    eSPACE,
    eMINUS, // Different symbol depending on language but same code
    eEQUAL, // Different symbol depending on language but same code
    eSQUARE_BRACKET_LEFT, // Different symbol depending on language but same code
    eUS_BACKSLASH, // US keyboard
    eNONUS_HASH, // Non-US keyboard
    eSEMI_COLON, // Different symbol depending on language but same code
    eAPOSTROPHE, // Different symbol depending on language but same code
    eGRAVE_ACCENT, // (or tilde) Different symbol depending on language but same code
    eCOMMA, // Different symbol depending on language but same code
    ePERIOD, // Different symbol depending on language but same code
    eFORWARD_SLASH, // Different symbol depending on language but same code
    eCAPS_LOCK,
    eF1,
    eF2,
    eF3,
    eF4,
    eF5,
    eF6,
    eF7,
    eF8,
    eF9,
    eF10,
    eF11,
    eF12,
    ePRINT_SCREEN,
    eINSERT,
    eHOME,
    ePAGE_UP,
    eDELETE,
    eEND,
    ePAGE_DOWN,
    eRIGHT,
    eLEFT,
    eDOWN,
    eUP,
    eNUM_LOCK_CLEAR, // Num lock for most keyboards except Mac where it's clear
    eKEYPAD_FORWARD_SLASH,
    eKEYPAD_ASTERIK,
    eKEYPAD_MINUS,
    eKEYPAD_PLUS,
    eKEYPAD_ENTER,
    eKEYPAD_1,
    eKEYPAD_2,
    eKEYPAD_3,
    eKEYPAD_4,
    eKEYPAD_5,
    eKEYPAD_6,
    eKEYPAD_7,
    eKEYPAD_8,
    eKEYPAD_9,
    eKEYPAD_0,
    eKEYPAD_PERIOD,
    eNONUS_BACKSLASH, // Non-US keyboard
    eAPPLICATION, // Genuinely idk but on the page
    ePOWER, // Power button I think
    eKEYPAD_EQUALS,
    eF13,
    eF14,
    eF15,
    eF16,
    eF17,
    eF18,
    eF19,
    eF20,
    eF21,
    eF22,
    eF23,
    eF24,
    eEXECUTE,
    eHELP,
    eMENU,
    eSELECT,
    eSTOP,
    eAGAIN,
    eUNDO, // Not ctrl/cmd + z, but a specific button?
    eCUT, // Not ctrl/cmd + x, but a specific button?
    eCOPY, // Not ctrl/cmd + c, but a specific button?
    ePASTE, // Not ctrl/cmd + v, but a specific button?
    eFIND, // Not ctrl/cmd + f, but a specific button?
    eMUTE,
    eVOLUME_UP,
    eVOLUME_DOWN,
    eKEYPAD_COMMA, // Brazilian keypad period key
    eKEYPAD_EQUAL_AS400, // Specific keyboard type
    eINTERNATIONAL1, // Brazilian forward slash and question mark and certain Japanese symbols?
    eINTERNATIONAL2, // Hiragana and katakana? Or kana? That's what the Japanese says on the page
    eINTERNATIONAL3, // Other Japanese symbols and yen?
    eINTERNATIONAL4, // Previous candidate when cycling through Japanese and Chinese words
    eINTERNATIONAL5, // Next candidate cycling through Japanese and Chinese words
    eINTERNATIONAL6, // Japanese comma (it shows a picture of a comma and says comma in katakana)
    eINTERNATIONAL7, // "Toggle Double-Byte/Single-Byte mode" whatever that means
    eINTERNATIONAL8, // "Undefined, available for other Front End Language Processors"
    eINTERNATIONAL9, // "Undefined, available for other Front End Language Processors"
    eLANG1, // Hangul/English toggle (Korean)
    eLANG2, // Hanja key (Korean)
    eLANG3, // Katakana key (Japanese)
    eLANG4, // Hiragana key (Japanese)
    eLANG5, // Zenkaku/Hankaku (Japanese) (half-width and full-width characters)
    eLANG6, // Reserved language key
    eLANG7, // Reserved language key
    eLANG8, // Reserved language key
    eLANG9, // Reserved language key
    eALTERNATE_ERASE, // Unique erase key that some keyboards might have
};

enum class MouseCode : UINT32
{
    eUNKNOWN = 0U,
};

enum class GamepadCode : UINT32
{
    eUNKNOWN = 0U,
    eBUTTON_SOUTH,
    eBUTTON_EAST,
    eBUTTON_WEST,
    eBUTTON_NORTH,
    eBACK,
    eGUIDE,
    eSTART,
    eLEFT_STICK,
    eLEFT_STICK_PRESS,
    eRIGHT_STICK,
    eRIGHT_STICK_PRESS,
    eLEFT_TRIGGER,
    eLEFT_SHOULDER,
    eRIGHT_TRIGGER,
    eRIGHT_SHOULDER,
    eDPAD,
    eDPAD_UP,
    eDPAD_DOWN,
    eDPAD_LEFT,
    eDPAD_RIGHT,
    eTOUCHPAD,
    eTOUCHPAD_PRESS,
    eBUTTON_MISC1, // See SDL docs
    eBUTTON_MISC2, // See SDL docs
    eBUTTON_MISC3, // See SDL docs
    eBUTTON_MISC4, // See SDL docs
    eBUTTON_MISC5, // See SDL docs
    eBUTTON_MISC6, // See SDL docs
    eLEFT_PADDLE1, // See SDL docs
    eLEFT_PADDLE2, // See SDL docs
    eRIGHT_PADDLE1, // See SDL docs
    eRIGHT_PADDLE2, // See SDL docs
    COUNT
};
