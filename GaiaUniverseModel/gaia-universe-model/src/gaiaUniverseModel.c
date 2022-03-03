#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#ifdef _MSC_VER
#pragma warning (disable: 4005 4996 6011)
#endif//_MSC_VER

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <engine/shEngine.h>

#include <shvulkan/shVkCore.h>
#include <shvulkan/shVkMemoryInfo.h>
#include <shvulkan/shVkPipelineData.h>
#include <shvulkan/shVkDrawloop.h>

#include <ecs/shEcsImplementation.h>
#include <ecs/shCamera.h>
#include <ecs/shTransform.h>

#include <gaia-archive-tools/gaiaArchiveTools.h>

#include "gaia-universe-model/gaiaUniverseModel.h"

void gaiaEngineSetup(ShEngine* p_engine) {
	assert(p_engine != NULL);
	shWindowSetup("Gaia EDR3 Universe Model", 1900, 1000, &p_engine->window);
	shCreateInstance(&p_engine->core, "Gaia EDR3 Universe Model", "SH-Engine", 1, p_engine->window.instance_extension_count, p_engine->window.pp_instance_extensions);
	shCreateWindowSurface(p_engine);
	shSelectPhysicalDevice(&p_engine->core, VK_QUEUE_GRAPHICS_BIT);
	shSetLogicalDevice(&p_engine->core);
	shGetGraphicsQueue(&p_engine->core);
	shGetComputeQueue(&p_engine->core);
	shInitSwapchainData(&p_engine->core);
	shInitDepthData(&p_engine->core);
	shCreateRenderPass(&p_engine->core);
	shSetFramebuffers(&p_engine->core);
	shSetSyncObjects(&p_engine->core);
	shCreateGraphicsCommandBuffer(&p_engine->core);
}

const char* gaiaReadBinaryGeneric(const char* path, uint32_t* p_size) {
	FILE* stream = fopen(path, "rb");
	if (stream == NULL) {
		return NULL;
	}
	fseek(stream, 0, SEEK_END);
	uint32_t code_size = ftell(stream);
	fseek(stream, 0, SEEK_SET);
	char* code = (char*)calloc(1, code_size);
	if (code == NULL) {
		return NULL;
	}
	fread(code, code_size, 1, stream);
	*p_size = code_size;
	fclose(stream);
	return code;
}

void gaiaSetupMaterial(ShEngine* p_engine, const char* vertex_shader_path, const char* fragment_shader_path, GaiaUniverseModelMemory* p_universe_model) {
	p_engine->p_materials = p_universe_model->materials;
	float one = 1.0f;
	memcpy(&((char*)p_universe_model->uniform_buffer)[12], &one, 4);
	p_engine->material_count = 1;
	p_engine->p_materials->pipeline.shader_module_count = 0;

	uint32_t vertex_shader_size = 0;
	uint32_t fragment_shader_size = 0;
	char* vertex_code = (char*)gaiaReadBinaryGeneric(vertex_shader_path, &vertex_shader_size);
	char* fragment_code = (char*)gaiaReadBinaryGeneric(fragment_shader_path, &fragment_shader_size);
	shCreateShaderModule(p_engine->core.device, vertex_shader_size, vertex_code, &p_engine->p_materials[0].pipeline);
	shCreateShaderModule(p_engine->core.device, fragment_shader_size, fragment_code, &p_engine->p_materials[0].pipeline);
	free(vertex_code);
	free(fragment_code);
	shCreateShaderStage(p_engine->core.device, p_engine->p_materials[0].pipeline.shader_modules[0], VK_SHADER_STAGE_VERTEX_BIT, &p_engine->p_materials[0].pipeline);
	shCreateShaderStage(p_engine->core.device, p_engine->p_materials[0].pipeline.shader_modules[1], VK_SHADER_STAGE_FRAGMENT_BIT, &p_engine->p_materials[0].pipeline);

	shSetPushConstants(VK_SHADER_STAGE_VERTEX_BIT, 0, 128, &p_engine->p_materials[0].pipeline);

	shCreateUniformBuffer(&p_engine->core, 0, 16, &p_engine->p_materials[0].pipeline);
	shAllocateUniformBuffers(&p_engine->core, &p_engine->p_materials[0].pipeline);
	shDescriptorSetLayout(&p_engine->core, 0, VK_SHADER_STAGE_FRAGMENT_BIT, &p_engine->p_materials[0].pipeline);
	shCreateDescriptorPools(&p_engine->core, &p_engine->p_materials[0].pipeline);
	shAllocateDescriptorSets(&p_engine->core, &p_engine->p_materials[0].pipeline);

	shSetVertexInputAttribute(0, SH_VEC1_SIGNED_FLOAT, 0, 4, &p_engine->p_materials[0].fixed_states);	//asc
	shSetVertexInputAttribute(1, SH_VEC1_SIGNED_FLOAT, 4, 4, &p_engine->p_materials[0].fixed_states);	//dec
	shSetVertexInputAttribute(2, SH_VEC1_SIGNED_FLOAT, 8, 4, &p_engine->p_materials[0].fixed_states);	//baricentric_distance
	shSetVertexInputAttribute(3, SH_VEC1_SIGNED_FLOAT, 12, 4, &p_engine->p_materials[0].fixed_states);	//teff

	shSetFixedStates(&p_engine->core, SH_FIXED_STATES_POLYGON_MODE_FACE | SH_FIXED_STATES_PRIMITIVE_TOPOLOGY_POINT_LIST, &p_engine->p_materials[0].fixed_states);
	shSetupGraphicsPipeline(&p_engine->core, p_engine->p_materials[0].fixed_states, &p_engine->p_materials[0].pipeline);
}

