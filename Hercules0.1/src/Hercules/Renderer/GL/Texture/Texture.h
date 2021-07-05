#pragma once

namespace Hercules {
	class Texture {
	public:
		Texture(const char* filename, int id, bool type);
		~Texture();

		void Bind() const;

		const inline unsigned int GetID() const { return m_ID; }
	private:
		unsigned int m_ID;
	};
}

#define HC_IMG_PNG 1
#define HC_IMG_JPG 0