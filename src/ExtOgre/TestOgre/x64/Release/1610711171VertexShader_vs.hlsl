#if 0
	***	[Hash 0x1c1faad4]	1
	***	[Hash 0x24d6fb8f]	1
	***	[Hash 0x25dc73c6]	635204550
	***	[Hash 0x2dd3a2cd]	0
	***	[Hash 0x367aa843]	4
	***	[Hash 0x378f5735]	1
	***	[Hash 0x3b038020]	0
	***	[Hash 0x3fcb60f1]	1070293233
	***	[Hash 0x516d43dd]	1
	***	[Hash 0x675280f4]	1
	***	[Hash 0x74824502]	1
	***	[Hash 0x7e693a86]	0
	***	[Hash 0x8421366d]	2
	***	[Hash 0x875516cf]	0
	***	[Hash 0x93f2327b]	-334286542
	***	[Hash 0x9abd84b5]	-1698855755
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


// START UNIFORM DECLARATION

//Uniforms that change per pass
cbuffer PassBuffer : register(b0)
{
	struct PassData
	{
	
	//Vertex shader
	float4x4 viewProj[2];
			
				float4 depthRange;
				//Pixel Shader
	float4 invWindowSize;
	

	} passBuf;
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

Buffer<float4> worldMatBuf : register(t0);


// END UNIFORM DECLARATION

struct VS_INPUT
{
	float4 vertex : POSITION;


	uint drawId : DRAWID;
	
};

struct PS_INPUT
{

		
						

	float4 gl_Position : SV_Position;

};


	


PS_INPUT main( VS_INPUT input )
{
	PS_INPUT outVs;
	

	
		float4x4 worldViewProj;
		worldViewProj = UNPACK_MAT4( worldMatBuf, input.drawId );
	


	outVs.gl_Position = mul( input.vertex, worldViewProj );






	
	
				
			float shadowConstantBias = asfloat( worldMaterialIdx[input.drawId].y );
				
		
		
		
			//We can't make the depth buffer linear without Z out in the fragment shader;
			//however we can use a cheap approximation ("pseudo linear depth")
			//see http://www.yosoygames.com.ar/wp/2014/01/linear-depth-buffer-my-ass/
			
				outVs_Position.z = outVs_Position.z + shadowConstantBias * passBuf.depthRange.y * passBuf.depthRange.y;
					
			



	

	return outVs;
}
