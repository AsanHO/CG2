// Data Types (HLSL)
// https://learn.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-data-types

// Shader Constants (HLSL)
// https://learn.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-constants

// Register
// https://learn.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-variable-register

// float4, matrix
// https://learn.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-per-component-math

cbuffer ModelViewProjectionConstantBuffer : register(b0) { //constant Buffer : cpp 코드와 싱크를 맞춰야함
    matrix model; // matrix 대신에 float4x4를 사용할 수도 있습니다.
    matrix view;
    matrix projection;
};

// Semantics
// https://learn.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-semantics

struct VertexShaderInput {
    float3 pos : POSITION;
    float3 color : COLOR0;
    // TODO8: 텍스춰 좌표 추가!
    float2 texcoord : TEXCOORD;
};

struct PixelShaderInput { //vertexshader 의 리턴 값. Output
    float4 pos : SV_POSITION; // System Value
    float3 color : COLOR;
    // TODO9: 텍스춰 좌표 추가!
    float2 texcoord : TEXCOORD;
};

// Intrinsic Functions : gpu에서 사용가능한 함수들.
// https://learn.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-intrinsic-functions

PixelShaderInput main(VertexShaderInput input) {

    PixelShaderInput output;
    float4 pos = float4(input.pos, 1.0f);

    pos = mul(pos, model);
    pos = mul(pos, view);
    pos = mul(pos, projection);

    output.pos = pos;
    output.color = input.color;
    // DO: 텍스춰 좌표 추가!
    output.texcoord = input.texcoord;

    return output;
}
