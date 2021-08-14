#include "stdafx.h"
#include "Sprite.h"

CSprite::CSprite()
{
}

CSprite::~CSprite()
{
	Release();
}

HRESULT CSprite::LoadTexture(const wstring& path, LPDIRECT3DDEVICE9 pGrahicDev, float x, float y)
{

	D3DXCreateSprite(CDeviceMgr::GetInstance()->GetDevice(), &objSprite);

	HRESULT hr;
	hr = D3DXCreateTextureFromFileEx(pGrahicDev, path.c_str(), x, y, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, NULL, NULL, NULL, &objTexture);

	//cout << path.c_str() << endl;
	FAILED_CHECK_MSG_RETURN(hr, L"D3DXCreateTextureFromFileEx Sprite Failed", E_FAIL);

	return S_OK;
}

CSprite* CSprite::CreateS(const wstring& path, LPDIRECT3DDEVICE9 pGrahicDev, float x, float y)
{

	CSprite* pInstance = new CSprite;

	if (FAILED(pInstance->LoadTexture(path, pGrahicDev, x, y)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;


}

const LPD3DXSPRITE & CSprite::GetSprite() const
{
	return objSprite;

}

const LPDIRECT3DTEXTURE9 & CSprite::GetTex() const
{
	return  objTexture;
}






void CSprite::Release()
{
		objSprite->Release();
		objTexture->Release();
}
