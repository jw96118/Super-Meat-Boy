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
		const wstring& wstrFilePath, /* �ؽ�ó ��� */
		const wstring& wstrObjectKey /* ������Ʈ Ű */ , float x, float y
		);

private:
	void Release();
private:
	map<wstring, CSprite*>	m_mapTexture;
};

