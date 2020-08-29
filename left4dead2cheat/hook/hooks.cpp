#include "hooks.h"

std::unique_ptr<vmthook> clientmodehook;
std::unique_ptr<vmthook> chlclienthook;
std::unique_ptr<vmthook> enginevguihook;
std::unique_ptr<vmthook> renderviewhook;
std::unique_ptr<vmthook> modelrenderhook;
std::unique_ptr<vmthook> surfacehook;

void hook::setup_hook()
{

	clientmodehook = std::make_unique<vmthook>(g_clientmode);
	if (clientmodehook->hook(hook::overrideview, index::overrideview))
		tools::log("[Hook] hooked clientmode::overrideview.\n");

	chlclienthook = std::make_unique<vmthook>(g_baseclientdll);
	if (chlclienthook->hook(hook::createmove, index::createmove))
		tools::log("[Hook] hooked chlclient::createmove.\n");
	if (chlclienthook->hook(hook::frame_stage_notify, index::frame_stage_noify))
		tools::log("[Hook] hooked chlclient::frame_stage_notify.\n");
	
	modelrenderhook = std::make_unique<vmthook>(g_modelrender);
	if (modelrenderhook->hook(hook::draw_model_execute, index::draw_model_execute))
		tools::log("[Hook] hooked modelrender::draw_model_execute.\n");

	surfacehook = std::make_unique<vmthook>(g_surfaces);
	if (surfacehook->hook(hook::on_screen_size_changed, index::on_screen_size_changed))
		tools::log("[Hook] hooked surfaces::on_screen_size_changed.\n");

	enginevguihook = std::make_unique<vmthook>(g_enginevgui);
	if (enginevguihook->hook(hook::enginepaint, index::paint))
		tools::log("[Hook] hooked enginevgui::paint.\n");

}
