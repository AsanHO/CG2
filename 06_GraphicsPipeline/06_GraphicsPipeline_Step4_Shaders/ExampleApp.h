#pragma once

#include <algorithm>
#include <directxtk/SimpleMath.h>
#include <iostream>
#include <memory>
#include <vector>

#include "AppBase.h"

namespace hlab {

using DirectX::SimpleMath::Matrix;
using DirectX::SimpleMath::Vector2;
using DirectX::SimpleMath::Vector3;

// 이 예제에서 사용하는 Vertex 정의
struct Vertex {
    Vector3 position;
    Vector3 color;
    // TODO3: texture coordinates 추가
    Vector2 texcoord;
};

// 이 예제에서 ConstantBuffer로 보낼 데이터
struct ModelViewProjectionConstantBuffer {
    Matrix model;
    Matrix view;
    Matrix projection;
};

// 주의:
// For a constant buffer (BindFlags of D3D11_BUFFER_DESC set to
// D3D11_BIND_CONSTANT_BUFFER), you must set the ByteWidth value of
// D3D11_BUFFER_DESC in multiples of 16, and less than or equal to
// D3D11_REQ_CONSTANT_BUFFER_ELEMENT_COUNT.
// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11device-createbuffer

static_assert((sizeof(ModelViewProjectionConstantBuffer) % 16) == 0,
              "Constant Buffer size must be 16-byte aligned");

// TODO6: 픽셀 쉐이더로 보낼 ConstantBuffer
struct PixelShaderConstantBuffer {
    float xSplit; // 4bytes
    float padding[3]; // 4 * 3 = 12 bytes
};

class ExampleApp : public AppBase {
  public:
    ExampleApp();

    virtual bool Initialize() override;
    virtual void UpdateGUI() override;
    virtual void Update(float dt) override;
    virtual void Render() override;

  protected:
    ComPtr<ID3D11VertexShader> m_colorVertexShader;
    ComPtr<ID3D11PixelShader> m_colorPixelShader;
    ComPtr<ID3D11InputLayout> m_colorInputLayout;

    ComPtr<ID3D11Buffer> m_vertexBuffer;
    ComPtr<ID3D11Buffer> m_indexBuffer;
    ComPtr<ID3D11Buffer> m_constantBuffer;
    UINT m_indexCount;

    // TODO4: 픽셀쉐이더에서 사용할 Constant Buffer
    ComPtr<ID3D11Buffer> m_pixelShaderconstantBuffer;

    ModelViewProjectionConstantBuffer m_constantBufferData;

    // TODO5: 픽셀쉐이더에서 사용할 Constant Buffer Data
    PixelShaderConstantBuffer m_pixelShaderConstantBufferData;


    bool m_usePerspectiveProjection = true;
    Vector3 m_modelTranslation = Vector3(0.0f);
    Vector3 m_modelRotation = Vector3(0.0f);
    Vector3 m_modelScaling = Vector3(0.5f);
    Vector3 m_viewEyePos = {0.0f, 0.0f, -2.0f};
    Vector3 m_viewEyeDir = {0.0f, 0.0f, 1.0f};
    Vector3 m_viewUp = {0.0f, 1.0f, 0.0f};
    float m_projFovAngleY = 70.0f;
    float m_nearZ = 0.01f;
    float m_farZ = 100.0f;
    float m_aspect = AppBase::GetAspectRatio();
};
} // namespace hlab