#ifdef BU_GL_H
  #error This header file should never need to be included twice!
#endif
#define BU_GL_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

namespace bu
{

	struct Face
	{
	  glm::vec3 pa;
	  glm::vec3 pb;
	  glm::vec3 pc;

	  glm::vec2 tca;
	  glm::vec2 tcb;
	  glm::vec2 tcc;

	  glm::vec3 na;
	  glm::vec3 nb;
	  glm::vec3 nc;

	  glm::vec2 lmca;
	  glm::vec2 lmcb;
	  glm::vec2 lmcc;
	};

	template <typename T>
	void splitStringWhitespace(const std::string& input,
	  std::vector<std::string>& output)
	{
	  std::string curr;

	  output.clear();

	  for(size_t i = 0; i < input.length(); i++)
	  {
		if(input.at(i) == ' ' ||
		  input.at(i) == '\r' ||
		  input.at(i) == '\n' ||
		  input.at(i) == '\t')
		{
		  if(curr.length() > 0)
		  {
			output.push_back(curr);
			curr = "";
		  }
		}
		else
		{
		  curr += input.at(i);
		}
	  }

	  if(curr.length() > 0)
	  {
		output.push_back(curr);
	  }
	}

	template <typename T>
	void splitString(const std::string& input, char splitter,
	  std::vector<std::string>& output)
	{
	  std::string curr;

	  output.clear();

	  for(size_t i = 0; i < input.length(); i++)
	  {
		if(input.at(i) == splitter)
		{
		  output.push_back(curr);
		  curr = "";
		}
		else
		{
		  curr += input.at(i);
		}
	  }

	  if(curr.length() > 0)
	  {
		output.push_back(curr);
	  }
	}

