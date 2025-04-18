#include "plugin_vc.h"
#include "game_vc/CPed.h"
#include "game_vc/CFont.h"
#include "game_vc/CPools.h"
#include "game_vc/CVector.h"
#include "game_vc/CCamera.h"
#include "game_vc/CSprite.h"
#include "CSprite2d.h"
#include "game_vc/image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "game_vc/stb_image.h"
#include <windows.h>

using namespace plugin;

// Global variable to keep track of the toggle state
bool g_bShowPedInfo = false;

CVector MultiplyPoint(const CMatrix& matrix, const CVector& point) {
    CVector result;
    result.x = point.x * matrix.right.x + point.y * matrix.up.x + point.z * matrix.at.x + matrix.pos.x;
    result.y = point.x * matrix.right.y + point.y * matrix.up.y + point.z * matrix.at.y + matrix.pos.y;
    result.z = point.x * matrix.right.z + point.y * matrix.up.z + point.z * matrix.at.z + matrix.pos.z;
    return result;
}

bool WorldToScreen(const CVector& worldPos, float& screenX, float& screenY) {
    RwV3d pos = { worldPos.x, worldPos.y, worldPos.z };
    RwV3d screen;
    float w, h;
    if (CSprite::CalcScreenCoors(pos, &screen, &w, &h, true)) {
        screenX = screen.x;
        screenY = screen.y;
        return true;
    }
    return false;
}

const char* GetWeaponName(int weaponId) {
    switch (weaponId) {
    case 0:  return "Unarmed";
    case 1:  return "Brass Knuckles";
    case 2:  return "Golf Club";
    case 3:  return "Nightstick";
    case 4:  return "Knife";
    case 5:  return "Baseball Bat";
    case 6:  return "Shovel";
    case 7:  return "Pool Cue";
    case 8:  return "Katana";
    case 9:  return "Chainsaw";
    case 10: return "Grenade";
    case 11: return "Molotov Cocktail";
    case 12: return "Colt 45";
    case 13: return "Silenced 45";
    case 14: return "Shotgun";
    case 15: return "Uzi";
    case 16: return "MP5";
    case 17: return "AK-47";
    case 18: return "Rocket Launcher";
    case 19: return "Flame Thrower";
    case 20: return "Minigun";
    case 21: return "Satchel Charge";
    case 22: return "Fire Extinguisher";
    case 23: return "Spray Can";
    case 24: return "Rocket Launcher (Ammo)";
    case 25: return "Tank Cannon";
    case 26: return "Flamethrower";
    case 27: return "Tank Cannon";
    case 28: return "Fire Extinguisher";
    case 29: return "Sawn-Off Shotgun";
    case 30: return "Auto Shotgun";
    case 31: return "Tec-9";
    case 32: return "Rocket Launcher";
    case 33: return "Molotov Cocktail";
    case 34: return "Flame Thrower";
    case 35: return "Knife";
    case 36: return "Sawn-Off Shotgun";
    case 37: return "Chain Saw";
    case 38: return "RPG Launcher";
    case 39: return "Shotgun";
    case 40: return "Flame Thrower";
    default: return "Unknown";
    }
}

