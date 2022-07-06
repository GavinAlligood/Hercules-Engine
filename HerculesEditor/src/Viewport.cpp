#include "imgwh.h"
#include "Viewport.h"

namespace Hercules {
	
	void Viewport::ConditionalRender()
	{
		UIData& r_EditorUIData = UIRenderer::GetEditorUIData();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		//Check, ImGUiWIndowFlags_unsaveddocument
		ImGui::Begin("Scene");

		ImVec2 viewSize = ImGui::GetContentRegionAvail();
		r_EditorUIData.m_ViewportSize.x = viewSize.x;
		r_EditorUIData.m_ViewportSize.y = viewSize.y;
		Camera::SetAspectRatio(viewSize.x, viewSize.y);
		Camera::UpdateAspectRatio();

		//HC_CORE_TRACE(framebuffer.GetIntBuffer());
		//UIRenderer::GetFramebuffer
		//m_Framebuffer
		ImGui::Image((void*)m_Framebuffer.GetColorBuffer(), viewSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		auto viewportOffset = ImGui::GetCursorPos();
		auto windowSize = ImGui::GetWindowSize();
		ImVec2 minBound = ImGui::GetWindowPos();
		minBound.x += viewportOffset.x;
		viewportOffset.y -= minBound.y;

		ImVec2 maxBound = { minBound.x + windowSize.x, minBound.y + windowSize.y };
		//m_ViewportBounds[0] = { minBound.x, minBound.y };
		//m_ViewportBounds[1] = { maxBound.x, maxBound.y };

		ImGui::End();
		ImGui::PopStyleVar();
	}
}