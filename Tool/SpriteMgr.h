#pragma once
class CSprite;
class CSpriteMgr
{
	DECLARE_SINGLETON(CSpriteMgr)

private:
	CSpriteMgr();
	~CSpriteMgr();

public:
	const LPDIRECT3DTEXTURE9 GetTexInfo(const wstring& wstrObjectKey) const;
	const LPD3DXSPRITE GetSprite(const wstring& wstrObjectKey) const;
	const CSprite* GetSpriteInfo(const wstring& wstrObjectKey);
public:
	HRESULT LoadTexture(LPDIRECT3DDEVICE9 pGrahicDev,
		const wstring& wstrFilePath, /* 텍스처 경로 */
		const wstring& wstrObjectKey /* 오브젝트 키 */ , float x, float y
		);

private:
	void Release();
private:
	map<wstring, CSprite*>	m_mapTexture;
};

