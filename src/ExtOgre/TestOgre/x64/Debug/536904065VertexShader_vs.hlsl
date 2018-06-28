#if 0
	***	first_valid_detail_map_nm	0
	***	hlms_dual_paraboloid_mapping	0
	***	hlms_lights_spotparams	0
	***	PsoBlendblock	0
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
	***	forward3d	0
	***	syntax	-334286542
	***	hlms_lights_point	0
	***	metal	-1698855755
	***	s_lights_directional_non_caster	0
	***	uv_diffuse	0
	***	hlms_lights_attenuation	0
	***	hlms_render_depth_only	1
	***	hlsl	-334286542
	DONE DUMPING PROPERTIES
	DONE DUMPING PIECES
#endif

#define INLINE
#define outVs_Position outVs.gl_Position
#define OGRE_SampleLevel( tex, sampler, uv, lod ) tex.SampleLevel( sampler, uv.xy, lod )



float4x4 UNPACK_MAT4( Buffer<float4> matrixBuf, uint pixelIdx )
{
	float4 row1 = matrixBuf.Load( int((pixelIdx) << 2u) );
	float4 row2 = matrixBuf.Load( int(((pixelIdx) << 2u) + 1u) );
	float4 row3 = matrixBuf.Load( int(((pixelIdx) << 2u) + 2u) );
	float4 row4 = matrixBuf.Load( int(((pixelIdx) << 2u) + 3u) );

	return transpose( float4x4( row1, row2, row3, row4 ) );
}


float4x3 UNPACK_MAT4x3( Buffer<float4> matrixBuf, uint pixelIdx )
{
	float4 row1 = matrixBuf.Load( int((pixelIdx) << 2u) );
	float4 row2 = matrixBuf.Load( int(((pixelIdx) << 2u) + 1u) );
	float4 row3 = matrixBuf.Load( int(((pixelIdx) << 2u) + 2u) );

	return transpose( float3x4( row1, row2, row3 ) );
}


struct VS_INPUT
{
	float4 vertex : POSITION;








	uint drawId : DRAWID;
	
};

struct PS_INPUT
{

    	
	
							
	

	float4 gl_Position: SV_Position;

};

// START UNIFORM DECLARATION

struct ShadowReceiverData
{
	float4x4 texViewProj;
	float2 shadowDepthRange;
	float2 padding;
	float4 invShadowMapSize;
};

struct Light
{
	float4 position; //.w contains the objLightMask
	float3 diffuse;
	float3 specular;
};



//Uniforms that change per pass
cbuffer PassBuffer : register(b0)
{
	struct PassData
	{
	//Vertex shader (common to both receiver and casters)
	float4x4 viewProj;




	//Vertex shader
		float2 depthRange;


	


	
	} passBuf;
};


//Uniforms that change per Item/Entity
cbuffer InstanceBuffer : register(b2)
{
    //.x =
	//The lower 9 bits contain the material's start index.
    //The higher 23 bits contain the world matrix start index.
    //
    //.y =
    //shadowConstantBias. Send the bias directly to avoid an
    //unnecessary indirection during the shadow mapping pass.
    //Must be loaded with uintBitsToFloat
	
		uint4 worldMaterialIdx[2];
	};

Buffer<float4> worldMatBuf : register(t0);

// END UNIFORM DECLARATION










 //SkeletonTransform // !hlms_skeleton


    






PS_INPUT main( VS_INPUT input )
{
	PS_INPUT outVs;
	

	float4x3 worldMat = UNPACK_MAT4x3( worldMatBuf, input.drawId );
	

	float4 worldPos = float4( mul( input.vertex, worldMat ).xyz, 1.0f );




	
	
	//Lighting is in view space
	
	
	

	outVs.gl_Position = mul( worldPos, passBuf.viewProj );



	
	
				
			float shadowConstantBias = asfloat( worldMaterialIdx[input.drawId].y );
				
		
		
		
			//We can't make the depth buffer linear without Z out in the fragment shader;
			//however we can use a cheap approximation ("pseudo linear depth")
			//see http://www.yosoygames.com.ar/wp/2014/01/linear-depth-buffer-my-ass/
			
				outVs_Position.z = (outVs_Position.z + shadowConstantBias * passBuf.depthRange.y) * passBuf.depthRange.y * outVs_Position.w;
					
			

	/// hlms_uv_count will be 0 on shadow caster passes w/out alpha test




	



	

	return outVs;
}
