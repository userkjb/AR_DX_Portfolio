#include "PreCompile.h"
#include "ContentsConstValue.h"

const float UContentsConstValue::TileSize = 64.0f;
const float UContentsConstValue::AutoSizeValue = 2.0f;
std::shared_ptr<UEngineTexture> UContentsConstValue::MapTex;
float4 UContentsConstValue::MapTexScale;