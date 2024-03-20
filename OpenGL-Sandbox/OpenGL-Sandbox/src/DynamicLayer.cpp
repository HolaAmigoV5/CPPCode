#include "DynamicLayer.h"

using namespace GLCore;
using namespace GLCore::Utils;

struct Vec3
{
	float x, y, z;
};

struct Vec2
{
	float x, y;
};

struct Vec4
{
	float x, y, z, w;
};

// 定义顶点结构
struct Vertex
{
	Vec3 Position;
	Vec4 Color;
	Vec2 TexCoords;
	float TexID;
};

DynamicLayer::DynamicLayer()
	:m_CameraController(16.0f / 9.0f), m_QuadIB(0), m_QuadVA(0), m_QuadVB(0), m_JtTex(0), m_XmTex(0)
{

}

DynamicLayer::~DynamicLayer()
{

}

static GLuint LoadTexture(const std::string& path) {
	int w, h, bits;
	stbi_set_flip_vertically_on_load(1);
	auto* pixes = stbi_load(path.c_str(), &w, &h, &bits, STBI_rgb);
	GLuint textureID;
	glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixes);

	stbi_image_free(pixes);

	return textureID;
}

void DynamicLayer::OnAttach()
{
	EnableGLDebugging();

	// Init here

	m_Shader = std::unique_ptr<Shader>(Shader::FromGLSLTextFiles(
		"assets/shaders/glsl.vert.shader",
		"assets/shaders/glsl.frag.shader"
	));

	glUseProgram(m_Shader->GetRendererID());
	auto loc = glGetUniformLocation(m_Shader->GetRendererID(), "u_Textures");
	int samplers[2] = { 0, 1 };
	glUniform1iv(loc, 2, samplers);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	const size_t MaxQuadCount = 1000;					// 四边形个数
	const size_t MaxVertexCount = MaxQuadCount * 4;		// 顶点数
	const size_t MaxIndexCount = MaxQuadCount * 6;		// 索引数



	// 顶点位置(3)+颜色(4)+纹理坐标(2)+ 纹理索引(1)
	/*float vertices[] = {
		-1.5f, -0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,	0.18f, 0.6f, 0.96f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,	0.18f, 0.6f, 0.96f, 1.0f, 1.0f, 1.0f, 0.0f,
		-1.5f,  0.5f, 0.0f,	0.18f, 0.6f, 0.96f, 1.0f, 0.0f, 1.0f, 0.0f,

		0.5f, -0.5f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f, 0.0f, 0.0f, 1.0f,
		1.5f, -0.5f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f, 1.0f, 0.0f, 1.0f,
		1.5f,  0.5f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.5f,  0.5f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f, 0.0f, 1.0f, 1.0f
	};*/

	// 创建顶点数组
	glCreateVertexArrays(1, &m_QuadVA);
	glBindVertexArray(m_QuadVA);

	// 创建能存储1000个顶点的顶点缓冲区
	glCreateBuffers(1, &m_QuadVB);
	glBindBuffer(GL_ARRAY_BUFFER, m_QuadVB);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 1000, nullptr, GL_DYNAMIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

	// 设置顶点属性
	glEnableVertexArrayAttrib(m_QuadVA, 0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, Position));

	// 设置颜色属性
	glEnableVertexArrayAttrib(m_QuadVA, 1);
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (const void*)12);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Color));

	// 设置纹理坐标属性
	glEnableVertexArrayAttrib(m_QuadVA, 2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexCoords));

	// 设置纹理索引属性
	glEnableVertexArrayAttrib(m_QuadVA, 3);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexID));

	/*uint32_t indices[] = {
		0,1,2,2,3,0,
		4,5,6,6,7,4
	};*/


	// 动态生成索引
	//uint32_t indices[MaxIndexCount]{};
	std::unique_ptr<uint32_t[]> indices(new uint32_t[MaxIndexCount]);
	uint32_t offset = 0;
	for (size_t i = 0; i < MaxIndexCount; i += 6)
	{
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;

		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = 0 + offset;

		offset += 4;
	}

	m_JtTex = LoadTexture("assets/jt.png");
	m_XmTex = LoadTexture("assets/xm.png");


	// 创建索引缓冲区
	glCreateBuffers(1, &m_QuadIB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_QuadIB);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, MaxIndexCount * sizeof(uint32_t), indices.get(), GL_STATIC_DRAW);
}

void DynamicLayer::OnDetach()
{
	// Shutdown here
}

