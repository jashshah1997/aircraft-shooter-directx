#include "SpriteNode.h"
#include "Game.hpp"

SpriteNode::SpriteNode(Game* game, std::string name, bool scale) : Entity(game)
{
	mName = name;
	mScale = scale;
	mActive = true;
}

void SpriteNode::setActive(bool flag)
{
	mActive = flag;
}

void SpriteNode::drawCurrent() const
{
	renderer->World = getTransform();
	renderer->NumFramesDirty++;
}

bool SpriteNode::isActive()
{
	return mActive;
}

void SpriteNode::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	if (mScale) XMStoreFloat4x4(&renderer->TexTransform, XMMatrixScaling(10.0f, 10.0f, 10.0f));
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()[mName].get();
	renderer->Geo = game->getGeometries()["boxGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;

	game->getRenderItems().push_back(std::move(render));
}