	template <typename T>
	GLuint loadModel(const std::string& path, size_t *vertexCount,
	  std::string& currentLine)
	{
	  std::vector<glm::vec3> positions;
	  std::vector<glm::vec2> tcs;
	  std::vector<glm::vec3> normals;
	  std::vector<glm::vec2> lmcs;
	  std::vector<Face> faces;

	  std::ifstream file(path.c_str());

	  if(!file.is_open())
	  {
		throw std::exception();
	  }
	  std::vector<std::string> tokens;
	  while(!file.eof())
	  {
		std::getline(file, currentLine);
		if(currentLine.length() < 1) continue;
		//std::cout << "Line [" << currentLine << "]" << std::endl;

		splitStringWhitespace<int>(currentLine, tokens);
		if(tokens.size() < 1) continue;

		if(tokens.at(0) == "v")
		{
		  glm::vec3 p(atof(tokens.at(1).c_str()),
			atof(tokens.at(2).c_str()),
			atof(tokens.at(3).c_str()));

		  positions.push_back(p);
		}
		else if(tokens.at(0) == "vt")
		{
		  glm::vec2 tc(atof(tokens.at(1).c_str()),
			1.0f - atof(tokens.at(2).c_str()));

		  tcs.push_back(tc);
		}
		else if(tokens.at(0) == "vn")
		{
		  glm::vec3 n(atof(tokens.at(1).c_str()),
			atof(tokens.at(2).c_str()),
			atof(tokens.at(3).c_str()));

		  normals.push_back(n);
		}
		else if(tokens.at(0) == "f")
		{
		  if(tokens.size() < 4) continue;

		  Face f;
		  std::vector<std::string> sub;
		  splitString<int>(tokens.at(1), '/', sub);
		  if(sub.size() >= 1) f.pa = positions.at(atoi(sub.at(0).c_str()) - 1);
		  if(sub.size() >= 2) f.tca = tcs.at(atoi(sub.at(1).c_str()) - 1);
		  if(sub.size() >= 3) f.na = normals.at(atoi(sub.at(2).c_str()) - 1);
		  if(sub.size() >= 4) f.lmca = lmcs.at(atoi(sub.at(3).c_str()) - 1);

		  splitString<int>(tokens.at(2), '/', sub);
		  if(sub.size() >= 1) f.pb = positions.at(atoi(sub.at(0).c_str()) - 1);
		  if(sub.size() >= 2) f.tcb = tcs.at(atoi(sub.at(1).c_str()) - 1);
		  if(sub.size() >= 3) f.nb = normals.at(atoi(sub.at(2).c_str()) - 1);
		  if(sub.size() >= 4) f.lmcb = lmcs.at(atoi(sub.at(3).c_str()) - 1);

		  splitString<int>(tokens.at(3), '/', sub);
		  if(sub.size() >= 1) f.pc = positions.at(atoi(sub.at(0).c_str()) - 1);
		  if(sub.size() >= 2) f.tcc = tcs.at(atoi(sub.at(1).c_str()) - 1);
		  if(sub.size() >= 3) f.nc = normals.at(atoi(sub.at(2).c_str()) - 1);
		  if(sub.size() >= 4) f.lmcc = lmcs.at(atoi(sub.at(3).c_str()) - 1);

		  faces.push_back(f);
		  if(tokens.size() < 5) continue;

		  Face fq;
		  fq.pa = f.pc;
		  fq.tca = f.tcc;
		  fq.na = f.nc;
		  fq.lmca = f.lmcc;

		  splitString<int>(tokens.at(4), '/', sub);
		  if(sub.size() >= 1) fq.pb = positions.at(atoi(sub.at(0).c_str()) - 1);
		  if(sub.size() >= 2) fq.tcb = tcs.at(atoi(sub.at(1).c_str()) - 1);
		  if(sub.size() >= 3) fq.nb = normals.at(atoi(sub.at(2).c_str()) - 1);
		  if(sub.size() >= 4) fq.lmcb = lmcs.at(atoi(sub.at(3).c_str()) - 1);

		  fq.pc = f.pa;
		  fq.tcc = f.tca;
		  fq.nc = f.na;
		  fq.lmcc = f.lmca;

		  faces.push_back(fq);
		}
	  }

	  GLuint vboId = 0;
	  GLuint vaoId = 0;

	  glGenVertexArrays(1, &vaoId);

	  if(!vaoId)
	  {
		throw std::exception();
	  }

	  if(positions.size() < 1)
	  {
		currentLine = "No positions specified";
		throw std::exception();
	  }

	  *vertexCount = faces.size() * 3;
	  std::vector<float> vPos;
	  {
		std::vector<float> b;

		for(std::vector<Face>::iterator fit = faces.begin();
		  fit != faces.end(); fit++)
		{
		  b.push_back(fit->pa.x); b.push_back(fit->pa.y); b.push_back(fit->pa.z);
		  b.push_back(fit->pb.x); b.push_back(fit->pb.y); b.push_back(fit->pb.z);
		  b.push_back(fit->pc.x); b.push_back(fit->pc.y); b.push_back(fit->pc.z);
		}

		glGenBuffers(1, &vboId);

		if(!vboId)
		{
		  throw std::exception();
		}

		glBindBuffer(GL_ARRAY_BUFFER, vboId);

		glBufferData(GL_ARRAY_BUFFER, sizeof(b.at(0)) * b.size(), &b.at(0),
		  GL_STATIC_DRAW);

		glBindVertexArray(vaoId);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);

		glDeleteBuffers(1, &vboId);
		vPos = b;
	  }

	  std::vector<float> tPos;
	  if(tcs.size() > 0)
	  {
		std::vector<float> b;

		for(std::vector<Face>::iterator fit = faces.begin();
		  fit != faces.end(); fit++)
		{
		  b.push_back(fit->tca.x); b.push_back(fit->tca.y);
		  b.push_back(fit->tcb.x); b.push_back(fit->tcb.y);
		  b.push_back(fit->tcc.x); b.push_back(fit->tcc.y);
		}

		glGenBuffers(1, &vboId);

		if(!vboId)
		{
		  throw std::exception();
		}

		glBindBuffer(GL_ARRAY_BUFFER, vboId);

		glBufferData(GL_ARRAY_BUFFER, sizeof(b.at(0)) * b.size(), &b.at(0),
		  GL_STATIC_DRAW);

		glBindVertexArray(vaoId);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
		glEnableVertexAttribArray(1);
		glBindVertexArray(0);

		glDeleteBuffers(1, &vboId);
		tPos = b;
	  }

