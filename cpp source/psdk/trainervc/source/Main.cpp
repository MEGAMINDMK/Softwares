#include "plugin.h"
#include "game_vc/CFont.h"
#include "game_vc/CPlayerPed.h"
#include "game_vc/CStreaming.h"
#include "game_vc/CWorld.h"
#include "game_vc/CTimer.h"
#include "game_vc/CHud.h"
#include "extensions/ScriptCommands.h"
#include "game_vc/eScriptCommands.h"
#include "game_vc/CPlayerInfo.h"

#include <fstream>
#include <sstream>
#include <algorithm>

using namespace plugin;

// Utility to trim whitespace
static std::string Trim(const std::string& s) {
    auto ws = " \t\n\r";
    size_t start = s.find_first_not_of(ws);
    size_t end = s.find_last_not_of(ws);
    return start == std::string::npos
        ? std::string()
        : s.substr(start, end - start + 1);
}

class SimpleTrainer {
public:
    struct MenuItem {
        std::string label;
        std::function<void()> action;
    };

    // Key bindings (populated from trainer.cfg)
    int keyUp, keyDown, keyLeft, keyRight;
    int keyToggleMenu, keyConfirm;

    std::vector<MenuItem> menuItems;
    int selectedIndex = 0;
    bool menuOpen = false;
    int typedModelID = 0;

    std::vector<std::pair<std::string, eWeaponType>> weaponList = {
        {"FISTS", WEAPONTYPE_UNARMED},
        {"BRASS KNUCKLES", WEAPONTYPE_BRASSKNUCKLE},
        {"SCREWDRIVER", WEAPONTYPE_SCREWDRIVER},
        {"GOLFCLUB", WEAPONTYPE_GOLFCLUB},
        {"NIGHTSTICK", WEAPONTYPE_NIGHTSTICK},
        {"KNIFE", WEAPONTYPE_KNIFE},
        {"Baseball bat", WEAPONTYPE_BASEBALLBAT},
        {"HAMMER", WEAPONTYPE_HAMMER},
        {"MACHETE", WEAPONTYPE_MACHETE},
        {"KATANA", WEAPONTYPE_KATANA},
        {"CHAINSAW", WEAPONTYPE_CHAINSAW},
        {"GRENADE", WEAPONTYPE_GRENADE},
        {"REMOTE GRENADES", WEAPONTYPE_DETONATOR_GRENADE},
        {"TEARGAS", WEAPONTYPE_TEARGAS},
        {"MOLOTOV", WEAPONTYPE_MOLOTOV},
        {"MISSILE", WEAPONTYPE_ROCKET},
        {"PYTHON", WEAPONTYPE_PYTHON},
        {"SHOTGUN", WEAPONTYPE_SHOTGUN},
        {"STUBBY SHOTGUN", WEAPONTYPE_STUBBY_SHOTGUN},
        {"TEC 9", WEAPONTYPE_TEC9},
        {"UZI", WEAPONTYPE_UZI},
        {"MP5", WEAPONTYPE_MP5},
        {"M4", WEAPONTYPE_M4},
        {"RUGER", WEAPONTYPE_RUGER},
        {"SNIPER RIFLE", WEAPONTYPE_SNIPERRIFLE},
        {"LASER SNIPER", WEAPONTYPE_LASERSCOPE},
        {"ROCKET LAUNCHER", WEAPONTYPE_ROCKETLAUNCHER},
        {"FLAMETHROWER", WEAPONTYPE_FLAMETHROWER},
        {"M60", WEAPONTYPE_M60},
        {"MINIGUN", WEAPONTYPE_MINIGUN},
        {"CAMERA", WEAPONTYPE_CAMERA}
    };
    int selectedWeaponIndex = 0;

