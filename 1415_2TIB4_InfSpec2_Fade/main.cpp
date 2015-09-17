#include "flib.h"

TGfxImage * g_pBackground;
TGfxTexture * g_pTextureTest;
TGfxSprite * g_pSpritesBg;

TGfxImage * g_pPixel;
TGfxTexture* g_pTexturePixel;
TGfxSprite * g_pSpritePixel;

float g_fSizeX;
float g_fSizeY;
float g_fScreenSizeX;
float g_fScreenSizeY;
float g_fScale;
float g_fScale1;
float g_fScale2;
float g_fAlpha = 255;
float g_fSpeed = 0;


struct TScreenOverlayData
{

	enum EScreenOverlayState
	{
		EScreenOverlayState_AllBlack = 1,
		EScreenOverlayState_Fadingin,
		EScreenOverlayState_AllTranslucent,
		EScreenOverlayState_FadingOut
	};
	
	EScreenOverlayState m_eScreenOverlayState = EScreenOverlayState_AllBlack;
	
	void Input()
	{
		if (GfxInputIsJustPressed(EGfxInputID_KeySpace))
		{
			switch (m_eScreenOverlayState)
			{
			case EScreenOverlayState_AllBlack:
				ScreenOverlay_StartFadeIn(1);
				break;
			case EScreenOverlayState_Fadingin:
				ScreenOverlay_StartFadeOut(3);
				break;
			case EScreenOverlayState_AllTranslucent:
				ScreenOverlay_StartFadeOut(3);
				break;
			case EScreenOverlayState_FadingOut:
				ScreenOverlay_StartFadeIn(1);
				break;
			default:
				break;
			}
		}
	}
	void ScreenOverlay_Update()
	{
		if (m_eScreenOverlayState == EScreenOverlayState_Fadingin)
		{
			g_fAlpha -= 255 / g_fSpeed * GfxTimeFrameGetCurrentDurationInSeconds();
			if (g_fAlpha <= 0)
			{
				g_fAlpha = 0;
				m_eScreenOverlayState = EScreenOverlayState_AllTranslucent;
			}
		}
	
		if (m_eScreenOverlayState == EScreenOverlayState_FadingOut)
		{
			g_fAlpha += 255 / g_fSpeed * GfxTimeFrameGetCurrentDurationInSeconds();
			if (g_fAlpha >= 255)
			{
				g_fAlpha = 255;
				m_eScreenOverlayState = EScreenOverlayState_AllBlack;
			}
		}
	
	}
	
	void ScreenOverlay_StartFadeIn(float fDelay)
	{
		g_fSpeed = fDelay;
		m_eScreenOverlayState = EScreenOverlayState_Fadingin;
	}
	
	void ScreenOverlay_StartFadeOut(float fDelay)
	{
		g_fSpeed = fDelay;
		m_eScreenOverlayState = EScreenOverlayState_FadingOut;
	}

};

TScreenOverlayData g_tScreenOverlayData;

void Initialize()
{
	g_pBackground = GfxImageLoad("gfx/image.tga");
	g_pTextureTest = GfxTextureCreate(g_pBackground);
	g_pSpritesBg = GfxSpriteCreate(g_pTextureTest);


	g_fSizeX = float(GfxSpriteGetSizeX(g_pSpritesBg));
	g_fSizeY = float(GfxSpriteGetSizeY(g_pSpritesBg));

	g_pPixel = GfxImageCreate(1, 1);
	unsigned int * pData = GfxImageGetData(g_pPixel);
	*pData = EGfxColor_Black;
	g_pTexturePixel = GfxTextureCreate(g_pPixel);
	g_pSpritePixel = GfxSpriteCreate(g_pTexturePixel);
	GfxSpriteSetScale(g_pSpritePixel, g_fSizeX, g_fSizeY);

	g_fScreenSizeX = float((GfxGetDisplaySizeX()));
	g_fScreenSizeY = float((GfxGetDisplaySizeY()));
//--------------------------------------------------------------------------
	g_fScale1 = (g_fScreenSizeX / g_fSizeX);
	g_fScale2 = (g_fScreenSizeY / g_fSizeY);

	if (g_fScale1 < g_fScale2)
	{
		g_fScale = g_fScale1;
	}
	if (g_fScale1 > g_fScale2)
	{
		g_fScale = g_fScale2;
	}
//---------------------------------------------------------------------------
}

void Update()
{
	g_tScreenOverlayData.Input();



	g_tScreenOverlayData.ScreenOverlay_Update();
	
}

void Render()
{
	GfxClear(EGfxColor_Black);
	GfxSpriteSetScale(g_pSpritesBg, g_fScale, g_fScale);
	GfxSpriteSetColor(g_pSpritePixel, GfxColor(255, 255, 255, g_fAlpha));
	GfxSpriteRender(g_pSpritesBg);
	GfxSpriteRender(g_pSpritePixel);
}
void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
}


