#if 0
	***	[Hash 0x010d84dd]	2
	***	[Hash 0x039b2d3e]	2
	***	[Hash 0x0b4678e4]	1
	***	[Hash 0x1c1faad4]	1
	***	[Hash 0x24d6fb8f]	1
	***	[Hash 0x25dc73c6]	635204550
	***	[Hash 0x277ebc85]	0
	***	[Hash 0x2abbd528]	1
	***	[Hash 0x2dd3a2cd]	0
	***	[Hash 0x3192e903]	0
	***	[Hash 0x367aa843]	2
	***	[Hash 0x3b038020]	0
	***	[Hash 0x3fcb60f1]	1070293233
	***	[Hash 0x419acab7]	0
	***	[Hash 0x461efaa9]	1
	***	[Hash 0x47e65364]	1
	***	[Hash 0x4a23671c]	4
	***	[Hash 0x4ecb6a4b]	0
	***	[Hash 0x675280f4]	1
	***	[Hash 0x6d28c426]	1
	***	[Hash 0x74824502]	0
	***	[Hash 0x79c337a5]	0
	***	[Hash 0x7e693a86]	0
	***	[Hash 0x816c6186]	0
	***	[Hash 0x8421366d]	2
	***	[Hash 0x875516cf]	0
	***	[Hash 0x928aef67]	0
	***	[Hash 0x93f2327b]	-334286542
	***	[Hash 0x9abd84b5]	-1698855755
	***	[Hash 0xa7fb3663]	16
	***	[Hash 0xb967bb7b]	0
	***	[Hash 0xc5ed03e2]	0
	***	[Hash 0xe0f2a51a]	2
	***	[Hash 0xe1f4c441]	0
	***	[Hash 0xe60012f8]	1
	***	[Hash 0xeb9401b3]	0
	***	[Hash 0xec133132]	-334286542
	***	[Hash 0xfcef2411]	1
	DONE DUMPING PROPERTIES
	***	[Hash 0x01fb3e75]	xy
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
