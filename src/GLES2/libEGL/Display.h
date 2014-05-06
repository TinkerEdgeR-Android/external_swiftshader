// SwiftShader Software Renderer
//
// Copyright(c) 2005-2012 TransGaming Inc.
//
// All rights reserved. No part of this software may be copied, distributed, transmitted,
// transcribed, stored in a retrieval system, translated into any human or computer
// language by any means, or disclosed to third parties without the explicit written
// agreement of TransGaming Inc. Without such an agreement, no rights or licenses, express
// or implied, including but not limited to any patent rights, are granted to you.
//

// Display.h: Defines the egl::Display class, representing the abstract
// display on which graphics are drawn. Implements EGLDisplay.
// [EGL 1.4] section 2.1.2 page 3.

#ifndef INCLUDE_DISPLAY_H_
#define INCLUDE_DISPLAY_H_

#include "Config.h"
#include "Surface.h"
#include "libGLESv2/Context.h"
#include "libGLESv2/Device.hpp"

#include <set>

namespace egl
{
	class Display
	{
	public:
		~Display();

		static egl::Display *getDisplay(EGLNativeDisplayType displayId);

		bool initialize();
		void terminate();

		bool getConfigs(EGLConfig *configs, const EGLint *attribList, EGLint configSize, EGLint *numConfig);
		bool getConfigAttrib(EGLConfig config, EGLint attribute, EGLint *value);

		EGLSurface createWindowSurface(EGLNativeWindowType window, EGLConfig config, const EGLint *attribList);
		EGLSurface createOffscreenSurface(EGLConfig config, const EGLint *attribList);
		EGLContext createContext(EGLConfig configHandle, const gl::Context *shareContext);

		void destroySurface(egl::Surface *surface);
		void destroyContext(gl::Context *context);

		bool isInitialized() const;
		bool isValidConfig(EGLConfig config);
		bool isValidContext(gl::Context *context);
		bool isValidSurface(egl::Surface *surface);
		bool isValidWindow(EGLNativeWindowType window);
		bool hasExistingWindowSurface(EGLNativeWindowType window);

		EGLint getMinSwapInterval();
		EGLint getMaxSwapInterval();

		virtual gl::Device *getDevice();

		EGLNativeDisplayType getNativeDisplay() const;
		const char *getExtensionString() const;

	private:
		Display(EGLNativeDisplayType displayId);

		DisplayMode getDisplayMode() const;

		const EGLNativeDisplayType displayId;
		gl::Device *mDevice;

		EGLint mMaxSwapInterval;
		EGLint mMinSwapInterval;
    
		typedef std::set<Surface*> SurfaceSet;
		SurfaceSet mSurfaceSet;

		ConfigSet mConfigSet;

		typedef std::set<gl::Context*> ContextSet;
		ContextSet mContextSet;

		bool createDevice();

		void initExtensionString();
		std::string mExtensionString;
	};
}

#endif   // INCLUDE_DISPLAY_H_