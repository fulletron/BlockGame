#if 0
	***	hlms_uv_count0	2
	***	texture_bind0	2
	***	hlms_uv_count	1
	***	PsoBlendblock	1
	***	fast_shader_build_hack	1
	***	glsl	635204550
	***	uv_diffuse0	0
	***	out_uv_count	1
	***	hlms_high_quality	0
	***	num_array_textures	0
	***	PsoMacroblock	2
	***	alpha_test	0
	***	glsles	1070293233
	***	out_uv0_out_uv	0
	***	hlms_identity_viewproj	1
	***	diffuse_map0	1
	***	OperationTypeV1	4
	***	out_uv0_texture_matrix	0
	***	hlms_alphablend	1
	***	num_textures	1
	***	hlms_shadow_uses_depth_texture	0
	***	hlms_tangent	0
	***	hlms_bones_per_vertex	0
	***	out_uv0_tex_unit	0
	***	materials_per_buffer	2
	***	hlms_skeleton	0
	***	out_uv0_source_uv	0
	***	syntax	-334286542
	***	metal	-1698855755
	***	diffuse_map	16
	***	hlms_render_depth_only	0
	***	hlms_qtangent	0
	***	out_uv_half_count0	2
	***	diffuse	0
	***	out_uv_half_count	1
	***	hlms_normal	0
	***	hlsl	-334286542
	***	hlms_colour	1
	DONE DUMPING PROPERTIES
	***	out_uv0_swizzle	xy
	DONE DUMPING PIECES
#endif

#define INLINE
#define outVs_Position outVs.gl_Position
#define OGRE_SampleLevel( tex, sampler, uv, lod ) tex.SampleLevel( sampler, uv.xy, lod )



float4x4 UNPACK_MAT4( Buffer<float4> matrixBuf, uint pixelIdx )
{
	float4 row1 = matrixBuf.Load( int((pixelIdx) << 2u) );
	float4 row2 = matrixBuf.Load( int(((pixelIdx) << 2u) + 1u) );
	float4 row3 = matrixBuf.Load( int(((pixelIdx) << 2u) + 2u) );
	float4 row4 = matrixBuf.Load( int(((pixelIdx) << 2u) + 3u) );

	return transpose( float4x4( row1, row2, row3, row4 ) );
}


// START UNIFORM DECLARATION

//Uniforms that change per pass
cbuffer PassBuffer : register(b0)
{
	struct PassData
	{
	
	//Vertex shader
	float4x4 viewProj[2];
				//Pixel Shader
	float4 invWindowSize;
	

	} passBuf;
};


//Uniforms that change per Item/Entity
cbuffer instance : register(b2)
{
	//.x =
	//Contains the material's start index.
    //
    //.y =
    //shadowConstantBias. Send the bias directly to avoid an
    //unnecessary indirection during the shadow mapping pass.
    //Must be loaded with uintBitsToFloat
    //
    //.z =
	//Contains 0 or 1 to index into passBuf.viewProj[]. Only used
	//if hlms_identity_viewproj_dynamic is set.
	
		uint4 worldMaterialIdx[2];
	};

Buffer<float4> worldMatBuf : register(t0);


// END UNIFORM DECLARATION

struct VS_INPUT
{
	float4 vertex : POSITION;
	float4 colour : COLOR0;

	float2 uv0 : TEXCOORD0;
	uint drawId : DRAWID;
	
};

struct PS_INPUT
{

	
		nointerpolation uint drawId	: TEXCOORD0;
		float4 colour	: TEXCOORD1;		
			float2 uv0	: TEXCOORD2;			

	float4 gl_Position : SV_Position;

};


	


PS_INPUT main( VS_INPUT input )
{
	PS_INPUT outVs;
	

	
		float4x4 worldViewProj;
		worldViewProj = UNPACK_MAT4( worldMatBuf, input.drawId );
	


	outVs.gl_Position = mul( input.vertex, worldViewProj );





	outVs.colour = input.colour;




	
		outVs.uv0.xy = input.uv0.xy;
	

	outVs.drawId = input.drawId;



	
	



	

	return outVs;
}
