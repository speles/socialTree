#include "TextureManager.h"

#include "MainWidget.h"

TextureManager::TextureManager()
{
}

uint TextureManager::getTexture(const QString& imagePath)
{
    for (size_t i = 0; i < textures_.size(); i++)
    {
        if (imagePath == textures_[i].path)
        {
            if (textures_[i].linksCount == 0)
                textures_[i].openglId = loadTexture(imagePath);
            textures_[i].linksCount++;
            return textures_[i].openglId;
        }
    }
    TextureInfo texture;
    texture.linksCount = 1;
    texture.openglId = loadTexture(imagePath);
    texture.path = imagePath;
    textures_.push_back(texture);
    return texture.openglId;
}

void TextureManager::freeTexture(uint id)
{
    for (size_t i = 0; i < textures_.size(); i++)
    {
        if ((id == textures_[i].openglId) && (textures_[i].linksCount > 0))
        {
            textures_[i].linksCount--;
            if (textures_[i].linksCount == 0)
                unloadTexture(id);
            break;
        }
    }
}

uint TextureManager::loadTexture(const QString& imagePath)
{
    QImage image(imagePath);
    if (!image.valid(1, 1))
        return 0;

    uint id = widget->bindTexture(image);

    // Set nearest filtering mode for texture minification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    // Set bilinear filtering mode for texture magnification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    return id;
}

void TextureManager::unloadTexture(uint id)
{
    widget->deleteTexture(id);
}
