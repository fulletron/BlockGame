#if 0
	***	[Hash 0x010d84dd]	2
	***	[Hash 0x039b2d3e]	2
	***	[Hash 0x0b4678e4]	1
	***	[Hash 0x1c1faad4]	1
	***	[Hash 0x1f2c6e82]	0
	***	[Hash 0x2337351f]	3
	***	[Hash 0x24d6fb8f]	1
	***	[Hash 0x25dc73c6]	635204550
	***	[Hash 0x277ebc85]	0
	***	[Hash 0x2abbd528]	1
	***	[Hash 0x2dd3a2cd]	0
	***	[Hash 0x3192e903]	0
	***	[Hash 0x367aa843]	4
	***	[Hash 0x3b038020]	0
	***	[Hash 0x3fcb60f1]	1070293233
	***	[Hash 0x419acab7]	0
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
	***	[Hash 0x05ee2e06]	@insertpiece( NormalNonPremul)
	***	[Hash 0x1039ce45]	xy
	***	[Hash 0x21b2a83b]	@insertpiece( NormalNonPremul)
	***	[Hash 0x2984421d]	@insertpiece( NormalNonPremul)
	***	[Hash 0x2f520d11]	@insertpiece( NormalNonPremul)
	***	[Hash 0x31264294]	@insertpiece( NormalNonPremul)
	***	[Hash 0x5aeee477]	@insertpiece( NormalNonPremul)
	***	[Hash 0x8c81fe52]	@insertpiece( NormalNonPremul)
	***	[Hash 0x8cdbdef3]	@insertpiece( NormalNonPremul)
	***	[Hash 0x9665d4fe]	@insertpiece( NormalNonPremul)
	***	[Hash 0xa1396b98]	@insertpiece( NormalNonPremul)
	***	[Hash 0xbbc3e11f]	@insertpiece( NormalNonPremul)
	***	[Hash 0xc28e4029]	@insertpiece( NormalNonPremul)
	***	[Hash 0xcbb75443]	@insertpiece( NormalNonPremul)
	***	[Hash 0xcfbdae4d]	@insertpiece( NormalNonPremul)
	***	[Hash 0xd7b24f83]	@insertpiece( NormalNonPremul)
	***	[Hash 0xeeaa8ddc]	@insertpiece( NormalNonPremul)
	***	[Hash 0xf0941837]	xxxy
	DONE DUMPING PIECES
#endif

#define INLINE
#define outVs_Position outVs.gl_Position
#define OGRE_SampleLevel( tex, sampler, uv, lod ) tex.SampleLevel( sampler, uv.xy, lod )


// START UNIFORM DECLARATION



struct Material
{
	float4 alpha_test_threshold;
	float4 diffuse;

	uint4 indices0_3;
	uint4 indices4_7;

	
};

cbuffer materialArray : register(b1)
{
	Material materialArray[2];
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



// END UNIFORM DECLARATION
struct PS_INPUT
{

	
		nointerpolation uint drawId	: TEXCOORD0;
		float4 colour	: TEXCOORD1;		
			float2 uv0	: TEXCOORD2;			

};





Texture2D textureMaps0 : register(t2);





SamplerState samplerState0 : register(s2);




	struct PS_OUTPUT
	{
		
			float4 colour0 : SV_Target0;
		
	};


PS_OUTPUT main( PS_INPUT inPs
)
{
	PS_OUTPUT outPs;
	

	Material material;


	uint materialId	= worldMaterialIdx[inPs.drawId].x;
	material = materialArray[materialId];


	




	//Load base image
	outPs.colour0 = textureMaps0.Sample( samplerState0, inPs.uv0.xy ).xxxy;





	outPs.colour0 *= inPs.colour ;
	


	



	


	return outPs;

}

