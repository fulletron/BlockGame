#if 0
	***	[Hash 0x010d84dd]	2
	***	[Hash 0x039b2d3e]	2
	***	[Hash 0x0b4678e4]	1
	***	[Hash 0x1c1faad4]	1
	***	[Hash 0x1f2c6e82]	0
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
	***	[Hash 0x61e63948]	1
	***	[Hash 0x675280f4]	1
	***	[Hash 0x6d28c426]	1
	***	[Hash 0x74824502]	0
	***	[Hash 0x79c337a5]	0
	***	[Hash 0x7e693a86]	0
	***	[Hash 0x816c6186]	0
	***	[Hash 0x8421366d]	1024
	***	[Hash 0x875516cf]	0
	***	[Hash 0x928aef67]	0
	***	[Hash 0x93f2327b]	635204550
	***	[Hash 0x9abd84b5]	-1698855755
	***	[Hash 0xa1b3cd70]	1
	***	[Hash 0xa7fb3663]	16
	***	[Hash 0xafaf1bb3]	330
	***	[Hash 0xb967bb7b]	0
	***	[Hash 0xc5ed03e2]	0
	***	[Hash 0xe0f2a51a]	2
	***	[Hash 0xe1f4c441]	0
	***	[Hash 0xe60012f8]	1
	***	[Hash 0xeb9401b3]	0
	***	[Hash 0xec133132]	-334286542
	***	[Hash 0xf742ff75]	1
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


#version 330 core


    #extension GL_ARB_shading_language_420pack: require
    #define layout_constbuffer(x) layout( std140, x )

    #define bufferFetch texelFetch

#define float2 vec2
#define float3 vec3
#define float4 vec4

#define int2 ivec2
#define int3 ivec3
#define int4 ivec4

#define uint2 uvec2
#define uint3 uvec3
#define uint4 uvec4

#define float3x3 mat3
#define float4x4 mat4

#define mul( x, y ) ((x) * (y))
#define saturate(x) clamp( (x), 0.0, 1.0 )
#define lerp mix
#define INLINE

#define outVs_Position gl_Position
#define OGRE_SampleLevel( tex, sampler, uv, lod ) textureLod( tex, uv.xy, lod )



layout(std140) uniform;
#define FRAG_COLOR		0




layout(location = FRAG_COLOR, index = 0) out vec4 outColour;


// START UNIFORM DECLARATION



struct Material
{
	vec4 alpha_test_threshold;
	vec4 diffuse;

	uvec4 indices0_3;
	uvec4 indices4_7;

	
};

layout_constbuffer(binding = 1) uniform MaterialBuf
{
	Material m[1024];
} materialArray;


//Uniforms that change per Item/Entity
layout_constbuffer(binding = 2) uniform InstanceBuffer
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
	uvec4 worldMaterialIdx[4096];
} instance;



// END UNIFORM DECLARATION

in block
{

	
		flat uint drawId;
		vec4 colour;		
			vec2 uv0;			

} inPs;




uniform sampler2D	textureMaps[1];



Material material;

void main()
{
	

	uint materialId	= instance.worldMaterialIdx[inPs.drawId].x;
	material = materialArray.m[materialId];

	




	//Load base image
	outColour = texture( textureMaps[0], inPs.uv0.xy ).xxxy;





	outColour *= inPs.colour ;
	


	



	
}


