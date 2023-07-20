#pragma once
#include "RenderQueuePass.h"
#include "Job.h"
#include <vector>
#include "Sink.h"
#include "Source.h"
#include "Stencil.h"
#include "Camera.h"
#include "DepthStencil.h"
#include "ShadowCameraCbuf.h"
#include "ShadowSampler.h"
#include "Sampler.h"

class Graphics;

namespace Rgph
{
	class LambertianPass : public RenderQueuePass
	{
	public:
		LambertianPass(Graphics& gfx, std::string name)
			:
			RenderQueuePass(std::move(name)),
			pShadowCbuf{ std::make_shared<Bind::ShadowCameraCbuf>(gfx) }
		{
			using namespace Bind;
			AddBind(pShadowCbuf);
			RegisterSink(DirectBufferSink<RenderTarget>::Make("renderTarget", renderTarget));
			RegisterSink(DirectBufferSink<DepthStencil>::Make("depthStencil", depthStencil));
			AddBindSink<Bind::Bindable>("shadowMap");
			AddBind(std::make_shared<Bind::ShadowSampler>(gfx));
			AddBind(std::make_shared<Bind::Sampler>(gfx, Bind::Sampler::Type::Anisotropic, false, 2));
			RegisterSource(DirectBufferSource<RenderTarget>::Make("renderTarget", renderTarget));
			RegisterSource(DirectBufferSource<DepthStencil>::Make("depthStencil", depthStencil));
			AddBind(Stencil::Resolve(gfx, Stencil::Mode::Off));
		}
		void BindMainCamera(const Camera& cam) noexcept
		{
			pMainCamera = &cam;
		}
		void BindShadowCamera(const Camera& cam) noexcept
		{
			pShadowCbuf->SetCamera(&cam);
		}
		void Execute(Graphics& gfx) const noxnd override
		{
			assert(pMainCamera);
			pShadowCbuf->Update(gfx);
			pMainCamera->BindToGraphics(gfx);
			RenderQueuePass::Execute(gfx);
		}
	private:
		std::shared_ptr<Bind::ShadowCameraCbuf> pShadowCbuf;
		const Camera* pMainCamera = nullptr;
	};
}