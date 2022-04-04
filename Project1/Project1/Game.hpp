#include "World.hpp"
#include "Player.h"
#include "StateStack.h"
#include "TextUtil.h"
#include <vector>

enum class RenderLayer : int
{
	Opaque = 0,
	AlphaTested,
	Count
};

//!
//! A Space Shooter game.
//! Author Jash Shah.
//!
//! Shoot enemy spaceships appearing from the desert sand.
//!
//! Controls:
//!   W, A, S, D to move the player spaceship.
//!   Left click to fire bullets.
//!
class Game : public D3DApp
{
public:
	Game(HINSTANCE hInstance);
	Game(const Game& rhs) = delete;
	Game& operator=(const Game& rhs) = delete;
	~Game();

	virtual bool Initialize()override;

	//! Render text on screen
	void RenderText(Font font, std::wstring text, XMFLOAT2 pos, XMFLOAT2 scale = XMFLOAT2(1.0f, 1.0f), std::vector<XMFLOAT4> color = { XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) }, XMFLOAT2 padding = XMFLOAT2(0.5f, 0.0f));
	
	//! this will store our arial font information
	Font mArialFont;

private:
	virtual void OnResize()override;
	virtual void Update(const GameTimer& gt)override;
	virtual void Draw(const GameTimer& gt)override;

	virtual void OnMouseDown(WPARAM btnState, int x, int y)override;
	virtual void OnMouseUp(WPARAM btnState, int x, int y)override;
	virtual void OnMouseMove(WPARAM btnState, int x, int y)override;
	virtual void OnAnyKeyDown();

	void OnKeyboardInput(const GameTimer& gt);
	void UpdateCamera(const GameTimer& gt);
	void AnimateMaterials(const GameTimer& gt);
	void UpdateObjectCBs(const GameTimer& gt);
	void UpdateMaterialCBs(const GameTimer& gt);
	void UpdateMainPassCB(const GameTimer& gt);

	//step5
	void LoadTextures();

	void BuildRootSignature();

	//step9
	void BuildDescriptorHeaps();

	void BuildShadersAndInputLayout();
	void BuildShapeGeometry();
	void BuildPSOs();
	void BuildFrameResources();
	void BuildMaterials();
	void BuildRenderItems();
	void DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems);
	void BuildFonts();

	std::array<const CD3DX12_STATIC_SAMPLER_DESC, 6> GetStaticSamplers();
private:

	std::vector<std::unique_ptr<FrameResource>> mFrameResources;
	FrameResource* mCurrFrameResource = nullptr;
	int mCurrFrameResourceIndex = 0;

	UINT mCbvSrvDescriptorSize = 0;

	ComPtr<ID3D12RootSignature> mRootSignature = nullptr;

	//step11
	ComPtr<ID3D12DescriptorHeap> mSrvDescriptorHeap = nullptr;

	std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;
	std::unordered_map<std::string, std::unique_ptr<Material>> mMaterials;

	//step7
	std::unordered_map<std::string, std::unique_ptr<Texture>> mTextures;

	std::unordered_map<std::string, ComPtr<ID3DBlob>> mShaders;

	std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;
	std::vector<D3D12_INPUT_ELEMENT_DESC> mTextInputLayout;
	
	// PSOs
	std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> mPSOs;


	// List of all the render items.
	std::vector<std::unique_ptr<RenderItem>> mAllRitems;

	PassConstants mMainPassCB;

	// Render items divided by PSO.
	std::vector<RenderItem*> mRitemLayer[(int)RenderLayer::Count];

	//XMFLOAT3 mEyePos = { 0.0f, 0.0f, -10.0f };
	//XMFLOAT4X4 mView = MathHelper::Identity4x4();
	//XMFLOAT4X4 mProj = MathHelper::Identity4x4();

	//float mTheta = 1.3f * XM_PI;
	//float mPhi = 0.4f * XM_PI;
	//float mRadius = 2.5f;

	POINT mLastMousePos;
	Camera mCamera;
	World mWorld;
	Player mPlayer;
	StateStack mStateStack;


	int maxNumTextCharacters = 1024; // the maximum number of characters you can render during a frame. This is just used to make sure
									// there is enough memory allocated for the text vertex buffer each frame

	static const int mFrameBufferCount = 1; // number of buffers we want, 2 for double buffering, 3 for tripple buffering
	ID3D12Resource* mTextVertexBuffer[mFrameBufferCount];
	D3D12_VERTEX_BUFFER_VIEW mTextVertexBufferView[mFrameBufferCount]; // a view for our text vertex buffer
	UINT8* mTextVBGPUAddress[mFrameBufferCount]; // this is a pointer to each of the text constant buffers
	UINT8 mSrvHandlSize;

	Font LoadFont(LPCWSTR filename, int windowWidth, int windowHeight); // load a font



public:
	std::vector<std::unique_ptr<RenderItem>>& getRenderItems() { return mAllRitems; }
	std::unordered_map<std::string, std::unique_ptr<Material>>& getMaterials() { return mMaterials; }
	std::unordered_map<std::string, std::unique_ptr<MeshGeometry>>& getGeometries() { return mGeometries; }
};
