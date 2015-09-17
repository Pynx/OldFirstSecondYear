----------------------------------------------|
Create a Sprite with a texture file :		  |
----------------------------------------------|

 1) First create these :
 
//  TGfxSprite * SPRITE_NAME;
//  TGfxTexture * TEXTURE_NAME;

2) Then load a texture in a var

//  TEXTURE_NAME = GfxTextureLoad("gfx/tileset.tga");

3) Choose from which texture you must take a part

//  SPRITE_NAME = GfxSpriteCreate(TEXTURE_NAME);

4) choose what you take from the texture

//  GfxSpriteSetCutout(SPRITE_NAME, PosX , PosY, SizeX, SizeY);

5) choose the scale

//  GfxSpriteSetScale(SPRITE_NAME, SizeX, SizeY);

6) Use this

//  GfxSpriteSetFilteringEnabled(SPRITE_NAME, false);

7) Set the position

//  GfxSpriteSetPosition(SPRITE_NAME, PosX, PosY);

OPTIONAL 8) Choose the position point position

//  GfxSpriteSetPivot(SPRITE_NAME, X, Y);





-----------------------------------|
Create an image without texture :  |
-----------------------------------|

First create it and create the future name :

//       TGfxImage * IMAGE_NAME;               It will be the texture name
//       TGfxSprite * SPRITE_NAME;
//       TGfxTexture* TEXTURE_NAME;

Then create the texture :
 
//       IMAGE_NAME = GfxImageCreate(1, 1);

Then modify data and set it to a color :

//	     unsigned int * DATA_NAME = GfxImageGetData(g_pPixel);
//	     *DATA_NAME = EGfxColor_Black;

Then Import the texture in the sprite :

//       TEXTURE_NAME = GfxTextureCreate(IMAGE_NAME);
//       SPRITE_NAME = GfxSpriteCreate(TEXTURE_NAME);

Then choose the scale

//       GfxSpriteSetScale(SPRITE_NAME, SizeX, SizeY);

Then choose color

//		 GfxSpriteSetColor(SPRITE_NAME, GfxColor(255, 255, 255, 255));