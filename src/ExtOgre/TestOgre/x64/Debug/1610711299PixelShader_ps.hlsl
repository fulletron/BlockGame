#if 0
	***	PsoBlendblock	1
	***	hlms_disable_stage	0
	***	texcoord	0
	***	fast_shader_build_hack	1
	***	glsl	635204550
	***	hlms_high_quality	0
	***	PsoMacroblock	4
	***	hlms_shadowcaster	1
	***	alpha_test	0
	***	glsles	1070293233
	***	hlms_alphablend	1
	***	hlms_shadow_uses_depth_texture	1
	***	hlms_bones_per_vertex	0
	***	materials_per_buffer	2
	***	hlms_skeleton	0
	***	syntax	-334286542
	***	metal	-1698855755
	***	hlms_render_depth_only	1
	***	hlsl	-334286542
	DONE DUMPING PROPERTIES
	DONE DUMPING PIECES
#endif

#define INLINE
#define outVs_Position outVs.gl_Position
#define OGRE_SampleLevel( tex, sampler, uv, lod ) tex.SampleLevel( sampler, uv.xy, lod )


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

void main( PS_INPUT inPs
)
{
	PS_OUTPUT outPs;
	
	
		
	
	return outPs;
}

