#if 0
	***	hlms_uv_count0	2
	***	texture_bind0	2
	***	hlms_uv_count	1
	***	PsoBlendblock	1
	***	hlms_disable_stage	0
	***	glsl	635204550
	***	uv_diffuse0	0
	***	out_uv_count	1
	***	hlms_high_quality	0
	***	num_array_textures	0
	***	PsoMacroblock	2
	***	alpha_test	0
	***	glsles	1070293233
	***	out_uv0_out_uv	0
	***	hlms_identity_viewproj	1
	***	diffuse_map0	1
	***	OperationTypeV1	4
	***	out_uv0_texture_matrix	0
	***	GL_ARB_shading_language_420pack	1
	***	hlms_alphablend	1
	***	num_textures	1
	***	hlms_shadow_uses_depth_texture	0
	***	hlms_tangent	0
	***	hlms_bones_per_vertex	0
	***	out_uv0_tex_unit	0
	***	materials_per_buffer	1024
	***	hlms_skeleton	0
	***	out_uv0_source_uv	0
	***	syntax	635204550
	***	metal	-1698855755
	***	GL_ARB_base_instance	1
	***	diffuse_map	16
	***	GL3+	330
	***	hlms_render_depth_only	0
	***	hlms_qtangent	0
	***	out_uv_half_count0	2
	***	diffuse	0
	***	out_uv_half_count	1
	***	hlms_normal	0
	***	hlsl	-334286542
	***	GL_ARB_texture_buffer_range	1
	***	hlms_colour	1
	DONE DUMPING PROPERTIES
	***	blend_mode_idx3	@insertpiece( NormalNonPremul)
	***	uv_diffuse_swizzle0	xy
	***	blend_mode_idx11	@insertpiece( NormalNonPremul)
	***	blend_mode_idx2	@insertpiece( NormalNonPremul)
	***	blend_mode_idx14	@insertpiece( NormalNonPremul)
	***	blend_mode_idx5	@insertpiece( NormalNonPremul)
	***	blend_mode_idx8	@insertpiece( NormalNonPremul)
	***	blend_mode_idx10	@insertpiece( NormalNonPremul)
	***	blend_mode_idx9	@insertpiece( NormalNonPremul)
	***	blend_mode_idx15	@insertpiece( NormalNonPremul)
	***	blend_mode_idx6	@insertpiece( NormalNonPremul)
	***	blend_mode_idx7	@insertpiece( NormalNonPremul)
	***	blend_mode_idx1	@insertpiece( NormalNonPremul)
	***	blend_mode_idx0	@insertpiece( NormalNonPremul)
	***	blend_mode_idx12	@insertpiece( NormalNonPremul)
	***	blend_mode_idx4	@insertpiece( NormalNonPremul)
	***	blend_mode_idx13	@insertpiece( NormalNonPremul)
	***	diffuse_map0_tex_swizzle	xxxy
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


