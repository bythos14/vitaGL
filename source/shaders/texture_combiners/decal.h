/*
 * GL_DECAL
 */
const char *decal_src =
R"(float4 texenv1(sampler2D tex, float2 texcoord, float4 prepass, float4 fragcol, float4 texenvcol) {
	float4 res = tex2D(tex, texcoord);
	res.rgb = lerp(prepass.rgb, res.rgb, res.a);
	res.a = prepass.a;
	return res;
}
)";
