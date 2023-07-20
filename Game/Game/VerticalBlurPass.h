#pragma once
#include "FullscreenPass.h"
#include "ConstantBuffersExtension.h"

class Graphics;
namespace Bind
{
	class PixelShader;
	class RenderTarget;
}

namespace Rgph
{
	class VerticalBlurPass : public FullscreenPass
	{
	public:
		VerticalBlurPass(std::string name, Graphics& gfx);
		void Execute(Graphics& gfx) const noxnd override;
	private:
		std::shared_ptr<Bind::CachingPixelConstantBufferEx> direction;
	};
}