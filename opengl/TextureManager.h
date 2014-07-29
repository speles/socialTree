#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <vector>

#include <QtGlobal>
#include <QString>
#include <QImage>

struct TextureInfo
{
    QString path;
    uint openglId;
    size_t linksCount;
};

class TextureManager
{
public:
    TextureManager();
    ~TextureManager();
    uint getTexture(const QString& imagePath);
    void freeTexture(uint id);
private:
    std::vector<TextureInfo> textures_;
    uint loadTexture(const QString& imagePath);
    void unloadTexture(uint id);
};

#endif // TEXTUREMANAGER_H
