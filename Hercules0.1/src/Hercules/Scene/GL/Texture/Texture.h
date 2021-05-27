#pragma once

namespace Hercules {
	class Texture {
	public:
		Texture(const char* filename, int id);
		~Texture();

		void Bind() const;
	private:
		unsigned int m_ID;
	};
}

#define HC_IMG_PNG 1
#define HC_IMG_JPG 0