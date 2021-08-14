#pragma once
class CSprite
{
public:
	CSprite();
	~CSprite();
private:
	HRESULT LoadTexture(const wstring& path , LPDIRECT3DDEVICE9 pGrahicDev, float x, float y);
public:
	static CSprite* CreateS(const wstring& path , LPDIRECT3DDEVICE9 pGrahicDev, float x, float y);
	const LPD3DXSPRITE& GetSprite() const;
	const LPDIRECT3DTEXTURE9& GetTex() const;
public:
	void Release();
private:
	LPD3DXSPRITE       objSprite;
	LPDIRECT3DTEXTURE9 objTexture;
public:
};