	  std::vector<float> nPos;
	  if(normals.size() > 0)
	  {
		std::vector<float> b;

		for(std::vector<Face>::iterator fit = faces.begin();
		  fit != faces.end(); fit++)
		{
		  b.push_back(fit->na.x); b.push_back(fit->na.y); b.push_back(fit->na.z);
		  b.push_back(fit->nb.x); b.push_back(fit->nb.y); b.push_back(fit->nb.z);
		  b.push_back(fit->nc.x); b.push_back(fit->nc.y); b.push_back(fit->nc.z);
		}

		glGenBuffers(1, &vboId);

		if(!vboId)
		{
		  throw std::exception();
		}

		glBindBuffer(GL_ARRAY_BUFFER, vboId);

		glBufferData(GL_ARRAY_BUFFER, sizeof(b.at(0)) * b.size(), &b.at(0),
		  GL_STATIC_DRAW);

		glBindVertexArray(vaoId);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
		glEnableVertexAttribArray(2);
		glBindVertexArray(0);

		glDeleteBuffers(1, &vboId);
		nPos = b;
	  }
	  if (vPos.size() < 0 || tPos.size() < 0 || nPos.size() < 0)
	  {
	  
	  }
	  else
	  {
		  std::vector<float> tangent;
		  std::vector<float> bitangent;
		  CalculateTangentArray<int>(*vertexCount, vPos, tPos, nPos, tangent, bitangent);

		  glGenBuffers(1, &vboId);

		  if (!vboId)
		  {
			  throw std::exception();
		  }

		  glBindBuffer(GL_ARRAY_BUFFER, vboId);

		  glBufferData(GL_ARRAY_BUFFER, sizeof(tangent.at(0)) * tangent.size(), &tangent.at(0),
			  GL_STATIC_DRAW);

		  glBindVertexArray(vaoId);
		  glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		  glEnableVertexAttribArray(4);
		  glBindVertexArray(0);

		  glDeleteBuffers(1, &vboId);

		  glGenBuffers(1, &vboId);

		  if (!vboId)
		  {
			  throw std::exception();
		  }

		  glBindBuffer(GL_ARRAY_BUFFER, vboId);

		  glBufferData(GL_ARRAY_BUFFER, sizeof(bitangent.at(0)) * bitangent.size(), &bitangent.at(0),
			  GL_STATIC_DRAW);

		  glBindVertexArray(vaoId);
		  glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		  glEnableVertexAttribArray(5);
		  glBindVertexArray(0);

		  glDeleteBuffers(1, &vboId);
	  }

	  if(lmcs.size() > 0)
	  {
		  std::vector<float> b;

		  for (std::vector<Face>::iterator fit = faces.begin();
			  fit != faces.end(); fit++)
		  {
			  b.push_back(fit->lmca.x); b.push_back(fit->lmca.y); 
			  b.push_back(fit->lmcb.x); b.push_back(fit->lmcb.y); 
			  b.push_back(fit->lmcc.x); b.push_back(fit->lmcc.y);
		  }

		  glGenBuffers(1, &vboId);

		  if (!vboId)
		  {
			  throw std::exception();
		  }

		  glBindBuffer(GL_ARRAY_BUFFER, vboId);

		  glBufferData(GL_ARRAY_BUFFER, sizeof(b.at(0)) * b.size(), &b.at(0),
			  GL_STATIC_DRAW);

		  glBindVertexArray(vaoId);
		  glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		  glEnableVertexAttribArray(3);
		  glBindVertexArray(0);

		  glDeleteBuffers(1, &vboId);
	  }

