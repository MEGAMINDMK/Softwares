#include "plugin.h"
#include "CSprite2d.h"
#include "game_vc/image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "game_vc/stb_image.h"
#include <windows.h>

using namespace plugin;

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
