#include <simd/simd.h>

using namespace simd;

#pragma region Vertex {

    struct VertexData {

        float4 pos;
        float2 texture_coords;

    };

    struct TransformationData {

        float4x4 model_mtrx;
        float4x4 view_mtrx;
        float4x4 perspective_mtrx;

    };

#pragma endregion Vertex }