	  return vaoId;
	}
	template <typename T>
	void CalculateTangentArray(size_t vertexCount, std::vector<float> vertex, std::vector<float> texcoord,
		std::vector<float> normal, std::vector<float> &ftangent, std::vector<float>& fbitangent)
	{
		std::vector<float> tan1;
		std::vector<float> tan2;


		for (size_t a = 0; a < vertexCount; a+=3)
		{
			size_t i1 = a * 3;
			size_t i2 = a * 3+ 3;
			size_t i3 = a * 3 + 6;
			size_t ti1 = a * 2;
			size_t ti2 = a * 2 + 2;
			size_t ti3 = a * 2 + 4;

			glm::vec3 v1 = glm::vec3(vertex.at(i1), vertex.at(i1 + 1), vertex.at(i1 + 2));
			glm::vec3 v2 = glm::vec3(vertex.at(i2), vertex.at(i2 + 1), vertex.at(i2 + 2));
			glm::vec3 v3 = glm::vec3(vertex.at(i3), vertex.at(i3 + 1), vertex.at(i3 + 2));

			glm::vec2 w1 = glm::vec2(texcoord.at(ti1), texcoord.at(ti1 + 1));
			glm::vec2 w2 = glm::vec2(texcoord.at(ti2), texcoord.at(ti2 + 1));
			glm::vec2 w3 = glm::vec2(texcoord.at(ti3), texcoord.at(ti3 + 1));

			float x1 = v2.x - v1.x; //deltaPos1
			float y1 = v2.y - v1.y;
			float z1 = v2.z - v1.z;
			glm::vec3 edge1 = v2 - v1;
			glm::vec3 edge2 = v3 - v1;
			float x2 = v3.x - v1.x; //deltaPos2
			float y2 = v3.y - v1.y;
			float z2 = v3.z - v1.z;

			glm::vec2 deltaUV1 = w2 - w1;
			glm::vec2 deltaUV2 = w3 - w1;

			float s1 = w2.x - w1.x; //deltaU1
			float s2 = w3.x - w1.x; //deltaU2
			float t1 = w2.y - w1.y; //deltaV1
			float t2 = w3.y - w1.y; //deltaV2

			float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

			glm::vec3 tangent1;
			glm::vec3 bitangent1;
			tangent1.x = r * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
			tangent1.y = r * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
			tangent1.z = r * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

			bitangent1.x = r * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
			bitangent1.y = r * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
			bitangent1.z = r * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

			
				tan1.push_back(tangent1.x);
				tan1.push_back(tangent1.y);
				tan1.push_back(tangent1.z);

				tan1.push_back(tangent1.x);
				tan1.push_back(tangent1.y);
				tan1.push_back(tangent1.z);

				tan1.push_back(tangent1.x);
				tan1.push_back(tangent1.y);
				tan1.push_back(tangent1.z);

				tan2.push_back(bitangent1.x);
				tan2.push_back(bitangent1.y);
				tan2.push_back(bitangent1.z);

				tan2.push_back(bitangent1.x);
				tan2.push_back(bitangent1.y);
				tan2.push_back(bitangent1.z);

				tan2.push_back(bitangent1.x);
				tan2.push_back(bitangent1.y);
				tan2.push_back(bitangent1.z);
		
 
		}

		for (size_t a = 0; a < vertexCount; a++)
		{
			glm::vec3 n = glm::vec3(normal.at(a * 3), normal.at(a * 3 + 1), normal.at(a *3 + 2));
			glm::vec3 t = glm::vec3(tan1.at(a * 3), tan1.at(a * 3 + 1), tan1.at(a * 3 + 2));
			

			// Gram-Schmidt orthogonalize
			t = glm::normalize(t - glm::dot(n, t) * n);

			glm::vec3 b = glm::cross(n, t);

			 //Calculate handedness
			if (glm::dot(glm::cross(n, t), b) < 0.0F)
			{
				t *= -1.0f;
			}

			ftangent.push_back(t.x);
			ftangent.push_back(t.y);
			ftangent.push_back(t.z);

			fbitangent.push_back(b.x);
			fbitangent.push_back(b.y);
			fbitangent.push_back(b.z);

		}
	}

	template <typename T>
	GLuint loadModel(const std::string& path, size_t *vertexCount)
	{
	  std::string currentLine = path;

	  try
	  {
		return loadModel<int>(path, vertexCount, currentLine);
	  }
	  catch(std::exception& e)
	  {
		std::cout << "Failed to parse model data [" + currentLine + "]"
		  << std::endl;

		throw std::exception();
		//throw Exception("Failed to parse model data [" + currentLine + "]");
	  }
	}

}

#define buLoadModel bu::loadModel<int>
