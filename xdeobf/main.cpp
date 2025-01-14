#include "stdafx.h"

InsnOptimizer optInsn;
Unflattener optBlock;

#if IDA_SDK_VERSION < 760
hexdsp_t *hexdsp = nullptr;
#endif

plugmod_t *(idaapi onInitialize)() {
	if (!init_hexrays_plugin()) {
		msg("[E] Decompiler plugin not found!");
		return PLUGIN_SKIP;
	}

	install_optinsn_handler(&optInsn);
	install_optblock_handler(&optBlock);

	msg("[I] Hex-rays version %s has been detected, xdeobf is ready to use\n", get_hexrays_version());
	return PLUGIN_KEEP;
}

void idaapi onTerminate()
{
#if IDA_SDK_VERSION < 760
	if (hexdsp == nullptr) {
		return;
	}
#endif

	remove_optinsn_handler(&optInsn);
	remove_optblock_handler(&optBlock);
	term_hexrays_plugin();
}

bool idaapi onInvoke(size_t arg) {
	if (arg == 0xBEEF) {
		PLUGIN.flags |= PLUGIN_UNL; // Unload plugin
	}
	return true;
}

plugin_t PLUGIN = {
	IDP_INTERFACE_VERSION,
	0,                     // Plugin flags
	&onInitialize,         // Initialize
	&onTerminate,          // Terminate
	&onInvoke,             // Invoke plugin
	"Deobfuscator plugin", // Long comment about the plugin
	"",                    // Multiline help about the plugin
	"xdeobf",              // The preferred short name of the plugin
	""                     // The preferred hotkey to run the plugin
};