    std::vector<std::pair<std::string, int>> vehicleList = {
        {"Landstalker", 130}, {"Idaho", 131}, {"Stinger", 132}, {"Linerunner", 133},
        {"Perennial", 134}, {"Sentinel", 135}, {"Rio", 136}, {"Firetruck", 137},
        {"Trashmaster", 138}, {"Stretch", 139}, {"Manana", 140}, {"Infernus", 141},
        {"Voodoo", 142}, {"Pony", 143}, {"Mule", 144}, {"Cheetah #1", 145},
        {"Ambulance", 146}, {"FBI Washington", 147}, {"Moonbeam", 148}, {"Esperanto", 149},
        {"Taxi", 150}, {"Washington", 151}, {"Bobcat", 152}, {"Mr Whoopee", 153},
        {"BF Injection", 154}, {"Hunter", 155}, {"Police", 156}, {"Enforcer", 157},
        {"Securicar", 158}, {"Banshee", 159}, {"Predator", 160}, {"Bus", 161},
        {"Rhino", 162}, {"Barracks OL", 163}, {"Cuban Hermes", 164}, {"Angel", 166},
        {"Coach", 167}, {"Cabbie", 168}, {"Stallion", 169}, {"Rumpo", 170},
        {"RC Bandit", 171}, {"Romero's Hearse", 172}, {"Packer", 173},
        {"Sentinel XS", 174}, {"Admiral", 175}, {"Squalo", 176}, {"Sea Sparrow", 177},
        {"Pizza boy", 178}, {"Gang Burrito", 179}, {"Speeder", 182}, {"Reefer", 183},
        {"Tropic", 184}, {"Flatbed", 185}, {"Yankee", 186}, {"Caddy", 187},
        {"Zebra Cab", 188}, {"Top Fun", 189}, {"Skimmer", 190}, {"PCJ 600", 191},
        {"Faggio", 192}, {"Freeway", 193}, {"RC Baron", 194}, {"RC Raider", 195},
        {"Glendale", 196}, {"Oceanic", 197}, {"Sanchez", 198}, {"Sparrow", 199},
        {"Patriot", 200}, {"Love Fist", 201}, {"Coast Guard", 202}, {"Dinghy", 203},
        {"Hermes", 204}, {"Sabre", 205}, {"Sabre Turbo", 206}, {"Phoenix", 207},
        {"Walton", 208}, {"Regina", 209}, {"Comet", 210}, {"Deluxo", 211},
        {"Burrito", 212}, {"Spand Express", 213}, {"Marquis", 214}, {"Baggage Handler", 215},
        {"Kaufman Cab", 216}, {"Maverick", 217}, {"VCN Maverick", 218}, {"Rancher", 219},
        {"FBI Rancher", 220}, {"Virgo", 221}, {"Greenwood", 222}, {"Cuban Jetmax", 223},
        {"Hotring Racer #1", 224}, {"Sandking", 225}, {"Blista Compact", 226},
        {"Police Maverick", 227}, {"Boxville", 228}, {"Benson", 229}, {"Mesa Grande", 230},
        {"RC Goblin", 231}, {"Hotring Racer #2", 232}, {"Hotring Racer #3", 233},
        {"Bloodring Banger #1", 234}, {"Bloodring Banger #2", 235}, {"Cheetah #2", 236}
    };
    int selectedVehicleIndex = 0;

    std::vector<std::pair<std::string, int>> weatherList = {
        {"Mostly Clear", 0}, {"Overcast", 1}, {"Rainy-Lightning", 2}, {"Foggy", 3},
        {"Clear Skies", 4}, {"Rainy", 5}, {"Dark Sky", 6}, {"Light Sky", 7},
        {"Partly Cloudy", 8}, {"Grey/Black Clouds", 9}, {"Waves touches the sky", 386},
        {"Big waves", 375}, {"Medium waves", 377}, {"Smaller waves", 379}, {"Dust on streets", 91}
    };
    int selectedWeatherIndex = 0;

    SimpleTrainer() {
        LoadConfig();      // read trainer.cfg
        InitMenu();
        Events::gameProcessEvent += [this] { HandleInput(); };
        Events::drawingEvent += [this] { if (menuOpen) DrawMenu(); };
    }

    void LoadConfig() {
        std::ifstream file("trainer.cfg");
        if (!file.is_open()) return;
        std::string line;
        while (std::getline(file, line)) {
            if (auto p = line.find('#'); p != std::string::npos) line.erase(p);
            line = Trim(line);
            if (line.empty()) continue;
            auto eq = line.find('=');
            if (eq == std::string::npos) continue;
            std::string key = Trim(line.substr(0, eq));
            std::string val = Trim(line.substr(eq + 1));
            int code = 0;
            try { code = std::stoi(val, nullptr, 0); }
            catch (...) { continue; }
            if (key == "ToggleMenuKey") keyToggleMenu = code;
            else if (key == "TrainerUp")     keyUp = code;
            else if (key == "TrainerDown")   keyDown = code;
            else if (key == "TrainerLeft")   keyLeft = code;
            else if (key == "TrainerRight")  keyRight = code;
            else if (key == "ConfirmKey")    keyConfirm = code;
        }
    }

