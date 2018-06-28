#if 0
	***	[Hash 0x0790ba12]	0
	***	[Hash 0x08ffb38a]	0
	***	[Hash 0x123606a9]	0
	***	[Hash 0x1c1faad4]	0
	***	[Hash 0x25dc73c6]	635204550
	***	[Hash 0x2dd3a2cd]	0
	***	[Hash 0x354d66c0]	0
	***	[Hash 0x359e8062]	0
	***	[Hash 0x367aa843]	1
	***	[Hash 0x378f5735]	1
	***	[Hash 0x3b038020]	0
	***	[Hash 0x3fcb60f1]	1070293233
	***	[Hash 0x4508a85c]	1
	***	[Hash 0x57643473]	0
	***	[Hash 0x5a1459c4]	1
	***	[Hash 0x5cb4719a]	0
	***	[Hash 0x61e63948]	1
	***	[Hash 0x675280f4]	0
	***	[Hash 0x6962e498]	0
	***	[Hash 0x74824502]	1
	***	[Hash 0x8421366d]	256
	***	[Hash 0x86319b9f]	1
	***	[Hash 0x875516cf]	0
	***	[Hash 0x8a7512d7]	0
	***	[Hash 0x93f2327b]	635204550
	***	[Hash 0x962aeb1a]	0
	***	[Hash 0x9abd84b5]	-1698855755
	***	[Hash 0xa1b3cd70]	1
	***	[Hash 0xa461daa9]	0
	***	[Hash 0xa6ac776b]	0
	***	[Hash 0xafaf1bb3]	330
	***	[Hash 0xb22f037a]	0
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


mat3x4 UNPACK_MAT3x4( samplerBuffer matrixBuf, uint pixelIdx )
{
	vec4 row0 = texelFetch( matrixBuf, int((pixelIdx) << 2u) );
	vec4 row1 = texelFetch( matrixBuf, int(((pixelIdx) << 2u) + 1u) );
	vec4 row2 = texelFetch( matrixBuf, int(((pixelIdx) << 2u) + 2u) );
	return mat3x4( row0, row1, row2 );
}


in vec4 vertex;











	in uint drawId;






// START UNIFORM DECLARATION

struct ShadowReceiverData
{
    mat4 texViewProj;
	vec2 shadowDepthRange;
	vec4 invShadowMapSize;
};

struct Light
{
	vec4 position; //.w contains the objLightMask
	vec3 diffuse;
	vec3 specular;
};



//Uniforms that change per pass
layout_constbuffer(binding = 0) uniform PassBuffer
{
	//Vertex shader (common to both receiver and casters)
	mat4 viewProj;




	//Vertex shader
		vec2 depthRange;


	


	
} passBuf;


//Uniforms that change per Item/Entity
layout_constbuffer(binding = 2) uniform InstanceBuffer
{
    //.x =
	//The lower 9 bits contain the material's start index.
    //The higher 23 bits contain the world matrix start index.
    //
    //.y =
    //shadowConstantBias. Send the bias directly to avoid an
    //unnecessary indirection during the shadow mapping pass.
    //Must be loaded with uintBitsToFloat
    //
    //.z =
    //lightMask. Ogre must have been compiled with OGRE_NO_FINE_LIGHT_MASK_GRANULARITY
    uvec4 worldMaterialIdx[4096];
} instance;

/*layout(binding = 0) */uniform samplerBuffer worldMatBuf;


// END UNIFORM DECLARATION










//SkeletonTransform // !hlms_skeleton


    






void main()
{


    
    

    
    mat3x4 worldMat = UNPACK_MAT3x4( worldMatBuf, drawId );
	
    
	vec4 worldPos = vec4( (vertex * worldMat).xyz, 1.0f );




	
	
	//Lighting is in view space
	
	
	

	gl_Position = worldPos * passBuf.viewProj;



	
	
		
			float shadowConstantBias = uintBitsToFloat( instance.worldMaterialIdx[drawId].y );
						
		
		
		
			//We can't make the depth buffer linear without Z out in the fragment shader;
			//however we can use a cheap approximation ("pseudo linear depth")
			//see http://www.yosoygames.com.ar/wp/2014/01/linear-depth-buffer-my-ass/
			
				outVs_Position.z = (outVs_Position.z + shadowConstantBias * passBuf.depthRange.y) * passBuf.depthRange.y * outVs_Position.w;
					
			

	/// hlms_uv_count will be 0 on shadow caster passes w/out alpha test




	



	
}
