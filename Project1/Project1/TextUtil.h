#pragma once

#include <DirectXMath.h>
#include <d3d12.h>

#include <string>

//! Vertex describing each letter to be rendered on the screen
struct TextVertex {
	TextVertex(float r, float g, float b, float a, float u, float v, float tw, float th, float x, float y, float w, float h) 
		: color(r, g, b, a), texCoord(u, v, tw, th), pos(x, y, w, h) {}
	DirectX::XMFLOAT4 pos;
	DirectX::XMFLOAT4 texCoord;
	DirectX::XMFLOAT4 color;
};

//! A structure containing information about the text character
struct FontChar
{
    //! the unicode id
    int id;

    //! these need to be converted to texture coordinates 
    //! (where 0.0 is 0 and 1.0 is textureWidth of the font)
    //! u texture coordinate
    float u;
    //! v texture coordinate
    float v; 
    //! width of character on texture
    float twidth; 
    //! height of character on texture
    float theight; 

    //! width of character in screen coords
    float width; 
    //! height of character in screen coords
    float height; 

    //! these need to be normalized based on size of font
    //! offset from current cursor pos to left side of character
    float xoffset; 
    //! offset from top of line to top of character
    float yoffset; 
    //! how far to move to right for next character
    float xadvance; 
};

//! A structure containing information about the font padding
struct FontKerning
{
    //! the first character
    int firstid; 
    //! the second character
    int secondid; 
    //! the amount to add/subtract to second characters x
    float amount; 
};

//! A structure containing font information
struct Font
{
    //! name of the font
    std::wstring name; 
    std::wstring fontImage;
    //! size of font, lineheight and baseheight will be based on this as if this is a single unit (1.0)
    int size; 
    //! how far to move down to next line, will be normalized
    float lineHeight;
    //! height of all characters, will be normalized
    float baseHeight;
    //! width of the font texture
    int textureWidth; 
    //! height of the font texture
    int textureHeight; 
    //! number of characters in the font
    int numCharacters; 
    //! list of characters
    FontChar* CharList;
    //! the number of kernings
    int numKernings; 
    //! list to hold kerning values
    FontKerning* KerningsList; 
    //! the font texture resource
    ID3D12Resource* textureBuffer; 
    //! the font srv
    D3D12_GPU_DESCRIPTOR_HANDLE srvHandle; 

    //! these are how much the character is padded in the texture. We
    //! add padding to give sampling a little space so it does not accidentally
    //! padd the surrounding characters. We will need to subtract these paddings
    //! from the actual spacing between characters to remove the gaps you would otherwise see
    float leftpadding;
    float toppadding;
    float rightpadding;
    float bottompadding;

    //! this will return the amount of kerning we need to use for two characters
    float GetKerning(wchar_t first, wchar_t second)
    {
        for (int i = 0; i < numKernings; ++i)
        {
            if ((wchar_t)KerningsList[i].firstid == first && (wchar_t)KerningsList[i].secondid == second)
                return KerningsList[i].amount;
        }
        return 0.0f;
    }

    //! this will return a FontChar given a wide character
    FontChar* GetChar(wchar_t c)
    {
        for (int i = 0; i < numCharacters; ++i)
        {
            if (c == (wchar_t)CharList[i].id)
                return &CharList[i];
        }
        return nullptr;
    }
};