#if 0
	***	[Hash 0x0790ba12]	0
	***	[Hash 0x08ffb38a]	0
	***	[Hash 0x123606a9]	0
	***	[Hash 0x1c1faad4]	0
	***	[Hash 0x24d6fb8f]	1
	***	[Hash 0x25dc73c6]	635204550
	***	[Hash 0x2dd3a2cd]	0
	***	[Hash 0x354d66c0]	0
	***	[Hash 0x359e8062]	0
	***	[Hash 0x367aa843]	1
	***	[Hash 0x378f5735]	1
	***	[Hash 0x3b038020]	0
	***	[Hash 0x3fcb60f1]	1070293233
	***	[Hash 0x4508a85c]	1
	***	[Hash 0x516d43dd]	1
	***	[Hash 0x57643473]	0
	***	[Hash 0x5a1459c4]	1
	***	[Hash 0x5cb4719a]	0
	***	[Hash 0x675280f4]	0
	***	[Hash 0x6962e498]	0
	***	[Hash 0x74824502]	1
	***	[Hash 0x8421366d]	2
	***	[Hash 0x86319b9f]	1
	***	[Hash 0x875516cf]	0
	***	[Hash 0x8a7512d7]	0
	***	[Hash 0x93f2327b]	-334286542
	***	[Hash 0x962aeb1a]	0
	***	[Hash 0x9abd84b5]	-1698855755
	***	[Hash 0xa461daa9]	0
	***	[Hash 0xa6ac776b]	0
	***	[Hash 0xb22f037a]	0
	***	[Hash 0xb967bb7b]	1
	***	[Hash 0xec133132]	-334286542
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
			
				outVs_Position.z = outVs_Position.z + shadowConstantBias * passBuf.depthRange.y * passBuf.depthRange.y;
					
			

	/// hlms_uv_count will be 0 on shadow caster passes w/out alpha test




	



	

	return outVs;
}
