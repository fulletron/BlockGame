#if 0
	***	first_valid_detail_map_nm	0
	***	hlms_dual_paraboloid_mapping	0
	***	hlms_lights_spotparams	0
	***	PsoBlendblock	0
	***	hlms_disable_stage	0
	***	texcoord	0
	***	fast_shader_build_hack	1
	***	glsl	635204550
	***	hlms_high_quality	0
	***	hlms_num_shadow_map_lights	0
	***	hlms_lights_directional	0
	***	PsoMacroblock	1
	***	hlms_shadowcaster	1
	***	alpha_test	0
	***	glsles	1070293233
	***	hw_gamma_write	1
	***	hlms_pssm_splits	0
	***	signed_int_textures	1
	***	hlms_lights_spot	0
	***	hlms_alphablend	0
	***	hlms_num_shadow_map_textures	0
	***	hlms_shadow_uses_depth_texture	1
	***	materials_per_buffer	2
	***	hw_gamma_read	1
	***	hlms_skeleton	0
	***	hlms_pssm_splits_minus_one	-1
	***	forward3d	0
	***	syntax	-334286542
	***	NeedsMoreThan1BonePerVertex	-1
	***	hlms_lights_point	0
	***	metal	-1698855755
	***	s_lights_directional_non_caster	0
	***	uv_diffuse	0
	***	hlms_lights_attenuation	0
	***	hlms_render_depth_only	1
	***	use_planar_reflections	0
	***	hlsl	-334286542
	DONE DUMPING PROPERTIES
	DONE DUMPING PIECES
#endif

#define INLINE
#define outVs_Position outVs.gl_Position
#define OGRE_SampleLevel( tex, sampler, uv, lod ) tex.SampleLevel( sampler, uv.xy, lod )


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
	


// START UNIFORM DECLARATION


// END UNIFORM DECLARATION
struct PS_INPUT
{

    	
	
							
	

};





	
	
		#define outDepth outPs.colour0
	







	struct PS_OUTPUT
	{
		
			
			
				float colour0 : SV_Depth;
			
		
	};


void main( PS_INPUT inPs )
{

	

	
/// !alpha_test

	
		

	


}


