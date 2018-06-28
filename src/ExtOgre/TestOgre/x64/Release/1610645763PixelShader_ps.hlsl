#if 0
	***	[Hash 0x1c1faad4]	1
	***	[Hash 0x1f2c6e82]	0
	***	[Hash 0x2337351f]	0
	***	[Hash 0x24d6fb8f]	1
	***	[Hash 0x25dc73c6]	635204550
	***	[Hash 0x2dd3a2cd]	0
	***	[Hash 0x367aa843]	4
	***	[Hash 0x378f5735]	1
	***	[Hash 0x3b038020]	0
	***	[Hash 0x3fcb60f1]	1070293233
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

