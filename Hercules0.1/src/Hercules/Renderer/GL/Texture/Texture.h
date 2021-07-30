#pragma once

namespace Hercules {
	class Texture {
	public:
		Texture(const char* filename, int id, bool type);
		~Texture() {};

		void Bind() const;

		const inline unsigned int GetID() const { return m_ID; }
		const inline void SetID(unsigned int id) { m_ID = id; }
	private:
		unsigned int m_ID;
	};
}