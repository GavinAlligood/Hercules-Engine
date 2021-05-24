#pragma once

namespace Hercules {
	class Texture {
	public:
		Texture(int sWrap, int tWrap, int minFilter, int magFilter,
			const char* filename, int format, int srcFormat, int dataFormat, int id);
		~Texture();

		void Bind() const;
	private:
		unsigned int m_ID;
	};
}