const char* GetPedType(CPed* ped) {
    switch (ped->m_nModelIndex) {
    case 0:  return "Male Civilian";
    case 1:  return "Cop";
    case 2:  return "Male Gangster";
    case 3:  return "Female Gangster";
    case 4:  return "Male Thug";
    case 5:  return "Female Thug";
    case 6:  return "Biker";
    case 7:  return "Army";
    case 8:  return "FBI";
    case 9:  return "Swat";
    case 10: return "Paramedic";
    case 11: return "Firefighter";
    case 12: return "Police";
    case 13: return "Gang Member";
    case 14: return "Prostitute";
    case 15: return "Hobo";
    case 16: return "Helicopter Pilot";
    case 17: return "Boat Pilot";
    case 18: return "Plane Pilot";
    case 19: return "Gang Leader";
    case 20: return "Thug Leader";
    case 21: return "Mafia";
    case 22: return "Bodyguard";
    case 23: return "Scientist";
    case 24: return "Tourist";
    case 25: return "Weapon Dealer";
    case 26: return "FBI Special Agent";
    case 27: return "Military";
    case 28: return "Vigilante";
    case 29: return "Rival Gang";
    case 30: return "Rival Thug";
    case 31: return "Cop";
    case 32: return "Gangster";
    case 33: return "Thug";
    case 34: return "Biker";
    case 35: return "Army";
    case 36: return "FBI";
    case 37: return "Mafia Boss";
    case 38: return "Army General";
    case 39: return "Civilian Male";
    case 40: return "Civilian Female";
    case 41: return "Tourist Male";
    case 42: return "Tourist Female";
    case 43: return "Gangster Male";
    case 44: return "Gangster Female";
    case 45: return "Thug Male";
    case 46: return "Thug Female";
    case 47: return "Swat Officer";
    case 48: return "Swat Leader";
    case 49: return "Police Chief";
    case 50: return "FBI Agent";
    case 51: return "Prostitute Male";
    case 52: return "Prostitute Female";
    case 53: return "Vigilante Officer";
    case 54: return "Mafia Member";
    case 55: return "Mafia Boss";
    case 56: return "Mafia Underboss";
    case 57: return "Mafia Don";
    case 58: return "Scientist Male";
    case 59: return "Scientist Female";
    case 60: return "Fisherman";
    case 61: return "Taxi Driver";
    case 62: return "Bus Driver";
    case 63: return "Ambulance Driver";
    case 64: return "Firetruck Driver";
    case 65: return "Gang Leader Male";
    case 66: return "Gang Leader Female";
    case 67: return "Rival Gang Member";
    case 68: return "Rival Thug Male";
    case 69: return "Rival Thug Female";
    case 70: return "Biker Gang Member";
    case 71: return "Biker Gang Leader";
    case 72: return "Military Soldier";
    case 73: return "Military General";
    case 74: return "Police Officer";
    case 75: return "Military Pilot";
    case 76: return "Police Helicopter Pilot";
    case 77: return "Criminal";
    case 78: return "Mafia Muscle";
    case 79: return "Drug Dealer";
    case 80: return "Terrorist";
    case 81: return "Weapon Dealer Male";
    case 82: return "Weapon Dealer Female";
    case 83: return "Bodyguard Male";
    case 84: return "Bodyguard Female";
    case 85: return "Rival Police Officer";
    case 86: return "Rival FBI Agent";
    case 87: return "Rival Swat Officer";
    case 88: return "Rival Gang Boss";
    case 89: return "Rival Thug Leader";
    case 90: return "Criminal Male";
    case 91: return "Criminal Female";
    case 92: return "Biker Male";
    case 93: return "Biker Female";
    case 94: return "Pedestrian Male";
    case 95: return "Pedestrian Female";
    default: return "Unknown";
    }
}

// This function checks if F9 was pressed and toggles the state
void CheckToggleKey() {
    if (GetAsyncKeyState(VK_F9) & 0x8000) {  // If F9 key is pressed
        g_bShowPedInfo = !g_bShowPedInfo;    // Toggle the state
        while (GetAsyncKeyState(VK_F9) & 0x8000) {}  // Wait for key release
    }
}