void gaiaReadSources(ShEngine* p_engine, const GaiaCelestialBodyFlags celestial_body_flags, GaiaUniverseModelMemory* p_universe_model) {
	assert(p_universe_model != NULL);

	uint32_t available_video_memory = 0;
	shGetMemoryBudgetProperties(p_engine->core.physical_device, &available_video_memory, NULL, NULL);
	available_video_memory /= 20;
	p_universe_model->p_celestial_bodies = calloc(1, available_video_memory);
	assert(p_universe_model->p_celestial_bodies != NULL);
	void* src;
	for (uint32_t i = 0; i < 2; i++) {
		uint32_t bytes_read = 0;
		gaiaReadBinaryFileFromID("../gaia_resources/", i, celestial_body_flags, 0, 0, &bytes_read, &src);
		if (p_universe_model->used_vram + bytes_read >= available_video_memory) {
			break;
		}
		memcpy(&((char*)p_universe_model->p_celestial_bodies)[p_universe_model->used_vram], src, bytes_read);
		p_universe_model->used_vram += bytes_read;
	}
	gaiaFree(src);
}

void gaiaWriteVertexBuffers(ShEngine* p_engine, GaiaUniverseModelMemory* p_universe_model) {
	const uint32_t MAX_GPU_HEAP_SIZE = 67108864;
	uint32_t written_memory = 0;
	
	p_universe_model->vertex_buffer_count = (p_universe_model->used_vram > MAX_GPU_HEAP_SIZE) ? (p_universe_model->used_vram / MAX_GPU_HEAP_SIZE) : 1;
	for (uint32_t i = 0; i < p_universe_model->vertex_buffer_count; i++) {
		uint32_t buffer_size = p_universe_model->used_vram > MAX_GPU_HEAP_SIZE ? MAX_GPU_HEAP_SIZE : p_universe_model->used_vram;
		shCreateVertexBuffer(&p_engine->core, buffer_size, &p_universe_model->vertex_buffers[i]);

		shAllocateVertexBuffer(&p_engine->core, p_universe_model->vertex_buffers[i], &p_universe_model->vertex_buffers_memory[i]);

		shWriteVertexBufferMemory(&p_engine->core, p_universe_model->vertex_buffers_memory[i], buffer_size, &((char*)p_universe_model->p_celestial_bodies)[written_memory]);
		written_memory += buffer_size;
		if (written_memory >= p_universe_model->used_vram) { break; }
	}
}

void gaiaSceneSetup(ShEngine* p_engine) {
	shCreateScene(&p_engine->scenes[0]);
	const uint32_t camera_entity = shCreateEntity(&p_engine->scenes[0]);
	ShCamera* p_camera = shAddShCamera(&p_engine->scenes[0], camera_entity);
	p_camera->fov = 1.0f;
	p_camera->nc = 1.0E-3f;
	p_camera->fc = 1.0E3f;
	p_camera->speed = 0.5f;
	p_camera->flags = SH_CAMERA_SETUP_FREE_FLIGHT;
	ShTransform* p_camera_transform = shAddShTransform(&p_engine->scenes[0], camera_entity);
	shSceneInit(p_engine, 0);
}

void gaiaSceneUpdate(ShEngine* p_engine, GaiaUniverseModelMemory* p_universe_model) {
	ShCamera* p_camera = shGetShCamera(&p_engine->scenes[0], 0);
	if (shIsKeyPressed(p_engine->window, SH_KEY_LEFT_SHIFT)) {
		p_camera->speed = 5.0f;
	}
	if (shIsKeyReleased(p_engine->window, GLFW_KEY_LEFT_SHIFT)) {
		p_camera->speed = 0.1f;
	}
	shSceneUpdate(p_engine, 0);
	shBindPipeline(&p_engine->core, &p_engine->p_materials[0].pipeline);

	shUpdateUniformBuffers(&p_engine->core, &p_engine->p_materials[0].pipeline);

	memcpy(p_universe_model->uniform_buffer, shGetShTransform(&p_engine->scenes[0], 0)->position, 12);
	shWriteUniformBufferMemory(&p_engine->core, 0, p_universe_model->uniform_buffer, &p_engine->p_materials[0].pipeline);
	shBindUniformBuffer(&p_engine->core, 0, &p_engine->p_materials[0].pipeline);

	memcpy(p_universe_model->push_constant, p_camera->projection, 64);
	memcpy(&p_universe_model->push_constant[64 / sizeof(void*)], p_camera->view, 64);
	shPushConstants(&p_engine->core, p_universe_model->push_constant, &p_engine->p_materials[0].pipeline);

	for (uint32_t i = 0; i < p_universe_model->vertex_buffer_count; i++) {
		shBindVertexBuffer(&p_engine->core, &p_universe_model->vertex_buffers[i]);
	}
}

void gaiaMemoryRelease(ShEngine* p_engine, GaiaUniverseModelMemory* p_universe_model) {
	free(p_universe_model->p_celestial_bodies);
	for (uint32_t i = 0; i < p_universe_model->vertex_buffer_count; i++) {
		shClearBufferMemory(p_engine->core.device, p_universe_model->vertex_buffers[i], p_universe_model->vertex_buffers_memory[i]);
	}
}

void gaiaEngineShutdown(ShEngine* p_engine) {
	shClearUniformBufferMemory(&p_engine->core, 0, &p_engine->p_materials[0].pipeline);
	shDestroyPipeline(&p_engine->core, &p_engine->p_materials[0].pipeline);
	shSceneRelease(p_engine, 0);
	shVulkanRelease(&p_engine->core);
}

#ifdef __cplusplus
}
#endif//__cplusplus