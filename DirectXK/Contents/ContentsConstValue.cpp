#include "PreCompile.h"
#include "ContentsConstValue.h"

const float UContentsConstValue::TileSize = 64.0f; // 16 * 4
std::shared_ptr<UEngineTexture> UContentsConstValue::MapTex;
float4 UContentsConstValue::MapTexScale;