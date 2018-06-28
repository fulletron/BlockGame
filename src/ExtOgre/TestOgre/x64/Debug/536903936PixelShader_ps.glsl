#if 0
	***	first_valid_detail_map_nm	0
	***	hlms_dual_paraboloid_mapping	0
	***	hlms_lights_spotparams	0
	***	PsoBlendblock	0
	***	hlms_disable_stage	0
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
	***	hlms_pssm_splits_minus_one	-1
	***	forward3d	0
	***	syntax	635204550
	***	NeedsMoreThan1BonePerVertex	-1
	***	hlms_lights_point	0
	***	metal	-1698855755
	***	GL_ARB_base_instance	1
	***	s_lights_directional_non_caster	0
	***	uv_diffuse	0
	***	GL3+	330
	***	hlms_lights_attenuation	0
	***	hlms_render_depth_only	1
	***	use_planar_reflections	0
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







	#define UV_DIFFUSE(x) (x)
	#define UV_NORMAL(x) (x)
	#define UV_SPECULAR(x) (x)
	#define UV_ROUGHNESS(x) (x)
	#define UV_DETAIL_WEIGHT(x) (x)
	#define UV_DETAIL0(x) (x)
	#define UV_DETAIL1(x) (x)
	#define UV_DETAIL2(x) (x)
	#define UV_DETAIL3(x) (x)
	#define UV_DETAIL_NM0(x) (x)
	#define UV_DETAIL_NM1(x) (x)
	#define UV_DETAIL_NM2(x) (x)
	#define UV_DETAIL_NM3(x) (x)
	#define UV_EMISSIVE(x) (x)
	


layout(std140) uniform;
#define FRAG_COLOR		0










// START UNIFORM DECLARATION


// END UNIFORM DECLARATION






	
				
			#define outDepth gl_FragDepth
			
	





void main()
{
	

/// !alpha_test

	
		

	
}

