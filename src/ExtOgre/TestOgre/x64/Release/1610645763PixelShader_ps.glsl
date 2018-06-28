#if 0
	***	[Hash 0x1c1faad4]	1
	***	[Hash 0x1f2c6e82]	0
	***	[Hash 0x25dc73c6]	635204550
	***	[Hash 0x2dd3a2cd]	0
	***	[Hash 0x367aa843]	4
	***	[Hash 0x378f5735]	1
	***	[Hash 0x3b038020]	0
	***	[Hash 0x3fcb60f1]	1070293233
	***	[Hash 0x61e63948]	1
	***	[Hash 0x675280f4]	1
	***	[Hash 0x74824502]	1
	***	[Hash 0x7e693a86]	0
	***	[Hash 0x8421366d]	1024
	***	[Hash 0x875516cf]	0
	***	[Hash 0x93f2327b]	635204550
	***	[Hash 0x9abd84b5]	-1698855755
	***	[Hash 0xa1b3cd70]	1
	***	[Hash 0xafaf1bb3]	330
	***	[Hash 0xb967bb7b]	1
	***	[Hash 0xec133132]	-334286542
	***	[Hash 0xf742ff75]	1
	DONE DUMPING PROPERTIES
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




layout(location = FRAG_COLOR, index = 0) out float outColour;


// START UNIFORM DECLARATION



// END UNIFORM DECLARATION



	
		
	


	
				
			#define outDepth gl_FragDepth
			
	



void main()
{
	
	
		
	
}

