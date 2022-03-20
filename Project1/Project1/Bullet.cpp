#include "Bullet.h"
#include "Game.hpp"

bool Bullet::IsBulletShot = false;

Bullet::Bullet(Game* game, bool scale) : Entity(game)
{
	mScale = scale;
	mActive = true;
}

void Bullet::setActive(bool flag)
{
	mActive = flag;
}

void Bullet::drawCurrent() const
{
	renderer->World = getTransform();
	renderer->NumFramesDirty++;
}

bool Bullet::isActive()
{
	return mActive;
}

void Bullet::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	if (mScale) XMStoreFloat4x4(&renderer->TexTransform, XMMatrixScaling(10.0f, 10.0f, 10.0f));
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()["Bullet"].get();
	renderer->Geo = game->getGeometries()["boxGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;

	game->getRenderItems().push_back(std::move(render));
}

unsigned int Bullet::getCategory() const
{
	return Category::Bullet;
}