#pragma once

///// Only intended to be included by client applications

#include <stdio.h>
#include <functional>

//Application/Core
#include "Hercules/Application/Application.h"
#include "Hercules/Core/Log/Log.h"

//Rendering
#include "Hercules/Renderer/3D/3DRenderer.h"
#include "Hercules/Renderer/2D/2DRenderer.h"
#include "Hercules/Scene/Camera/Camera.h"
#include "Hercules/Scene/SceneManager.h"

//Input
#include "Hercules/Core/Input/Input.h"

// -----------------Entry point---------------------
#include "Hercules/Application/main.h"