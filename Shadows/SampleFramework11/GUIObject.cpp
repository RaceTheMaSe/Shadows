//=================================================================================================
//
//  MJP's DX11 Sample Framework
//  http://mynameismjp.wordpress.com/
//
//  All code licensed under the MIT license
//
//=================================================================================================

#include "PCH.h"

#include "GUIObject.h"

#include "Utility.h"

namespace SampleFramework11
{

SpriteFont GUIObject::font;
ID3D11ShaderResourceViewPtr GUIObject::barTexture;
ID3D11ShaderResourceViewPtr GUIObject::knobTexture;

void GUIObject::InitGlobalResources(ID3D11Device* device)
{
    // Load the texures
    barTexture = LoadTexture(device, L"SampleFramework11\\Images\\SliderBar.png");
    knobTexture = LoadTexture(device, L"SampleFramework11\\Images\\SliderKnob.png");

    font.Initialize(L"Tahoma", 8.5f, SpriteFont::Regular, true, device);
}

}