void DynamicLayer::OnEvent(Event& event)
{
	// Events here
	m_CameraController.OnEvent(event);
}

static void SetUniformMat4(uint32_t shader, const char* name, const glm::mat4& matrix) {
	int loc = glGetUniformLocation(shader, name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

static std::array<Vertex, 4> CreateQuad(float x, float y, float textureID) {
	float size = 1.0f;

	Vertex v0{};
	v0.Position = { x, y, 0.0f };
	v0.Color = { 0.18f, 0.6f, 0.96f, 1.0f };
	v0.TexCoords = { 0.0f, 0.0f };
	v0.TexID = textureID;

	Vertex v1{};
	v1.Position = { x+size, y, 0.0f };
	v1.Color = { 0.18f, 0.6f, 0.96f, 1.0f };
	v1.TexCoords = { 1.0f, 0.0f };
	v1.TexID = textureID;

	Vertex v2{};
	v2.Position = { x+size, y+size, 0.0f };
	v2.Color = { 0.18f, 0.6f, 0.96f, 1.0f };
	v2.TexCoords = { 1.0f, 1.0f };
	v2.TexID = textureID;

	Vertex v3{};
	v3.Position = { x, y+size, 0.0f };
	v3.Color = { 0.18f, 0.6f, 0.96f, 1.0f };
	v3.TexCoords = { 0.0f, 1.0f };
	v3.TexID = textureID;

	return { v0,v1,v2,v3 };
}

static Vertex* CreateQuad(Vertex* target, float x, float y, float textureID) {
	float size = 1.0f;

	target->Position = { x, y, 0.0f };
	target->Color = { 0.18f, 0.6f, 0.96f, 1.0f };
	target->TexCoords = { 0.0f, 0.0f };
	target->TexID = textureID;
	target++;

	target->Position = { x + size, y, 0.0f };
	target->Color = { 0.18f, 0.6f, 0.96f, 1.0f };
	target->TexCoords = { 1.0f, 0.0f };
	target->TexID = textureID;
	target++;

	target->Position = { x + size, y + size, 0.0f };
	target->Color = { 0.18f, 0.6f, 0.96f, 1.0f };
	target->TexCoords = { 1.0f, 1.0f };
	target->TexID = textureID;
	target++;

	target->Position = { x, y + size, 0.0f };
	target->Color = { 0.18f, 0.6f, 0.96f, 1.0f };
	target->TexCoords = { 0.0f, 1.0f };
	target->TexID = textureID;
	target++;

	return target;
}

void DynamicLayer::OnUpdate(Timestep ts)
{
	// Render here
	m_CameraController.OnUpdate(ts);

	// Set dynamic vertex buffer
	/*auto q0 = CreateQuad(m_QuadPosition[0], m_QuadPosition[1], 0.0f);
	auto q1 = CreateQuad(0.5f, -0.5f, 1.0f);
	Vertex vertices[8];
	memcpy(vertices, q0.data(), q0.size() * sizeof(Vertex));
	memcpy(vertices + q0.size(), q1.data(), q1.size() * sizeof(Vertex));*/

	uint32_t indexCount = 0;
	//std::array<Vertex, 1000> vertices{};
	std::unique_ptr<Vertex[]> vertices(new Vertex[1000]);

	Vertex* buffer = &vertices[0];
	for (float y = 0.0f; y < 5.0f; y++)
	{
		for (float x = 0.0f; x < 5.0f; x++)
		{
			buffer = CreateQuad(buffer, x, y, (int)(x + y) % 2 == 0 ? 0.0f : 1.0f);
			indexCount += 6;
		}
	}
	buffer = CreateQuad(buffer, m_QuadPosition[0], m_QuadPosition[1], 0.0f);
	indexCount += 6;

	glBindBuffer(GL_ARRAY_BUFFER, m_QuadVB);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 1000 * sizeof(Vertex), vertices.get());


	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(m_Shader->GetRendererID());

	glBindTextureUnit(0, m_JtTex);
	glBindTextureUnit(1, m_XmTex);

	auto& vp = m_CameraController.GetCamera().GetViewProjectionMatrix();

	SetUniformMat4(m_Shader->GetRendererID(), "u_ViewProj", vp);
	SetUniformMat4(m_Shader->GetRendererID(), "u_Transform", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));

	glBindVertexArray(m_QuadVA);
	//glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}

void DynamicLayer::OnImGuiRender()
{
	// ImGui here
	ImGui::Begin("Controls");
	ImGui::DragFloat2("Quad Position", m_QuadPosition, 0.1f);
	ImGui::End();
}