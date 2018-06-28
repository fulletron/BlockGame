#if 0
	***	PsoBlendblock	1
	***	glsl	635204550
	***	hlms_high_quality	0
	***	PsoMacroblock	4
	***	hlms_shadowcaster	1
	***	alpha_test	0
	***	glsles	1070293233
	***	hlms_shadowcaster_directional	1
	***	GL_ARB_shading_language_420pack	1
	***	hlms_alphablend	1
	***	hlms_shadow_uses_depth_texture	1
	***	hlms_bones_per_vertex	0
	***	materials_per_buffer	1024
	***	hlms_skeleton	0
	***	syntax	635204550
	***	metal	-1698855755
	***	GL_ARB_base_instance	1
	***	GL3+	330
	***	hlms_render_depth_only	1
	***	hlsl	-334286542
	***	GL_ARB_texture_buffer_range	1
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


in vec4 vertex;





	in uint drawId;






// START UNIFORM DECLARATION

//Uniforms that change per pass
layout_constbuffer(binding = 0) uniform PassBuffer
{
	
	//Vertex shader
	float4x4 viewProj[2];
			
				float4 depthRange;
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






	
	
		
			float shadowConstantBias = uintBitsToFloat( instance.worldMaterialIdx[drawId].y );
						
		
		
		
			//We can't make the depth buffer linear without Z out in the fragment shader;
			//however we can use a cheap approximation ("pseudo linear depth")
			//see http://www.yosoygames.com.ar/wp/2014/01/linear-depth-buffer-my-ass/
			
				outVs_Position.z = outVs_Position.z + shadowConstantBias * passBuf.depthRange.y * passBuf.depthRange.y;
					
			



	
}
