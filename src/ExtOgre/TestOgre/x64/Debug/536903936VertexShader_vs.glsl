#if 0
	***	first_valid_detail_map_nm	0
	***	hlms_dual_paraboloid_mapping	0
	***	hlms_lights_spotparams	0
	***	PsoBlendblock	0
	***	glsl	635204550
	***	hlms_high_quality	0
	***	hlms_num_shadow_map_lights	0
	***	hlms_lights_directional	0
	***	PsoMacroblock	1
	***	hlms_shadowcaster	1
	***	alpha_test	0
	***	glsles	1070293233
	***	hw_gamma_write	1
	***	hlms_shadowcaster_directional	1
	***	hlms_pssm_splits	0
	***	signed_int_textures	1
	***	hlms_lights_spot	0
	***	GL_ARB_shading_language_420pack	1
	***	hlms_alphablend	0
	***	hlms_num_shadow_map_textures	0
	***	hlms_shadow_uses_depth_texture	1
	***	materials_per_buffer	256
	***	hw_gamma_read	1
	***	hlms_skeleton	0
	***	forward3d	0
	***	syntax	635204550
	***	hlms_lights_point	0
	***	metal	-1698855755
	***	GL_ARB_base_instance	1
	***	s_lights_directional_non_caster	0
	***	uv_diffuse	0
	***	GL3+	330
	***	hlms_lights_attenuation	0
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
			
				outVs_Position.z = outVs_Position.z + shadowConstantBias * passBuf.depthRange.y * passBuf.depthRange.y;
					
			

	/// hlms_uv_count will be 0 on shadow caster passes w/out alpha test




	



	
}