    void InitMenu() {
        menuItems = {
            {"FULL HEALTH", []() { if (auto p = FindPlayerPed()) { p->m_fHealth = 9999.0f; CHud::SetHelpMessage("~g~9999 Health",1,0); } }},
            {"FULL ARMOUR", []() { if (auto p = FindPlayerPed()) { p->m_fArmour = 9999.0f; CHud::SetHelpMessage("~g~9999 Armour",1,0); } }},
            {"MAX STAMINA", []() { if (auto p = FindPlayerPed()) { p->m_fMaxStamina = p->m_fCurrentStamina = 9999.0f; CHud::SetHelpMessage("~g~Stamina Maxed",1,0); } }},
            {"SET TIME: DAY", []() { Command<eScriptCommands::COMMAND_SET_TIME_OF_DAY>(12,0); CHud::SetHelpMessage("~g~Time Set to Day",1,0); } },
            {"SET TIME: NIGHT", []() { Command<eScriptCommands::COMMAND_SET_TIME_OF_DAY>(22,0); CHud::SetHelpMessage("~g~Time Set to Night",1,0); } },
            {"CLEAR WANTED LEVEL", []() { if (auto p = FindPlayerPed()) { p->SetWantedLevelNoDrop(0); p->SetWantedLevel(0); CHud::SetHelpMessage("~g~Wanted Level Cleared",1,0); } }},
            {"MAX WANTED LEVEL", []() { if (auto p = FindPlayerPed()) { p->SetWantedLevelNoDrop(6); p->SetWantedLevel(6); CHud::SetHelpMessage("~r~Wanted Level Set to Max",1,0); } }},
            {"SPAWN VEHICLE", [this]() {
                int m = vehicleList[selectedVehicleIndex].second;
                CStreaming::RequestModel(m,0); CStreaming::LoadAllRequestedModels(0);
                auto pos = FindPlayerPed()->GetPosition();
                Command<eScriptCommands::COMMAND_CREATE_CAR>(m,
                    pos.x + cos(FindPlayerHeading()) * 5,
                    pos.y + sin(FindPlayerHeading()) * 5,
                    pos.z
                );
                CHud::SetHelpMessage(("~g~Spawned: " + vehicleList[selectedVehicleIndex].first).c_str(),1,0);
            }},
            {"SELECT WEAPON", [this]() { GiveWeaponToPlayer(); }},
            {"CHANGE WEATHER", [this]() {
                Command<eScriptCommands::COMMAND_FORCE_WEATHER_NOW>(weatherList[selectedWeatherIndex].second);
                CHud::SetHelpMessage(("~b~Weather: " + weatherList[selectedWeatherIndex].first).c_str(),1,0);
            }}
        };
    }

    void HandleInput() {
        if (GetAsyncKeyState(keyToggleMenu) & 1) menuOpen = !menuOpen;
        if (!menuOpen) return;
        if (GetAsyncKeyState(keyUp) & 1) selectedIndex = (selectedIndex - 1 + menuItems.size()) % menuItems.size();
        if (GetAsyncKeyState(keyDown) & 1) selectedIndex = (selectedIndex + 1) % menuItems.size();
        if (GetAsyncKeyState(keyConfirm) & 1) menuItems[selectedIndex].action();
        // Cycle slots
        if (selectedIndex == 7) {
            if (GetAsyncKeyState(keyLeft) & 1)  selectedVehicleIndex = (selectedVehicleIndex - 1 + vehicleList.size()) % vehicleList.size();
            if (GetAsyncKeyState(keyRight) & 1)  selectedVehicleIndex = (selectedVehicleIndex + 1) % vehicleList.size();
        }
        if (selectedIndex == 8) {
            if (GetAsyncKeyState(keyLeft) & 1)  selectedWeaponIndex = (selectedWeaponIndex - 1 + weaponList.size()) % weaponList.size();
            if (GetAsyncKeyState(keyRight) & 1)  selectedWeaponIndex = (selectedWeaponIndex + 1) % weaponList.size();
        }
        if (selectedIndex == 9) {
            if (GetAsyncKeyState(keyLeft) & 1)  selectedWeatherIndex = (selectedWeatherIndex - 1 + weatherList.size()) % weatherList.size();
            if (GetAsyncKeyState(keyRight) & 1)  selectedWeatherIndex = (selectedWeatherIndex + 1) % weatherList.size();
        }
    }

    void GiveWeaponToPlayer() {
        if (auto p = FindPlayerPed()) {
            auto w = weaponList[selectedWeaponIndex];
            p->GiveWeapon(w.second, 9999, true);
            p->SetCurrentWeapon(w.second);
            CHud::SetHelpMessage(("~g~" + w.first + " Given").c_str(), 1, 0);
        }
    }

    void DrawMenu() {
        float x = 80.0f, y = 50.0f;
        CFont::SetOrientation(ALIGN_LEFT);
        CFont::SetScale(1.0f, 1.0f);
        CFont::SetBackground(false);
        CFont::SetFontStyle(2);
        CFont::SetColor(CRGBA(0, 255, 255, 255));
        CFont::PrintString(x, y, "MEGAMIND Trainer v1.0");
        y += 50.0f;
        CFont::SetScale(0.8f, 0.8f);
        for (size_t i = 0; i < menuItems.size(); ++i) {
            CFont::SetColor(i == selectedIndex ? CRGBA(255, 255, 0, 255) : CRGBA(255, 255, 255, 255));
            std::string txt = (i == selectedIndex ? "> " : "  ") + menuItems[i].label;
            if (i == 7) txt += " [" + vehicleList[selectedVehicleIndex].first + "]";
            else if (i == 8) txt += " [" + weaponList[selectedWeaponIndex].first + "]";
            else if (i == 9) txt += " [" + weatherList[selectedWeatherIndex].first + "]";
            CFont::PrintString(x, y + i * 30, txt.c_str());
        }
    }
};

SimpleTrainer trainer;