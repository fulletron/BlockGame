#if 0
	***	PsoBlendblock	1
	***	hlms_disable_stage	0
	***	glsl	635204550
	***	hlms_high_quality	0
	***	PsoMacroblock	4
	***	hlms_shadowcaster	1
	***	alpha_test	0
	***	glsles	1070293233
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



layout(std140) uniform;
#define FRAG_COLOR		0




layout(location = FRAG_COLOR, index = 0) out float outColour;


// START UNIFORM DECLARATION



// END UNIFORM DECLARATION



	
		
	


	
				
			#define outDepth gl_FragDepth
			
	



void main()
{
	
	
		
	
}

