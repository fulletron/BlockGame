#if 0
	***	[Hash 0x010d84dd]	2
	***	[Hash 0x039b2d3e]	2
	***	[Hash 0x0b4678e4]	1
	***	[Hash 0x1c1faad4]	1
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
	***	[Hash 0x01fb3e75]	xy
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



out gl_PerVertex
{
	vec4 gl_Position;

};

layout(std140) uniform;


mat4 UNPACK_MAT4( samplerBuffer matrixBuf, uint pixelIdx )
{
	vec4 row0 = texelFetch( matrixBuf, int((pixelIdx) << 2u) );
	vec4 row1 = texelFetch( matrixBuf, int(((pixelIdx) << 2u) + 1u) );
	vec4 row2 = texelFetch( matrixBuf, int(((pixelIdx) << 2u) + 2u) );
	vec4 row3 = texelFetch( matrixBuf, int(((pixelIdx) << 2u) + 3u) );
    return mat4( row0, row1, row2, row3 );
}


in vec4 vertex;
in vec4 colour;


in vec2 uv0;


	in uint drawId;





out block
{

	
		flat uint drawId;
		vec4 colour;		
			vec2 uv0;			

} outVs;


// START UNIFORM DECLARATION

//Uniforms that change per pass
layout_constbuffer(binding = 0) uniform PassBuffer
{
	
	//Vertex shader
	float4x4 viewProj[2];
				//Pixel Shader
	float4 invWindowSize;
	

} passBuf;


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

/*layout(binding = 0) */uniform samplerBuffer worldMatBuf;



// END UNIFORM DECLARATION


	


void main()
{

    
	
	
		mat4 worldViewProj;
		worldViewProj = UNPACK_MAT4( worldMatBuf, drawId );
	


	gl_Position = vertex * worldViewProj;





	outVs.colour = colour;




	
		outVs.uv0.xy = uv0.xy;
	

	outVs.drawId = drawId;



	
	



	
}