void DrawPedInfo() {
    // Only run if toggle is enabled
    if (!g_bShowPedInfo)
        return;

    CPed* localPlayer = FindPlayerPed();
    if (!localPlayer || localPlayer->m_fHealth <= 0.0f)
        return;

    for (int i = 0; i < CPools::ms_pPedPool->m_nSize; i++) {
        CPed* ped = CPools::ms_pPedPool->GetAt(i);
        if (!ped || ped == localPlayer)
            continue;

        float distance = (ped->GetPosition() - localPlayer->GetPosition()).Magnitude();
        if (distance > 10.0f)
            continue;

        CVector headPos = ped->GetPosition();
        headPos.z += 1.0f;

        float screenX, screenY;
        if (WorldToScreen(headPos, screenX, screenY)) {
            CFont::SetOrientation(ALIGN_CENTER);
            CFont::SetScale(0.8f, 0.8f);
            CFont::SetBackground(false);

            char line[64];
            float lineHeight = 12.0f;

            if (ped->m_fHealth <= 0.0f) {
                CFont::SetColor(CRGBA(255, 0, 0, 255));  // Red
                sprintf(line, "WASTED");
                CFont::PrintString(screenX, screenY, line);
                continue;
            }

            // Display Health
            CFont::SetColor(CRGBA(238, 130, 238, 255));  // Pink for HP
            sprintf(line, "%.0f HP", ped->m_fHealth);
            CFont::PrintString(screenX, screenY, line); screenY += lineHeight;

            // Display Armor
            sprintf(line, "Armor: %.0f", ped->m_fArmour);
            CFont::SetColor(CRGBA(0, 128, 255, 220)); // Blue
            CFont::PrintString(screenX, screenY, line); screenY += lineHeight;

            // Display Distance
            CFont::SetColor(CRGBA(0, 255, 255, 255));  // Cyan for distance
            sprintf(line, "%.1fm", distance);
            CFont::PrintString(screenX, screenY, line); screenY += lineHeight;

            // Display Skin / Model
            CFont::SetColor(CRGBA(0, 255, 0, 255));  // Green for model
            sprintf(line, "Skin: %d", ped->m_nModelIndex);
            CFont::PrintString(screenX, screenY, line); screenY += lineHeight;

            // Display Weapon
            CFont::SetColor(CRGBA(255, 128, 0, 255));  // Orange for weapon
            sprintf(line, "Weapon: %s", GetWeaponName(ped->m_nCurrentWeapon));
            CFont::PrintString(screenX, screenY, line); screenY += lineHeight;

            // Display Vehicle status
            CFont::SetColor(CRGBA(128, 0, 255, 255));  // Purple for vehicle status
            sprintf(line, "Vehicle: %s", ped->m_pVehicle ? "Yes" : "No");
            CFont::PrintString(screenX, screenY, line); screenY += lineHeight;

            // Display Ped Type
            CFont::SetColor(CRGBA(255, 255, 0, 255)); // Yellow for Ped Type
            sprintf(line, "Type: %s", GetPedType(ped));
            CFont::PrintString(screenX, screenY, line); screenY += lineHeight;

            // Display Ped Money (from CPed.h, m_nPedMoney)
            CFont::SetColor(CRGBA(0, 255, 0, 255));  // Green-ish for money
            sprintf(line, "Cash: $%d", ped->m_nPedMoney);
            CFont::PrintString(screenX, screenY, line); screenY += lineHeight;
        }
    }
}

class PedESPPlugin {
public:
    PedESPPlugin() {
        // This event checks for the F9 key and toggles visibility
        Events::drawHudEvent += [] {
            CheckToggleKey();
            DrawPedInfo();
            };
    }
} pedESPPlugin;

class EmbeddedImagePlugin {
public:
    CSprite2d sprite;
    RwTexture* texture = nullptr;
    bool textureReady = false;

    // Position and scale for drawing
    float posX = 100.0f;
    float posY = 100.0f;
    float scale = 1.0f;

    // Variables to store the screen width and height
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);  // Screen width
    int screenHeight = GetSystemMetrics(SM_CYSCREEN); // Screen height

    void CreateTextureFromMemory() {
        int width, height, channels;
        unsigned char* pixels = stbi_load_from_memory(
            embeddedImageData,
            static_cast<int>(embeddedImageSize),
            &width, &height, &channels,
            STBI_rgb_alpha
        );
        if (!pixels) {
            OutputDebugStringA("Failed to decode embedded image\n");
            return;
        }

        RwRaster* raster = RwRasterCreate(
            width, height,
            32,
            rwRASTERTYPETEXTURE | rwRASTERFORMAT8888
        );
        if (!raster) {
            stbi_image_free(pixels);
            OutputDebugStringA("Failed to create raster\n");
            return;
        }

        void* dst = RwRasterLock(raster, 0, rwRASTERLOCKWRITE);
        if (dst) {
            memcpy(dst, pixels, width * height * 4);
            RwRasterUnlock(raster);
            texture = RwTextureCreate(raster);
            sprite.m_pTexture = texture;
            textureReady = true;
        }
        else {
            OutputDebugStringA("Failed to lock raster\n");
        }
        stbi_image_free(pixels);
    }

    EmbeddedImagePlugin() {
        Events::initGameEvent += [this] {
            // Adjust the position of the image to the bottom-right corner
            // Position it at the bottom-right corner of the screen
            posX = screenWidth - embeddedImageWidth * scale;  // Adjust for image width
            posY = screenHeight - embeddedImageHeight * scale;  // Adjust for image height

            // Create the texture from memory
            CreateTextureFromMemory();
            };

        Events::drawingEvent += [this] {
            if (!textureReady) return;

            // Compute draw rectangle based on image size and scale
            int w = static_cast<int>(embeddedImageWidth * scale);
            int h = static_cast<int>(embeddedImageHeight * scale);

            sprite.Draw(
                CRect(posX, posY, posX + w, posY + h),
                CRGBA(255, 255, 255, 255)
            );
            };

        Events::d3dLostEvent += [this] {
            if (texture) {
                sprite.Delete();
                textureReady = false;
                texture = nullptr;
            }
            };
    }
} embeddedImagePlugin;
