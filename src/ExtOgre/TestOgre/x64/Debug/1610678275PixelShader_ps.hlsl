#if 0
	***	hlms_uv_count0	2
	***	texture_bind0	2
	***	hlms_uv_count	1
	***	PsoBlendblock	1
	***	hlms_disable_stage	0
	***	texcoord	3
	***	fast_shader_build_hack	1
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
	***	hlms_alphablend	1
	***	num_textures	1
	***	hlms_shadow_uses_depth_texture	0
	***	hlms_tangent	0
	***	hlms_bones_per_vertex	0
	***	out_uv0_tex_unit	0
	***	materials_per_buffer	2
	***	hlms_skeleton	0
	***	out_uv0_source_uv	0
	***	syntax	-334286542
	***	metal	-1698855755
	***	diffuse_map	16
	***	hlms_render_depth_only	0
	***	hlms_qtangent	0
	***	out_uv_half_count0	2
	***	diffuse	0
	***	out_uv_half_count	1
	***	hlms_normal	0
	***	hlsl	-334286542
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

#define INLINE
#define outVs_Position outVs.gl_Position
#define OGRE_SampleLevel( tex, sampler, uv, lod ) tex.SampleLevel( sampler, uv.xy, lod )


// START UNIFORM DECLARATION



struct Material
{
	float4 alpha_test_threshold;
	float4 diffuse;

	uint4 indices0_3;
	uint4 indices4_7;

	
};

cbuffer materialArray : register(b1)
{
	Material materialArray[2];
};


//Uniforms that change per Item/Entity
cbuffer instance : register(b2)
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
	
		uint4 worldMaterialIdx[2];
	};



// END UNIFORM DECLARATION
struct PS_INPUT
{

	
		nointerpolation uint drawId	: TEXCOORD0;
		float4 colour	: TEXCOORD1;		
			float2 uv0	: TEXCOORD2;			

};





Texture2D textureMaps0 : register(t2);





SamplerState samplerState0 : register(s2);




	struct PS_OUTPUT
	{
		
			float4 colour0 : SV_Target0;
		
	};


PS_OUTPUT main( PS_INPUT inPs
)
{
	PS_OUTPUT outPs;
	

	Material material;


	uint materialId	= worldMaterialIdx[inPs.drawId].x;
	material = materialArray[materialId];


	




	//Load base image
	outPs.colour0 = textureMaps0.Sample( samplerState0, inPs.uv0.xy ).xxxy;





	outPs.colour0 *= inPs.colour ;
	


	



	


	return outPs;

}

